package main

import "fmt"

type Stack struct {
	vertexes []Vertex
	count    int
}

func (s *Stack) InitStack(n int) {
	s.vertexes = make([]Vertex, n)
	s.count = 0
}

func (s *Stack) Push(v Vertex) {
	s.vertexes[s.count] = v
	s.count++
}

func (s *Stack) Pop() Vertex {
	s.count--
	return s.vertexes[s.count]
}

type Vertex struct {
	edges *Edge
	comp  int
	T1    int
	low   int
	order int
}

type Edge struct {
	v    *Vertex
	next *Edge
}

func Tarjan(G *[]*Vertex) {
	s.InitStack(len(*G))
	for _, v := range *G {
		if v.T1 == 0 {
			VisitVertex_Tarjan(v)
		}
	}
}

func VisitVertex_Tarjan(v *Vertex) {
	v.low = time
	v.T1 = time
	time++
	s.Push(*v)

	c := v.edges
	for c != nil {
		if c.v.T1 == 0 {
			VisitVertex_Tarjan(c.v)
		}
		if c.v.comp == 0 && v.low > c.v.low {
			v.low = c.v.low
		}
		c = c.next
	}
	if v.T1 == v.low {
		u := s.Pop()
		u.comp = count

		for u.order != *&v.order {
			u = s.Pop()
			u.comp = count
		}

		count++
	}
}

var N, M, u, v, time, count int
var s Stack

func main() {
	time = 1
	count = 1

	fmt.Scanf("%d\n%d", &N, &M)

	vlist := make([]*Vertex, N)
	for i := 0; i < N; i++ {
		vlist[i] = &Vertex{nil, 0, 0, 0, i}
	}
	for i := 0; i < M; i++ {
		fmt.Scanf("%d %d\n", &u, &v)

		c := vlist[u].edges
		if c == nil {
			vlist[u].edges = &Edge{vlist[v], nil}
		} else {
			for c.next != nil {
				c = c.next
			}
			c.next = &Edge{vlist[v], nil}
		}

		c = vlist[v].edges
		if c == nil {
			vlist[v].edges = &Edge{vlist[u], nil}
		} else {
			for c.next != nil {
				c = c.next
			}
			c.next = &Edge{vlist[u], nil}
		}
	}

	Tarjan(&vlist)

	fmt.Printf("%d\n", count)
}
