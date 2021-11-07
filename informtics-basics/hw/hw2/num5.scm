(define (o . xs)
  (if (null? xs)
      (lambda (x) x)
      (lambda (x) ((car xs) ((apply o (cdr xs)) x)))))

(define (f x) (+ x 2))
(define (g x) (* x 3))
(define (h x) (- x))