import sys
from utils.AocController import AocController
from utils.BinaryTreeNode.BinaryTreeNode import BinaryTreeNode
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

class XLogicBinaryNode(BinaryTreeNode):

    g_sNamePrefixes = 'xy'

    def __init__(self, sName):
        super().__init__(None)
        self._sName = sName
        self._sType = None
        self._iHighestBit = self.__initHighestBit(sName)
        self._bIsValid = self.__initIsValid(sName)

    def __initHighestBit(self, sName):
        if sName[0] in XLogicBinaryNode.g_sNamePrefixes:
            return int(sName[1:])
        else:
            return -1
			
    def __initIsValid(self, sName):
        return sName[0] in XLogicBinaryNode.g_sNamePrefixes

    def getName(self):
        return self._sName
        
    def setType(self, sType):
        self._sType = sType

    def getType(self):
        return self._sType
    
    def GetHighestBit(pNode: BinaryTreeNode):
        if pNode == None:
            return -1
        if pNode._getHighestBit() >= 0:
            return pNode._getHighestBit()
        iLeftHighestBit = XLogicBinaryNode.GetHighestBit(pNode.getLeft())
        iRightHighestBit = XLogicBinaryNode.GetHighestBit(pNode.getRight())
        iHighestBit = max(iLeftHighestBit, iRightHighestBit)
        pNode.setHighestBit(iHighestBit)
        return iHighestBit
    
    def _getHighestBit(self):
        return self._iHighestBit
    
    def setHighestBit(self, iHighestBit):
        self._iHighestBit = iHighestBit

    def isValid(self):
        return self._bIsValid
    
    def setValid(self, bIsValid: bool):
        self._bIsValid = bIsValid
    
    def hasData(self):
        return self._sType != None

    def SwapOutput(self, pOther):
        self.__swapLeft(pOther)
        self.__swapRight(pOther)
        self.__swapType(pOther)
        self.__swapHighestBit(pOther)

    def __swapLeft(self, pOther):
        pTmp = pOther.getLeft()
        pOther.setLeft(self.getLeft())
        self.setLeft(pTmp)

    def __swapRight(self, pOther):
        pTmp = pOther.getRight()
        pOther.setRight(self.getRight())
        self.setRight(pTmp)

    def __swapType(self, pOther):
        sTmp = pOther.getType()
        pOther.setType(self._sType)
        self._sType = sTmp

    def __swapHighestBit(self, pOther):
        iTmp = self._iHighestBit
        self._iHighestBit = pOther._getHighestBit()
        pOther.setHighestBit(iTmp)
    
class XLogicBinaryTree:

    g_pLogicBinaryNodeIndex = {}

    def __init__(self, sRootName, pGateList):
        self._pRoot = self.__buildTree(sRootName, pGateList)
    
    def __buildTree(self, sRootName, pGateList):
        pRoot = XLogicBinaryNode(sName=sRootName)
        self.__rBuildTree(pRoot, pGateList)
        _ = XLogicBinaryNode.GetHighestBit(pRoot)
        return pRoot

    def __rBuildTree(self, pNode: XLogicBinaryNode, pGateList):
        sName = pNode.getName()
        if sName not in pGateList:
            return
        if pNode.hasData():
            return
        tData = pGateList[sName]
        pNode.setLeft(self.__makeNode(tData[0]))
        pNode.setType(tData[1])
        pNode.setRight(self.__makeNode(tData[2]))
        self.__rBuildTree(pNode.getLeft(), pGateList)
        self.__rBuildTree(pNode.getRight(), pGateList)

    def __makeNode(self, sName):
        if sName in XLogicBinaryTree.g_pLogicBinaryNodeIndex:
            return XLogicBinaryTree.g_pLogicBinaryNodeIndex[sName]
        pNode = XLogicBinaryNode(sName)
        XLogicBinaryTree.g_pLogicBinaryNodeIndex[sName] = pNode
        return pNode

    def getRoot(self):
        return self._pRoot

    def isValid(self):
        iHighestBit = self._pRoot.GetHighestBit()
        iRef = 0x7 << iHighestBit >> 1
        # print("{:0x}".format(iRef))
        iX = iRef
        for _ in range(3):
            iY = iRef
            for __ in range(3):
                if self.Evaluate(iX, iY) != 0x1 & (iX + iY) >> iHighestBit:
                    return False
                iY >>= 1
            iX >>= 1
        return True

    def Evaluate(self, iX, iY):
        self.__rEvaluate(self._pRoot, iX, iY)
        return self._pRoot.getData()

    def __rEvaluate(self, pNode, iX, iY):
        if pNode == None:
            return
        self.__rEvaluate(pNode.getLeft(), iX, iY)
        self.__rEvaluate(pNode.getRight(), iX, iY)
        sName = pNode.getName()
        if sName[0] == 'x':
            iData = iX >> int(sName[1:])
            iData &= 0x1
        elif sName[0] == 'y':
            iData = iY >> int(sName[1:])
            iData &= 0x1
        else:
            iLeft = pNode.getLeft().getData()
            iRight = pNode.getRight().getData()
            sType = pNode.getType()
            if sType == 'AND':
                iData = iLeft & iRight
            elif sType == 'OR':
                iData = iLeft | iRight
            elif sType == 'XOR':
                iData = iLeft ^ iRight
        pNode.setData(iData)

    def SetNodesValid(self):
        XLogicBinaryTree.__rSetNodesValid(self._pRoot)
        
    def __rSetNodesValid(pNode: XLogicBinaryNode):
        if pNode == None:
            return
        XLogicBinaryTree.__rSetNodesValid(pNode.getLeft())
        XLogicBinaryTree.__rSetNodesValid(pNode.getRight())
        pNode.setValid(True)

