#include <iostream>
#include <cmath>


using namespace std;


double function1(double x) {
    double y = 2 - sqrt(4 - pow(x + 2, 2));
    return y;
}


double function2(double x) {
    return -1 * x;
}


double function3(double x) {
    double y = sqrt(pow(2, 2) - pow(x - 3, 2)) - 1;
    return y;
}


void compute_table(double X_start, double X_end, double dx) {
    // Table header
    cout << "X\t| Y" << endl;
    cout << "-----------------------" << endl;

    double x = X_start;
    while (x <= X_end) {
        double y1 = function1(x);
        double y2 = function2(x);
        double y3 = function3(x);

        if (y1 <= 2 && x <= -2) {
            cout << x << "\t| " << y1 << endl;
        }
        if (y2 <= 0 && x >= 0 && x <= 3) {
            cout << x << "\t| " << y2 << endl;
        }
        if (y3 >= -1 && x >= 3 && x <= 5) {
            cout << x << "\t| " << y3 << endl;
        }
        x += dx;
    }
}




int main() {
    // Setting interval and step
    double X_start = -5;
    double X_end = 5;
    double dx = 0.5;

    // Compute and display the table
    compute_table(X_start, X_end, dx);

    return 0;
}