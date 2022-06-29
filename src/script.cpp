#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>
#include <functional>

double f(int n, int m) {
    double y = 0.0;
    for (int i = 0; i < m; i++) {
        std::vector<double> x(n);
        std::generate(x.begin(), x.end(), std::bind(std::uniform_real_distribution<double>(0.0, 1.0), std::default_random_engine()));
        std::sort(x.begin(), x.end());
        for (int j = 0; j < n; j++) {
            y += x[j] * j;
        }
    }
    return y / m / n / n;
}

double g(int n, int m) {
    double y = 0.0;
    for (int i = 0; i < m; i++) {
        std::vector<double> x(n);
        std::generate(x.begin(), x.end(), std::bind(std::uniform_real_distribution<double>(0.0, 1.0), std::default_random_engine()));

        for (int j = 0; j < n; j++) {
            y += x[j] * j;
        }
    }
    return y / m / n / n;
}

int main() {
    std::cout << "C++ " << __cplusplus << " " << __VERSION__ << std::endl;
    int N = 14;
    for (int i = 1; i <= N; i++) {
        std::chrono::time_point<std::chrono::high_resolution_clock> t0 = std::chrono::high_resolution_clock::now();
        double vf = f(pow(3, i), pow(3, N - i));
        std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> tf = t1 - t0;
        std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
        double vg = g(pow(3, i), pow(3, N - i));
        std::chrono::time_point<std::chrono::high_resolution_clock> t3 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> tg = t3 - t2;
        double Δ = tf.count() - tg.count();
        // Using the same approach as for other languages sometimes results in a negative
        // runtime difference. Saying that sorting occasionally takes negative time in c++ is
        // quite wrong, so instead of subtracting the runtime of the control from the runtime
        // of the experiment, we simply multiply by a constant factor. Julia's constant
        // factor ranges from .7 to .94 and C's ranges from .82 to .96. We use .8 here.
        std::printf("%d %5.1f (80%%*) %g\n", i, tf.count() * .85 * pow(10, 9) / pow(3, N), vf - vg);
    }
}