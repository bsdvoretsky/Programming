package main
import "fmt"

var N int

func NOD(a, b int) int {
	if a == 0 {
		return b
	}
	return NOD(b % a, a)
}

func NOK(a, b int) int {
	return a * b / NOD(a, b)
}

func triangulation (matrix [][]int, N int) [][]int {
	for j := 0; j < N; j++ {
		max := matrix[j][j]
		row := j
		for i := j + 1; i < N; i++ {
			if matrix[i][j] > max {
				max = matrix[i][j]
				row = i
			}
		}
		if max != 0 {
			matrix[j], matrix[row] = matrix[row], matrix[j]
			for i := j + 1; i < N; i++ {
				if matrix[i][j] != 0 {
					q := NOK(matrix[i][j], matrix[j][j]) / matrix[i][j]
					p := NOK(matrix[i][j], matrix[j][j]) / matrix[j][j]
					for k := 0; k < N + 1; k++ {
						matrix[i][k] = matrix[i][k] * q - matrix[j][k] * p
					}
				}
 			}
		}
	}
	return matrix
}

func main() {
	fmt.Scanf("%d", &N)
	matrix := make([][]int, N)
	for i := 0; i < N; i++ {
		matrix[i] = make([]int, N + 1)
		for j := 0; j < N + 1; j++ {
			fmt.Scanf("%d", &matrix[i][j])
		}
	}
	matrix = triangulation(matrix, N)
	roots := [][2]int {}
	fl := false
	for i := N - 1; i >= 0; i-- {
		if matrix[i][i] != 0 {
			q := 0
			m := 1
			for _, r := range(roots) {
				m = NOK(m, r[1])
			}
			for j := i + 1; j < N; j++ {
				q -= matrix[i][j] * roots[N - 1 - j][0] * (m / roots[N - 1 - j][1])
			}
			q += matrix[i][N] * m
			t := NOD(q, m * matrix[i][i])
			if m * matrix[i][i] / t < 0 {
				m *= -1
				q *= -1
			}
			roots = append(roots, [2]int{q / t, m * matrix[i][i] / t})

		} else {
			fl = true
			break
		}
	}
	if fl {
		fmt.Printf("No solution\n")
	} else {
		for i := N - 1; i >= 0; i-- {
			fmt.Printf("%d/%d\n", roots[i][0], roots[i][1])
		}
	}
}