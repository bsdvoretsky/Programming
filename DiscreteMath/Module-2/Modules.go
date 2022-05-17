package main
import (
	"fmt"
	"os"
	"bufio"
)

type Vertices []*Vertex

type Vertex struct {
	name string
	edges *Edge
	comp int
	T1 int
	low int
}

type Edge struct {
	v *Vertex
	next *Edge
}

var lexemes, funcs, vars []string
var line string
var pos, cur_1, cur_2, time, count int
var vertices Vertices
var s Stack


type Stack struct {
	vertices Vertices
	count int
}

func (s *Stack) InitStack (n int) {
	s.vertices = make(Vertices, n)
	s.count = 0
}

func (s *Stack) Push (v *Vertex) {
	s.count++
	s.vertices[s.count - 1] = v
}

func (s *Stack) Pop () *Vertex {
	s.count--
	return s.vertices[s.count]
}

func Tarjan(g Vertices) {
	s.InitStack(len(g))
	for _, v := range(g) {
		if v.T1 == 0 {
			VisitVertex_Tarjan(g, v)
		}
	}
}

func VisitVertex_Tarjan(g Vertices, v *Vertex) {
	v.T1 = time
	v.low = time
	time++
	s.Push(v)
	e := v.edges
	for e != nil {
		u := e.v
		if u.T1 == 0 {
			VisitVertex_Tarjan(g, u)
		}
		if u.comp == -1 && v.low > u.low {
			v.low = u.low
		}
		e = e.next
	}
	if v.T1 == v.low {
		u := s.Pop()
		u.comp = count
		for u != v {
			u = s.Pop()
			u.comp = count
		}
		count++
	}
}

func find(name string) int {
	for i, f := range(vertices) {
		if f.name == name {
			return i
		}
	}
	return -1
}

func AddLex(lex string) {
	lexemes = append(lexemes, lex)
	pos++
	Space()
}

func Error() {
	fmt.Printf("error\n")
	os.Exit(0)
}

func Program() {
	Function()
	if pos < len(line) - 1 {
		Space()
		Program()
	}
}

func Function() {
	Ident()
	if find(lexemes[len(lexemes)-1]) == -1 {
		vertices = append(vertices, &Vertex{lexemes[len(lexemes)-1], nil, -1, 0, 0})
		cur_1 = len(vertices) - 1
	} else {
		cur_1 = find(lexemes[len(lexemes)-1])
	}
	Space()
	if line[pos] == '(' {
		AddLex("(")
		FormalArgsList()
		if line[pos] == ')' {
			AddLex(")")
			if line[pos] == ':' {
				pos++
				if pos < len(line) && line[pos] == '=' {
					AddLex(":=")
					Expr()
					if line[pos] == ';' {
						lexemes = append(lexemes, ";")
						pos++
					} else {
						Error()
					}
				} else {
					Error()
				}
			} else {
				Error()
			}
		} else {
			Error()
		}
	} else {
		Error()
	}
}

func Ident() {
	temp := []rune{}
	if (line[pos] >= 'a' && line[pos] <= 'z') ||
	   (line[pos] >= 'A' && line[pos] <= 'Z') {
	    for pos < len(line) &&
	    	(line[pos] >= 'a' && line[pos] <= 'z') ||
			(line[pos] >= 'A' && line[pos] <= 'Z') ||
			(line[pos] >= '0' && line[pos] <= '9') {
			temp = append(temp, rune(line[pos]))
			pos++
		}
		if pos >= len(line) {
			Error()
		}
	} else {
		Error()
	}
	pos--
	AddLex(string(temp))
}

func FormalArgsList() {
	if !(line[pos] == ')') {
		IdentList()
	}
}

func IdentList() {
	Ident()
	if line[pos] == ',' {
		AddLex(",")
		IdentList()
	}
}

func Expr() {
	ComparisonExpr()
	if line[pos] == '?' {
		AddLex("?")
		ComparisonExpr()
		if line[pos] == ':' {
			AddLex(":")
			Expr()
		}
	}
}

func ComparisonExpr() {
	ArifmExpr()
	if line[pos] == '=' {
		AddLex("=")
		ArifmExpr()
	} else if line[pos] == '<' {
		pos++
		if pos < len(line) && line[pos] == '>' {
			AddLex("<>")
			ArifmExpr()
		} else if pos < len(line) && line[pos] == '=' {
			AddLex("<=")
			ArifmExpr()
		} else {
			AddLex("<")
			ArifmExpr()
		}
	} else if line[pos] == '>' {
		pos++
		if pos < len(line) && line[pos] == '=' {
			AddLex(">=")
			ArifmExpr()
		} else {
			AddLex(">")
			ArifmExpr()
		}
	}
}

func ArifmExpr() {
	Term()
	if line[pos] == '+' {
		AddLex("+")
		ArifmExpr()
	} else if line[pos] == '-' {
		AddLex("-")
		ArifmExpr()
	}
}

func Term() {
	Factor()
	if line[pos] == '*' {
		AddLex("*")
		Factor()
	} else if line[pos] == '/' {
		AddLex("/")
		Factor()
	}
}

func Factor() {
	if line[pos] == '-' {
		AddLex("-")
		Factor()
	} else if line[pos] == '(' {
		AddLex("(")
		Expr()
		if line[pos] == ')' {
			AddLex(")")
		} else {	
			Error()
		}
	} else if (line[pos] >= 'a' && line[pos] <= 'z') || 
			  (line[pos] >= 'A' && line[pos] <= 'Z') {
		Ident()
		if line[pos] == '(' {
			if find(lexemes[len(lexemes)-1]) == -1 {
				vertices = append(vertices, &Vertex{lexemes[len(lexemes)-1], nil, -1, 0, 0})
				cur_2 = len(vertices) - 1
			} else {
				cur_2 = find(lexemes[len(lexemes)-1])
			}
			e := vertices[cur_1].edges
			if e == nil {
				vertices[cur_1].edges = &Edge{vertices[cur_2], nil}
			} else {
				for e.next != nil {
					e = e.next
				}
			e.next = &Edge{vertices[cur_2], nil}
			}
			AddLex("(")
			ActualArgsList()
			if line[pos] == ')' {
				AddLex(")")
			} else {
				Error()
			}
		}
	} else {
		Number()
		Space()
	}
}

func Number() {
	temp := []rune{}
	for pos < len(line) && line[pos] >= '0' && line[pos] <= '9' {
		temp = append(temp, rune(line[pos]))
		pos++
	}
	if pos >= len(line) {
		Error()
	} else {
		pos--
		AddLex(string(temp))
		Space()
	}
}

func ActualArgsList() {
	if !(line[pos] == ')') {
		ExprList()
	}
}

func ExprList() {
	Expr()
	if line[pos] == ',' {
		AddLex(",")
		ExprList()
	}
}

func Space() {
	for pos < len(line) && line[pos] == ' ' || line[pos] == '\t' {
		pos++
	}
}

func main() {
	time = 1
	count = 0

	vertices = Vertices{}
	lexemes = []string{}
	pos = 0

	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line = scanner.Text()
		if len(line) > 0 {
			pos = 0
			Space()
			Program()
		}
	} 

	Tarjan(vertices)

	fmt.Printf("%d\n", count)
}