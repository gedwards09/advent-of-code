import sys
from utils.AocController import AocController
from utils.Map2D.Map2D import Map2D

g_sSearchWord = 'XMAS'
g_sSearchWord2 = 'MAS'

def Alg1(sFileName):
    map = Map2D(sFileName)
    return wordSearchStringCount(map, g_sSearchWord)

def wordSearchStringCount(map: Map2D, sSearchWord: str):
    ct = 0
    for line in map.iterateRows():
        ct += substringOrReverseSubstringCount(line, sSearchWord)
    for line in map.iterateCols():
        ct += substringOrReverseSubstringCount(line, sSearchWord)
    for line in map.iterateDiagonals():
        ct += substringOrReverseSubstringCount(line, sSearchWord)
    return ct

# assumes string and reverse have no repeated characters
def substringOrReverseSubstringCount(sInput, sSearchWord):
    iSzInput = len(sInput)
    iSzSearchWord = len(sSearchWord)
    sReverseSearchWord = sSearchWord[::-1]
    ct = 0
    i = 0
    while i < iSzInput:
        j = getMatchSubstringCharacterCount(sInput, iSzInput, sSearchWord, iSzSearchWord, iStartIndex=i)
        if j == 0:
            j = getMatchSubstringCharacterCount(sInput, iSzInput, sReverseSearchWord, iSzSearchWord, iStartIndex=i)
        if j == iSzSearchWord:
            # match!
            ct += 1
            # increment 1 less because reverse string can start on the last letter
            i += j - 1
        else:
            i += j
            if j == 0:
                i += 1
    return ct

def getMatchSubstringCharacterCount(sInput, iSzInput, sSearchWord, iSzSearchWord, iStartIndex):
    j = 0
    while j < iSzSearchWord and iStartIndex + j < iSzInput\
        and sInput[iStartIndex + j] == sSearchWord[j]:
        j += 1
    return j

def Alg2(sFileName):
    map = Map2D(sFileName)
    iSzSearchWord = len(g_sSearchWord2)
    return getMatchXSubstringCount(map, g_sSearchWord2, iSzSearchWord)

def getMatchXSubstringCount(map: Map2D, sSearchWord: str, iSzSearchWord: int):
    iCount = 0
    iRowNum = map.getYLength() - iSzSearchWord
    iColNum = 0
    # iterate over all starting positions:  .>->->
    #                                       ^
    #                                       ^
    #                                       ^
    while iRowNum >= 0 and iColNum <= map.getYLength() - iSzSearchWord:
        iCount += getXSubstringCount(map, sSearchWord, iSzSearchWord, iStartRow=iRowNum, iStartCol=iColNum)
        if iRowNum > 0:
            iRowNum -= 1
        else:
            iColNum += 1
    return iCount

def getXSubstringCount(map: Map2D, sSearchWord, iSzSearchWord, iStartRow, iStartCol):
    iRowNum = iStartRow
    iColNum = iStartCol
    iCount = 0
    while iRowNum <= map.getYLength() - iSzSearchWord and iColNum <= map.getXLength() - iSzSearchWord:
        bIsMatch, iFirstMatchCharCount = matchBlockPattern(map, sSearchWord, iSzSearchWord, iRowNum, iColNum)
        if bIsMatch:
            iCount += 1
        iIncrement = iFirstMatchCharCount - 1 if iFirstMatchCharCount == iSzSearchWord\
                    else iFirstMatchCharCount if iFirstMatchCharCount > 0\
                    else 1
        iRowNum += iIncrement
        iColNum += iIncrement
    return iCount

def matchBlockPattern(map: Map2D, sSearchWord, iSzSearchWord, iRowNum, iColNum):
    if iRowNum + iSzSearchWord > map.getYLength() or iColNum + iSzSearchWord > map.getXLength()\
        or iRowNum < 0 or iColNum < 0:
        return False, 0
    
    sFirstDiag = ''.join([map.get(iRowNum + i, iColNum + i) for i in range(iSzSearchWord)])
    iFirstMatchCharCount = getMatchSubstringOrReverseSubstringCharacterCount(sFirstDiag, iSzSearchWord, sSearchWord, iSzSearchWord)
    if iFirstMatchCharCount != iSzSearchWord:
        return False, iFirstMatchCharCount
    sSecondDiag = ''.join([map.get(iRowNum + iSzSearchWord - i - 1, iColNum + i) for i in range(iSzSearchWord)])
    iMatchCharCount = getMatchSubstringOrReverseSubstringCharacterCount(sSecondDiag, iSzSearchWord, sSearchWord, iSzSearchWord)
    return iMatchCharCount == iSzSearchWord, iFirstMatchCharCount

# Assumes no repeated characters
# true for search string 'MAS'
def getMatchSubstringOrReverseSubstringCharacterCount(sInput, iSzInput, sSearchWord, iSzSearchWord, iStartIndex=0):
    sReverseSearchWord = sSearchWord[::-1]
    iMatchCharCount = getMatchSubstringCharacterCount(sInput, iSzInput, sSearchWord, iSzSearchWord, iStartIndex)
    if iMatchCharCount == 0:
        iMatchCharCount = getMatchSubstringCharacterCount(sInput, iSzInput, sReverseSearchWord, iSzSearchWord, iStartIndex)
    return iMatchCharCount


def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()