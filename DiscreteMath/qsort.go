package main
import "fmt"

func qsort(i, j int, 
		   less func(i, j int) bool,
		   swap func(i, j int)) {
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
		qsort(i, r, less, swap)
		qsort(r + 1, j, less, swap)
	}
}

var a = [12]int{5, 2, 2, 1, -3, 4, 3, 5, -4, 2, 2, 1}

func less (i, j int) bool {
	return a[i] < a[j]
}
func swap (i, j int) {
	a[i], a[j] = a[j], a[i]
}

func main() {
	qsort(0, len(a) - 1, less, swap)
	fmt.Printf("%d\n", a);
}