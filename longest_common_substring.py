import sys

input = lambda: sys.stdin.readline().rstrip()

string_A = input()
string_B = input()

LCS = [[] * len(string_A) for _ in range(len(string_B))]

for i in range(len(string_A)):
    for j in range(len(string_B)):
        if i == 0 and j == 0:
            LCS[i][j] = 0
        elif string_A[i] == string_B[j]:
            LCS[i][j] = LCS[i - 1][j - 1] + 1
        else:
            LCS[i][j] = 0