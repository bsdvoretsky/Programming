package main
import (
	"fmt"
	"math"
	"sort"
)

type deviders []int

func (d deviders) Len() int {return len(d)}
func (d deviders) Swap(i, j int) {d[i], d[j] = d[j], d[i]}
func (d deviders) Less(i, j int) bool {return d[i] < d[j]}

var x int
func main() {
	var d deviders
	fmt.Scanf("%d", &x)
	for i := int(math.Sqrt(float64(x))); i > 0; i-- {
		if x % i == 0 {
			if i * i != x {
				d = append(d, i)
				d = append(d, x / i)
			} else {
				d = append(d, i)
			}
		}
	}
	sort.Sort(d)
	fmt.Printf("graph deviders {\n")
	for _, c := range(d) {
		fmt.Printf("    %d;\n", c)
	}
	for i := len(d) - 1; i > 0; i-- {
		for j := i - 1; j >= 0; j-- {
			if d[i] % d[j] == 0 {
				fl := true
				for k := i - 1; k > j; k-- {
					if (d[k] % d[j] == 0 && d[i] % d[k] == 0) {
						fl = false
						break
					}
				}
				if fl {
					fmt.Printf("    %d -- %d;\n", d[i], d[j])
				}
			}
		}
	}
	fmt.Printf("}\n")
} 