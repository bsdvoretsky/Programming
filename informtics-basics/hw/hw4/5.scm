(define-syntax define-data
  (syntax-rules ()
    ((define-data figure ((f1 v1 ...) ...))
     (let ((ie (interaction-environment)))
       (eval `(define f1
                ,(lambda (v1 ...) (append (list 'figure) (list 'f1) (list (list 'v1 v1) ...)))) ie) ...
       (eval `(define ,(string->symbol (string-append (symbol->string 'figure) "?"))
                (lambda (p) (and (list? p) (equal? (car p) 'figure)))) ie)
       ))))

(define-syntax match
  (syntax-rules ()
    ((match f ((f1 v1 ...) e1) ...)
     (cond
       ((equal? (cadr f) 'f1)
        (let ((v1 (cadr (assoc 'v1 (cddr f)))) ...)
          e1))
       ...
       (else f)))))



; Test
(define-data figure ((square a)
                     (rectangle a b)
                     (triangle a b c)
                     (circle r)))

(define s (square 10))
(define r (rectangle 10 20))
(define t (triangle 10 20 30))
(define c (circle 10))

(and (figure? s)
     (figure? r)
     (figure? t)
     (figure? c))

(define pi (acos -1))

(define (perim f)
  (match f 
    ((square a)       (* 4 a))
    ((rectangle a b)  (* 2 (+ a b)))
    ((triangle a b c) (+ a b c))
    ((circle r)       (* 2 pi r))))

(perim s)
(perim r)
(perim t)