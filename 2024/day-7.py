import sys
from utils.AocController import AocController

def Alg1(sFileName):
    pInput = getInput(sFileName)
    fpTargetChecker = lambda iTarget, pFactors : binaryCanAchieveTarget(iTarget, pFactors)
    return processEquations(pInput, fpTargetChecker)

def getInput(sFileName):
    with open(sFileName, 'r') as f:
        return f.read().split('\n')
    
def processEquations(pInput, fpTargetChecker):
    iSum = 0
    for sLine in pInput:
        pArr = sLine.split(': ')
        iTarget = int(pArr[0])
        pFactors = [int(s) for s in pArr[1].split(' ')]
        if fpTargetChecker(iTarget, pFactors):
            iSum += iTarget
    return iSum

def binaryCanAchieveTarget(iTarget, pFactors):
    return _canAchieveTarget(pFactors[0], iTarget, pFactors, 1, '+*')

def _canAchieveTarget(iCurrentData, iTarget, pFactors, idx, sOperations):
    if idx == len(pFactors):
        return iCurrentData == iTarget
    elif iCurrentData > iTarget:
        return False
    
    iNextData = pFactors[idx]
    for c in sOperations:
        if c == '+' and _canAchieveTarget(iCurrentData + iNextData, iTarget, pFactors, idx+1, sOperations):
            return True
        elif c == '*' and _canAchieveTarget(iCurrentData * iNextData, iTarget, pFactors, idx+1, sOperations):
            return True
        elif c == '|':
            iNext = intConcat(iCurrentData, iNextData)
            if _canAchieveTarget(iNext, iTarget, pFactors, idx+1, sOperations):
                return True
    return False
    
def intConcat(iFirst, iSecond):
    return int(str(iFirst) + str(iSecond))

def Alg2(sFileName):
    pInput = getInput(sFileName)
    fpTargetChecker = lambda iTarget, pFactors : trinaryCanAchieveTarget(iTarget, pFactors)
    return processEquations(pInput, fpTargetChecker)

def trinaryCanAchieveTarget(iTarget, pFactors):
    return _canAchieveTarget(pFactors[0], iTarget, pFactors, 1, '+*|')

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()