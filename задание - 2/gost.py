import random
import math

def resheto(n):
    all_numbers = list(range(2, n + 1))
    primes = []
    while all_numbers:
        current_prime = all_numbers[0]
        primes.append(current_prime)
        all_numbers = [x for x in all_numbers if x % current_prime != 0]
    return primes

def rn(a, b):
    randomNumber = round(random.uniform(a, b), 1)
    return randomNumber

def build_new_from_old(q, bit):
    while True:
        zakaruchka = rn(0, 1)
        n = pow(2, bit - 1) / q + (pow(2, bit - 1) * zakaruchka) / q
        if int(n) % 2 == 1:
            n += 1
        u = 0
        while True:
            flag1 = False
            flag2 = False
            p = int((n + u) * q) + 1
            if p > pow(2, bit):
                break
            res = 2 % int(p)
            for i in range(2, int(p)):
                res *= 2
                res = res % int(p)
            if res == 1:
                flag1 = True

            res = 2 % int(p)
            for i in range(2, int(n + u + 1)):
                res *= 2
                res = res % int(p)
            if res != 1:
                flag2 = True
            if flag1 and flag2:
                return int(p)
            u += 2

def main():
    c = resheto(500)
    bit = int(input("Введите количество бит: "))

    print("+", end="")
    for _ in range(10):
        print("--------+", end="")
    print()

    print("|", end="")
    for i in range(10):
        print(f"{i + 1:8}|", end="")
    print()

    print("+", end="")
    for _ in range(10):
        print("--------+", end="")
    print()

    print("|", end="")
    rand = random.randint(0, (len(c) - 10) // 10) * 10
    for i in range(10):
        print(f"{build_new_from_old(c[rand + i], bit):8}|", end="")
    print()

    print("+", end="")
    for _ in range(10):
        print("--------+", end="")
    print()

if __name__ == "__main__":
    main()
