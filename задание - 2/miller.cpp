#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <random>
#include <limits>
#include <algorithm>

using namespace std;

vector<int> primes(int n);
pair<int, vector<int>> builder_test(vector<int> prime, int bit);
pair<int, int> test_millera(vector<int> prime, int bit, int t);

int power_mod(int a, int b, int n);
int rn(int a, int b);

int main() {
    int size_primes = 1000;
    vector<int> prime = primes(size_primes);

    int bit = 0;
    cin >> bit;

    vector<int> res;
    int r;
    int n;

    while(res.size() != 10) {
        tie(n, r) = test_millera(prime, bit, 10);

        if (r == 1) {
            if (find(res.begin(), res.end(), n) == res.end()) {
                res.push_back(n);
            }
        }
    }

    for (int num : res) {
        cout << num << " ";
    }
}

vector<int> primes(int n) {
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;

    for (int p = 2; p * p <= n; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p)
                is_prime[i] = false;
        }
    }

    for (int p = 2; p <= n; ++p) {
        if (is_prime[p])
            primes.push_back(p);
    }

    return primes;
}

pair<int, vector<int>> builder_test(vector<int> prime, int bit) {
    int max_index = 0;
    int max_pow = 1;

    for (; prime[max_index] < pow(2, bit - 1); max_index++);
    for (; pow(2, max_pow) < pow(2, bit - 1); max_pow++);
    
    int64_t m = 1;
    vector<int> q;

    while(true){
        int num = rn(0, max_index);
        int power = rn(1, max_pow);
        
        if (pow(prime[num], power)) {
            if(m * pow(prime[num], power) < INT64_MAX) {
                m *= pow(prime[num], power);
                q.push_back(prime[num]);
            }
        }

        if(m > pow(2, bit - 2)){

            if(m >= pow(2, bit - 1)){
                m = 1;
                q.clear();
            }
            
            else{
                break;
            }
        }
    }

    int n = 2 * m + 1;

    return make_pair(n, q);
}

pair<int, int> test_millera(vector<int> prime, int bit, int t) {
    int n;
    vector<int> q;
    tie(n, q) = builder_test(prime, bit);

    vector<int> a;
    int aj;

    while (a.size() != t) {
        aj = rn(2, n - 1);

        if (find(a.begin(), a.end(), aj) == a.end()) {
            a.push_back(aj);
        }
    }

    for (int aj : a) {
        if (power_mod(aj, n - 1, n) != 1) {
            return make_pair(n, 0);
            break;
        }
    }


    bool flag = true;
    int i = 0;
    for (int aj : a) {
        if (q[i] != 0 && power_mod(aj, (n - 1) / q[i], n) != 1) {
            flag = false;
        }
        i++;
    }

    if (flag) {
        return make_pair(n, 0);
    }

    return make_pair(n, 1);;
}

int power_mod(int a, int b, int n) {
    long long result = 1;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % n;
        a = (a * a) % n;
        b /= 2;
    }
    return result;
}

int rn(int a, int b) {
    mt19937 mt_rand(random_device{}());
    return uniform_int_distribution<int>(a, b)(mt_rand);
}

