package main

import "fmt"

type Vetrex struct {
	index int
	key   int
	value *Vetrex
	edges *Edge
	order int
}

type Edge struct {
	v    *Vetrex
	next *Edge
	len  int
}

type PQueue struct {
	cap   int
	heap  []*Vetrex
	count int
}

func InitPriorityQueue(pq *PQueue, n int) {
	pq.heap = make([]*Vetrex, n)
	pq.cap = n
	pq.count = 0
}

func QueueEmpty(pq *PQueue) bool {
	return pq.count == 0
}

func Insert(pq *PQueue, v *Vetrex) {
	i := pq.count
	pq.count = i + 1
	pq.heap[i] = v
	for i > 0 && pq.heap[(i-1)/2].key > pq.heap[i].key {
		pq.heap[(i-1)/2], pq.heap[i] = pq.heap[i], pq.heap[(i-1)/2]
		pq.heap[i].index = i
		i = (i - 1) / 2
	}
	pq.heap[i].index = i
}

func Heapify(i, n int, pq *PQueue) {
	for {
		l := 2*i + 1
		r := l + 1
		j := i
		if l < n && pq.heap[i].key > pq.heap[l].key {
			i = l
		}
		if r < n && pq.heap[i].key > pq.heap[r].key {
			i = r
		}
		if i == j {
			break
		}
		pq.heap[i], pq.heap[j] = pq.heap[j], pq.heap[i]
		pq.heap[i].index = i
		pq.heap[j].index = j
	}
}

func ExtractMin(pq *PQueue) *Vetrex {
	res := pq.heap[0]
	pq.count--
	if pq.count > 0 {
		pq.heap[0] = pq.heap[pq.count]
		pq.heap[0].index = 0
		Heapify(0, pq.count, pq)
	}
	return res
}

func DecreaseKey(pq *PQueue, v *Vetrex, nk int) {
	i := v.index
	v.key = nk
	for i > 0 && pq.heap[(i-1)/2].key > nk {
		pq.heap[(i-1)/2], pq.heap[i] = pq.heap[i], pq.heap[(i-1)/2]
		pq.heap[i].index = i
		i = (i - 1) / 2
	}
	v.index = i
}

func MST_Prim(vlist []*Vetrex) int {
	var pq PQueue
	InitPriorityQueue(&pq, len(vlist))
	sum := 0
	v := vlist[0]
	for {
		v.index = -2
		c := v.edges
		for c != nil {
			if c.v.index == -1 {
				c.v.key = c.len
				c.v.value = v
				Insert(&pq, c.v)
			} else if c.v.index != -2 && c.len < c.v.key {
				c.v.value = v
				DecreaseKey(&pq, c.v, c.len)
			}
			c = c.next
		}
		if QueueEmpty(&pq) {
			break
		}
		v = ExtractMin(&pq)
		sum += v.key
	}
	return sum
}

func main() {
	var n, m, v, u, len int
	fmt.Scanf("%d\n%d\n", &n, &m)

	vlist := make([]*Vetrex, n)
	for i := 0; i < n; i++ {
		vlist[i] = &Vetrex{-1, 0, nil, nil, i}
	}
	for i := 0; i < m; i++ {
		fmt.Scanf("%d %d %d\n", &v, &u, &len)
		c := vlist[v].edges
		if c == nil {
			vlist[v].edges = &Edge{vlist[u], nil, len}
		} else {
			for c.next != nil {
				c = c.next
			}
			c.next = &Edge{vlist[u], nil, len}
		}
		c = vlist[u].edges
		if c == nil {
			vlist[u].edges = &Edge{vlist[v], nil, len}
		} else {
			for c.next != nil {
				for c.next != nil {
					c = c.next
				}
			}
			c.next = &Edge{vlist[v], nil, len}
		}
	}

	fmt.Printf("%d\n", MST_Prim(vlist))
}
