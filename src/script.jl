using Random

"""
    f(n, m)

Estimate the expected the dot product of `1:n` and `sort(rand(n))` divided by `n^2`.
Return the average of `m` trials.
"""
function f(n, m)
    x = zeros(n)
    y = 0.0
    for _ in 1:m
        rand!(x)
        sort!(x)
        y += sum(x .* eachindex(x))
    end
    y / m / n^2
end

"""
    g(n, m)

Same as `f`, but without sorting.
"""
function g(n, m)
    x = zeros(n)
    y = 0.0
    for _ in 1:m
        rand!(x)

        y += sum(x .* eachindex(x))
    end
    y / m / n^2
end

println("julia $VERSION")
N = 15
for i in 1:N
    tf = @elapsed vf = f(3^i, 3^(N-i))
    tg = @elapsed vg = g(3^i, 3^(N-i))
    Δ = tf - tg
    println("$i $(lpad(round(Int, 10*1e9Δ/3^N)/10, 5)) ($(round(Int, (100Δ/tf)))%) $(vf-vg)")
end
