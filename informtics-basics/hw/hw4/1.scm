(define memoized-factorial
  (let ((known-results '((0 1))))
    (lambda (n)
      (let ((res (assoc n known-results)))
        (if res
            (cadr res)
            (let ((res (* n (memoized-factorial (- n 1)))))
              (set! known-results (cons (list n res) known-results))
              res))))))

; test
(begin
  (display (memoized-factorial 10)) (newline)
  (display (memoized-factorial 50)) (newline))