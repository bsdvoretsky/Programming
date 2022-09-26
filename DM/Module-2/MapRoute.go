package main

import (
	"fmt"
	"os"
)

var (
	N int // Размер карты
)

type Vertex struct {
	dist   int     // Вес кратчайшего пути из начальной вершины до данной
	parent *Vertex
	edges  *Edge
	weight int
	marked bool    // Уточнили ли вершину
}

type Edge struct {
	v      *Vertex // Инцидентая вершина
	next   *Edge   // Следующее ребро
}

type Map [][]*Vertex

func Relax(u, v *Vertex) bool {
	changed := (u.dist + u.weight < v.dist)
	if changed {
		v.dist = u.dist + u.weight
		v.parent = u
	}
	return changed
}

func Dijkstra(map_ Map, s *Vertex) {
	for _, row := range(map_) {
		for _, v := range(row) {
			v.dist = 21000000
			v.parent = nil
		}
	}
	s.dist = 0
	q := 0

	for q != N * N {
		m := 21000001
		var k *Vertex
		for _, row := range(map_) {
			for _, v := range(row) {
				if !v.marked && v.dist < m {
					m = v.dist
					k = v
				}
			}
		}
		k.marked = true
		q++
		for e := k.edges; e != nil; e = e.next {
			Relax(k, e.v)
		}
	}

}

func main() {
	fmt.Scanf("%d", &N)

	map_ := Map{}

	for i := 0; i < N; i++ {
		t_arr := []*Vertex{} // i-я строка карты

		for j := 0; j < N; j++ {
			var t int // Текущее число на позиции (i, j)
			fmt.Scanf("%d", &t)
			t_arr = append(t_arr, &Vertex{0, nil, nil, t, false})
		}

		map_ = append(map_, t_arr)
	}

	if N == 1 {
		fmt.Printf("%d\n", map_[0][0].weight)
		os.Exit(0)
	}

	if N == 2 {
		map_[0][0].edges = &Edge{map_[0][1], nil}
		map_[0][0].edges.next = &Edge{map_[1][0], nil}

		map_[0][1].edges = &Edge{map_[0][0], nil}
		map_[0][1].edges.next = &Edge{map_[1][1], nil}

		map_[1][0].edges = &Edge{map_[0][0], nil}
		map_[1][0].edges.next = &Edge{map_[1][1], nil}

		map_[1][1].edges = &Edge{map_[0][1], nil}
		map_[1][1].edges.next = &Edge{map_[1][0], nil}
	} else {
		map_[0][0].edges = &Edge{map_[0][1], nil}
		map_[0][0].edges.next = &Edge{map_[1][0], nil}

		map_[0][N - 1].edges = &Edge{map_[0][N - 2], nil}
		map_[0][N - 1].edges.next = &Edge{map_[1][N - 1], nil}

		map_[N - 1][0].edges = &Edge{map_[N - 2][0], nil}
		map_[N - 1][0].edges.next = &Edge{map_[N - 1][1], nil}

		map_[N - 1][N - 1].edges = &Edge{map_[N - 1][N - 2], nil}
		map_[N - 1][N - 1].edges.next = &Edge{map_[N - 2][N - 1], nil}

		for i := 1; i < N - 1; i++ {
			map_[0][i].edges = &Edge{map_[0][i - 1], nil}
			map_[0][i].edges.next = &Edge{map_[0][i + 1], nil}
			map_[0][i].edges.next.next = &Edge{map_[1][i], nil}

			map_[N - 1][i].edges = &Edge{map_[N - 1][i - 1], nil}
			map_[N - 1][i].edges.next = &Edge{map_[N - 1][i + 1], nil}
			map_[N - 1][i].edges.next.next = &Edge{map_[N - 2][i], nil}

			map_[i][0].edges = &Edge{map_[i - 1][0], nil}
			map_[i][0].edges.next = &Edge{map_[i + 1][0], nil}
			map_[i][0].edges.next.next = &Edge{map_[i][1], nil}

			map_[i][N - 1].edges = &Edge{map_[i - 1][N - 1], nil}
			map_[i][N - 1].edges.next = &Edge{map_[i + 1][N - 1], nil}
			map_[i][N - 1].edges.next.next = &Edge{map_[i][N - 2], nil}
		}

		for i := 1; i < N - 1; i++ {
			for j := 1; j < N - 1; j++ {
				map_[i][j].edges = &Edge{map_[i - 1][j], nil}
				map_[i][j].edges.next = &Edge{map_[i + 1][j], nil}
				map_[i][j].edges.next.next = &Edge{map_[i][j - 1], nil}
				map_[i][j].edges.next.next.next = &Edge{map_[i][j + 1], nil}
			}
		}
	}

	Dijkstra(map_, map_[0][0])

	fmt.Printf("%d\n", map_[N - 1][N - 1].dist + map_[N - 1][N - 1].weight)

	for _, row := range(map_) {
		for _, el := range(row) {
			fmt.Printf("%d ", el.dist + el.weight)
		}
		fmt.Println()
	}

}