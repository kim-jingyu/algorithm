# 1 1 2 3 5 8 13

def fibonacci_loop(n):
    if n <= 0:
        return []
    elif n == 1:
        return [1]
    elif n == 2:
        return [1, 1]

    fibo_arr = [1, 1]
    for i in range(2, n):
        fibo_arr.append(fibo_arr[i - 1] + fibo_arr[i - 2])
    return fibo_arr


def fibonacci_recursive(n):
    if n <= 0:
        return []
    elif n == 1:
        return [1]
    elif n == 2:
        return [1, 1]

    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)


def fibonacci_another_recursive(n):
    if n <= 0:
        return []
    elif n == 1:
        return [1]
    elif n == 2:
        return [1, 1]
    else:
        sequence = fibonacci_another_recursive(n - 1)
        sequence.append(sequence[-1] + sequence[-2])
        return sequence


dp = [1, 1] + [0] * 9


def fibo_dp(n):
    if dp[n]:
        return n
    dp[n] = fibo_dp(n - 1) + fibo_dp(n - 2)
    return dp[n]


if __name__ == '__main__':
    print(fibo_dp(3))
