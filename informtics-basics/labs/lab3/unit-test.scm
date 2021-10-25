(define-syntax test
  (syntax-rules ()
    ((test expression var)
     (list (equal? expression var) expression))))

(define (run-test t)
  (begin
    (display (cadr t))
    (let ((te (eval t (interaction-environment))))
      (if (car te)
          (begin (display " ok\n") #t)
          (begin (display " FAIL\n  Expected: ") (display (caddr t))
                 (display "\n  Reterned: ")
                 (display (cadr te)) (newline) #f)))))

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
  '((test (signum -2) -1)
    (test (signum  0)  0)
    (test (signum  2)  1)))

