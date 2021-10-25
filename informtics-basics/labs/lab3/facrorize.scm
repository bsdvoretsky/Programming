(load "unit-test.scm")

(define (factorize e)
  (let ((x (cadadr e)) (y (car (cdaddr e))))
    (cond ((= (car (cddadr e)) 2)
           `(* (- ,x ,y) (+ ,x ,y)))
          ((= (car (cddadr e)) 3)
           (if (equal? (car e) '-)
               `(* (- ,x ,y) (+ (expt ,x 2) (* ,x ,y) (expt ,y 2)))
               `(* (+ ,x ,y) (- (+ (expt ,x 2) (expt ,y 2)) (* ,x ,y))))))))

(define tests
  '((test (factorize '(- (expt x 2) (expt y 2))) '(* (- x y) (+ x y)))
    (test (factorize '(- (expt (+ first 1) 2) (expt (- second 1) 2))) '(* (- (+ first 1) (- second 1))
         (+ (+ first 1) (- second 1))))))

(run-tests tests)