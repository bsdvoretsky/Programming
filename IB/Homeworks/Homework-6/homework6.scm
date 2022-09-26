(define (head xs n)
  (if (<= n 0)
      '()
      (cons (car xs) (head (cdr xs) (- n 1)))))

(define (alphabetic? word)
  (let ((code (char->integer word)))
    (or (and (>= code 97) (<= code 122))
        (and (>= code 65) (<= code 90)))))

(define (numeric? char)
  (let ((code (char->integer char)))
    (and (>= code 48) (<= code 57))))

(define return 0)

; 1. Лексический анализ
; <expr> ::= +<expr> | -<expr> | *<expr> | /<expr> | (<expr> |
; | )<expr> | <whitespace><expr> | <var><expr> | <num><expr> | .
; <whitespace> ::= #\space | #\tab | #\newline
; <var> ::= <alphabetic><var> | <alphabetic>
; <num> ::= <num>e+<num> | <num>e-<num> | <num>.<num> | 0 | 1 |
; | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | <num><num>
; <alphabetic> ::= a | A | b | B | ... | z | Z | <alphabetic><alphabetic>
(define (tokenize expr)
  (define (var-name-end-index lexpr)
    (let loop ((lexpr lexpr) (i 0))
      (if (or (null? lexpr) (not (alphabetic? (car lexpr))))
          i
          (loop (cdr lexpr) (+ 1 i)))))
  (define (num-end-index lexpr)
    (let loop ((lexpr lexpr) (i 0) (prev-word #f) (floating-point #f))
      (if (null? lexpr) i
          (let ((word (car lexpr)))
            (if (or (numeric? word) (member word '(#\e #\.))
                    (and (member word '(#\+ #\-)) (equal? prev-word #\e)))
                (if (equal? word #\.)
                    (if floating-point
                        (return #f)
                        (loop (cdr lexpr) (+ i 1) word #t))
                    (loop (cdr lexpr) (+ i 1) word floating-point))
                i)))))
  (let ((lexpr (string->list expr)))
    (define (loop lexpr out)
      (if (null? lexpr)
          out
          (let ((word (car lexpr)))
            (cond
              ((member word '(#\+ #\- #\^ #\* #\/)) (loop (cdr lexpr) (append out (list (string->symbol (string word))))))
              ((member word '(#\( #\))) (loop (cdr lexpr) (append out (list (string word)))))
              ((char-whitespace? word) (loop (cdr lexpr) out))
              ((alphabetic? word)
               (let ((index (var-name-end-index lexpr)))
                 (loop (list-tail lexpr index) (append out (list (string->symbol (list->string (head lexpr index))))))))
              ((numeric? word)
               (let ((index (num-end-index lexpr)))
                 (loop (list-tail lexpr index) (append out (list (string->number (list->string (head lexpr index))))))))
              (else (return #f))))))
    (call-with-current-continuation
     (lambda (c)
       (set! return c)
       (loop lexpr '())))))

; 2. Синтаксический анализ
; Expr    ::= Term Expr' .
; Expr'   ::= AddOp Term Expr' | .
; Term    ::= Factor Term' .
; Term'   ::= MulOp Factor Term' | .
; Factor  ::= Power Factor' .
; Factor' ::= PowOp Power Factor' | .
; Power   ::= value | "(" Expr ")" | unaryMinus Power .
(define (parse tokens)
  (define i 0)
  (define bracket-index #f)
  (define (inc) (set! i (+ i 1)))
  (define (in-bounds?) (< i (length tokens)))
  (define (current) (list-ref tokens i))

  (define (has-close-bracket?)
    (let loop ((i i) (offset 0))
      (and (not (= i (length tokens)))
           (let ((current (list-ref tokens i)))
             (cond
               ((and (equal? current ")") (zero? offset)))
               ((equal? current "(") (loop (+ i 1) (+ offset 1)))
               ((equal? current ")") (loop (+ i 1) (- offset 1)))
               (else (loop (+ i 1) offset)))))))
  
  (define (expr open-bracket-index)
    (let loop ((T (term)))
      (if (and (in-bounds?) (or (equal? (current) '-) (equal? (current) '+)))
          (let ((op (current)))
            (inc)
            (if (not (in-bounds?)) (return #f))
            (loop (list T op (term))))
          (if (in-bounds?)
              (if (and (equal? (current) ")") open-bracket-index)
                  (begin (inc) T)
                  (return #f))
              T))))

  (define (term)
    (let loop ((F (factor)))
      (if (and (in-bounds?) (or (equal? (current) '/) (equal? (current) '*)))
          (let ((op (current)))
            (inc)
            (loop (list F op (factor))))
          F)))

  (define (factor)
    (let ((P (power)))
      (if (and (in-bounds?) (equal? (current) '^))
          (begin (inc) (list P '^ (factor)))
          P)))

  (define (power)
    (if (not (in-bounds?))(return #f))
    (let ((current (current)))
      (inc)
      (cond
        ((equal? current '-) (list '- (power)))
        ((equal? current "(") (if (has-close-bracket?)
                                  (expr (- i 1))
                                  (return #f)))
        ((number? current) current)
        ((symbol? current) current)
        (else (return #f)))))

  (call-with-current-continuation
   (lambda (c)
     (set! return c)
     (expr #f))))
; 3. Преобразование дерева разбора в выражение на Scheme
(define (tree->scheme tree)
  (if (and (list? tree) (= (length tree) 3))
      (let ((a (car tree)) (op (cadr tree)) (b (caddr tree)))
        (let ((op (if (equal? op '^) 'expt op)))
          (list op (tree->scheme a) (tree->scheme b))))
      tree))