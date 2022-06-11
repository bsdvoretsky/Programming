package main
import ("math/rand")

// АВЛ-дерево

type AVLNode struct {
	left, right *AVLNode
	key string
	value int
	height int
}

func (n *AVLNode) Init(k string, v int) {
	n.key = k
	n.value = v
	n.left = nil
	n.right = nil
	n.height = 1
}

func height(n *AVLNode) int {
	if n != nil {
		return n.height
	}
	return 0
}

func bfactor(n *AVLNode) int {
	return height(n.right)-height(n.left)
}

func fixheight(n *AVLNode) {
	hl := height(n.left)
	hr := height(n.right)
	if hl > hr {
		n.height = hl + 1
	} else {
		n.height = hr + 1
	}
}

func rotateright(n *AVLNode) {
	q := n.left
	n.left = n.right
	n.right = q
	fixheight(n)
	fixheight(q)
}

func rotateleft(n *AVLNode) {
	q := n.right
	n.right = n.left
	n.left = q
	fixheight(n)
	fixheight(q)
}

func balance(n *AVLNode) {
	fixheight(n)
	if bfactor(n) == 2 {
		if bfactor(n.right) < 0 {
			rotateright(n.right)
		}
		rotateleft(n)
	}
	if bfactor(n) == -2 {
		if bfactor(n.left) > 0 {
			rotateleft(n.left)
		}
		rotateright(n)
	}
}

func (n *AVLNode) Assign(s string, x int) {
	for n != nil {
		if s < n.key {
			if n.left == nil {
				n.left = new(AVLNode)
				(n.left).Init(s, x)
				break
			}
			n = n.left
		} else {
			if n.right == nil {
				n.right = new(AVLNode)
				(n.right).Init(s, x)
				break
			}
			n = n.right
		}
	}
	balance(n)
}

func (n *AVLNode) Lookup(s string) (int, bool) {
	if n == nil {
		return -1, false
	}
	if (s == n.key) {
		return n.value, true
	}
	if (s > n.key) {
		return (n.right).Lookup(s)
	}
	return (n.left).Lookup(s)
}

// Список с пропусками

type Node struct {
	down, next *Node
	key string
	value int
}

type List struct {
	head, tail *Node
}

func (l *List) IsEmpty() bool {
	return l.head == nil
}

func (l *List) Assign(s string, x int) *Node {
	var n Node
	n.key = s
	n.value = x
	if l.IsEmpty() {
		n.next = nil
		l.head = &n
	} else {
		c := l.head
		for {
			if c.next == nil {
				c.next = &n
				n.next = nil
				break
			}
			if c.next.value > x {
				c.next = &n
				n.next = c.next
				break
			}
			c = c.next
		}

	}
	return &n
}

type SkipList struct {
	lists []List
	levels int
}

func (l *SkipList) Init(m int) {
	l.levels = m
	var list List
	list.head = nil
	list.tail = nil
	l.lists = append(l.lists, list)
	for i := 1; i < m; i++ {
		var list List
		list.head = l.lists[i-1].head
		list.tail = l.lists[i-1].tail
		l.lists = append(l.lists, list)
	}
}

func (l *SkipList) IsEmpty() bool {
	return l.lists[0].head == nil
}

func (l *SkipList) Assign(s string, x int) {
	q := l.lists[0].Assign(s, x)
	k := 1
	for rand.Intn(2) == 1 && k < l.levels {
		t := l.lists[k].Assign(s, x)
		t.down = q
		q = t
		k++
	}
}

func (l *SkipList) Lookup(s string) (int, bool) {
	q := l.levels - 1
	c := l.lists[q].head
	for c == nil || c.key != s {
		if c == nil {
			if q == 0 {
				return -1, false
			}
			c = l.lists[q-1].head
			q--
			continue
		}
		c = c.next
	}
	return c.value, true
}

type AssocArray interface {
	Assign(s string, x int)
	Lookup(s string) (x int, exists bool)
}

// Лексический анализатор

func lex(sentence string, array AssocArray) []int {
	res := []int {}
	s := []rune {}
	m := 1
	for _, c := range sentence {
		if c != ' ' {
			s = append(s, c)
		} else {
			if len(s) != 0 {
				x, exists := array.Lookup(string(s))
				if exists {
					res = append(res, x)
				} else {
					array.Assign(string(s), m)
					res = append(res, m)
					m++
				}
			}
			s = []rune {}
		}
	}
	if len(s) != 0 {
		x, exists := array.Lookup(string(s))
		if exists {
			res = append(res, x)
		} else {
			array.Assign(string(s), m)
			res = append(res, m)
			m++
		}
	}
	s = []rune {}
	return res
}

func main() {
	
}