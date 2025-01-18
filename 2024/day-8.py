import sys
from utils.AocController import AocController
from utils.Map2D.Map2D import Map2D

def Alg1(sFileName):
    return doAntinodeCount(sFileName, bSequential=False)

def doAntinodeCount(sFileName, bSequential):
    pMap = Map2D(sFileName)
    return antinodeCount(pMap, bSequential)

def antinodeCount(pMap: Map2D, bSequential):
    pPositions = getAntennaPositions(pMap)
    pAntinodes = {}
    for cElement in pPositions:
        pAntinodes = getAntinodes(pAntinodes, pMap, pPositions[cElement], bSequential)
    return countAntinodes(pAntinodes)

def getAntennaPositions(pMap: Map2D):
    pPositions = {}
    for iRowNum in range(pMap.getYLength()):
        for iColNum in range(pMap.getXLength()):
            cElement = pMap.get(iRowNum, iColNum)
            if cElement == '.':
                continue
            elif cElement not in pPositions:
                pPositions[cElement] = [(iRowNum, iColNum)]
            else:
                pPositions[cElement].append((iRowNum, iColNum))
    return pPositions

def getAntinodes(pAntinodes, pMap: Map2D, pPositionList, bSequential):
    iSzList = len(pPositionList)
    for iLeftIdx in range(iSzList-1):
        iLeftRow, iLeftCol = pPositionList[iLeftIdx]
        for iRightIdx in range(iLeftIdx+1, iSzList):
            iRightRow, iRightCol = pPositionList[iRightIdx]
            iRowDiff = iLeftRow - iRightRow
            iColDiff = iLeftCol - iRightCol

            if bSequential:
                pAntinodes = addAntinodeSequence(pAntinodes, pMap, iLeftRow, iLeftCol, iRowDiff, iColDiff)
                pAntinodes = addAntinodeSequence(pAntinodes, pMap, iRightRow, iRightCol, -iRowDiff, -iColDiff)
            else:
                pAntinodes = addAntinode(pAntinodes, pMap, iLeftRow + iRowDiff, iLeftCol + iColDiff)
                pAntinodes = addAntinode(pAntinodes, pMap, iRightRow - iRowDiff, iRightCol - iColDiff)
    return pAntinodes

def addAntinodeSequence(pAntinodes, pMap: Map2D, iAntinodeRow, iAntinodeCol, iRowDiff, iColDiff):
    while pMap.isValid(iAntinodeRow, iAntinodeCol):
        pAntinodes = addAntinode(pAntinodes, pMap, iAntinodeRow, iAntinodeCol)
        iAntinodeRow += iRowDiff
        iAntinodeCol += iColDiff
    return pAntinodes

def addAntinode(pAntinodes, pMap: Map2D, iRow, iCol):
    if pMap.isValid(iRow, iCol) and (iRow, iCol) not in pAntinodes:
        pAntinodes[(iRow, iCol)] = None
    return pAntinodes

def countAntinodes(pAntinodes):
    return len(list(pAntinodes.keys()))

def Alg2(sFileName):
    return doAntinodeCount(sFileName, bSequential=True)

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()