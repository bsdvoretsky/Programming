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