(define (iterate f x n)
  (if (= n 0)
      '()
      (cons x (iterate f (f x) (- n 1)))))