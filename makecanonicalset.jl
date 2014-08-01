#!/usr/bin/julia

fns = []

count = 7

for i = 1:count
	val = int((i - 1) * 5399 / (count - 1)) + 1
	fns = vcat(fns,@sprintf("res/image-%05d.jpeg", val))
end

function pairup(a::Array{Float64,1})
	l = int(length(a) / 2)
	reshape(a, 2, l)
end

function parsethread(c, indices; reverse = false)
	#uses a bernstein-schroeder technique to make unique optimal threads through images.

	#start with the first array of coordinates.
	for (ldx = 2:length(c))
		layer = reverse ? c[length(c) - ldx + 2] : c[ldx - 1]
		nextlayer = reverse? c[length(c) - ldx + 1] : c[ldx]

		for idx = 1:length(indices)
			if (indices[idx] != 0)
				#a vector of the distances squared.
				(d, indices[idx]) = findmin(sum((nextlayer - layer[:,indices[idx]] * ones(1,size(nextlayer,2))) .^ 2, 1))
				if (d >= 225.0)
					indices[idx] = 0
				end
			end
		end
	end

	sort!(indices)
	a = [indices[1]]
	for (idx = 2:length(indices))
		if (indices[idx] != indices[idx - 1])
			a = vcat(a, indices[idx])
		end
	end

	if a[1] == 0
		return a[2:end]
	else
		return a
	end
end

coords = cell(length(fns))

for (i=1:length(fns))
	coords[i] = pairup(map(parsefloat, split(chomp(readall(`./extractfeatures $(fns[i])`)),r"\s")))
end

forwardindices = [1:length(coords[1][1,:])]
fwdres = parsethread(coords, forwardindices)
revres = parsethread(coords, fwdres, reverse = true)

println(coords[1][:,revres]')
