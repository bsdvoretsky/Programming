(load "unit-test.scm")

(define (factorize e)
  (let ((x (cadadr e)) (y (car (cdaddr e))))
    (cond ((and (= (car (cddadr e)) 2) (= (car (cdr (cdaddr e))) 2))
           `(* (- ,x ,y) (+ ,x ,y)))
          ((and (= (car (cddadr e)) 3) (= (car (cdr (cdaddr e))) 3))
           (if (equal? (car e) '-)
               `(* (- ,x ,y) (+ (expt ,x 2) (* ,x ,y) (expt ,y 2)))
               `(* (+ ,x ,y) (- (+ (expt ,x 2) (expt ,y 2)) (* ,x ,y))))))))

(define tests
  (list (test (factorize '(- (expt x 2) (expt y 2))) '(* (- x y) (+ x y)))
    (test (factorize '(- (expt (+ first 1) 2) (expt (- second 1) 2))) '(* (- (+ first 1) (- second 1))
                                                                          (+ (+ first 1) (- second 1))))))

(run-tests tests)

(run-test (test (eval (list (list 'lambda
                                   '(x y)
                                   (factorize '(- (expt x 3) (expt y 3))))
                             1 2)
                       (interaction-environment))
                 -7))
(run-test (test (eval (list (list 'lambda
                                   '(x y)
                                   (factorize '(+ (expt x 3) (expt y 3))))
                             2 1)
                       (interaction-environment))
                 9))
(run-test (test (eval (list (list 'lambda 
                                   '(x y) 
                                   (factorize '(- (expt x 2) (expt y 2))))
                             1 2)
                       (interaction-environment))
                 -3))
              
                 