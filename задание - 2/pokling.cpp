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

int rn(int a, int n) {
    // Инициализация генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());

    // Создание распределения для заданного диапазона [a, n]
    uniform_int_distribution<int> distribution(a, n);

    // Генерация случайного числа в заданном диапазоне и возврат его
    return distribution(gen);
}
tuple<string, int> test_pokling(int n, vector<int> delit, int t) {
    vector<int> a;
    int ai;
    while (a.size() != t) {
        ai = rn(2, n - 1);
        if (find(a.begin(), a.end(), ai) >= a.end()) {
            a.push_back(ai);
        }
    }
    int res = 1;
    int promez;
    for (int i = 0; i < a.size(); i++) {
        res = a[i] % n;
        for (int j = 2; j <= n - 1; j++) {
            res *= a[i];
            res = res % n;
        }
        if (res != 1) {
            return make_tuple(" - составное число", 0);
        }
    }
    int res2;
    double prom;
    bool flag = true;
    double n32 = (double)(n - 1);
    double deliti;
    for (int j = 0; j < a.size(); j++) {
        flag = true;
        for (int i = 0; i < delit.size(); i++) {
            res2 = a[j] % n;
            deliti = (double)delit[i];
            prom = n32 / deliti;
            for (int d = 2; d <= prom; d++) {
                res2 *= a[j];
                res2 = res2 % n;
            }
            if (res2 == 1) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return make_tuple(" - простое число", 1);
        }
    }
    return make_tuple(" - вероятно, составное число", 0);
}

tuple<string, int, int> build_pokling(int bit, vector<int>& c, int t) {
    tuple<string, int> resultat = { "", 0 };

    vector<int> geted;
    int z = 1;
    bool f = true;
    int rnum;
    int rind;
    int rpow;
    int max;
    int m;
    int n;
    int glim = 0;
    string oleg;

    while (true) {
        z = 1;
        f = true;
        geted = {};
        vector<int> delit;

        while (f && geted.size() < 1) {
            z = 1;
            for (int i = 0; i < c.size(); i++) {
                vector<int> delitt;
                if (c[i] > pow(2, bit / 2 + 1) - 1) {
                    break;
                }
                for (max = 1; pow(c[i], max) <= pow(2, bit / 2 + 1); max++) {
                }
                rpow = rn(1, max - 1);
                rnum = rn(0, rpow);
                z *= pow(c[i], rnum);
                if (z > pow(2, bit / 2 + 1) - 1) {
                    z /= pow(c[i], rnum);
                    if (z >= pow(2, bit / 2)) {
                        if (find(geted.begin(), geted.end(), z) >= geted.end()) {
                            geted.push_back(z);
                        }
                        z = 1;
                        f = false;
                        delit = delitt;
                    }
                }
                else {
                    if (rnum != 0){
                        delitt.push_back(c[i]);
                    }
                }
            }
        }
        n = rn(pow(2, bit / 2 - 1), pow(2, bit / 2) - 1);
        n = n * geted[0];
        n++;
        resultat = test_pokling(n, delit, t);
        tuple<string, int> result_ver;
        if (get<1>(resultat) == 0) {
            result_ver = test_pokling(n, c, 1);
            if (get<1>(result_ver) == 1) {
                glim++;
            }
        }
        else {
            result_ver = test_pokling(n, c, 1);
            if (get<1>(result_ver) == 1) {
                oleg = '+';
            }
            else {
                oleg = '-';
            }
        }
        if (get<1>(resultat) == 1) {
            return make_tuple(oleg, n, glim);
        }
    }

}


int main() {
    setlocale(LC_ALL, "russian");
    vector <int> c;
    int bit;
    cin >> bit;
    c = resheto(500);

    int p;
    vector<tuple<string, int, int>> pokling_res;
    vector<int> pokling_res_p;
    tuple<string, int, int> pokling_result;
    for (int i = 0; i < 10; i++) {
        pokling_result = build_pokling(bit, c, 10);
        p = get<1>(pokling_result);
        if (find(pokling_res_p.begin(), pokling_res_p.end(), p) >= pokling_res_p.end()) {
            pokling_res_p.push_back(p);
            pokling_res.push_back(pokling_result);
        }
        else {
            i--;
        }
    }
    int correct = 0;
    int incorrect = 0;
    int ress;

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
    for (int i = 0; i < 10; i++) {
        cout << setw(8) << get<1>(pokling_res[i]) << "|";
    }
    cout << endl;

    cout << "+";
    for (int i = 0; i < 10; i++) {
        cout << "--------+";
    }
    cout << endl;

    cout << "|";
    for (int i = 0; i < 10; i++) {
        cout << setw(8) << get<0>(pokling_res[i]) << "|";
    }
    cout << endl;

    cout << "+";
    for (int i = 0; i < 10; i++) {
        cout << "--------+";
    }
    cout << endl;

    cout << "|";
    for (int i = 0; i < 10; i++) {
        cout << setw(8) << get<2>(pokling_res[i]) << "|";
    }
    cout << endl;

    cout << "+";
    for (int i = 0; i < 10; i++) {
        cout << "--------+";
    }
    cout << endl;

    return 0;
}