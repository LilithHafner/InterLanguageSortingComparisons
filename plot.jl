using GLMakie
using CSV: File

function data(commands = [
        `julia +alpha script.jl`,
        `julia +1.8 script.jl`,
        `python3 script.py`,
        `python3 num.py`,
        `bash -c 'gcc script.c && ./a.out'`,
        `bash -c 'g++ -std=c++11 script.cpp && ./a.out'`,
        `go run script.go`,
        `RScript script.R`,
        `java Script.java`,
        `bash -c 'cd script_rs; rustc --version; cargo run -q --release; cd ..'`,
        `bash -c 'cd glide_rs; echo -n glidesort/; rustc --version; cargo run -q --release; cd ..'`])

    cd(joinpath(@__DIR__, "src")) do
        map(commands) do c
            print(c)
            @time s = String(read(c))
            println(s)
            i = findfirst('\n', s)
            head = replace(s[begin:i-1], r"\([^()]*\)"=>"")
            tail = s[i+1:end]
            head, File(IOBuffer(tail), header=["n", "x", "p", "c"], ignorerepeated=true, delim=' ')
        end
    end
end

function plot(results = data())
    f = Figure(size=10 .*(640,480))
    ax = Axis(f[1, 1], xscale=log10, limits=(3, 3^15, 0,300),
        xlabel="Number of elements", ylabel="Runtime in ns per element",
        title="Sorting speed as a function of language and collection size")
    colors = [:black, :black, "#00B25D", "#00B25D", "#4053D3", "#00BEFF", "#DDB310", "#FB49B0", "#B51D14", "#DEA584", "#DEA584"]
    linestyles = [:solid, :dash, :solid, :dash, :solid, :solid, :solid, :solid, :solid, :solid, :dash]
    lins = map(last.(results), colors, linestyles) do f, color, linestyle
        lines!(ax, 3 .^ f.n, f.x; color, linestyle)
    end
    f[2, 1] = Legend(f, lins, first.(results), tellwidth=false, tellheight=true, nbanks=3, framevisible=false)
    f
end
