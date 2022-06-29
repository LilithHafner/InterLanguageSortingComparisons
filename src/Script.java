import java.util.Arrays;

public class Script {
    public static double f(int n, int m) {
        double[] x = new double[n];
        double y = 0.0;
        int i, j;
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                x[j] = Math.random();
            }
            Arrays.sort(x);
            for (j = 0; j < n; j++) {
                y += x[j] * j;
            }
        }
        return y / m / n / n;
    }

    public static double g(int n, int m) {
        double[] x = new double[n];
        double y = 0.0;
        int i, j;
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                x[j] = Math.random();
            }

            for (j = 0; j < n; j++) {
                y += x[j] * j;
            }
        }
        return y / m / n / n;
    }

    public static void main(String[] args) {
        System.out.println("Java " + Runtime.version());
        int N = 15;
        for (int i = 1; i <= N; i++) {
            int n = (int)Math.pow(3, i);
            int m = (int)Math.pow(3, N-i);
            long tf0 = System.nanoTime();
            double vf = f(n, m);
            long tf1 = System.nanoTime();
            long tg0 = System.nanoTime();
            double vg = g(n, m);
            long tg1 = System.nanoTime();
            long tf = tf1 - tf0;
            long tg = tg1 - tg0;
            long Δ = tf - tg;
            System.out.printf("%d %5.1f (%2.0f%%) %g\n", i, Δ/Math.pow(3,N), 100.0*Δ/tf, vf-vg);
        }
    }
}