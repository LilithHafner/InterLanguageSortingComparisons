#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int compare(const void *a, const void *b) {
    double *x = (double *)a;
    double *y = (double *)b;
    if (*x < *y)
        return -1;
    else if (*x > *y)
        return 1;
    else
        return 0;
}
double f(int n, int m) {
    double *x = malloc(n * sizeof(double));
    double y = 0.0;
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            x[j] = rand() / (double)RAND_MAX;
        }
        qsort(x, n, sizeof(double), compare);
        for (j = 0; j < n; j++) {
            y += x[j] * j;
        }
    }
    return y / m / n / n;
}
double g(int n, int m) {
    double *x = malloc(n * sizeof(double));
    double y = 0.0;
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            x[j] = rand() / (double)RAND_MAX;
        }

        for (j = 0; j < n; j++) {
            y += x[j] * j;
        }
    }
    return y / m / n / n;
}

int main() {
    printf("C gcc %s\n", __VERSION__);
    int N = 15;
    for (int i = 1; i <= N; i++) {
        int n = pow(3, i);
        int m = pow(3, N-i);
        float tf0 = (float)clock()/CLOCKS_PER_SEC;
        double vf = f(n, m);
        float tf1 = (float)clock()/CLOCKS_PER_SEC;
        float tg0 = (float)clock()/CLOCKS_PER_SEC;
        double vg = g(n, m);
        float tg1 = (float)clock()/CLOCKS_PER_SEC;
        float tf = tf1 - tf0;
        float tg = tg1 - tg0;
        float Δ = tf - tg;
        printf("%d %5.1f (%2.0f%%) %g\n", i, Δ*pow(10,9)/pow(3,N), 100*Δ/tf, vf-vg);
    }
    return 0;
}