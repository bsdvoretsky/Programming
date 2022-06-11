package main
import (
	"fmt"
	"os")

type Graph struct {
	vertexes []*Vertex
}

type Vertex struct {
	edges *Edge
	order int
	marked bool
	team int
}

type Edge struct {
	v *Vertex
	next *Edge
}



func PrintGraph(g Graph) {
	for _, v := range(g.vertexes) {
		fmt.Printf("%d ", v.order)
	}
}

func DFS(v *Vertex, g *Graph) {
	v.marked = true
	g.vertexes = append(g.vertexes, v)
	e := v.edges
	for e != nil {
		if !e.v.marked {
			DFS(e.v, g)
		}
		e = e.next
	}
}

func identifyComponents(g Graph) []Graph {
	ans := []Graph{}
	for _, v := range(g.vertexes) {
		if !v.marked {
			t := Graph{}
			DFS(v, &t)
			ans = append(ans, t)
		}
	}
	return ans
}

func teamDFS(v *Vertex, t int) (int, bool) {
	v.team = t
	if t == 1 {
		n++
	}
	e := v.edges
	for e != nil {
		if e.v.team == v.team {
			return 0, false
		} else if e.v.team == -1 {
			teamDFS(e.v, 3 - t)
		}
		e = e.next
	}
	return n, true
}

func checkComponent(g Graph) (int, int, Graph, Graph, bool) {
	// 1st way
	n = 0
	a, ok_1 := teamDFS(g.vertexes[0], 1)
	if !ok_1 {
		return 0, 0, Graph{}, Graph{}, false
	}
	g_1 := Graph{}
	g_1.vertexes = []*Vertex{}
	for _, v := range(g.vertexes) {
		if v.team == 1 {
			g_1.vertexes = append(g_1.vertexes, v)
		}
	}

	for _, v := range(g.vertexes) {
		v.team = -1
	}

	// 2nd way
	n = 0
	b, ok_2 := teamDFS(g.vertexes[0], 2)
	if !ok_2 {
		return 0, 0, Graph{}, Graph{}, false
	}
	g_2 := Graph{}
	g_2.vertexes = []*Vertex{}
	for _, v := range(g.vertexes) {
		if v.team == 1 {
			g_2.vertexes = append(g_2.vertexes, v)
		}
	}

	for _, v := range(g.vertexes) {
		v.team = -1
	}

	return a, b, g_1, g_2, true
}

var N, n int
var c rune

func main() {
	fmt.Scanf("%d", &N)

	g := Graph{}
	g.vertexes = make([]*Vertex, N)
	for i, _ := range(g.vertexes) {
		g.vertexes[i] = &Vertex{nil, i + 1, false, -1}
	}

	for i := 0; i < N; i++ {
		for j := 0; j < N; {
			fmt.Scanf("%c", &c)
			if c == '+' {
				e := g.vertexes[i].edges
				if e == nil {
					g.vertexes[i].edges = &Edge{g.vertexes[j], nil}
				} else {
					for e.next != nil { 
						e = e.next 
					}
					e.next = &Edge{g.vertexes[j], nil}
				}
			}
			if c == '+' || c == '-' {
				j++
			}
		}
	}

	components := identifyComponents(g)

	arr := [][]bool{}
	for i := 0; i < len(components) + 1; i++ {
		t := make([]bool, N / 2 + 1)
		for j := 0; j < N / 2 + 1; j++ {
			t[j] = false
		}
		arr = append(arr, t)
	}

	content := [][]Graph{}
	for i := 0; i < len(components) + 1; i++ {
		t := make([]Graph, N / 2 + 1)
		for j := 0; j < N / 2 + 1; j++ {
			t[j] = Graph{}
		}
		content = append(content, t)
	}

	arr[0][0] = true

	for i := 1; i < len(components) + 1; i++ {
		for j := 0; j < N / 2 + 1; j++ {
			a, b, g_1, g_2, ok := checkComponent(components[len(components) - i])
			if !ok {
				fmt.Printf("No solution\n")
				os.Exit(0)
			}

			if j - a >= 0 && arr[i - 1][j - a] {
				arr[i][j] = true
				content[i][j] = g_1
			} else if j - b >= 0 && arr[i - 1][j - b] {
				arr[i][j] = true
				content[i][j] = g_2
			} else {
				arr[i][j] = false
			}
		}
	}

	res := []*Vertex{}
	i := len(components)
	j := N / 2
	for i > 0 && j > 0 {
		if arr[i][j] {
			for _, v := range(content[i][j].vertexes) {
				res = append(res, v)
			}
			j -= len(content[i][j].vertexes)
			i--
		} else {
			j--
		}
	}

	for i = 0; i < len(res) - 1; i++ {
		for j = i + 1; j < len(res); j++ {
			if res[j].order < res[i].order {
				res[j], res[i] = res[i], res[j]
			}
		}
	}

	for _, v := range(res) {
		fmt.Printf("%d ", v.order)
	}
	fmt.Printf("\n")

}