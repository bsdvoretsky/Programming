package main

import (
	"fmt"
	"os"
)

type State struct {
	i       int
	parent  *State
	depth   int
	marked  bool
	trans   []*State
	outs    []string
}

var (
	n1, m1, q10 int
	n2, m2, q20 int
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
	*mt = len(automat)
	for i := 0; i < len(automat) - 1; i++ {
		for j := i + 1; j < len(automat); j++ {
			if Find(automat[i]) != Find(automat[j]) {
				eq := true
				for c := 0; c < len(automat[0].outs); c++ {
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
	*mt = len(automat)
	for i := 0; i < len(automat) - 1; i++ {
		for j := i + 1; j < len(automat); j++ {
			if (*pi)[automat[i].i] == (*pi)[automat[j].i] && Find(automat[i]) != Find(automat[j]) {
				eq := true
				for c := 0; c < len(automat[0].outs); c++ {
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
	pi := make([]*State, len(automat))
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
			for i := 0; i < len(automat[0].outs); i++ {
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

func DFS(s *State, num int) {
	s.i = num
	s.marked = true

	for i := 0; i < len(s.outs); i++ {
		if !s.trans[i].marked {
			DFS(s.trans[i], num + 1)
		}
	}
}

func main() {
	fmt.Scanf("%d", &n1)
	fmt.Scanf("%d", &m1)
	fmt.Scanf("%d", &q10)

	automat1 := make([]*State, n1)

	for i := 0; i < n1; i++ {
		automat1[i] = &State{i, nil, 0, false, make([]*State, m1), make([]string, m1)}
	}

	for i := 0; i < n1; i++ {
		for j := 0; j < m1; j++ {
			var t int
			fmt.Scanf("%d", &t)
			automat1[i].trans[j] = automat1[t]
		}
	}

	for i := 0; i < n1; i++ {
		for j := 0; j < m1; j++ {
			fmt.Scanf("%s", &automat1[i].outs[j])
		}
	}

	min_automat1 := AufenkampHohn(automat1)

	for _, q := range(min_automat1) {
		if q.i == q10 {
			DFS(q, 0)
			break
		}
	}
	
	for i := 0; i < len(min_automat1) - 1; i++ {
		for j := i + 1; j < len(min_automat1); j++ {
			if min_automat1[j].i < min_automat1[i].i {
				min_automat1[j], min_automat1[i] = min_automat1[i], min_automat1[j]
			}
		}
	}

	fmt.Scanf("%d", &n2)
	fmt.Scanf("%d", &m2)
	fmt.Scanf("%d", &q20)

	automat2 := make([]*State, n2)

	for i := 0; i < n2; i++ {
		automat2[i] = &State{i, nil, 0, false, make([]*State, m2), make([]string, m2)}
	}

	for i := 0; i < n2; i++ {
		for j := 0; j < m2; j++ {
			var t int
			fmt.Scanf("%d", &t)
			automat2[i].trans[j] = automat2[t]
		}
	}

	for i := 0; i < n2; i++ {
		for j := 0; j < m2; j++ {
			fmt.Scanf("%s", &automat2[i].outs[j])
		}
	}

	min_automat2 := AufenkampHohn(automat2)

	for _, q := range(min_automat2) {
		if q.i == q20 {
			DFS(q, 0)
			break
		}
	}
	
	for i := 0; i < len(min_automat2) - 1; i++ {
		for j := i + 1; j < len(min_automat2); j++ {
			if min_automat2[j].i < min_automat2[i].i {
				min_automat2[j], min_automat2[i] = min_automat2[i], min_automat2[j]
			}
		}
	}

	if len(min_automat1) != len(min_automat2) || m1 != m2 {
		fmt.Printf("NOT EQUAL\n")
		os.Exit(0)
	} else {
		for i := 0; i < len(min_automat1); i++ {
			for j := 0; j < m1; j++ {
				if min_automat2[i].trans[j].i != min_automat2[i].trans[j].i ||
				   min_automat2[i].outs[j] != min_automat2[i].outs[j] {
					fmt.Printf("NOT EQUAL\n")
					os.Exit(0)
				}
			}
		}
	}

	fmt.Printf("EQUAL\n")
}