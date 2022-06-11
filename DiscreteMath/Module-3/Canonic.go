package main

import "fmt"

var (
	n 				  int 		// Кол-во состояний
	m 				  int 		// Размер входного алфавита
	q0 				  int 		// Номер начального состояния
	states 			  []*State
	transition_matrix [][]int
	outputs_matrix 	  [][]string
	num				  int 	    // Текущий номер состояния
)

type State struct { 
	order   		 int
	marked  		 bool
	edges   		 *Edge
	count_of_parents int
}

type Edge struct {
	s    *State // Инцидентное состояние
	out  string // Выходной сигнал
	next *Edge
}

func DFS(s *State) {
	s.marked = true
	s.order = num
	num++

	for e := s.edges; e != nil; e = e.next {
		if !e.s.marked {
			DFS(e.s)
		}
	}
}

func main () {
	num = 0
	states = []*State{}

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
		states = append(states, &State{i, false, nil, 0})
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			var t int
			fmt.Scanf("%d", &t)
			transition_matrix[i][j] = t
		}
	}

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
			states[transition_matrix[i][j]].count_of_parents++
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

	DFS(states[q0])

	fmt.Printf("%d\n%d\n%d\n", n, m, 0)

	for i := 0; i < n - 1; i++ {
		for j := i + 1; j < n; j++ {
			if states[i].order > states[j].order {
				states[i], states[j] = states[j], states[i]
			}
		}
	}

	for i := 0; i < n; i++ {
		for e := states[i].edges; e != nil; e = e.next {
			fmt.Printf("%d ", e.s.order)
		}
		fmt.Println()
	}

	for i := 0; i < n; i++ {
		for e := states[i].edges; e != nil; e = e.next {
			fmt.Printf("%s ", e.out)
		}
		fmt.Println()
	}
}