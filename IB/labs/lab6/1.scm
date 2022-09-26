; <frac> ::= + <num> / <num> | <num> / <num> | - <num> / <num>
; <num> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | <num><num>

(define call/cc
  call-with-current-continuation)
(define (find s c)
  (and (not (null? s)) 
       (or (equal? (car s) c) 
           (find (cdr s) c))))

(define (check-frac str)
  (let ((nums (string->list "0123456789")) (sign (string->list "+-")) (lstr (string->list str)))
    (define (parse2 lstr t)
      (cond
        ((and (= t 0) (null? lstr)) #f)
        ((and (> t 0) (null? lstr)) #t)
        ((find nums (car lstr)) (parse2 (cdr lstr) (+ t 1)))
        (else #f)))
    (define (parse1 lstr t)
      (cond 
        ((null? lstr) #f)
        ((and (> t 0) (equal? (car lstr) #\/)) (parse2 (cdr lstr) 0))
        ((find nums (car lstr)) (parse1 (cdr lstr) (+ t 1)))
        (else #f)))
    (cond
      ((null? lstr) #f)
      ((find sign (car lstr)) (parse1 (cdr lstr) 0))
      ((find nums (car lstr)) (parse1 lstr 0))
      (else #f))))

(define (scan-frac str)
  (and (check-frac str)
       (let ((num1 '())
             (num2 '())
             (lstr (string->list str)))
         (define (loop lstr status)
           (cond
             ((null? lstr) #f)
             ((equal? (car lstr) #\/)
              (loop (cdr lstr) 1))
             ((= status 0)
              (begin
                (set! num1 (append num1 (list (car lstr))))
                (loop (cdr lstr) 0)))
             ((= status 1)
              (if (not (null? lstr))
                  (begin
                    (set! num2 (append num2 (list (car lstr))))
                    (loop (cdr lstr) 1))))))
         (loop lstr 0)
         (eval `(/ ,(string->number (list->string num1))
                   ,(string->number (list->string num2)))
               (interaction-environment)))))

(define return #f)
(call/cc (lambda (x) (set! return x)))
(define (scan-many-fracs str)
  (let ((fracs '()) (lstr (string->list str)))
    (define (loop lstr ts)
      (if (not (null? lstr))
          (if (not (char-whitespace? (car lstr)))
              (loop (cdr lstr) (append ts (list (car lstr))))
              (begin
                (if (not (null? ts))
                    (set! fracs (append fracs (list (list->string ts)))))
                (loop (cdr lstr) '())))
          (if (not (null? ts))
              (set! fracs (append fracs (list (list->string ts)))))))
    (loop lstr '())
    (and (not (null? fracs))
         (map (lambda (x) (if (not (check-frac x))
                              (return #f)
                              (scan-frac x))) fracs))))

; TESTS

; 1
(display "TEST 1") (newline)
(write `(check-frac "110/111")) (display " => ")
(display (check-frac "110/110")) (newline)
; 2
(display "TEST 2") (newline)
(write `(check-frac "-4/3")) (display " => ")
(display (check-frac "-4/3")) (newline)
; 3
(display "TEST 3") (newline)
(write `(check-frac "+5/10")) (display " => ")
(display (check-frac "+5/10")) (newline)
; 4
(display "TEST 4") (newline)
(write `(check-frac "5.0/10")) (display " => ")
(display (check-frac "5.0/10")) (newline)
; 5
(display "TEST 5") (newline)
(write `(check-frac "FF/10")) (display " => ")
(display (check-frac "FF/10")) (newline)

; 6
(display "TEST 6") (newline)
(write `(scan-frac "110/111")) (display " => ")
(display (scan-frac "110/111")) (newline)
; 7
(display "TEST 7") (newline)
(write `(scan-frac "-4/3")) (display " => ")
(display (scan-frac "-4/3")) (newline)
; 8
(display "TEST 8") (newline)
(write `(scan-frac "+5/10")) (display " => ")
(display (scan-frac "+5/10")) (newline)
; 9
(display "TEST 9") (newline)
(write `(scan-frac "5.0/10")) (display " => ")
(display (scan-frac "5.0/10")) (newline)
; 10
(display "TEST 10") (newline)
(write `(scan-frac "FF/10")) (display " => ")
(display (scan-frac "FF/10")) (newline)

; 11
(display "TEST 11") (newline)
(write `(scan-many-fracs "\t1/2 1/3\n\n10/8")) (display " => ")
(display (scan-many-fracs "\t1/2 1/3\n\n10/8")) (newline)
; 12
(display "TEST 12") (newline)
(write `(scan-many-fracs "\t1/2 1/3\n\n2/-5")) (display " => ")
(display (scan-many-fracs "\t1/2 1/3\n\n2/-5")) (newline)