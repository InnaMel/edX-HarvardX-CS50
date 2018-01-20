from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances2():
    distances('cat', 'eat')


def printMatrix(Matrix, lenA, lenB):
    for i in range(lenA):
        for j in range(lenB):
            print(' ', Matrix[i][j], end='')
        print()


# my method for calculation each tuple
def findIndex(topIndex, leftIndex, diagonalIndex, amendmentSubtitude):
    # we can not add to any tuple, so we must create lists
    minIndex = []
    delIndex = []
    insertIndex = []
    subtitudeIndex = []
    # find tuple for delete
    delIndex.append(topIndex[0] + 1)
    delIndex.append(Operation.DELETED)
    # find tuple for insert
    insertIndex.append(leftIndex[0] + 1)
    insertIndex.append(Operation.INSERTED)
    # find tuple for insert subtitude
    subtitudeIndex.append(diagonalIndex[0] + amendmentSubtitude)
    subtitudeIndex.append(Operation.SUBSTITUTED)
    # choose minimum of value
    if (delIndex[0] < insertIndex[0] and delIndex[0] < subtitudeIndex[0]) or (delIndex[0] == subtitudeIndex[0]) or (subtitudeIndex[0] == delIndex[0] and subtitudeIndex[0] == insertIndex[0]):
        minIndex = delIndex
    elif (insertIndex[0] < delIndex[0] and insertIndex[0] < subtitudeIndex[0]) or (insertIndex[0] == subtitudeIndex[0]):
        minIndex = insertIndex
    elif subtitudeIndex[0] < delIndex[0] and subtitudeIndex[0] < insertIndex[0]:
        minIndex = subtitudeIndex
    # return minIndex as tuple (now it is list)
    return tuple(minIndex)


def distances(a, b):
    lenA = len(a) + 1
    lenB = len(b) + 1
    list1 = a
    list2 = b
    # fill matrList by zeros. matrList - is 2d array with coefficient for substitute (if characters equal = 0, else = 1). Dimension must be equal dimension of Matrix
    matrList = [[0 for j in range(lenB)] for i in range(lenA)]
    for i in range(lenA):
        for j in range(lenB):
            matrList[0][j] = j
            matrList[i][0] = i
    # fill matrList by coefficients for subtitute
    for i in range(lenA - 1):
        for j in range(lenB - 1):
            if list1[i] == list2[j]:
                matrList[i + 1][j + 1] = 0
            else:
                matrList[i + 1][j + 1] = 1
    # fill Matrix by zeros
    Matrix = [[0 for j in range(lenB)] for i in range(lenA)]
    # fill zero row and zero column of Matrix by indexes
    for j in range(1, lenB):
        Matrix[0][j] = (j, Operation.INSERTED)
    for i in range(1, lenA):
        Matrix[i][0] = (i, Operation.DELETED)
    # important! value = 0, opertion = None
    Matrix[0][0] = (0, None)
    # fill Matrix by tuples
    for i in range(1, lenA):
        for j in range(1, lenB):
            # call my method "findIndex"
            Matrix[i][j] = findIndex(Matrix[i - 1][j], Matrix[i][j - 1],
                                     Matrix[i - 1][j - 1], matrList[i][j])
    #printMatrix(Matrix, lenA, lenB)
    return Matrix


if __name__ == "__main__":
    distances2()