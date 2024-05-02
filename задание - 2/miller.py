import random
import math

def primes(n):
    is_prime = [True] * (n + 1)
    primes = []

    for p in range(2, int(math.sqrt(n)) + 1):
        if is_prime[p]:
            for i in range(p * p, n + 1, p):
                is_prime[i] = False

    for p in range(2, n + 1):
        if is_prime[p]:
            primes.append(p)

    return primes

def builder_test(prime, bit):
    max_index = 0
    max_pow = 1

    while prime[max_index] < 2 ** (bit - 1) and max_index < len(prime):
        max_index += 1
    while 2 ** max_pow < 2 ** (bit - 1):
        max_pow += 1

    m = 1
    q = []

    while True:
        num = random.randint(0, max_index)
        power = random.randint(1, max_pow)

        if prime[num] ** power:
            if m * prime[num] ** power < 2 ** 31 - 1:
                m *= prime[num] ** power
                q.append(prime[num])

        if m > 2 ** (bit - 2):
            if m >= 2 ** (bit - 1):
                m = 1
                q.clear()
            else:
                break

    n = 2 * m + 1

    return n, q

def test_millera(n, t, q):
    a = []

    while len(a) != t:
        aj = random.randint(2, n - 1)

        if aj not in a:
            a.append(aj)

    for aj in a:
        if pow(aj, n - 1, n) != 1:
            return 0

    flag = True
    i = 0
    for aj in a:
        if i < len(q) and q[i] != 0 and pow(aj, (n - 1) // q[i], n) != 1:
            flag = False
            if i < len(q):
                i += 1

    if flag:
        return 0

    return 1

def power_mod(a, b, n):
    result = 1
    while b > 0:
        if b % 2 == 1:
            result = (result * a) % n
        a = (a * a) % n
        b //= 2
    return result

def rn(a, b):
    return random.randint(a, b)

def print_results(res, res_ver_test, otvegnutie):
    print("Prime Numbers\tTest Results\tOccurrences")
    print("----------------------------------------------")

    for i in range(len(res)):
        print(f"{res[i]}\t\t{res_ver_test[i]}\t\t{otvegnutie[i]}")

if __name__ == "__main__":
    size_primes = 1000
    prime = primes(size_primes)

    bit = int(input())

    q = []
    k = 0
    probability = 0

    res = []
    res_ver_test = []
    otvegnutie = []

    while len(res) != 10:
        n, q = builder_test(prime, bit)
        probability = test_millera(n, 10, q)

        if probability == 1:
            if n not in res:
                res.append(n)

                probability = test_millera(n, 1, q)
                if probability == 1:
                    res_ver_test.append("+")
                else:
                    res_ver_test.append("-")

                otvegnutie.append(k)
                k = 0
        else:
            k += 1

    print_results(res, res_ver_test, otvegnutie)
