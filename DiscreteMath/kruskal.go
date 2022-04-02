package main
import (
	"fmt"
	"math"
	"sort"
)

type Vertex struct {
	x, y float64 
	parent *Vertex
	depth int
}

type Edge struct {
	v, u *Vertex
	length float64
}

type Edges []*Edge

func (edges Edges) Len() int {
	return len(edges)
}

func (edges Edges) Swap(i, j int) {
	edges[i], edges[j] = edges[j], edges[i]
}

func (edges Edges) Less(i, j int) bool {
	return edges[i].length < edges[j].length
}

func Find(v *Vertex) *Vertex {
	if v.parent == v {
		return v
	}
	return Find(v.parent)
}

func Union(v, u *Vertex) {
	root_v := Find(v)
	root_u := Find(u)
	if root_v.depth < root_u.depth {
		root_v.parent = root_u
	} else {
		root_u.parent = root_v
		if root_v.depth == root_u.depth && root_v != root_u {
			root_v.depth = root_u.depth + 1
		}
	}
}

func SpanningTree(edges Edges) Edges {
	i := 0
	result_edges := Edges{}
	for i < len(edges) && len(result_edges) < n - 1 {
		if Find(edges[i].u) != Find(edges[i].v) {
			result_edges = append(result_edges, edges[i])
			Union(edges[i].u, edges[i].v)
		}
		i++
	}
	return result_edges
}

func MST_Kruskal(edges Edges) Edges {
	sort.Sort(edges)
	return SpanningTree(edges)
}

var n int
var x, y float64

func main() {
	fmt.Scanf("%d", &n)
	edges := Edges{}
	vertexes := make([]*Vertex, n)

	for i := 0; i < n; i++ {
		fmt.Scanf("%f %f\n", &x, &y)
		vertexes[i] = new(Vertex)
		v := vertexes[i]
		v.x = x
		v.y = y
		v.parent = vertexes[i]
		v.depth = 0
	}

	for i := 0; i < n - 1; i++ {
		for j := i + 1; j < n; j++ {
			e := new(Edge)
			v := vertexes[i]
			u := vertexes[j]
			e.v = v
			e.u = u
			e.length = math.Sqrt(math.Pow(v.x - u.x, 2) + math.Pow(v.y - u.y, 2))
			edges = append(edges, e)
		}
	}

	result_edges := MST_Kruskal(edges)

	var ans float64
	ans = 0
	for _, e := range result_edges {
		ans += e.length
	}
	fmt.Printf("%.2f\n", ans)
}

