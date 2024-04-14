import random
import math

def test_miller(n, c, t):
    n1 = n - 1
    delit = []
    for i in range(len(c)):
        if n1 == 0 or c[i] > n1:
            break
        if n1 % c[i] == 0:
            delit.append(c[i])
            while n1 % c[i] == 0 and n1 != 0:
                n1 = n1 // c[i]
    a = []
    while len(a) != t:
        ai = random.randint(2, n)
        if ai not in a:
            a.append(ai)
    for ai in a:
        res = ai % n
        for _ in range(2, n):
            res *= ai
            res = res % n
        if res != 1:
            return " - составное число", 0

    for d in delit:
        flag = True
        for ai in a:
            res = ai % n
            for _ in range(2, (n - 1) // d + 1):
                res = ai * res
                res = res % n
            if res != 1:
                flag = False
                break
        if flag:
            return " - вероятно, составное число", 0
    return " - простое число", 1

def resheto(n):
    all_numbers = list(range(2, n + 1))
    primes = []
    while all_numbers:
        current_prime = all_numbers[0]
        primes.append(current_prime)
        all_numbers = [x for x in all_numbers if x % current_prime != 0]
    return primes

def build_miller(bit, c, t):
    while True:
        glim = 0
        z = 1
        f = True
        geted = []
        while f and len(geted) < 1:
            z = 1
            for i in range(len(c)):
                if c[i] > pow(2, bit - 1) - 1:
                    break
                max_val = int(math.log(pow(2, bit - 1), c[i]))
                rpow = random.randint(1, max_val)
                rnum = random.randint(0, rpow)
                z *= pow(c[i], rnum)
                if z > pow(2, bit - 1) - 1:
                    z //= pow(c[i], rnum)
                    if z >= pow(2, bit - 2):
                        if z not in geted:
                            geted.append(z)
                        z = 1
                        f = False
        m = random.choice(geted)
        n = 2 * m - 1
        resultat = test_miller(n, c, t)
        oleg = ''
        if resultat[1] == 1:
            res = test_miller(n, c, 1)
            if res[1] == 0:
                oleg = '-'
            else:
                oleg = "+"
        else:
            res = test_miller(n, c, 1)
            if res[1] == 1:
                glim += 1
        if resultat[1] == 1:
            return oleg, n, glim

def main():
    bit = int(input("Введите количество бит: "))
    c = resheto(500)
    miller_res = []
    miller_res_p = []
    while len(miller_res) != 10:
        miller_result = build_miller(bit, c, 10)
        p = miller_result[1]
        if p not in miller_res_p:
            miller_res_p.append(p)
            miller_res.append(miller_result)
    print("+", end="")
    for _ in range(10):
        print("--------+", end="")
    print("\n|", end="")
    for i in range(10):
        print(f"{i + 1:8}|", end="")
    print("\n+", end="")
    for _ in range(10):
        print("--------+", end="")
    print("\n|", end="")
    for i in range(10):
        print(f"{miller_res[i][1]:8}|", end="")
    print("\n+", end="")
    for _ in range(10):
        print("--------+", end="")
    print("\n|", end="")
    for i in range(10):
        print(f"       {miller_res[i][0]}|", end="")
    print("\n+", end="")
    for _ in range(10):
        print("--------+", end="")
    print("\n|", end="")
    for i in range(10):
        print(f"{miller_res[i][2]:8}|", end="")
    print("\n+", end="")
    for _ in range(10):
        print("--------+", end="")
    print()

if __name__ == "__main__":
    main()
