package main

import (
	"fmt"
	"io"
	"math"
)

type Work struct {
	name, color       string
	duration, maxTime int
	marked, removed   bool
	parents           []*Work
	edges             *Edge
	t1, low, comp     int
}

type Edge struct {
	color string
	w     *Work
	next  *Edge
}

type NetworkGraph []*Work

type Stack struct {
	works NetworkGraph
	count int
}

var (
	netgraph    NetworkGraph
	time, count int
	s           Stack
)

func (s *Stack) InitStack(n int) {
	s.works = make(NetworkGraph, n)
	s.count = 0
}

func (s *Stack) Push(w *Work) {
	s.count++
	s.works[s.count-1] = w
}

func (s *Stack) Pop() *Work {
	s.count--
	return s.works[s.count]
}

func Tarjan() {
	s.InitStack(len(netgraph))
	for _, w := range netgraph {
		if w.t1 == 0 {
			VisitVertex_Tarjan(w)
		}
	}
}

func VisitVertex_Tarjan(w *Work) {
	w.t1 = time
	w.low = time
	time++
	s.Push(w)
	e := w.edges
	for e != nil {
		u := e.w
		if u.t1 == 0 {
			VisitVertex_Tarjan(u)
		}
		if u.comp == -1 && w.low > u.low {
			w.low = u.low
		}
		e = e.next
	}
	if w.t1 == w.low {
		u := s.Pop()
		u.comp = count
		if u != w {
			u.removed = true
		}
		for u != w {
			u = s.Pop()
			u.comp = count
			u.removed = true
		}
		count++
	}
}

func scanWork(s string) (string, bool, int, bool) {
	pos := 0
	name := Ident(s, &pos)
	if pos == len(s) {
		return name, false, -1, false
	} else if pos == len(s)-1 {
		return name, false, -1, true
	} else {
		pos++
		duration := Number(s, &pos)
		if pos == len(s)-1 {
			return name, true, duration, false
		} else {
			return name, true, duration, true
		}
	}
}

func Ident(s string, pos *int) string {
	buf := ""
	for *pos < len(s) && ((s[*pos] >= 'a' && s[*pos] <= 'z') ||
		(s[*pos] >= 'A' && s[*pos] <= 'Z') ||
		(s[*pos] >= '0' && s[*pos] <= '9')) {
		buf += string(s[*pos])
		*pos++
	}
	return buf
}

func Number(s string, pos *int) int {
	buf := ""
	for *pos < len(s) && (s[*pos] >= '0' && s[*pos] <= '9') {
		buf += string(s[*pos])
		*pos++
	}
	c := len(buf) - 1
	res := 0
	for i, n := range buf {
		res += (int(n) - 48) * int(math.Pow(10, float64(c-i)))
	}
	return res
}

func findWork(name string, graph []*Work) *Work {
	for _, w := range graph {
		if w.name == name {
			return w
		}
	}
	return nil
}

func DFS(w *Work) {
	if !w.removed {
		if len(w.parents) == 0 {
			w.maxTime = w.duration
		} else {
			m := -1
			for _, v := range w.parents {
				if !v.removed {
					if v.maxTime == -1 {
						return
					}
					if v.maxTime > m {
						m = v.maxTime
					}
				}
			}
			w.maxTime = m + w.duration
		}
		w.marked = true
		e := w.edges
		for e != nil {
			if !e.w.marked {
				DFS(e.w)
			}
			e = e.next
		}
	}
}

func drawBack(w *Work) {
	if !w.removed {
		w.color = "red"
		for _, v := range w.parents {
			if !v.removed {
				if v.maxTime+w.duration == w.maxTime {
					for e := v.edges; e != nil; e = e.next {
						if e.w == w {
							e.color = "red"
							drawBack(v)
						}
					}
				}
			}
		}
	}
}

func removeWorks(w *Work) {
	if len(w.parents) != 0 {
		fl := false
		for _, p := range w.parents {
			if !p.removed {
				fl = true
				break
			}
		}
		if !fl {
			w.removed = true
		}
	}
	for e := w.edges; e != nil; e = e.next {
		if !e.w.removed {
			removeWorks(e.w)
		}
	}
}

func main() {
	time = 1
	count = 1
	var s string
	var prevWork *Work
	prevWork = nil
	netgraph = NetworkGraph{}

	for _, err := fmt.Scanf("%s", &s); err != io.EOF; _, err = fmt.Scanf("%s", &s) {
		if !(s == "<") {
			name, isDuration, duration, isEnd := scanWork(s)

			// If work is initialized
			if isDuration {
				netgraph = append(netgraph, &Work{name, "", duration, -1, false, false, []*Work{}, nil, 0, 0, -1})
			}

			w := findWork(name, netgraph)
			if prevWork != nil {
				w.parents = append(w.parents, prevWork)
				e := prevWork.edges
				if e == nil {
					prevWork.edges = &Edge{"", w, nil}
				} else {
					for e.next != nil {
						e = e.next
					}
					e.next = &Edge{"", w, nil}
				}
			}

			prevWork = w
			if isEnd {
				prevWork = nil
			}
		}
	}

	Tarjan()

	for _, w := range netgraph {
		removeWorks(w)
	}

	for _, w := range netgraph {
		if len(w.parents) == 0 {
			DFS(w)
			break
		}
	}

	for _, w := range netgraph {
		if w.edges == nil {
			drawBack(w)
		}
	}

	fmt.Printf("digraph cpm {\n")
	for _, w := range netgraph {
		if w.color == "red" {
			fmt.Printf("	%s [color=red];\n", w.name)
		} else {
			fmt.Printf("	%s;\n", w.name)
		}
	}
	for _, w := range netgraph {
		for e := w.edges; e != nil; e = e.next {
			if e.color == "red" {
				fmt.Printf("	%s -> %s [color=red];\n", w.name, e.w.name)
			} else {
				fmt.Printf("	%s -> %s;\n", w.name, e.w.name)
			}
		}
	}
	fmt.Printf("}\n")
}
