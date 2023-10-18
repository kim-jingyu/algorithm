from typing import MutableSequence


def qsort(a: MutableSequence, left: int, right: int) -> None:
    pl = left
    pr = right
    pivot = a[(left + right) // 2]

    # 퀵 정렬에서 나누는 과정 출력하기
    print(f'a[{left}] ~ a[{right}]: ', *a[left: right + 1])

    while pl <= pr:
        while a[pl] < pivot:
            pl += 1
        while a[pr] > pivot:
            pr -= 1
        if pl <= pr:
            a[pl], a[pr] = a[pr], a[pl]
            pl += 1
            pr -= 1

    # 킥 정렬의 배열 나누기
    if left < pr:
        qsort(a, left, pr)
    if pl < right:
        qsort(a, pl, right)


# 이렇게 작성하면 프로그램 본문에서 함수를 호출할 때 일관성을 유지할 수 있다.
def quick_sort(a: MutableSequence) -> None:
    qsort(a, 0, len(a) - 1)


if __name__ == '__main__':
    print('퀵 정렬을 수행한다.')
    num = int(input('원소 수를 입력하세요: '))
    arr = [None] * num

    for i in range(num):
        arr[i] = int(input(f'arr[{i}]: '))

    quick_sort(arr)

    print('오름차순으로 정렬했습니다.')
    for i in range(num):
        print(f'arr[{i}] = {arr[i]}')