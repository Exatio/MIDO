--- 1. Fibonacci ---
fibo 1 = 1
fibo 2 = 1
fibo n = fibo (n-1) + fibo (n-2)

--- 2. Opérations élémentaires ---
length' [] = 0
length' xs = 1 + length' (tail xs)

take' 0 _ = []
take' n (x:xs) = x : (take' (n-1) xs)

drop' 0 xs = xs
drop' n xs = drop' (n-1) (tail xs)

bangbang 0 xs = head xs
bangbang n xs = bangbang (n-1) (tail xs)

plusplus xo xt

main = print (drop' 2 "test")
