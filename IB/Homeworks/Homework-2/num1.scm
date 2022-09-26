;; 1) my-range
(define (my-range a b d)
  (if (>= (+ a d) b)
      (list a)
      (cons a (my-range (+ a d) b d))))

;; 2) my-flatten
(define (my-flatten l)
  (if (null? l)
      '()
      (if (list? (car l))
          (append (my-flatten (car l)) (my-flatten (cdr l)))
          (append (list (car l)) (my-flatten (cdr l))))))

;; 3) my-element?
(define (my-element? x xs)
  (and (not (null? xs)) (or (equal? x (car xs)) (my-element? x (cdr xs)))))

;; 4) my-filter
(define (my-filter pred? xs)
  (if (null? xs)
      '()
      (if (pred? (car xs))
          (append (list (car xs)) (my-filter pred? (cdr xs)))
          (my-filter pred? (cdr xs)))))

;; 5) my-fold-left
(define (my-fold-left op xs)
  (if (= (length xs) 1)
      (car xs)
      (op (my-fold-left op (reverse (cdr (reverse xs)))) (car (reverse xs)))))

;; 6) my-fold-right
(define (my-fold-right op xs)
  (if (= (length xs) 1)
      (car xs)
      (op (car xs) (my-fold-right op (cdr xs)))))
