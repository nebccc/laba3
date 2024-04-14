import math

def function1(x):
    y = 2 - math.sqrt(4 - math.pow(x + 2, 2))
    return y

def function2(x):
    return -1 * x

def function3(x):
    y = math.sqrt(math.pow(2, 2) - math.pow(x - 3, 2)) - 1
    return y

def compute_table(X_start, X_end, dx):
    # Table header
    print("X\t| Y")
    print("-----------------------")

    x = X_start

    while x <= X_end:
        y1 = function1(x)
        y2 = function2(x)
        y3 = function3(x)

        if y1 <= 2 and x <= -2:
            print(f"{x}\t| {y1}")

        if y2 <= 0 and x >= 0 and x <= 3:
            print(f"{x}\t| {y2}")

        if y3 >= -1 and x >= 3 and x <= 5:
            print(f"{x}\t| {y3}")

        x += dx

def main():
    X_start = -5
    X_end = 5
    dx = 0.5

    compute_table(X_start, X_end, dx)

if __name__ == "__main__":
    main()
