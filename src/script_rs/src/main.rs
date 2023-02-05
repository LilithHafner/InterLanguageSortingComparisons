use rand::{Rng, SeedableRng};
use rand_xoshiro::Xoshiro256PlusPlus;
use std::time::Instant;

fn dotindex(x: &[f64]) -> f64 {
    x.iter()
        .enumerate()
        .fold(0.0, |acc, (i, v)| v.mul_add(i as f64, acc))
}

fn f(n: i32, m: i32) -> f64 {
    let n = n as usize;
    let mut y: f64 = 0.0;
    let mut x: Vec<f64> = Vec::with_capacity(n);
    x.resize(n, 0.0);
    let mut rng = Xoshiro256PlusPlus::from_rng(rand::thread_rng()).unwrap();

    for _ in 0..m {
        rng.fill(&mut x[..]);
        x.sort_unstable_by(|a, b| if a < b {
            Ordering::Less
        } else {
            Ordering::Greater
        });
        y += dotindex(&x);
    }
    let n = n as f64;
    y / m as f64 / (n * n)
}

fn g(n: i32, m: i32) -> f64 {
    let n = n as usize;
    let mut y: f64 = 0.0;
    let mut x: Vec<f64> = Vec::with_capacity(n);
    x.resize(n, 0.0);
    let mut rng = Xoshiro256PlusPlus::from_rng(rand::thread_rng()).unwrap();

    for _ in 0..m {
        rng.fill(&mut x[..]);

        y += dotindex(&x);
    }
    let n = n as f64;
    y / m as f64 / (n * n)
}

fn time_since(t: Instant) -> f64 {
    t.elapsed().as_nanos() as f64 * 1e-9
}

fn main() {
    let n = 15;
    for i in 1..=n {
        let t1 = Instant::now();
        let vf = f(3_i32.pow(i), 3_i32.pow(n - i));
        let tf = time_since(t1);

        let t1 = Instant::now();
        let vg = g(3_i32.pow(i), 3_i32.pow(n - i));
        let tg = time_since(t1);

        let delta = tf - tg;

        println!(
            "{} {:5.1} ({:2.0}%) {}",
            i,
            1e9 * delta / 3_i32.pow(n) as f64,
            100.0 * delta / tf,
            vf - vg,
        );
    }
}
