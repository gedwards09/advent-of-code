import sys
from utils.AocController import AocController
from utils.LinkedList.LinkedList import LinkedList

class XLogicGate:

    def __init__(self, sFileName):
        with open(sFileName, 'r') as f:
            pParts = f.read().split('\n\n')
        self._pWires = self.__initWires(pParts[0])
        pZVarDict = self.__initZVarDict()
        self._pGateList = self.__initGateList(pParts[1], pZVarDict)
        self._pZVarList = self.__initZVarList(pZVarDict)

    def __initWires(self, sRawText):
        pWires = {}
        for sLine in sRawText.split('\n'):
            sName, iVal = self.__parseWire(sLine)
            pWires[sName] = iVal
        return pWires

    def __parseWire(self, sLine):
        sName, sVal = sLine.split(': ')
        return sName, int(sVal)
    
    def __initZVarDict(self):
        return {0:0}
        
    def __initGateList(self, sRawText, pZVarDict):
        pList = self._makeList()
        for tData in self.__iterateGateConfig(sRawText):
            self.__addZVarIfStartsWithZ(pZVarDict, tData[3])
            self._addToList(pList, tData)
        return pList
    
    def _makeList(self):
        return LinkedList()
    
    def __iterateGateConfig(self, sRawText):
        for sLine in sRawText.split('\n'):
            yield self.__parseGateConfig(sLine)

    def __parseGateConfig(self, sLine):
        pPiece = sLine.split(' ')
        return (pPiece[0], pPiece[1], pPiece[2], pPiece[4])
    
    def __addZVarIfStartsWithZ(self, pZVarDict, sName):
        if self.__startsWithZ(sName):
            self.__addToZVar(pZVarDict, sName)
    
    def __startsWithZ(self, sName):
        return sName[0] == 'z'
    
    def __addToZVar(self, pZVarDict, sName):
        iIdx = int(sName[1:])
        pZVarDict[iIdx+1] = sName
        pZVarDict[0] += 1
    
    def _addToList(self, pList, tData):
        pList.addToBack(tData)

    def __initZVarList(self, pZVarList):
        return [pZVarList[iIdx+1] for iIdx in range(pZVarList[0])]
    
    def canGetValue(self):
        for sZVar in self._pZVarList:
            if sZVar not in self._pWires:
                return False
        return True
    
    def getValue(self):
        iOutput = 0
        for iIdx in range(len(self._pZVarList), 0, -1):
            iOutput <<= 1
            sZVar = self._pZVarList[iIdx-1]
            iOutput += self._pWires[sZVar]
        return iOutput

    def Solve(self):
        while not self.canGetValue():
            self.__parseGateList()
        return self.getValue()

    def __parseGateList(self):
        pCurrent = self._pGateList.getHead()
        if pCurrent != None:
            tGate = pCurrent.getData()
            if self.__tryExecuteGate(tGate):
                _ = self._pGateList.removeFromFront()
        while pCurrent != None and pCurrent.getNext() != None:
            tGate = pCurrent.getNext().getData()
            if self.__tryExecuteGate(tGate):
                pCurrent.setNext(pCurrent.getNext().getNext())
            else:
                pCurrent = pCurrent.getNext()

    def __tryExecuteGate(self, tGate):
        if tGate[0] in self._pWires and tGate[2] in self._pWires:
            self.__executeGate(tGate)
            return 1
        return 0

    def __executeGate(self, tGate):
        sCmd = tGate[1]
        if sCmd == 'AND':
            self._pWires[tGate[3]] = self._pWires[tGate[0]] & self._pWires[tGate[2]]
        elif sCmd == 'XOR':
            self._pWires[tGate[3]] = self._pWires[tGate[0]] ^ self._pWires[tGate[2]]
        elif sCmd == 'OR':
            self._pWires[tGate[3]] = self._pWires[tGate[0]] | self._pWires[tGate[2]]

def Alg1(sFileName):
    pGate = XLogicGate(sFileName)
    return pGate.Solve()

def Alg2(sFileName):
    pass

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()