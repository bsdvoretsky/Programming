package main

import (
	"fmt"
	"os"
	"bufio"
)

type Graph struct {
	vertices []*Vertex 
}

type Condensation struct {
	vertices []*Component
}

type Component struct {
	order int
	edges *CondEdge
	vertices []*Vertex
	halfStep int
}

type CondEdge struct {
	c *Component
	next *CondEdge
}

type Vertex struct {
	order int
	edges *Edge
	T1 int
	low int
	comp int
}

type Edge struct {
	v *Vertex
	next *Edge
}

type Stack struct {
	vertices []*Vertex
	count int
}

func (s *Stack) InitStack (n int) {
	s.vertices = make([]*Vertex, n)
	s.count = 0
}

func (s *Stack) Push (v *Vertex) {
	s.count++
	s.vertices[s.count - 1] = v
}

func (s *Stack) Pop () *Vertex {
	s.count--
	return s.vertices[s.count]
}

func Tarjan(g *Graph) {
	s.InitStack(len(g.vertices))
	for _, v := range(g.vertices) {
		if v.T1 == 0 {
			VisitVertex_Tarjan(g, v)
		}
	}
}

func VisitVertex_Tarjan(g *Graph, v *Vertex) {
	v.T1 = time
	v.low = time
	time++
	s.Push(v)
	e := v.edges
	for e != nil {
		u := e.v
		if u.T1 == 0 {
			VisitVertex_Tarjan(g, u)
		}
		if u.comp == -1 && v.low > u.low {
			v.low = u.low
		}
		e = e.next
	}
	if v.T1 == v.low {
		u := s.Pop()
		u.comp = count
		for u != v {
			u = s.Pop()
			u.comp = count
		}
		count++
	}
}

var N, M, u, v, time, count int
var s Stack

func main() {
	bufstdin := bufio.NewReader(os.Stdin)

	time = 1
	count = 0
	g := Graph{}
	s = Stack{}

	fmt.Fscan(bufstdin, &N)
	g.vertices = make([]*Vertex, N)
	for i, _ := range(g.vertices) {
		g.vertices[i] = &Vertex{i, nil, 0, 0, -1}
	}

	fmt.Fscan(bufstdin, &M)
	for i := 0; i < M; i++ {
		fmt.Fscan(bufstdin, &u, &v)
		e := g.vertices[u].edges
		if e == nil {
			g.vertices[u].edges = &Edge{g.vertices[v], nil}
		} else {
			for e.next != nil {
				e = e.next
			}
			e.next = &Edge{g.vertices[v], nil}
		}	
	}

	Tarjan(&g)

	condencation := Condensation{}
	condencation.vertices = make([]*Component, count)

	for i := 0; i < count; i++ {
		temp := []*Vertex{}
		for _, v := range(g.vertices) {
			if v.comp == i {
				temp = append(temp, v)
			}
		}
		condencation.vertices[i] = &Component{i, nil, temp, 0}
	}

	for _, v := range(g.vertices) {
		e := v.edges
		for e != nil {
			u := e.v
			if v.comp != u.comp {
				ec := condencation.vertices[v.comp].edges
				condencation.vertices[u.comp].halfStep++
				if ec == nil {
					condencation.vertices[v.comp].edges = &CondEdge{condencation.vertices[u.comp], nil}
				} else {
					for ec.next != nil {
						ec = ec.next
					}
					ec.next = &CondEdge{condencation.vertices[u.comp], nil}
				}
			}
			e = e.next
		}
	}

	base := Condensation{}
	base.vertices = []*Component{}


	for _, c := range(condencation.vertices) {
		if c.halfStep == 0 {
			base.vertices = append(base.vertices, c)
		}
	}

	for _, c := range(base.vertices) {
		fmt.Printf("%d ", c.vertices[0].order)
	}

	fmt.Printf("\n")
}