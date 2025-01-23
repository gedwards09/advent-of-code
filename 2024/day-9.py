import sys
from utils.AocController import AocController
from utils.Comparable.IComparable import IComparable
from utils.LinkedList.OrderedLinkedList import OrderedLinkedList

class XDiskDefragmenter:

    def __init__(self, sDiskMap):
        self._sDiskMap = sDiskMap
        self._iSzDiskMap = len(sDiskMap)

    def ComputeChecksum(self):
        pass

    def GetIncrementSumFactor(iStart, iSize):
        return iSize * (iSize + 2 * iStart - 1) // 2
    
def Alg1(sFileName):
    with open(sFileName, 'r') as file:
        d = XDiskBlockDefragmenter(file.read())
    return d.ComputeChecksum()


class XDiskBlockDefragmenter(XDiskDefragmenter):

    def __init__(self, sDiskMap):
        super().__init__(sDiskMap)
        self._iLeftIdx = 0
        self._iLeftId = 0
        self._iRightIdx = self._iSzDiskMap - 1
        self._iRightId = self._iSzDiskMap // 2
        self._iRightDigit = int(sDiskMap[self._iRightIdx])

    def ComputeChecksum(self):
        iSum = 0
        for idx in range(self._iSzDiskMap):
            cDigit = self._sDiskMap[idx]
            iDigit = int(cDigit)
            if iDigit == 0:
                continue
            if self._iLeftId == self._iRightId:
                iSum += self._rightIncrement(self._iRightDigit)
                break
            if idx % 2 == 0:
                iSum += self._leftIncrement(iDigit)
            else:
                iSum += self._rightIncrement(iDigit)
        return iSum

    def _leftIncrement(self, iDigit):
        iIncrement = self._iLeftId * self._getSumIncrementFactor(iDigit)
        self._iLeftId += 1
        return iIncrement
    
    def _getSumIncrementFactor(self, iDigit):
        iFactor = XDiskDefragmenter.GetIncrementSumFactor(self._iLeftIdx, iDigit)
        self._iLeftIdx += iDigit
        return iFactor
    
    def _rightIncrement(self, iDigit):
        if iDigit < self._iRightDigit:
            iFactor = self._getSumIncrementFactor(iDigit)
            self._iRightDigit -= iDigit
            return self._iRightId * iFactor
        else:
            iIncrement = self._iRightId * self._getSumIncrementFactor(self._iRightDigit)
            iDigit -= self._iRightDigit
            self._decrementRightIdx()
            if iDigit > 0:
                iIncrement += self._rightIncrement(iDigit)
            return iIncrement

    def _decrementRightIdx(self):
        self._iRightIdx -= 2
        self._iRightDigit = int(self._sDiskMap[self._iRightIdx])
        self._iRightId -= 1

def Alg2(sFileName):
    with open(sFileName, 'r') as file:
        d = XDiskFileDefragmenter(file.read())
    return d.ComputeChecksum()

class XDiskFileDefragmenter(XDiskDefragmenter):

    def __init__(self, sDiskMap):
        super().__init__(sDiskMap)
        self._pList = self._initList(sDiskMap)

    def _initList(self, sDiskMap):
        pList = XBlockList()
        iStart = 0
        for idx in range(len(sDiskMap)):
            cDigit = sDiskMap[idx]
            iDigit = int(cDigit)
            if idx % 2 != 0 and iDigit > 0:
                pBlockRange = XBlockRange(iStart=iStart, iSize=iDigit)
                pList.addToBack(pBlockRange)
            iStart += iDigit
        return pList

    def ComputeChecksum(self):
        iStart = sum([int(c) for c in self._sDiskMap])
        iId = self._iSzDiskMap // 2
        iSum = 0
        for iIdx in range(len(self._sDiskMap), 0, -1):
            cDigit = self._sDiskMap[iIdx - 1]
            iDigit = int(cDigit)
            iStart -= iDigit
            if iIdx % 2 != 0:
                iSum += iId * self._getSumIncrementFactor(iStart, iDigit)
                iId -= 1
        return iSum

    def _getSumIncrementFactor(self, iStart, iSize):
        # default factor if we can't move block
        iFactor = XDiskDefragmenter.GetIncrementSumFactor(iStart, iSize)
        pNode = self._pList.getHead()
        # no free space
        if pNode == None:
            return iFactor
        # check the very first block
        pBlock = pNode.getData()
        if pBlock.getStart() <= iStart and pBlock.getSize() >= iSize:
            iFactor = self._allocateBlockAndGetFactor(pBlock, iSize)
            if pBlock.getSize() == 0:
                _ = self._pList.removeFromFront()
            self._free(iStart, iSize, pStartNode=None)
        elif pBlock.getStart() <= iStart:
            while pNode.getNext() != None:
                pBlock = pNode.getNext().getData()
                if pBlock.getStart() <= iStart and pBlock.getSize() >= iSize:
                    iFactor = self._allocateBlockAndGetFactor(pBlock, iSize)
                    if pBlock.getSize() == 0:
                        pNode.setNext(pNode.getNext().getNext())
                    self._free(iStart, iSize, pStartNode=pNode)
                    break
                elif pBlock.getStart() > iStart:
                    break
                pNode = pNode.getNext()
        return iFactor
    
    def _free(self, iStart, iSize, pStartNode=None):
        pBlock = XBlockRange(iStart, iSize)
        self._pList.insert(pBlock, pStartNode)
    
    def _allocateBlockAndGetFactor(self, pBlock, iSize):
        iFactor = XDiskDefragmenter.GetIncrementSumFactor(pBlock.getStart(), iSize)
        pBlock.AllocateBlock(iSize)
        return iFactor

class XBlockRange(IComparable):

    def __init__(self, iStart, iSize):
        self._iStart = iStart
        self._iSize = iSize

    def getStart(self):
        return self._iStart

    def getSize(self):
        return self._iSize
    
    # Override
    def Compare(self, pOther):
        if not isinstance(pOther, XBlockRange):
            raise Exception('XBlockRange:Compare:Cannot compare object to XBlockRange')
        return self._iStart - pOther.getStart()

    def AllocateBlock(self, iSize):
        if iSize > self._iSize:
            raise Exception('XBlockRange:AllocateBlock:Attempted to allocate block larger than avaialable in range')
        self._iStart += iSize
        self._iSize -= iSize

    def AppendToBack(self, iSize):
        self._iSize += iSize

class XBlockList(OrderedLinkedList):

    # Override
    def _putAfter(self, pCurrentNode, pNewNode):
        super()._putAfter(pCurrentNode, pNewNode)
        self._defragAt(pCurrentNode)

    def _defragAt(self, pCurrentNode):
        if pCurrentNode == None or pCurrentNode.getNext() == None:
            return
        if pCurrentNode.getNext().getNext() != None:
            self._defrag(pCurrentNode.getNext())
        self._defrag(pCurrentNode)

    def _defrag(self, pCurrentNode):
        pCurrentBlock = pCurrentNode.getData()
        pNextBlock = pCurrentNode.getNext().getData()
        if pCurrentBlock.getStart() + pCurrentBlock.getSize() == pNextBlock.getStart():
            pCurrentBlock.AppendToBack(pNextBlock.getSize())
            pCurrentNode.setNext(pCurrentNode.getNext().getNext())

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()