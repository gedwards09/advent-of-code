import sys
from utils.AocArgs import AocArgs

def alg(args):
    if args.PartNumber == 1:
        return alg_1(args.InputFileName)
    elif args.PartNumber == 2:
        return alg_2(args.InputFileName)

def alg_1(fileName):
    arr = parseFile(fileName)
    arr = transpose(arr)
    arr[0].sort()
    arr[1].sort()
    return getDistance(arr[0], arr[1])

def parseFile(fileName):
    with open(fileName,'r') as f:
        return [[int(el) for el in line.split()]\
                for line in f.read().split('\n')]

def transpose(arr):
        return [[int(arr[rowNum][colNum]) for rowNum in range(len(arr))]\
                for colNum in range(len(arr[0]))]
    
def getDistance(arr1,arr2):
    if len(arr1) != len(arr2):
        raise Exception()
    dist = 0
    for colNum in range(len(arr1)):
        dist += abs(arr2[colNum] - arr1[colNum])
    return dist

def alg_2(fileName):
    arr = parseFile(fileName)
    dic = {}
    colNum = 1
    for rowNum in range(len(arr)):
        val = arr[rowNum][colNum]
        if val in dic:
            dic[val] += 1
        else:
            dic[val] = 1
    sum = 0
    colNum = 0
    for rowNum in range(len(arr)):
        val = arr[rowNum][colNum]
        if val in dic:
            sum += val * dic[val]
    return sum

def __main__():
    args = AocArgs(sys.argv)
    print(alg(args))

if __name__ == "__main__":
    __main__()