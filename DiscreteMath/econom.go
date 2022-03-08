package main
import "fmt"

var input_str = "(#($(#xy)($(#ab)(#ab)))(@z($(#ab)(#ab))))"
var input_pos = 0
var buff []string

func economExpr() int {
	s := ""
	t := 1
	q := -1
	if input_str[input_pos] == '(' {
		m := input_pos
		for input_str[input_pos] != ')' || t != 0 {
			s += string(input_str[input_pos])
			input_pos++
			if input_str[input_pos] == '(' {
				t++
			} else if input_str[input_pos] == ')' {
				t--
			}
			if t == 0 {
				s += string(input_str[input_pos])
				break
			}
		}
		fl := false
		for _, c := range(buff) {
			if s == c {
				fl = true
				break
			}
		}
		if !fl {
			input_pos = m
			buff = append(buff, s)
			input_pos++
			for input_str[input_pos] != ')' {
				if input_str[input_pos] == '(' {
					q += economExpr() + 1
				} 
				if input_str[input_pos] >= 97 &&
						input_str[input_pos] <= 122 {
					q += 1
				}
				input_pos++
			}
			return q
		} else {
			return economExpr()
		}
	}
	return 0
}

func main () {
	fmt.Printf("%d\n", economExpr())
}