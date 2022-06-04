package main

import "fmt"

type State struct {
	i       int
	parent  *State
	depth   int
	marked  bool
	trans   []*State
	outs    []string
}

var (
	n, m, q0, num int
)

func Union(x, y *State) {
	root_x := Find(x)
	root_y := Find(y)
	if root_x.depth < root_y.depth {
		root_x.parent = root_y
	} else {
		root_y.parent = root_x
		if root_x.depth == root_y.depth && root_x != root_y {
			root_x.depth++
		}
	}
}

func Find(x *State) *State {
	if x.parent == x {
		return x
	} else {
		x.parent = Find(x.parent)
		return Find(x.parent)
	}
}

func Split1(automat []*State, mt *int, pi *[]*State) {
	for _, q := range(automat) {
		q.parent = q
		q.depth = 0
	}
	*mt = n
	for i := 0; i < n - 1; i++ {
		for j := i + 1; j < n; j++ {
			if Find(automat[i]) != Find(automat[j]) {
				eq := true
				for c := 0; c < m; c++ {
					if automat[i].outs[c] != automat[j].outs[c] {
						eq = false
						break
					}
				}
				if eq {
					Union(automat[i], automat[j])
					*mt = *mt - 1
				}
			}
		}
	}
	for _, q := range(automat) {
		(*pi)[q.i] = Find(q)
	}
}

func Split(automat []*State, mt *int, pi *[]*State) {
	for _, q := range(automat) {
		q.parent = q
		q.depth = 0
	}
	*mt = n
	for i := 0; i < n - 1; i++ {
		for j := i + 1; j < n; j++ {
			if (*pi)[automat[i].i] == (*pi)[automat[j].i] && Find(automat[i]) != Find(automat[j]) {
				eq := true
				for c := 0; c < m; c++ {
					w1 := automat[i].trans[c].i
					w2 := automat[j].trans[c].i
					if (*pi)[w1] != (*pi)[w2] {
						eq = false
						break
					}
				}
				if eq {
					Union(automat[i], automat[j])
					*mt = *mt - 1
				}
			}
		}
	}
	for _, q := range(automat) {
		(*pi)[q.i] = Find(q)
	}
}

func AufenkampHohn(automat []*State) []*State {
	var m1 int
	pi := make([]*State, n)
	Split1(automat, &m1, &pi)

	for {
		var m2 int
		Split(automat, &m2, &pi)
		if m1 == m2 {
			break
		}
		m1 = m2
	}

	ans := []*State{}

	for _, q := range(automat) {
		qt := pi[q.i]
		if !find(ans, qt) {
			ans = append(ans, qt)
			for i := 0; i < m; i++ {
				ans[len(ans) - 1].trans[i] = pi[q.trans[i].i]
				ans[len(ans) - 1].outs[i] = q.outs[i]
			}
		}
	}
	return ans
}

func find(automat []*State, q *State) bool {
	for _, s := range(automat) {
		if s == q {
			return true
		}
	}
	return false
}

func DFS(s *State) {
	s.i = num
	num++
	s.marked = true

	for i := 0; i < m; i++ {
		if !s.trans[i].marked {
			DFS(s.trans[i])
		}
	}
}

func main() {
	num = 0
	fmt.Scanf("%d", &n)
	fmt.Scanf("%d", &m)
	fmt.Scanf("%d", &q0)

	automat := make([]*State, n)

	for i := 0; i < n; i++ {
		automat[i] = &State{i, nil, 0, false, make([]*State, m), make([]string, m)}
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			var t int
			fmt.Scanf("%d", &t)
			automat[i].trans[j] = automat[t]
		}
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			fmt.Scanf("%s", &automat[i].outs[j])
		}
	}

	min_automat := AufenkampHohn(automat)

	for _, q := range(min_automat) {
		if q.i == q0 {
			DFS(q)
			break
		}
	}
	
	for i := 0; i < len(min_automat) - 1; i++ {
		for j := i + 1; j < len(min_automat); j++ {
			if min_automat[j].i < min_automat[i].i {
				min_automat[j], min_automat[i] = min_automat[i], min_automat[j]
			}
		}
	}

	fmt.Printf("digraph {\n")
	fmt.Printf("	rankdir = LR\n")
	for _, q := range(min_automat) {
		for i := 0; i < m; i++ {
			fmt.Printf("	%d -> %d [lable = \"%s(%s)\"]\n", q.i, q.trans[i].i, string(i + 97), q.outs[i])
		}
	}
	fmt.Printf("}\n")
}