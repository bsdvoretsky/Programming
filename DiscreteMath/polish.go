package main
import "fmt"

var input_str = "(+ (* 1 2) (* 9 0) 2 (- 1 (- 1 0)))"
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
	fmt.Printf("%d\n", Expr())
}