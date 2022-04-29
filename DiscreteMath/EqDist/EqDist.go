package main
import "fmt"

type Graph struct {
	vertices []*Vertex
}

type Vertex struct {
	order int
	edges *Edge
	dists []int
}

type Edge struct {
	v *Vertex
	next *Edge
}

func fillDist(v, cur *Vertex, d int) {
	e := cur.edges
	for e != nil {
		if v.dists[e.v.order] == -1 {
			v.dists[e.v.order] = d
		}
		e = e.next
	}

	e = cur.edges
	for e != nil {
		if v.dists[e.v.order] == d {
			fillDist(v, e.v, d + 1)
		}
		e = e.next
	}
}

var N, M, K, u, v int

func main() {
	fmt.Scanf("%d", &N)
	g := Graph{}
	g.vertices = make([]*Vertex, N)
	for i, _ := range(g.vertices) {
		t := make([]int, N)
		for j := 0; j < N; j++ {
			if j == i {
				t[j] = 0
			} else {
				t[j] = -1
			}
		}
		g.vertices[i] = &Vertex{i, nil, t}
	}

	fmt.Scanf("%d", &M)
	for i := 0; i < M; i++ {
		fmt.Scanf("%d %d", &u, &v)
		e := g.vertices[u].edges
		if e == nil {
			g.vertices[u].edges = &Edge{g.vertices[v], nil}
		} else {
			for e.next != nil {
				e = e.next
			}
			e.next = &Edge{g.vertices[v], nil}
		}

		e = g.vertices[v].edges
		if e == nil {
			g.vertices[v].edges = &Edge{g.vertices[u], nil}
		} else {
			for e.next != nil {
				e = e.next
			}
			e.next = &Edge{g.vertices[u], nil}
		}
	}

	temp := []*Vertex{}

	fmt.Scanf("%d", &K)
	for i := 0; i < K; i++ {
		fmt.Scanf("%d", &v)
		fillDist(g.vertices[v], g.vertices[v], 1)
		temp = append(temp, g.vertices[v])
	}

	fl_1 := false

	for j := 0; j < N; j++ {
		fl := false
		for i := 1; i < len(temp); i++ {
			if temp[i - 1].dists[j] != temp[i].dists[j] {
				fl = true
				break
			}
		}
		if !fl {
			fmt.Printf("%d ", j)
			if !fl_1 {
				fl_1 = true
			}
		}
	}

	if !fl_1 {
		fmt.Printf("-")
	}
	fmt.Printf("\n")
}