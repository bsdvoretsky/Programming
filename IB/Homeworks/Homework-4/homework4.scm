(define memoized-factorial
  (let ((known-results '((0 1))))
    (lambda (n)
      (let ((res (assoc n known-results)))
        (if res
            (cadr res)
            (let ((res (* n (memoized-factorial (- n 1)))))
              (set! known-results (cons (list n res) known-results))
              res))))))

; test
(begin
  (display (memoized-factorial 10)) (newline)
  (display (memoized-factorial 50)) (newline))






(define-syntax lazy-cons
  (syntax-rules ()
    ((lazy-cons a b) (cons a (delay b)))))

(define (lazy-car p)
  (car p))

(define (lazy-cdr p)
  (force (cdr p)))

(define (lazy-head xs k)
  (if (not (= k 0))
      (cons (lazy-car xs) (lazy-head (lazy-cdr xs) (- k 1)))
      '()))

(define (lazy-ref xs k)
  (if (not (= k 0))
      (lazy-ref (lazy-cdr xs) (- k 1))
      (lazy-car xs)))

; naturals
(define (naturals start)
  (lazy-cons start (naturals (+ start 1))))


; lazy-factorial
(define (factorials res n)
  (lazy-cons res (factorials (* res (+ n 1)) (+ n 1))))

(define (lazy-factorial n)
  (lazy-ref (factorials 1 1) n))








(define (read-words)
  (let ((res '()) (temp '()))
    (define (loop)
      (let ((char (read-char)))
        (if (eof-object? char)
            (if (not (null? temp))
                (begin (set! res (cons (list->string temp) res))
                       (set! temp '()))
                (reverse res))
            (if (char-whitespace? char)
                (if (not (null? temp))
                    (begin (set! res (cons (list->string temp) res))
                           (set! temp '())
                           (loop))
                    (loop))
                (begin (set! temp (append temp (list char))) (loop))))))
    (loop)))






(define-syntax define-struct
  (syntax-rules ()
    ((define-struct type (v1 ...))
     (let ((ie (interaction-environment)))
       (eval `(define ,(string->symbol (string-append "make-" (symbol->string 'type)))
                ,(lambda (v1 ...) (append (list 'type) (list (list 'v1 v1) ...)))) ie)
       (eval `(define ,(string->symbol (string-append (symbol->string 'type) "?"))
                ,(lambda (p) (and (list? p) (not (null? p)) (equal? (car p) 'type)))) ie)
       (eval `(define ,(string->symbol (string-append (symbol->string 'type) "-" (symbol->string 'v1)))
                ,(lambda (p) (cadr (assoc 'v1 (cdr p))))) ie) ...
       (eval `(define ,(string->symbol (string-append "set-" (symbol->string 'type) "-" (symbol->string 'v1) "!"))
                ,(lambda (p v) (set-car! (cdr (assoc 'v1 (cdr p))) v))) ie) ...))))