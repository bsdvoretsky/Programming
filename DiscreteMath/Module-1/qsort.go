package main

func partition (i, j int, 
				less func(i, j int) bool,
		   		swap func(i, j int)) int {
	l := i
	r := j
	q := (l + r) / 2

	for true {
		for less(l, q) {
			l++
		}
		for less(q, r) {
			r--
		}

		if l >= r {
			return r
		}

		if l == q {
			q = r
		} else if r == q {
			q = l
		}

		swap(l, r)
		l++
		r--
	}

	return -1
}

func subqsort(i, j int,
			  less func(i, j int) bool,
			  swap func(i, j int)) {
	if i < j {
		p := partition(i, j, less, swap)
		subqsort(i, p, less, swap)
		subqsort(p + 1, j, less, swap)
	}
}

func qsort(n int, 
		   less func(i, j int) bool,
		   swap func(i, j int)) {
	subqsort(0, n - 1, less, swap)
}

func main() {
	
}