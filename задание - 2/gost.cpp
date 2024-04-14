#include <iostream>
#include <cmath>
#include <cstdint>
#include <random>
#include <vector>
#include <string>
#include <tuple>
#include <locale.h>
#include <iomanip>


using namespace std;


vector<int> resheto(int n) {
    vector<int> all;
    vector<int> b;
    for (int i = 2; i <= n; i++) {
        all.push_back(i);
    }
    int i = 0;
    while (i < all.size()) {
        b.clear();
        for (int j = 0; j <= i; j++) {
            b.push_back(all[j]);
        }
        for (int z = i + 1; z < all.size(); z++) {
            if (all[z] % all[i] != 0) {
                b.push_back(all[z]);
            }
        }
        all.clear();
        all = b;
        i++;
    }
    return all;
}

double rn(double a, double b) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Создание распределения для заданного интервала [a, b] с одной цифрой после запятой
    std::uniform_real_distribution<double> distribution(a, b);
    double randomNumber = distribution(gen);

    // Округляем результат до одной цифры после запятой
    randomNumber = round(randomNumber * 10.0) / 10.0;
    return randomNumber;

}

int build_new_from_old(int q, int bit) {
    double n;
    double zakaruchka;
    int p;

    while (true) {
        zakaruchka = rn(0, 1);
        n = pow(2, bit - 1) / q + (pow(2, bit - 1) * zakaruchka) / q;
        if ((int)n % 2 == 1) {
            n++;
        }
        for (int u = 0; true; u += 2) {
            p = (n + u) * q + 1;
            if (p > pow(2, bit)) {
                break;
            }
            bool flag1 = false;
            bool flag2 = false;
            int res = 2 % p;
            for (int i = 2; i <= p - 1; i++) {
                res *= 2;
                res = res % p;
            }
            if (res == 1) {
                flag1 = true;
            }
            res = 2 % p;
            for (int i = 2; i <= n + u; i++) {
                res *= 2;
                res = res % p;
            }
            if (res != 1) {
                flag2 = true;
            }
            if (flag2 && flag1) {
                return p;
            }
        }
    }
}



int main() {
    setlocale(LC_ALL, "russian");

    vector<int> c = resheto(500);

    int bit;
    cin >> bit;

    cout << "+";
    for (int i = 0; i < 10; i++) {
        cout << "--------+";
    }
    cout << endl;

    cout << "|";
    for (int i = 0; i < 10; i++) {
        cout << setw(8) << i + 1 << "|";
    }
    cout << endl;

    cout << "+";
    for (int i = 0; i < 10; i++) {
        cout << "--------+";
    }
    cout << endl;

    cout << "|";
    int rand = rn(0, (c.size() - 10) / 10) * 10;
    for (int i = 0; i < 10; i++) {
        int oleg = c[rand + i];
        cout << setw(8) << build_new_from_old(c[rand + i], bit) << "|";
    }
    cout << endl;

    cout << "+";
    for (int i = 0; i < 10; i++) {
        cout << "--------+";
    }
    cout << endl;

    return 0;
}