import sys
from utils.AocController import AocController
from utils.Int2DArray import Int2DArray

def Alg1(sFileName):
    arr = Int2DArray(sFileName)
    arr.Transpose()
    arr.getRow(0).sort()
    arr.getRow(1).sort()
    return getDistance(arr.getRow(0), arr.getRow(1))
    
def getDistance(arr1, arr2):
    if len(arr1) != len(arr2):
        raise Exception()
    dist = 0
    for colNum in range(len(arr1)):
        dist += abs(arr2[colNum] - arr1[colNum])
    return dist

def Alg2(sFileName):
    arr = Int2DArray(sFileName)
    dic = {}
    colNum = 1
    for rowNum in range(arr.getYLength()):
        val = arr.get(rowNum, colNum)
        if val in dic:
            dic[val] += 1
        else:
            dic[val] = 1
    sum = 0
    colNum = 0
    for rowNum in range(arr.getYLength()):
        val = arr.get(rowNum, colNum)
        if val in dic:
            sum += val * dic[val]
    return sum

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()