package main

func subqsort(i, j int) {
	if i < j {
		q := (i + j) / 2
		l := i
		r := j
		for l <= r {
			for less(l, q) {
				l++
			}
			for less(q, r) {
				r--
			}
			if l >= r {
				break
			}
			swap(l, r)
			l++
			r--
		}
		subqsort(i, r)
		subqsort(r + 1, j)
	}
}

func qsort(n int, 
		   less func(i, j int) bool,
		   swap func(i, j int)) {
	subqsort(0, n - 1)
}