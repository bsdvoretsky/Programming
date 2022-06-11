package main

import (
	"fmt"
	"os"
	"bufio"
)

var (
	pos int
	prog string
	bufstdin *bufio.Scanner
	bufstdout *bufio.Writer
)

func error() {
	fmt.Fprint(bufstdout, "syntax error at ", pos, "\n")
	bufstdout.Flush()
	os.Exit(0)
}

func Expr() int {
	if prog[pos] == '(' {
		pos++
		if pos < len(prog) {
			c := prog[pos]
			pos++
			if pos >= len(prog) {
				error()
			}
			b := Expr()
			if c == '+' {
				for pos < len(prog) - 1 && prog[pos] != ')' {
					v := Expr()
					b += v	
				}
			} else if c == '-' {
				for pos < len(prog) - 1 && prog[pos] != ')' {
					v := Expr()
					b -= v		
				}
			} else if c == '*' {
				for pos < len(prog) - 1 && prog[pos] != ')' {
					v := Expr()
					b *= v	
				}
			}
			if prog[pos] == ')' {
				pos++
				return b
			} else {
				error()
			}
		} else {
			error()
		}
	} else if prog[pos] >= '0' &&
			  prog[pos] <= '9' {
		return Number()
	} else {
		error()
	}
	return -1
}

func Number() int {
	pos++
	return int(prog[pos - 1]) - 48
}

func main() {
	pos = 0
	bufstdin = bufio.NewScanner(os.Stdin)
	bufstdout = bufio.NewWriter(os.Stdout)
	prog = ""
	bufstdin.Split(bufio.ScanWords)
	for bufstdin.Scan() {
		prog += string(bufstdin.Bytes())
	}
	fmt.Fprint(bufstdout, Expr(), "\n")
	bufstdout.Flush()
}