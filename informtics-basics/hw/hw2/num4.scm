;; multi-vector
(define (mul a)
  (if (null? a)
      1
      (* (car a) (mul (cdr a)))))

(define (mul-list a b)
  (if (equal? b '())
      0
      (+ (* (car b) (mul (cdr a))) (mul-list (cdr a) (cdr b)))))

(define (make-multi-vector sizes . fill)
  (define (inner s . f)
    (if (not (null? fill))
        (make-vector (mul sizes) (car fill))
        (make-vector (mul sizes) 0)))
  (list sizes (inner sizes fill)))

(define (multi-vector? m)
  (and (list? m) (not (null? (car m))) (= (mul (car m)) (vector-length (cadr m)))))

(define (multi-vector-set! m indices x)
  (vector-set! (cadr m) (mul-list (car m) indices) x))

(define (multi-vector-ref m indices)
  (vector-ref (cadr m) (mul-list (car m) indices)))