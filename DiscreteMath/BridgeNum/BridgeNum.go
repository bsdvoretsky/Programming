package main
import "fmt"

type Vetrex struct {
	order int
	edge *Edge
	parent *Vetrex
	marked bool
}

type Edge struct {
	v *Vetrex
	next *Edge
}

type Queque struct {
	arr []*Vetrex
	count int
}

func (q *Queque) InitQueque () {
	q.arr = []*Vetrex{}
	q.count = 0
}

func (q *Queque) Push (v *Vetrex) {
	q.arr = append(q.arr, v)
	q.count++
}

func (q *Queque) Dequeque () *Vetrex {
	t := q.arr[0]
	for i := 1; i < q.count; i++ {
		q.arr[i - 1] = q.arr[i]
	}
	q.count--
	return t;
}

func (q *Queque) empty() bool {
	return q.count == 0
}

func DFS_1(v *Vetrex) {
	c := v.edge
	v.marked = true
	queque.Push(v)
	for c != nil {
		if !c.v.marked {
			c.v.parent = v
			DFS_1(c.v)
		}
		c = c.next
	}
}

func DFS_2(v *Vetrex) {
	v.marked = true
	c := v.edge
	for c != nil {
		if !c.v.marked && c.v.parent != v {
			DFS_2(c.v)
		}
		c = c.next
	}
}

var N, M, u, v, res int
var queque Queque

func main() {
	res = 0
	queque.InitQueque()
	fmt.Scanf("%d", &N)
	fmt.Scanf("%d", &M)
	vlist := make([]*Vetrex, N)
	for i := 0; i < N; i++ {
		vlist[i] = &Vetrex{i, nil, nil, false}
	}

	for i := 0; i < M; i++ {
		fmt.Scanf("%d %d\n", &u, &v)

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
		if !v.marked {
			DFS_1(v)
		}
	}

	for _, v := range(vlist) {
		v.marked = false
	}

	for !queque.empty() {
		t := queque.Dequeque()
		if !t.marked {
			DFS_2(t)
			res++
		}
	}

	fmt.Println(res - 1)

}