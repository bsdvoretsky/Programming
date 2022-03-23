package main
import "fmt"

type Vertex struct {
	marked bool
	relations []int
}

var n, m, x, y, p int

func DFS(graph []Vertex, p int) {
	fmt.Printf("%d ", p)
	graph[p].marked = true

	for i := 0; i < n; i++ {
		if graph[p].relations[i] == 1 && !graph[i].marked {
			DFS(graph, i)
		}
	}
}

func main() {
	fmt.Scanf("%d\n%d\n%d", &n, &m, &p)
	graph := make([]Vertex, n)
	for i := 0; i < n; i++ {
		graph[i].marked = false
		graph[i].relations = make([]int, n)
	}

	for i := 0; i < m; i++ {
		fmt.Scanf("%d %d", &x, &y)
		graph[x].relations[y] = 1
		graph[y].relations[x] = 1
	}

	DFS(graph, p)

	for i := 0; i < n; i++ {
		if !graph[i].marked {
			DFS(graph, p)
		}
	}

	fmt.Printf("\n")
}