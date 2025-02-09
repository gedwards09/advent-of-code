import sys
from utils.AocController import AocController

def Alg1(sFileName):
    with open(sFileName, 'r') as f:
        pInput = f.read().split('\n')
    return doAlg(pInput, countTriplesWithNameStartsWithT)

def doAlg(pInput, fpCountTriples, pDict = None, pOutput = None):
    if pDict == None:
        pDict = {}
    iCount = 0
    for sLine in pInput:
        sName, sOther = getNames(sLine)
        pDict = addConnection(pDict, sName, sOther)
        pDict = addConnection(pDict, sOther, sName)
        iCount += fpCountTriples(pDict, sName, sOther, pOutput)
    return iCount

def getNames(sLine):
    return sLine.split('-')

def addConnection(pDict, sName, sOther):
    if sName not in pDict:
        pDict[sName] = {}
    pDict[sName][sOther] = ''
    return pDict

def nameStartsWithT(sName):
    return sName[0] == 't'

def countTriplesWithNameStartsWithT(pDict, sName, sOther, pOutput):
    if nameStartsWithT(sName) or nameStartsWithT(sOther):
        return _countTriples(pDict, sName, sOther, bShouldStartWithT=False)
    else:
        return _countTriples(pDict, sName, sOther, bShouldStartWithT=True)
    
def _countTriples(pDict, sName, sOther, bShouldStartWithT=False, pOutput=None):
    iCount = 0
    for sThirdName in pDict[sName]:
        if sThirdName in pDict[sOther] and ((not bShouldStartWithT) or nameStartsWithT(sThirdName)):
            if pOutput != None:
                pList = [sName, sOther, sThirdName]
                makeSCC(pDict, pList)
                sSCCName = __makeName(pList)
                pOutput[sSCCName] = ''
            iCount += 1
    return iCount

def makeSCC(pDict, pList):
    bContinue = True
    while bContinue:
        bContinue = False
        for sNextName in pDict[pList[0]]:
            if sNextName in pList:
                continue
            if nodeIsSCC(sNextName, pDict, pList[1:]):
                bContinue=True
                break
        if bContinue:
            pList.append(sNextName)

def nodeIsSCC(sNextName, pDict, pList):
    for sOtherName in pList:
        if sNextName not in pDict[sOtherName]:
            return False
    return True

def __makeName(pList):
    pList.sort()
    return ','.join(pList)

def Alg2(sFileName):
    with open(sFileName, 'r') as f:
        pInput = f.read().split('\n')
    pDict = {}
    pOutput = {}
    _ = doAlg(pInput, countTriples, pDict=pDict, pOutput=pOutput)
    iMaxLen = 0
    sMaxKey = ''
    for sKey in pOutput:
        if len(sKey) > iMaxLen:
            iMaxLen = len(sKey)
            sMaxKey = sKey
    return sMaxKey

def countTriples(pDict, sName, sOther, pOutput):
    return _countTriples(pDict, sName, sOther, bShouldStartWithT=False, pOutput=pOutput)

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()