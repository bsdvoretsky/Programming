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
  (if (not (= k 1))
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