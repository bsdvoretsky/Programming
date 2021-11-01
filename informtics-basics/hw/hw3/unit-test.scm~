(load "trace.scm")

(define-syntax test
  (syntax-rules ()
    ((test expression var)
     (list 'expression var))))

(define (run-test t)
  (begin
    (display (car t))
    (let ((te (eval (car t) (interaction-environment))))
      (if (equal? te (cadr t))
          (begin (display " ok\n") #t)
          (begin (display " FAIL\n  Expected: ") (display (cadr t))
                 (display "\n  Reterned: ")
                 (display te) (newline) #f)))))

(define (and-fold x . xs)
  (if (null? xs)
      x
      (and x (apply and-fold xs))))

(define (run-tests ts)
  (if (null? ts)
      #t
      (apply and-fold (list (run-test (car ts)) (run-tests (cdr ts))))))

(define (signum x)
  (cond
    ((< x 0) -1)
    ((= x 0)  1) ; Ошибка здесь!
    (else     1)))

(define the-tests
  (list (test (signum -2) -1)
        (test (signum  0)  0)
        (test (signum  2)  1)))

(define (signum-right x)
  (cond
    ((< x 0) -1)
    ((= x 0) 0)
    (else 1)))

(define the-tests2
  (list (test (signum-right -2) -1)
        (test (signum-right 0) 0)
        (test (signum-right 2) 1)))

(define counter
  (let ((x 0))
    (lambda ()
      (set! x (+ x 1))
      x)))
      
(define counter-tests
  (list (test (counter) 1)
          (test (counter) 2)
          (test (counter) 3)))

(run-tests counter-tests)

(+ (trace-ex (counter)) 1)
(* (trace-ex (counter)) 100)

(run-tests the-tests)
(run-tests the-tests2)
(newline)

