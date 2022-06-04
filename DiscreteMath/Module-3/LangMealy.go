package main

import "fmt"

var (
	n 				  int // Кол-во состояний автомата
	m 				  int // Размер входного алфавита
	q0				  int // Начальное состояние
	M 				  int // Максимальная длина слова
	states 			  []*State
	transition_matrix [][]int
	outputs_matrix 	  [][]string
	ans 			  []string
)

type State struct { 
	edges  *Edge
}

type Edge struct {
	s    *State // Инцидентное состояние
	out  string // Выходной сигнал
	next *Edge
}

func find(s string) bool {
	for _, c := range(ans) {
		if c == s {
			return true
		}
	}
	return false
}

func generateWords(s *State, buf string) {
	if len(buf) > M {
		return
	}
	if len(buf) != 0 {
		if !find(buf) {
			ans = append(ans, buf)
		}
	}

	for e := s.edges; e != nil; e = e.next {
		if e.out == "-" && e.s != s {
			generateWords(e.s, buf)
		} else if e.out != "-" {
			generateWords(e.s, buf + e.out)
		}
	}
}

func main() {
	states = []*State{}

	fmt.Scanf("%d", &n)
	fmt.Scanf("\n")
	m = 2

	transition_matrix = make([][]int, n)
	outputs_matrix = make([][]string, n)
	for i := 0; i < n; i++ {
		transition_matrix[i] = make([]int, m)
		outputs_matrix[i] = make([]string, m)
	}

	for i := 0; i < n; i++ {
		states = append(states, &State{nil})
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			var t int
			fmt.Scanf("%d", &t)
			transition_matrix[i][j] = t
		}
	}

	fmt.Scanf("\n")

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			var o string
			fmt.Scanf("%s", &o)
			outputs_matrix[i][j] = o
		}
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			e := states[i].edges
			if e == nil {
				states[i].edges = &Edge{states[transition_matrix[i][j]],
										outputs_matrix[i][j], nil}
			} else {
				for e.next != nil {
					e = e.next
				}
				e.next = &Edge{states[transition_matrix[i][j]],
							   outputs_matrix[i][j], nil}
			}
		}
	}

	fmt.Scanf("\n")

	fmt.Scanf("%d", &q0)
	fmt.Scanf("%d", &M)

	generateWords(states[q0], "")

	for _, c := range(ans) {
		fmt.Printf("%s ", c)
	}
	fmt.Println()
}