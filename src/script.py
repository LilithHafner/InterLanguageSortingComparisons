from time import perf_counter_ns
from sys import version
import random

def f(n, m):
    x = [0.0] * n
    y = 0.0
    for i in range(m):
        for j in range(n):
            x[j] = random.random()
        x.sort()
        y += sum(x[i] * i for i in range(n))
    return y / m / n**2

def g(n, m):
    x = [0.0] * n
    y = 0.0
    for i in range(m):
        for j in range(n):
            x[j] = random.random()

        y += sum(x[i] * i for i in range(n))
    return y / m / n**2

print("python " + version.replace("\n", "").replace(r"\([^(]*\)", ""))
N = 13
for i in range(1,N+1):
    tf0 = perf_counter_ns()
    vf = f(3**i, 3**(N-i))
    tf1 = perf_counter_ns()
    tg0 = perf_counter_ns()
    vg = g(3**i, 3**(N-i))
    tg1 = perf_counter_ns()
    tf = tf1 - tf0
    tg = tg1 - tg0
    Δ = tf - tg
    print("{} {:5.1f} ({}%) {}".format(i, round(Δ/3**N, 1), round(100*Δ/tf), vf-vg))
