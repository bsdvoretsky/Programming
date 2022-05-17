package main

import (
	"bufio"
	"fmt"
	"os"
)

type Lexem struct {
	Tag
	Image string
}

type Tag int

const (
	NUMBER Tag = 1 << iota // Целое число
	VAR                    // Имя переменной
	PLUS                   // Знак +
	MINUS                  // Знак -
	MUL                    // Знак *
	DIV                    // Знак /
	LPAREN                 // Левая круглая скобка
	RPAREN                 // Правая круглая скобка
	EQUAL                  // Знак =
	COMMA				   // Знак ,
)

var (
	pos 	    int       // Индекс текущего символа в формуле
	buf		    string    // Имя переменной или целое число
	lexemes     []Lexem   // Срез лексем
	graph       Graph     // Граф с формулами
	curArr      *[]string // Текущий массив с переменными
	curFormula  Formula   // Текущая формула
	pL 		    int       // Число переменных в текущей формуле
	pR          int       // Число определений в текущей формуле
	sortedGraph Graph     // Отсортированный граф
)

type Formula struct {
	content     string   // Формула
	fullContent string   // Формула с пробелами
	leftPart    []string // Переменные в левой части
	rightPart   []string // Переменные в правой части
	color 	    string   // Цвет
	parents		int 	 // Число родителей формулы
	edges       *Edge    // Рёбра
}

type Edge struct {
	f    *Formula // Формула
	next *Edge    // Следующее ребро
}

type Graph []*Formula

func error() {
	fmt.Println("syntax error")
	os.Exit(0)
}

func isLetter(sym byte) bool {
	return (sym >= 'A' && sym <= 'Z') || (sym >= 'a' && sym <= 'z')
}

func isDigit(sym byte) bool {
	return sym >= '0' && sym <= '9'
}

func ParseFormula() {
	VarList()

	if pos >= len(curFormula.content) || curFormula.content[pos] != '=' {
		error()
	}

	lexemes = append(lexemes, Lexem{EQUAL, "="})
	pos++

	curArr = &curFormula.rightPart

	ExprList()

	if pos < len(curFormula.content) {
		error()
	}
}

func VarList() {
	Var()

	if pos < len(curFormula.content) && curFormula.content[pos] == ',' {
		lexemes = append(lexemes, Lexem{COMMA, ","})
		pos++

		pL++

		VarList()
	}
}

func ExprList() {
	Expr1()

	if pos < len(curFormula.content) && curFormula.content[pos] == ',' {
		lexemes = append(lexemes, Lexem{COMMA, ","})
		pos++

		pR++

		ExprList()
	}
}

func Var() {
	if pos >= len(curFormula.content) {
		error()
	}

	if !isLetter(curFormula.content[pos]) {
		error()
	}

	for pos < len(curFormula.content) && (isLetter(curFormula.content[pos]) || isDigit(curFormula.content[pos])) {
		buf += string(curFormula.content[pos])
		pos++
	}

	lexemes = append(lexemes, Lexem{VAR, buf})
	*curArr = append(*curArr, buf)
	buf = ""
}

func Expr1() {
	Term1()

	Expr2()
}

func Term1() {
	Factor()

	Term2()
}

func Expr2() {
	if pos >= len(curFormula.content) {
		return
	}

	if curFormula.content[pos] == '+' {
		lexemes = append(lexemes, Lexem{PLUS, "+"})
		pos++

		Term1()

		Expr2()

	} else if curFormula.content[pos] == '-' {
		lexemes = append(lexemes, Lexem{MINUS, "-"})
		pos++

		Term1()

		Expr2()
	}
}

func Factor() {
	if pos >= len(curFormula.content) {
		error()
	}

	if isDigit(curFormula.content[pos]) {
		Number()
	} else if isLetter(curFormula.content[pos]) {
		Var()
	} else if curFormula.content[pos] == '(' {
		lexemes = append(lexemes, Lexem{LPAREN, "("})
		pos++

		Expr1()

		if pos >= len(curFormula.content) || curFormula.content[pos] != ')' {
			error()
		}

		lexemes = append(lexemes, Lexem{RPAREN, ")"})
		pos++
	} else if curFormula.content[pos] == '-' {
		lexemes = append(lexemes, Lexem{MINUS, "-"})
		pos++

		Factor()
	} else {
		error()
	}
}

func Term2() {
	if pos >= len(curFormula.content) {
		return
	}

	if curFormula.content[pos] == '*' {
		lexemes = append(lexemes, Lexem{MUL, "*"})
		pos++

		Factor()

		Term2()

	} else if curFormula.content[pos] == '/' {
		lexemes = append(lexemes, Lexem{DIV, "/"})
		pos++

		Factor()

		Term2()
	}
}

func Number() {
	if pos >= len(curFormula.content) {
		error()
	}

	for pos < len(curFormula.content) && isDigit(curFormula.content[pos]) {
		buf += string(curFormula.content[pos])
		pos++
	}

	lexemes = append(lexemes, Lexem{NUMBER, buf})
	buf = ""
}

func findInLeftPart(w *Formula, s string) (bool, *Formula) {
	q := 0
	var cf *Formula
	cf = nil
	for _, f := range(graph) {
		for _, c := range(f.leftPart) {
			if c == s && f == w {
				error()
			}
			if c == s {
				q++
				cf = f
				if q > 1 {
					error()
				}
			}
		}
	}
	if q == 1 {
		return true, cf
	}
	return false, cf
}

func DFS(f *Formula) {
	f.color = "grey"
	for e := f.edges; e != nil; e = e.next {
		if e.f.color == "grey" {
			fmt.Printf("cycle\n")
			os.Exit(0)
		} else if e.f.color == "white" {
			DFS(e.f)
		}
	}
	f.color = "black"
	t := f
	sortedGraph = append(sortedGraph, t)
}

func main() {
	graph = Graph{}
	curArr = nil
	pos = 0
	pL = 1
	pR = 1
	buf = ""
	sc := bufio.NewScanner(os.Stdin)

	for sc.Scan() {
		curFormula = Formula{"", "", []string{}, []string{}, "white", 0, nil}
		for _, sym := range(sc.Text()) {
			if sym != ' ' && sym != '\t' {
				curFormula.content += string(sym)
			}
			curFormula.fullContent += string(sym)
		}
		curArr = &curFormula.leftPart
		ParseFormula()
		if pL != pR {
			error()
		}
		t := curFormula
		graph = append(graph, &t)
		pos = 0
		pL = 1
		pR = 1
	}

	for _, f := range(graph) {
		for _, c := range(f.rightPart) {
			ok, cf := findInLeftPart(f, c)
			if !ok {
				error()
			}
			e := f.edges
			if e == nil {
				f.edges = &Edge{cf, nil}
				cf.parents++
			} else {
				fl := true
				if e.f == cf {	
					break
				}
				for e.next != nil {
					if e.f == cf {	
						fl = false
						break
					}
					e = e.next
				}
				if fl {
					e.next = &Edge{cf, nil}
					cf.parents++
				}
		 	}
		}
	}
	
	sortedGraph = Graph{}

	for _, f := range(graph) {
		if f.parents == 0 {
			DFS(f)
		}
	}

	for _, f := range(sortedGraph) {
		fmt.Println(f.fullContent)
	}
}
