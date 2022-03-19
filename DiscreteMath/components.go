package main
import "fmt"

type Edges struct {
	v *Vertex
	next *Edges
}

type Vertex struct {
	component int
	edges *Edges
}

var n, m int

func makeChain(v *Vertex, k int) {
	v.component = k
	c := v.edges
	for c != nil {
		if c.v.component == 0 {
			makeChain(c.v, k)
		}
		c = c.next
	}
}

func main() {
	fmt.Scanf("%d\n%d", &n, &m)
	vertexes := make([]Vertex, n)

	for i := 0; i < n; i++ {
		vertexes[i] = Vertex {0, nil}
	}

	for k := 0; k < m; k++ {
		i, j := 0, 0
		fmt.Scanf("%d %d", &i, &j)
		c := &vertexes[i].edges
		for *c != nil {
			c = &(*c).next
		}
		*c = &Edges {&vertexes[j], nil}

		c = &vertexes[j].edges
		for *c != nil {
			c = &(*c).next
		}
		*c = &Edges {&vertexes[i], nil}
	}

	ans := 0

	for i := 0; i < n; i++ {
		if vertexes[i].component == 0 {
			ans++
			makeChain(&vertexes[i], ans)
		}
	}

	fmt.Printf("%d\n", ans)
}