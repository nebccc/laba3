#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <stdexcept>

using namespace std;

struct ApproximationResult {
	double a;
	double b;
};

struct CorrelationResult {
	double correlation;
	double t_value;
};

ApproximationResult aproks(const vector<double>& x, const vector<double>& y);
CorrelationResult korrel(const vector<double>& x, const vector<double>& y);
vector<double> coffee(double T, double Ts, double r, int time);

void printCoffee(vector<double> temperatures, vector<double>times);
void printApproximationResult(ApproximationResult result);
void printCorrelationResult(CorrelationResult result);

int main() {
	double T = 90; // Начальная температура кофе
	double Ts = 26; // Температура комнаты
	double r = 0.01; // Коэффициент остывания
	int time = 60; // Временной предел в минутах

	vector<double> temperatures = coffee(T, Ts, r, time);

	vector<double> times(time + 1);
	iota(times.begin(), times.end(), 0);

	ApproximationResult approx_result = aproks(times, temperatures);
	CorrelationResult corr_result = korrel(times, temperatures);

	printApproximationResult(approx_result);
	printCorrelationResult(corr_result);
	printCoffee(temperatures, times);

	return 0;
}


ApproximationResult aproks(const vector<double>& x, const vector<double>& y) {
	double x_sum = accumulate(x.begin(), x.end(), 0.0);
	double y_sum = accumulate(y.begin(), y.end(), 0.0);
	double x2_sum = inner_product(x.begin(), x.end(), x.begin(), 0.0);
	double xy_sum = inner_product(x.begin(), x.end(), y.begin(), 0.0);
	size_t n = x.size();

	double a = (n * xy_sum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);
	double b = (y_sum - a * x_sum) / n;

	return { a, b };
}

double mean(const vector<double>& vec) {
	return accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
}

CorrelationResult korrel(const vector<double>& x, const vector<double>& y) {
	double x_mean = mean(x);
	double y_mean = mean(y);
	double sum_xy = 0.0;
	double sum_x2 = 0.0;
	double sum_y2 = 0.0;
	size_t n = x.size();

	for (size_t i = 0; i < n; ++i) {
		sum_xy += (x[i] - x_mean) * (y[i] - y_mean);
		sum_x2 += (x[i] - x_mean) * (x[i] - x_mean);
		sum_y2 += (y[i] - y_mean) * (y[i] - y_mean);
	}

	double r = sum_xy / (sqrt(sum_x2) * sqrt(sum_y2));
	double t = r * sqrt(n - 2) / sqrt(1 - r * r);

	return { r, t };
}

vector<double> coffee(double T, double Ts, double r, int time) {
	vector<double> temperatures;

	for (int t = 0; t <= time; t++) {
		double temperature = Ts + (T - Ts) * exp(-r * t);
		temperatures.push_back(temperature);
	}

	return temperatures;
}

void printApproximationResult(ApproximationResult result) {
	cout << "Approximation Result:" << endl;
	cout << "a: " << result.a << ", b = " << result.b << endl;
}

void printCorrelationResult(CorrelationResult result) {
	cout << "Correlation Result:" << endl;
	cout << "Correlation: " << result.correlation << endl;
	cout << "T-value: " << result.t_value << endl;
}

void printCoffee(vector<double> temperatures, vector<double>times) {
	for (int i = 0; i < temperatures.size(); i++) {
		cout << "Time - " << times[i] << ":  " << temperatures[i] << " C" << endl;
	}
}