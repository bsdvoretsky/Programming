package main

import (
	"fmt"
	"os"
	"bufio"
	"sort"
)

var (
	n 				  int 		// Кол-во состояний
	m 				  int 		// Размер входного алфавита
	q0 				  int 		// Номер начального состояния
	states 			  States
	transition_matrix [][]int
	outputs_matrix 	  [][]string
	num				  int 	    // Текущий номер состояния
)

type States []*State

func (states States) Len() int { 
	return len(states) 
}
func (states States) Swap(i, j int) { 
	states[i], states[j] = states[j], states[i] 
}
func (states States) Less(i, j int) bool { 
	return states[i].order < states[j].order 
}

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

	bufstdin := bufio.NewReader(os.Stdin)
	bufstdout := bufio.NewWriter(os.Stdout)

	fmt.Fscan(bufstdin, &n)
	fmt.Fscan(bufstdin, &m)
	fmt.Fscan(bufstdin, &q0)

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
			fmt.Fscan(bufstdin, &t)
			transition_matrix[i][j] = t
		}
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			var o string
			fmt.Fscan(bufstdin, &o)
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

	fmt.Fprint(bufstdout, n)
	fmt.Fprint(bufstdout, "\n")

	fmt.Fprint(bufstdout, m)
	fmt.Fprint(bufstdout, "\n")

	fmt.Fprint(bufstdout, 0)
	fmt.Fprint(bufstdout, "\n")

	sort.Sort(states)

	for i := 0; i < n; i++ {
		for e := states[i].edges; e != nil; e = e.next {
			fmt.Fprint(bufstdout, e.s.order)
			fmt.Fprint(bufstdout, " ")
		}
		fmt.Fprint(bufstdout, "\n")
	}

	for i := 0; i < n; i++ {
		for e := states[i].edges; e != nil; e = e.next {
			fmt.Fprint(bufstdout, e.out)
			fmt.Fprint(bufstdout, " ")
		}
		fmt.Fprint(bufstdout, "\n")
	}

	bufstdout.Flush()
}