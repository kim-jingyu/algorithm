INF = int(1e9)

num_node = int(input("노드의 개수: "))
num_edge = int(input("간선의 개수: "))

distance_table = [[INF] * (num_node + 1) for _ in range(num_node + 1)]

for i in range(1, num_node + 1):
    for j in range(1, num_node + 1):
        if i == j:
            distance_table[i][j] = 0

for _ in range(num_edge):
    a, b, cost = map(int, input("출발노드, 도착노드, 비용 순으로 간선 정보를 입력: ").split())
    distance_table[a][b] = cost

for k in range(1, num_node + 1):
    for i in range(1, num_node + 1):
        for j in range(1, num_node + 1):
            distance_table[i][j] = min(distance_table[i][j], distance_table[i][k] + distance_table[k][j])

for i in range(1, num_node + 1):
    for j in range(1, num_node + 1):
        if distance_table[i][j] == INF:
            print("INF")
        else:
            print(distance_table[i][j], end=' ')
    print()