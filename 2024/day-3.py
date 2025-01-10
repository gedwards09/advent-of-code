import sys
from utils.AocController import AocController

g_iMaxDigitLength = 3
g_sDisableSubstring = 'don\'t()'
g_sEnableSubstring = 'do()'
g_sMulPrefixSubstring = 'mul('

def Alg1(sFileName):
    with open(sFileName, 'r') as f:
        sInput = f.read()
    return parseInput1(sInput)

def parseInput1(sInput):
    i = 0
    iInputLength = len(sInput)
    iPrefixLength = len(g_sMulPrefixSubstring)
    piDigit = [None, None]
    s = 0
    while i < iInputLength:
        # match against exact string 'mul('
        j = GetMatchSubstringPrefixCharacterCount(sInput, g_sMulPrefixSubstring, iStartIndex=i)
        i += j
        if j == 0:
            i += 1
        if j < iPrefixLength:
            continue
        # match up to 3 digits
        j = GetMatchDigitCharacterCount(sInput, iStartIndex=i, iMaxDigitMatch=g_iMaxDigitLength)
        if j == 0:
            continue
        piDigit[0] = int(sInput[i:i+j])
        i += j
        # match char ','
        j = GetMatchSubstringPrefixCharacterCount(sInput, sSearchWord=',', iStartIndex=i)
        if j == 0:
            continue
        i += j
        # match up to 3 digits
        j = GetMatchDigitCharacterCount(sInput, iStartIndex=i, iMaxDigitMatch=g_iMaxDigitLength)
        if j == 0:
            continue
        piDigit[1] = int(sInput[i:i+j])
        i += j
        # match next char '('
        j = GetMatchSubstringPrefixCharacterCount(sInput, sSearchWord=')', iStartIndex=i)
        if j == 0:
            continue
        i += j
        s += piDigit[0] * piDigit[1]
    return s

def GetMatchSubstringPrefixCharacterCount(sInput, sSearchWord, iStartIndex):
    j = 0
    while j < len(sSearchWord) and iStartIndex + j < len(sInput)\
        and sInput[iStartIndex+j] == sSearchWord[j]:
        j += 1
    return j

def GetMatchDigitCharacterCount(sInput, iStartIndex, iMaxDigitMatch):
    j = 0
    while j < iMaxDigitMatch and iStartIndex + j < len(sInput)\
    and '0' <= sInput[iStartIndex + j] and sInput[iStartIndex + j] <= '9':
        j += 1
    return j

def Alg2(sFileName):
    with open(sFileName, 'r') as f:
        sInput = f.read()
    return parseInput2(sInput)

def parseInput2(sInput):
    i = 0
    iDisableSubstringLength = len(g_sDisableSubstring)
    iEnableSubstringLength = len(g_sEnableSubstring)
    iInputLength = len(sInput)
    iMulPrefixSubstringLength = len(g_sMulPrefixSubstring)
    piDigit = [None, None]
    s = 0
    enable = True
    while i < iInputLength:
        # match against exact substring 'do()'
        j = GetMatchSubstringPrefixCharacterCount(sInput, g_sEnableSubstring, iStartIndex=i)
        if j == iEnableSubstringLength:
            i += j
            enable = True
            continue
        # match against exact substring 'dont()'
        j = GetMatchSubstringPrefixCharacterCount(sInput, g_sDisableSubstring, iStartIndex=i)
        if j == iDisableSubstringLength:
            i += j
            enable = False
            continue
        if not enable:
            i += 1
            continue
        # match against exact string 'mul('
        j = GetMatchSubstringPrefixCharacterCount(sInput, g_sMulPrefixSubstring, iStartIndex=i)
        i += j
        if j == 0:
            i += 1
        if j < iMulPrefixSubstringLength:
            continue
        # match up to 3 digits
        j = GetMatchDigitCharacterCount(sInput, iStartIndex=i, iMaxDigitMatch=g_iMaxDigitLength)
        if j == 0:
            continue
        piDigit[0] = int(sInput[i:i+j])
        i += j
        # match char ','
        j = GetMatchSubstringPrefixCharacterCount(sInput, sSearchWord=',', iStartIndex=i)
        if j == 0:
            continue
        i += j
        # match up to 3 digits
        j = GetMatchDigitCharacterCount(sInput, iStartIndex=i, iMaxDigitMatch=g_iMaxDigitLength)
        if j == 0:
            continue
        piDigit[1] = int(sInput[i:i+j])
        i += j
        # match next char '('
        j = GetMatchSubstringPrefixCharacterCount(sInput, sSearchWord=')', iStartIndex=i)
        if j == 0:
            continue
        i += j
        s += piDigit[0] * piDigit[1]
    return s

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()