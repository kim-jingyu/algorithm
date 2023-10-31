import sys
input = lambda: sys.stdin.readline().rstrip()

n = int(input())
board = [list(map(int, input().split())) for _ in range(n)]

for k in range(n):
    for i in range(n):
        for j in range(n):
            if board[i][j] == 1 or (board[i][k] == 1 and board[k][j] == 1):
                board[i][j] = 1

print(board)