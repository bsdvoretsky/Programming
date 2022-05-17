package main
import (
	"fmt"
	"bufio"
    "os"
    "strings"
)

var input_str string
var input_pos = 0

func Expr() int {
	q := 1
	if input_str[input_pos] == '(' {
		input_pos++
		res := 0
		if input_str[input_pos] == '*' {
			input_pos++
			res = Expr()
			for q != 0 {
				input_pos++
				if input_str[input_pos] == '(' {
					q++
				} else if input_str[input_pos] == ')' {
					q--
				}
				if q != 0 {
					res *= Expr()
				}
			}
		} else if input_str[input_pos] == '+' {
			input_pos++
			res = Expr()
			for q != 0 {
				input_pos++
				if input_str[input_pos] == '(' {
					q++
				} else if input_str[input_pos] == ')' {
					q--
				}
				if q != 0 {
					res += Expr()
				}
			}
		} else if input_str[input_pos] == '-' {
			input_pos++
			res = Expr()
			for q != 0 {
				input_pos++
				if input_str[input_pos] == '(' {
					q++
				} else if input_str[input_pos] == ')' {
					q--
				}
				if q != 0 {
					res -= Expr()
				}
			}
		}
		return res
	} else if input_str[input_pos] != ' ' {
		return int(input_str[input_pos]) - 48
	}
	input_pos++
	return Expr()
}

func main() {
	input_str, _ = bufio.NewReader(os.Stdin).ReadString('\n')
    input_str = strings.Trim(input_str, "\n")
	fmt.Printf("%d\n", Expr())
}