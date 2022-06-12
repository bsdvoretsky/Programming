package main

import (
	"fmt"
	"os"
	"sort"
	"bufio"
)

type State struct {
	i       int
	parent  *State
	depth   int
	marked  bool
	trans   States
	outs    []string
}

type States []*State

func (s States) Len() int { return len(s) }
func (s States) Less(i, j int) bool { return s[i].i < s[j].i }
func (s States) Swap(i, j int) { s[i], s[j] = s[j], s[i] }

var (
	n1, m1, q10 int
	n2, m2, q20 int
	num int
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

func Split1(automat States, mt *int, pi *States) {
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

func Split(automat States, mt *int, pi *States) {
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

func AufenkampHohn(automat States) States {
	var m1 int
	pi := make(States, len(automat))
	Split1(automat, &m1, &pi)

	for {
		var m2 int
		Split(automat, &m2, &pi)
		if m1 == m2 {
			break
		}
		m1 = m2
	}

	ans := States{}

	for _, q := range(automat) {
		qt := pi[q.i]
		if !find(ans, qt) {
			ans = append(ans, qt)
			for i := 0; i < len(automat[0].outs); i++ {
				qt.trans[i] = pi[q.trans[i].i]
				qt.outs[i] = q.outs[i]
			}
		}
	}
	return ans
}

func find(automat States, q *State) bool {
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

	for i := 0; i < len(s.outs); i++ {
		if !s.trans[i].marked {
			DFS(s.trans[i])
		}
	}
}

func main() {
	num = 0

	bufstdin := bufio.NewReader(os.Stdin)

	fmt.Fscan(bufstdin, &n1, &m1, &q10)

	automat1 := make(States, n1)

	for i := 0; i < n1; i++ {
		automat1[i] = &State{i, nil, 0, false, make(States, m1), make([]string, m1)}
	}

	for i := 0; i < n1; i++ {
		for j := 0; j < m1; j++ {
			var t int
			fmt.Fscan(bufstdin, &t)
			automat1[i].trans[j] = automat1[t]
		}
	}

	for i := 0; i < n1; i++ {
		for j := 0; j < m1; j++ {
			var s string
			fmt.Fscan(bufstdin, &s)
			automat1[i].outs[j] = s
		}
	}

	min_automat1 := AufenkampHohn(automat1)

	for _, q := range(min_automat1) {
		fl := true
		for i := 0; i < m1; i++ {
			if q.outs[i] != automat1[q10].outs[i] {
				fl = false
				break
			}
		}
		if fl {
			DFS(q)
			break
		}
	}
	
	sort.Sort(min_automat1)

	num = 0

	fmt.Fscan(bufstdin, &n2, &m2, &q20)

	automat2 := make(States, n2)

	for i := 0; i < n2; i++ {
		automat2[i] = &State{i, nil, 0, false, make(States, m2), make([]string, m2)}
	}

	for i := 0; i < n2; i++ {
		for j := 0; j < m2; j++ {
			var t int
			fmt.Fscan(bufstdin, &t)
			automat2[i].trans[j] = automat2[t]
		}
	}

	for i := 0; i < n2; i++ {
		for j := 0; j < m2; j++ {
			var s string
			fmt.Fscan(bufstdin, &s)
			automat2[i].outs[j] = s
		}
	}

	min_automat2 := AufenkampHohn(automat2)

	for _, q := range(min_automat2) {
		fl := true
		for i := 0; i < m2; i++ {
			if q.outs[i] != automat2[q20].outs[i] {
				fl = false
			}
		}
		if fl {
			DFS(q)
			break
		}
	}
	
	sort.Sort(min_automat2)

	if len(min_automat1) != len(min_automat2) || m1 != m2 {
		fmt.Printf("NOT EQUAL\n")
		os.Exit(0)
	} else {
		for i := 0; i < len(min_automat1); i++ {
			for j := 0; j < m1; j++ {
				if min_automat1[i].trans[j].i != min_automat2[i].trans[j].i ||
				   min_automat1[i].outs[j] != min_automat2[i].outs[j] {
					fmt.Printf("NOT EQUAL\n")
					os.Exit(0)
				}
			}
		}
	}

	fmt.Printf("EQUAL\n")
}