(define (my-element? x xs)
  (and (not (null? xs)) (or (equal? x (car xs)) (my-element? x (cdr xs)))))

;; 1) list->set
(define (list->set xs)
  (if (null? xs)
      '()
      (if (my-element? (car xs) (cdr xs))
          (list->set (cdr xs))
          (append (list (car xs)) (list->set (cdr xs)))
      )))

;; 2) set?
(define (set? xs)
  (equal? xs (list->set xs)))

;; 3) union
(define (union xs ys)
  (if (null? xs)
      ys
      (if (null? ys)
          xs
          (if (equal? (car xs) (car ys))
              (list->set (append (list (car xs)) (union (cdr xs) (cdr ys))))
              (list->set (append (list (car xs) (car ys)) (union (cdr xs) (cdr ys))))))))

;; 4) intersection
(define (intersection xs ys)
  (if (null? xs)
      '()
      (if (null? ys)
          '()
          (if (my-element? (car xs) ys)
              (list->set (append (list (car xs)) (intersection (cdr xs) ys)))
              (intersection (cdr xs) ys)))))

;; 5) difference
(define (difference xs ys)
  (if (null? xs)
      '()
      (if (null? ys)
          xs
          (if (my-element? (car xs) ys)
              (difference (cdr xs) ys)
              (list->set (append (list (car xs)) (difference (cdr xs) ys)))))))

;; 6) symmetric-difference
(define (symmetric-difference xs ys)
  (difference (union xs ys) (intersection xs ys)))

;; 7) set-eq?
(define (set-eq? xs ys)
  (equal? (difference (union xs ys) (intersection xs ys)) '()))