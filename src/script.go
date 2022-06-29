package main

import (
	"fmt"
	"math/rand"
	"math"
	"time"
	"sort"
	"runtime"
)

func f(n int, m int) float64 {
	x := make([]float64, n)
	y := float64(0)
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			x[j] = rand.Float64()
		}
		sort.Float64s(x)
		for j := 0; j < n; j++ {
			y += x[j] * float64(j)
		}
	}
	return y / float64(m) / float64(n*n)
}

func g(n int, m int) float64 {
	x := make([]float64, n)
	y := float64(0)
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			x[j] = rand.Float64()
		}

		for j := 0; j < n; j++ {
			y += x[j] * float64(j)
		}
	}
	return y / float64(m) / float64(n*n)
}

func main() {
	fmt.Println(runtime.Version())
	N := 14
	for i := 1; i <= N; i++ {
		n := int(math.Pow(float64(3), float64(i)));
        m := int(math.Pow(float64(3), float64(N-i)));
		tf0 := time.Now().UnixNano()
		vf := f(n, m)
		tf1 := time.Now().UnixNano()
		tg0 := time.Now().UnixNano()
		vg := g(n, m)
		tg1 := time.Now().UnixNano()
		tf := tf1 - tf0
		tg := tg1 - tg0
		Δ := tf - tg
		fmt.Printf("%d %5.1f (%2.0f%%) %g\n", i, float64(Δ) / math.Pow(float64(3), float64(N)), float64(Δ)/float64(tf)*100, vf-vg)
	}
}
