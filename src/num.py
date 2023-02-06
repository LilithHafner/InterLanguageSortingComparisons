from time import perf_counter_ns
from sys import version
import numpy as np
from numpy import random

def f(n, m):
    y = 0.0
    for i in range(m):
        x = random.random(n)
        x.sort()
        y += sum(x * np.arange(n))
    return y / m / n**2

def g(n, m):
    y = 0.0
    for i in range(m):
        x = random.random(n)

        y += sum(x * np.arange(n))
    return y / m / n**2

print("numpy/python " + version.replace("\n", ""))
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
    # Using the same approach as for other languages sometimes results in a negative runtime
    # difference. Saying that sorting occasionally takes negative time with python/numpy is
    # quite wrong, so instead of subtracting the runtime of the control from the runtime
    # of the experiment, we simply multiply by a constant factor. Julia's constant
    # factor ranges from .7 to .94 and Python's ranges from .13 to .64. We use k here.
    k = .04 * i + .09
    print("{} {:5.1f} ({}/{}%) {}".format(i, round(tf * k / 3**N, 1), round(100*k), round(100*Δ/tf), vf-vg))
