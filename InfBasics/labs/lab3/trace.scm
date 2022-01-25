(define-syntax trace-ex
  (syntax-rules ()
    ((trace-ex value) (begin (display 'value) (let ((v value))
                                                (display " => ")
                                                (display v)
                                                (newline)
                                                v)))))

(define (zip . xss)
  (if (or (null? xss)
          (null? (trace-ex (car xss)))) 
      '()
      (cons (map car xss)
            (apply zip (map cdr (trace-ex xss))))))

;(zip '(1 2 3) '(one two three))


