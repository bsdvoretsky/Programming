; <Program>  ::= <Articles> <Body> .
; <Articles> ::= <Article> <Articles> | .
; <Article>  ::= define word <Body> end .
; <Body>     ::= if <Body> endif <Body> | integer <Body> | word <Body> | .

(define return #f)

(define (find-tail xs target)
  (if (equal? (car xs) target)
      (cdr xs)
      (find-tail (cdr xs) target)))

(define (find-head xs target)
  (let loop ((xs xs) (acc '()))
    (and (not (null? xs))
         (if (equal? (car xs) target)
             acc
             (loop (cdr xs) (append acc (list (car xs))))))))
            
(define (tail-endif program)
  (let loop ((program program) (depth -1))
    (if (null? program) #f
        (let ((word (car program)))
          (cond
            ((and (equal? word 'endif) (zero? depth)) (cdr program))
            ((equal? word 'endif) (loop (cdr program) (- depth 1)))
            ((equal? word 'if) (loop (cdr program) (+ depth 1)))
            (else (loop (cdr program) depth)))))))
            
(define (last xs)
  (list-ref xs (- (length xs) 1)))

(define (head xs n)
  (if (or (= n -1) (null? xs))
      '()
      (cons (car xs) (head (cdr xs) (- n 1)))))

(define (push xs x)
  (append xs (list x)))

(define (parse program)
  (call-with-current-continuation
   (lambda (x)
     (set! return x)
     (let ((program (vector->list program)))
       (if (equal? (car program) 'define)
           (let ((articles (parse-articles program)))
             (cons (head articles (- (length articles) 2))
                   (list (parse-body (last articles)))))
           (cons '() (list (parse-body program))))))))

(define (parse-articles program)
  (let loop ((program program))
    (if (not (null? program))
        (let ((word (car program)) (other (cdr program)))
          (if (equal? word 'define)
              (if (null? other) (return #f)
                  (if (member (car other) '(if endif)) (return #f)
                      (let ((head (find-head (cdr other) 'end)))
                        (if (not head) (return #f)
                            (cons (cons (car other) (list (parse-body head)))
                                  (loop (find-tail (cdr other) 'end)))))))
              (list program)))
        (list program))))

(define (parse-body program)
  (let loop ((program program) (parsed '()) (stack '()))
    (if (not (null? program))
        (let ((word (car program)))
          (cond
            ((equal? word 'if)
             (let ((tail (tail-endif program)))
               (if (not tail) (return #f)
                   (loop tail (push parsed (list 'if (loop (cdr program) '() (cons 'if stack)))) stack))))
            ((equal? word 'endif)
             (if (and (not (null? stack)) (equal? (car stack) 'if))
                 parsed
                 (return #f)))
            ((member word '(define end)) (return #f))
            (else (loop (cdr program) (push parsed word) stack))))
        parsed)))

; TESTS

(display "TEST 1") (newline)
(parse #(1 2 +))
(newline)

(display "TEST 2") (newline)
(parse #(x dup 0 swap if drop -1 endif)) 
(newline)

(display "TEST 3") (newline)
(parse #( define -- 1 - end 
           define =0? dup 0 = end 
           define =1? dup 1 = end 
           define factorial 
           =0? if drop 1 exit endif 
           =1? if drop 1 exit endif 
           dup -- 
           factorial 
           * 
           end 
           0 factorial 
           1 factorial 
           2 factorial 
           3 factorial 
           4 factorial ))
(newline)

(display "TEST 4") (newline)
(parse #(2 5 mod 2 - if 1 1 + 2 = if 999 endif endif))
(newline)
