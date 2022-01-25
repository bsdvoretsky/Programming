;; strings

; trim
(define (string-trim-left s)
  (if (null? (string->list s)) 
      ""
      (if (not (or (equal? (car (string->list s)) '#\space)
                   (equal? (car (string->list s)) '#\tab)
                   (equal? (car (string->list s)) '#\newline)))
          s
          (string-trim-left (list->string (cdr (string->list s)))))))

(define (string-trim-right s)
  (if (null? (string->list s)) 
      ""
      (if (not (or (equal? (car (reverse (string->list s))) '#\space)
                   (equal? (car (reverse (string->list s))) '#\tab)
                   (equal? (car (reverse (string->list s))) '#\newline)))
          s
          (string-trim-right
           (list->string (reverse (cdr (reverse (string->list s)))))))))

(define (string-trim s)
  (string-trim-left (string-trim-right s)))

; prefix, suffix, infix
(define (string-prefix? a b)
  (if (null? (string->list a))
      #t
      (if (null? (string->list b))
          #f
          (if (equal? (car (string->list a)) (car (string->list b)))
              (string-prefix? (list->string (cdr (string->list a)))
                              (list->string (cdr (string->list b))))
              #f))))

(define (string-suffix? a b)
  (if (null? (string->list a))
      #t
      (if (null? (string->list b))
          #f
          (if (equal? (car (reverse (string->list a))) (car (reverse (string->list b))))
              (string-suffix? (list->string (reverse (cdr (reverse (string->list a)))))
                              (list->string (reverse (cdr (reverse (string->list b))))))
              #f))))
(define (string-infix? a b)
  (if (null? (string->list a))
      #t
      (if (null? (string->list b))
          #f
          (or (string-prefix? a b) (string-suffix? a b)
              (string-infix? a (list->string (cdr (string->list b))))
              (string-infix? a (list->string (cdr (string->list b))))))))

; split
(define (string-remove-prefix pref str)
  (define (inner lpref lstr)
    (if (or (null? lpref) (null? lstr))
        (list->string lstr)
        (inner (cdr lpref) (cdr lstr))))
  
  (inner (string->list pref) (string->list str)))

(define (string-split str sep)
  (define (inner lstr acc)
    (if (null? lstr)
        (list (list->string acc))
        (if (string-prefix? sep (list->string lstr))
            (cons (list->string acc)
                  (inner (string->list (string-remove-prefix sep (list->string lstr)))
                         '()))
            (inner (cdr lstr) (append acc (list (car lstr)))))))
  (inner (string->list str) '()))
