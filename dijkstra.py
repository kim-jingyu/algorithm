""" This is input value. you can just copy and paste it.
5 6 1
1 2 3
1 4 8
1 5 9
2 1 2
2 3 2
3 2 2
3 4 1
3 5 3
4 1 8
4 3 1
5 1 9
"""
import heapq
import sys


def dijkstra(start):
    heap = []
    heapq.heappush(heap, [0, start])  # 최소힙은 배열의 첫번째 값을 기준으로 배열을 정렬한다.
    INF = float('inf')
    weights = [INF] * (vertex + 1)  # DP에 활용할 memorization 테이블 생성
    weights[start] = 0  # 자기 자신으로 가는 사이클은 없다.

    while heap:
        weight, node = heapq.heappop(heap)
        if weight > weights[node]:  # 비용 최적화 전부터 큰 비용일 경우는 고려할 필요가 없다.
            continue

        for n, w in graph[node]:  # 최소 비용을 가진 노드를 그리디하게 방문한 경우에는 연결된 간선을 모두 확인해야 한다.
            W = weight + w
            if weights[n] > W:  # 여러 경로를 방문해 합쳐진 가중치 W가 더 비용이 적다면
                weights[n] = W  # 업데이트한다.
                heapq.heappush(heap, (W, n))  # 최소 비용을 가진 노드와 합쳐진 가중치를 추가한다.

    return weights


vertex, edge, start = map(int, sys.stdin.readline().rstrip().split())
graph = [[] for _ in range(vertex + 1)]

for _ in range(vertex + edge):
    src, dst, weight = map(int, sys.stdin.readline().rstrip().split())
    graph[src].append([dst, weight])

weights = dijkstra(start)
print(weights)