class XLogicForest(XLogicGate):

    def __init__(self, sFileName):
        super().__init__(sFileName)
        self._pForest = self.__initForest()

    # Override
    def _makeList(self):
        return {}

    # Override
    def _addToList(self, pList, tData):
        pList[tData[3]] = tData[:3]
    
    def __initForest(self):
        pForest = {}
        for sZVar in self._pZVarList:
            pForest[sZVar] = self.__buildTree(sZVar)
        return pForest

    def __buildTree(self, sZVar):
        return XLogicBinaryTree(sRootName=sZVar, pGateList=self._pGateList)
    
    def Solve(self):
        pSwapList = []
        for iIdx in range(len(self._pZVarList)):
            pTree = self.__getTree(iIdx)
            bIsValid = pTree.isValid()
            if bIsValid:
                self.SetNodesValid(iIdx)
            if not bIsValid:
                self.Fix(iIdx, pSwapList)
        pSwapList.sort()
        return ','.join(pSwapList)

    def __getTree(self, iIdx) -> XLogicBinaryTree:
        sName = self._pZVarList[iIdx]
        return self._pForest[sName]

    def SetNodesValid(self, iIdx):
        pTree = self.__getTree(iIdx)
        pTree.SetNodesValid()

    def Fix(self, iIdx, pSwapList):
        pTree = self.__getTree(iIdx)
        pQueue = self.GetFixQueue(pTree)
        iHighestBit = pTree.getRoot().GetHighestBit()
        for iSwapIdx in range(iIdx, len(self._pZVarList)):
            pSwapTree = self.__getTree(iSwapIdx)
            pSwapQueue = self.GetFixQueue(pSwapTree, iHighestBit)
            for pNode in pQueue:
                for pSwapNode in pSwapQueue:
                    if XLogicForest.ShouldNotSwap(pNode, pSwapNode):
                        continue
                    if XLogicForest.SwapOutputAndTest(pTree, pNode, pSwapTree, pSwapNode):
                        pSwapList.append(pNode.getName()) 
                        pSwapList.append(pSwapNode.getName())
                        return

    def GetFixQueue(self, pTree: XLogicBinaryTree, iHighestBit=None):
        pQueue = []
        XLogicForest.__rGetFixQueue(pTree.getRoot(), pQueue, iHighestBit)
        return pQueue
    
    def __rGetFixQueue(pNode:XLogicBinaryNode, pQueue, iHighestBit):
        if pNode == None:
            return
        if pNode.isValid():
            return
        if iHighestBit == None or pNode.GetHighestBit() <= iHighestBit:
            pQueue.append(pNode)
        XLogicForest.__rGetFixQueue(pNode.getLeft(), pQueue, iHighestBit)
        XLogicForest.__rGetFixQueue(pNode.getRight(), pQueue, iHighestBit)
        return

    def nodeIsValid(pNode: XLogicBinaryNode):
        return pNode != None and pNode.isValid()
    
    def ShouldNotSwap(pNode:XLogicBinaryNode, pSwapNode:XLogicBinaryNode):
        return XLogicForest.__isParentOfNode(pNode, pSwapNode)\
            or XLogicForest.__isParentOfNode(pSwapNode, pNode)

    def __isParentOfNode(pParentNode: XLogicBinaryNode, pOtherNode: XLogicBinaryNode):
        pQueue = [pParentNode]
        while len(pQueue) > 0:
            pCurrent = pQueue.pop(0)
            if pCurrent == pOtherNode:
                return True
            if not pCurrent.getLeft().isValid():
                pQueue.append(pCurrent.getLeft())
            if not pCurrent.getRight().isValid():
                pQueue.append(pCurrent.getRight())
        return False

    def SwapOutputAndTest(pTree: XLogicBinaryTree, pNode: XLogicBinaryNode, pSwapTree:XLogicBinaryTree, pSwapNode: XLogicBinaryNode):
        if pNode.getName() == 'cgh' and pSwapNode.getName() == 'rdj':
            raise Exception()
        pNode.SwapOutput(pSwapNode)
        if pTree.isValid() and pSwapTree.isValid():
            return True
        pNode.SwapOutput(pSwapNode)
        return False

def Alg1(sFileName):
    pGate = XLogicGate(sFileName)
    return pGate.Solve()

def Alg2(sFileName):
    pForest = XLogicForest(sFileName)
    return pForest.Solve()

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()