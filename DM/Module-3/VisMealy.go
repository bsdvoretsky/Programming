package main

import "fmt"

var (
	n 				  int // Кол-во состояний автомата
	m 				  int // Размер входного алфавита
	q0				  int // Начальное состояние
	transition_matrix [][]int
	outputs_matrix 	  [][]string
)

func main() {
	fmt.Scanf("%d", &n)
	fmt.Scanf("%d", &m)
	fmt.Scanf("%d", &q0)

	transition_matrix = make([][]int, n)
	outputs_matrix = make([][]string, n)

	for i := 0; i < n; i++ {
		transition_matrix[i] = make([]int, m)
		outputs_matrix[i] = make([]string, m)
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			fmt.Scanf("%d", &transition_matrix[i][j])
		}
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			fmt.Scanf("%s", &outputs_matrix[i][j])
		}
	}

	fmt.Printf("digraph {\n")
	fmt.Printf("    rankdir = LR\n")
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			fmt.Printf("    %d -> %d [label = \"%c(%s)\"]\n", i, transition_matrix[i][j], j + 97, outputs_matrix[i][j])
		}
	}
	fmt.Printf("}\n")
}