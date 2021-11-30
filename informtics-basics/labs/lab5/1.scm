(define ie (interaction-environment))

(define (arithm? op)
  (cond
    ((or (equal? op '+) (equal? op '-)  (equal? op '*) (equal? op '/))
     op)
    ((equal? op 'mod)
     'modulo)
    (else #f)))

(define (end-pos program n)
  (if (equal? (vector-ref program n) 'end)
      n
      (end-pos program (+ n 1))))

(define (endif-pos program n)
  (if (equal? (vector-ref program n) 'endif)
      n
      (endif-pos program (+ n 1))))

(define (comp-flag op stack)
  (cond
    ((and (equal? op '<)(< (cadr stack) (car stack))) -1)
    ((and (equal? op '>)(> (cadr stack) (car stack))) -1)
    ((and (equal? op '=)(= (cadr stack) (car stack))) -1)
    (else 0)))

(define (comp? op)
  (and (or (equal? op '<) (equal? op '=) (equal? op '>)) op))

(define (replace n stack)
  (set! stack (cons n (cddr stack)))
  stack)

(define (interpret program stack)
  (define (main program n _stack backstack functions)
    (if (= n (vector-length program))
        _stack
        (let ((word (vector-ref program n)))
          (cond
            ((number? word) (main program (+ n 1) (cons word _stack) backstack functions))
            ((arithm? word) (main program (+ n 1) (replace (eval (list (arithm? word) (cadr _stack) (car _stack)) ie) _stack)
                                  backstack functions))
            ((equal? word 'neg) (main program (+ n 1) (cons (-(car _stack)) (cdr _stack)) backstack functions))
            ((comp? word) (main program (+ n 1) (replace (comp-flag (comp? word) _stack) _stack) backstack functions))
            ((equal? word 'not) (main program (+ n 1) (cons (if (= (car _stack) 0) -1 0) (cdr _stack))
                                      backstack functons))
            ((equal? word 'and) (main program (+ n 1) (if (and (= (cadr _stack) -1) (= (car _stack) -1))
                                                          (cons -1 (cdr _stack)) (cons 0 (cdr _stack)))
                                      backstack functons))
            ((equal? word 'or) (main program (+ n 1) (if (and (= (cadr _stack) 0) (= (car _stack) 0))
                                                         (cons 0 (cdr _stack)) (cons -1 (cdr _stack)))
                                     backstack functons))
            ((equal? word 'drop) (main program (+ n 1) (cdr _stack) backstack functions))
            ((equal? word 'swap) (main program (+ n 1) (append (list (cadr _stack) (car _stack)) (cddr _stack))
                                       backstack functions))
            ((equal? word 'dup) (main program (+ n 1) (cons (car _stack) _stack)
                                      backstack functions))
            ((equal? word 'over) (main program (+ n 1) (cons (cadr _stack) _stack)
                                       backstack functions))
            ((equal? word 'rot) (main program (+ n 1) (append (list (caddr _stack) (cadr _stack) (car _stack)) (cdddr _stack))
                                      backstack functions))
            ((equal? word 'depth) (length _stack))
            ((equal? word 'define) (main program (+ (end-pos program n) 1) _stack
                                         backstack (cons (list (vector-ref program (+ n 1)) (+ n 2)) functions)))
            ((or (equal? word 'end) (equal? word 'exit)) (main program (car backstack) _stack (cdr backstack) functions))
            ((equal? word 'if) (main program (if (= (car _stack) 0) (+ (endif-pos program n) 1) (+ n 1)) (cdr _stack)
                                     backstack functions))
            ((equal? word 'endif) (main program (car backstack) _stack backstack functions))
            (else (main program (cadr (assoc word functions)) _stack (cons (+ n 1) backstack) functions))))))
  (main program 0 stack '() '()))

; Tests

(interpret #(   define abs 
                  dup 0 < 
                  if neg endif 
                end 
                abs    )
           '(-9))   

(interpret #(2 3 * 4 5 * +) '())

(interpret #(   define -- 1 - end
                 5 -- --    ) '())

(interpret #(   define abs 
                    dup 0 < 
                    if neg endif 
                end 
                 9 abs 
                -9 abs      ) (quote ()))

(interpret #(   define =0? dup 0 = end 
                define <0? dup 0 < end 
                define signum 
                    =0? if exit endif 
                    <0? if drop -1 exit endif 
                    drop 
                    1 
                end 
                 0 signum 
                -5 signum 
                10 signum       ) (quote ()))

(interpret #(   define -- 1 - end 
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
                4 factorial     ) (quote ()))

(interpret #(   define =0? dup 0 = end 
                define =1? dup 1 = end 
                define -- 1 - end 
                define fib 
                    =0? if drop 0 exit endif 
                    =1? if drop 1 exit endif 
                    -- dup 
                    -- fib 
                    swap fib 
                    + 
                end 
                define make-fib 
                    dup 0 < if drop exit endif 
                    dup fib 
                    swap -- 
                    make-fib 
                end 
                10 make-fib     ) (quote ()))

(interpret #(   define =0? dup 0 = end 
                define gcd 
                    =0? if drop exit endif 
                    swap over mod 
                    gcd 
                end 
                90 99 gcd 
                234 8100 gcd    ) '())

