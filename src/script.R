f <- function(n, m) {
    y <- 0
    for (i in 1:m) {
        x <- runif(n, 0.0, 1.0)
        x <- sort(x)
        for (j in 1:n) {
            y <- y + x[j] * j
        }
    }
    return(y / m / n^2)
}

g <- function(n, m) {
    y <- 0
    for (i in 1:m) {
        x <- runif(n, 0.0, 1.0)

        for (j in 1:n) {
            y <- y + x[j] * j
        }
    }
    return(y / m / n^2)
}

cat(R.version.string, "\n")
N <- 14
for (i in 4:N) {
    tf0 <- Sys.time()
    vf <- f(3^i, 3^(N-i))
    tf1 <- Sys.time()
    tg0 <- Sys.time()
    vg <- g(3^i, 3^(N-i))
    tg1 <- Sys.time()
    tf <- tf1 - tf0
    tg <- tg1 - tg0
    Δ <- tf - tg
    cat(sprintf("%d %5.1f (%d%%) %g\n", i, round(Δ*10^9/3^N, 1), round(100*(as.numeric(Δ)/as.numeric(tf))), vf-vg))
}
