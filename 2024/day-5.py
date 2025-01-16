import sys
from utils.AocController import AocController
from utils.List.IndexedList import IndexedList
from utils.Map2D.IndexedMap2D import IndexedMap2D

def Alg1(sFileName):
    pRulesIndex, psRawInputs = parseFile(sFileName)
    return _alg1(pRulesIndex, psRawInputs)

def parseFile(sFileName):
    with open(sFileName, 'r') as file:
        psInputRawText = file.read().split('\n\n')
    pRulesIndex = parseRules(psInputRawText[0])
    psRawInputs = parseInputs(psInputRawText[1])
    return pRulesIndex, psRawInputs

def parseRules(sRawText: str) -> IndexedMap2D:
    return IndexedMap2D(sRawText=sRawText, cDelim='|')

def parseInputs(sRawText: str) -> list:
    return [sLine for sLine in sRawText.split('\n')]

def _alg1(pRulesIndex: IndexedMap2D, psRawInputs: list):
    iCount = 0
    for sRawInput in psRawInputs:
        if inputPassesRules(sRawInput, pRulesIndex):
            iCount += getMiddleNumber(sRawInput)
    return iCount

def inputPassesRules(sRawInput: str, pRulesIndex: IndexedMap2D):
    pIndexedList = IndexedList(sRawInput, cDelim=',')
    return indexedListPassesRules(pIndexedList, pRulesIndex)

def indexedListPassesRules(pIndexedList: IndexedList, pRulesIndex: IndexedMap2D):
    for element in pIndexedList.iterate():
        if not pRulesIndex.contains(element):
            continue
        for iRowNum, iColNum in pRulesIndex.iterateCoordinates(element):
            # only check if the element is in the first column so we're not 
            # checking twice
            if iColNum > 0:
                continue
            pRow = pRulesIndex.getRow(iRowNum)
            sElement1 = pRow[0]
            sElement2 = pRow[1]
            if pIndexedList.contains(sElement1) and pIndexedList.contains(sElement2)\
                and pIndexedList.getFirstIndex(sElement1) > pIndexedList.getFirstIndex(sElement2):
                return False
    return True

def getMiddleNumber(sRawInput):
    pArray = sRawInput.split(',')
    iLength = len(pArray)
    iMiddleIndex = iLength // 2
    return int(pArray[iMiddleIndex])

def Alg2(sFileName):
    pRulesIndex, psRawInputs = parseFile(sFileName)
    return _alg2(pRulesIndex, psRawInputs)

def _alg2(pRulesIndex, psRawInputs):
    iSum = 0
    for sRawInput in psRawInputs:
        pIndexedList = IndexedList(sRawText=sRawInput, cDelim=',')
        if indexedListPassesRules(pIndexedList, pRulesIndex):
            continue
        bDoContinue = True
        while bDoContinue:
            pIndexedList = sortInputOrder(pIndexedList, pRulesIndex)
            bDoContinue = not indexedListPassesRules(pIndexedList, pRulesIndex)
        iEl = int(pIndexedList.get(pIndexedList.getLength() // 2))
        # print(iEl)
        iSum += iEl
    return iSum

def sortInputOrder(pIndexedList: IndexedList, pRulesIndex: IndexedMap2D) -> IndexedList:
    for pRow in pRulesIndex.iterateRows():
        sFirst, sSecond = pRow
        if pIndexedList.contains(sFirst) and pIndexedList.contains(sSecond):
            iFirstIndex = pIndexedList.getFirstIndex(sFirst)
            iSecondIndex = pIndexedList.getFirstIndex(sSecond)
            if iFirstIndex > iSecondIndex:
                # print(sFirst, '|', sSecond)
                # pIndexedList.print()
                pIndexedList = _shift(pIndexedList, iSecondIndex, iFirstIndex)
                # pIndexedList.print()
    return pIndexedList

def _shift(pIndexedList: IndexedList, iStartIdx: int, iStopIdx: int) -> IndexedList:
    if iStartIdx > iStopIdx:
        return _shift(pIndexedList, iStopIdx, iStartIdx)
    for idx in range(iStartIdx, iStopIdx):
        pIndexedList.swap(idx, idx + 1)
    return pIndexedList

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()