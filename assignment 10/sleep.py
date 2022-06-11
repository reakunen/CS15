def slowsort(A, i, j):
    if i >= j:
        return
    m = (i+j) / 2
    slowsort(A, i, m)
    slowsort(A, m+1, j)
    if A[j] < A[m]:
        A[j], A[m] = A[m], A[j]
    slowsort(A, i, j-1)

x = [3,2,4,7,3,6,9,1]
slowsort(x, 0, len(x)-1)
