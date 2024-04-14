import math

class ApproximationResult:
    def __init__(self, a, b):
        self.a = a
        self.b = b

class CorrelationResult:
    def __init__(self, correlation, t_value):
        self.correlation = correlation
        self.t_value = t_value

def aproks(x, y):
    x_sum = sum(x)
    y_sum = sum(y)
    x2_sum = sum(xi * xi for xi in x)
    xy_sum = sum(xi * yi for xi, yi in zip(x, y))
    n = len(x)

    a = (n * xy_sum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum)
    b = (y_sum - a * x_sum) / n

    return ApproximationResult(a, b)

def mean(vec):
    return sum(vec) / len(vec)

def korrel(x, y):
    x_mean = mean(x)
    y_mean = mean(y)
    sum_xy = sum((xi - x_mean) * (yi - y_mean) for xi, yi in zip(x, y))
    sum_x2 = sum((xi - x_mean) ** 2 for xi in x)
    sum_y2 = sum((yi - y_mean) ** 2 for yi in y)
    n = len(x)

    r = sum_xy / (math.sqrt(sum_x2) * math.sqrt(sum_y2))
    t = r * math.sqrt(n - 2) / math.sqrt(1 - r * r)

    return CorrelationResult(r, t)

def coffee(T, Ts, r, time):
    temperatures = []

    for t in range(time + 1):
        temperature = Ts + (T - Ts) * math.exp(-r * t)
        temperatures.append(temperature)

    return temperatures

def printApproximationResult(result):
    print("Approximation Result:")
    print("a:", result.a, ", b =", result.b)

def printCorrelationResult(result):
    print("Correlation Result:")
    print("Correlation:", result.correlation)
    print("T-value:", result.t_value)

def printCoffee(temperatures, times):
    for i in range(len(temperatures)):
        print("Time -", times[i], ":", temperatures[i], "C")

def main():
    T = 90  # Начальная температура кофе
    Ts = 26  # Температура комнаты
    r = 0.01  # Коэффициент остывания
    time = 60  # Временной предел в минутах

    temperatures = coffee(T, Ts, r, time)

    times = list(range(time + 1))

    approx_result = aproks(times, temperatures)
    corr_result = korrel(times, temperatures)

    printApproximationResult(approx_result)
    printCorrelationResult(corr_result)
    printCoffee(temperatures, times)

if __name__ == "__main__":
    main()
