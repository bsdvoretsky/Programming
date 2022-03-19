package main
import (
	"fmt" 
	"os"
	"sort"
)

type Candidate struct {
	team int
	order int 
	links []*Candidate
}

var first_team, second_team []int
var n int

func makeComponent(k *Candidate, t int) {
	k.team = t
	if t == 1 {
		first_team = append(first_team, k.order)
	} else {
		second_team = append(second_team, k.order)
	}
	for i := 0; i < n; i++ {
		if k.links[i] != nil && k.links[i].team == 0 {
			makeComponent(k.links[i], 3 - t)
		} else if k.links[i] != nil && k.links[i].team == t {
			fmt.Println("No solution")
			os.Exit(0)
		}
	}
}

func main() {
	var c byte
	fmt.Scanf("%d", &n)
	candidates := make([]Candidate, n)
	for i := 0; i < n; i++ {
		candidates[i].links = make([]*Candidate, n)
		candidates[i].order = i + 1
	}
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			fmt.Scanf("%c", &c)
			if c == '+' {
				candidates[i].links[j] = &candidates[j]
			}
		}
		fmt.Scanf("%c", &c)
	}
	for i := 0; i < n; i++ {
		if candidates[i].team == 0 {
			if len(first_team) <= len(second_team) {
				makeComponent(&candidates[i], 1)
			} else {
				makeComponent(&candidates[i], 2)
			}
		}
	}
	if len(first_team) <= len(second_team) {
		sort.Ints(first_team)
		for _, t := range(first_team) {
			fmt.Printf("%d ", t)
		}
		fmt.Printf("\n")
	} else {
		sort.Ints(second_team)
		for _, t := range(second_team) {
			fmt.Printf("%d ", t)
		}
		fmt.Printf("\n")
	}
}