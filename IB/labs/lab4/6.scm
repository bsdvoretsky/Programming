;; A
(define-syntax when
  (syntax-rules ()
    ((when cond? expr1 ...)
     (if cond?
         (begin expr1 ...)))))
(define-syntax unless
  (syntax-rules ()
    ((when cond? expr1 ...)
     (if (not cond?)
         (begin expr1 ...)))))


; Test
(define x 1)
(when   (> x 0) (display "x > 0")  (newline))
(unless (= x 0) (display "x != 0") (newline))





;; Б
(define-syntax for
  (syntax-rules (in as)
    ((for x in xs expr1 ...)
     (letrec
         ((iter
           (lambda (i)
             (if (not (= i (length xs)))
                 ((lambda (x) (begin expr1 ... (iter (+ i 1))))
                  (list-ref xs i)))))) (iter 0)))
    ((for xs as x expr1 ...)
     (letrec
         ((iter
           (lambda (i)
             (if (not (= i (length xs)))
                 ((lambda (x) (begin expr1 ... (iter (+ i 1))))
                  (list-ref xs i)))))) (iter 0)))))


; Test
(for i in '(1 2 3)
  (for j in '(4 5 6)
    (display (list i j))
    (newline)))
(newline)
(for '(1 2 3) as i
  (for '(4 5 6) as j
    (display (list i j))
    (newline)))





;; В
(define-syntax while
  (syntax-rules ()
    ((while cond? expr1 ...)
     ((letrec ((iter
                  (lambda () (if cond? (begin expr1 ... (iter))))))
        (lambda () (iter)))))))


; Test
(let ((p 0)
      (q 0))
  (while (< p 3)
         (set! q 0)
         (while (< q 3)
                (display (list p q))
                (newline)
                (set! q (+ q 1)))
         (set! p (+ p 1))))





;; Г
(define-syntax repeat
  (syntax-rules (until)
    ((repeat (expr1 ...) until cond?)
     ((letrec ((iter
                (lambda () (begin expr1 ... (if (not cond?) (iter))))))
        (lambda () (iter)))))))


; Test
(let ((i 0)
      (j 0))
  (repeat ((set! j 0)
           (repeat ((display (list i j))
                    (set! j (+ j 1)))
                   until (= j 3))
           (set! i (+ i 1))
           (newline))
          until (= i 3)))





;; Д
(define-syntax cout
  (syntax-rules (<< endl)
    ((cout << endl) (begin (newline)))
    ((cout << endl << xs ...) (begin (newline) (cout << xs ...)))
    ((cout << val) (begin (display val)))
    ((cout << val << xs ...) (begin (display val) (cout << xs ...)))))


; Test
(cout << "a = " << 1 << endl << "b = " << 2 << endl)