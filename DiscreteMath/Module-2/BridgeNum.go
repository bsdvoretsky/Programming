package main

import (
	"fmt"
	"os"
	"bufio"
)

type Vetrex struct {
	order  int
	edge   *Edge
	parent *Vetrex
	mark   string
	comp   int
}

type Vertices []*Vetrex

type Edge struct {
	v    *Vetrex
	next *Edge
}

type Queque struct {
	arr   Vertices
	count int
	begin int
}

func (q *Queque) InitQueque () {
	q.arr = Vertices{}
	q.count = 0
	q.begin = 0
}

func (q *Queque) Push (v *Vetrex) {
	q.arr = append(q.arr, v)
	q.count++
}

func (q *Queque) Dequeque () *Vetrex {
	t := q.arr[q.begin]
	q.begin++;
	if q.begin == len(q.arr) {
		q.begin = 0
	}
	q.count--
	return t;
}

func (q *Queque) empty() bool {
	return q.count == 0
}

func VisitVertex1(v *Vetrex) {
	v.mark = "grey"
	queque.Push(v)

	e := v.edge
	for e != nil {
		if e.v.mark == "white" {
			e.v.parent = v
			VisitVertex1(e.v)
		}
		e = e.next
	}

	v.mark = "black"
}

func VisitVertex2(v *Vetrex, components int) {
	v.comp = components

	e := v.edge
	for e != nil {
		if e.v.comp == -1 && e.v.parent != v {
			VisitVertex2(e.v, components)
		} else if e.v.comp != -1 && e.v.comp != components {
			res++
		}
		e = e.next
	}
}



var N, M, u, v, components, res int
var queque Queque

func main() {
	bufstdin := bufio.NewReader(os.Stdin)

	components = 0
	res = 0
	queque.InitQueque()

	fmt.Fscan(bufstdin, &N, &M)

	vlist := make(Vertices, N)
	for i := 0; i < N; i++ {
		vlist[i] = &Vetrex{i, nil, nil, "white", -1}
	}

	for i := 0; i < M; i++ {
		fmt.Fscan(bufstdin, &u, &v)

		c := vlist[u].edge
		if c == nil {
			vlist[u].edge = &Edge{vlist[v], nil}
		} else {
			for c.next != nil {
				c = c.next
			}
			c.next = &Edge{vlist[v], nil}
		}

		c = vlist[v].edge
		if c == nil {
			vlist[v].edge = &Edge{vlist[u], nil}
		} else {
			for c.next != nil {
				c = c.next
			}
			c.next = &Edge{vlist[u], nil}
		}
	}

	for _, v := range(vlist) {
		if v.mark == "white" {
			VisitVertex1(v)
		}
	}

	for !queque.empty() {
		u := queque.Dequeque()
		if u.comp == -1 {
			VisitVertex2(u, components)
			components++
		}
	}

	fmt.Printf("%d", res)
}