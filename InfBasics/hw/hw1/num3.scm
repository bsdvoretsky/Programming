(define (my-gcd a b)
  (if (= a 0)
      b
      (if (= b 0)
          a
          (if (> a b)
              (my-gcd (modulo a b) b)
              (my-gcd (modulo b a) a)))))

(define (my-lcm a b)
  (/ (* a b) (my-gcd a b)))

(define (prime? n)
  (define (in_prime? n d)
            (if (= d 1)
                #t
                (if (= (modulo n d) 0)
                    #f
                    (in_prime? n (- d 1)))))
  (if (= n 1)
      #f
      (if (= n 2)
          #t
          (in_prime? n (+ (truncate (sqrt n)) 1)))))
