package main
import "fmt"

type Vertex struct {
	order int
	edge *Edge
	marked bool
	color string
}

type Edge struct {
	v *Vertex
	next *Edge
	color string
}

func PrintGraph(graph []*Vertex) {
	for _, v := range(graph) {
		v.marked = false
	}
	fmt.Printf("graph maxcomponent {\n")
	for _, v := range(graph) {
		if v.color == "red" {
			fmt.Printf("    %d [color=red];\n", v.order)
		} else {
			fmt.Printf("    %d;\n", v.order)
		}
	}
	for _, v := range(graph) {
		v.marked = true
		c := v.edge
		for c != nil {
			if !c.v.marked {
				if c.color == "red" {
					fmt.Printf("    %d -- %d [color=red];\n", v.order, c.v.order)
				} else {
					fmt.Printf("    %d -- %d;\n", v.order, c.v.order)
				}
			}
			c = c.next
		}
	}
	fmt.Printf("}\n")
}

func DFS(v *Vertex) {
	v.marked = true
	if v.order < ordmin_temp {
		ordmin_temp = v.order
	}
	v_temp++
	tempgraph = append(tempgraph, v)
	c := v.edge
	for c != nil {
		if !c.v.marked {
			e_temp++
			DFS(c.v)
		}
		c = c.next
	}
}

func color(v *Vertex) {
	v.color = "red"
	c := v.edge
	for c != nil {
		c.color = "red"
		if c.v.color != "red" {
			color(c.v)
		}
		c = c.next
	}
}

var N, M, u, v, v_temp, e_temp, v_ans, e_ans, ordmin_temp, ordmin_ans int
var tempgraph, ansgraph []*Vertex

func main() {
	v_ans = 0
	e_ans = 0
	ordmin_ans = N
	ordmin_temp = N
	tempgraph = []*Vertex{}
	fmt.Scanf("%d", &N);
	fmt.Scanf("%d", &M);

	vlist := make([]*Vertex, N)
	for i := 0; i < N; i++ {
		vlist[i] = &Vertex{i, nil, false, ""}
	}

	for i := 0; i < N; i++ {
		fmt.Scanf("%d %d\n", &u, &v)

		c := vlist[u].edge
		if c == nil {
			vlist[u].edge = &Edge{vlist[v], nil, ""}
		} else {
			for c.next != nil {
				c = c.next
			}
			c.next = &Edge{vlist[v], nil, ""}
		}

		c = vlist[v].edge
		if c == nil {
			vlist[v].edge = &Edge{vlist[u], nil, ""}
		} else {
			for c.next != nil {
				c = c.next
			}
			c.next = &Edge{vlist[u], nil, ""}
		}
	}

	for _, v := range(vlist) {
		if !v.marked {
			DFS(v)
			if v_temp > v_ans || e_temp > e_ans || ordmin_temp < ordmin_ans {
				ansgraph = tempgraph
				v_ans = v_temp
				e_ans = e_temp
				ordmin_ans = ordmin_temp
			}
			v_temp = 0
			e_temp = 0
			ordmin_temp = N
		}
	}

	color(ansgraph[0])

	PrintGraph(vlist)

}