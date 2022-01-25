(define (intersperse e xs)
  (if (null? xs)
      '()
      (if (= (length xs) 1)
          xs
          (append (list (car xs)) (list e) (intersperse e (cdr xs))))))
