import sys
from utils.AocController import AocController
from utils.BinaryTree.BinaryTreeNode import BinaryTreeNode

class XBinaryTreeNode(BinaryTreeNode):

    def CanAchieveTarget(self, iTarget, pFactors):
        return self._rCanAchieveTarget(iTarget, pFactors, 1)
    
    def makeNode(self, vData):
        return XBinaryTreeNode(vData)

    # internal
    def _rCanAchieveTarget(self, iTarget, pFactors, idx):
        iCurrentData = self.getData()

        # We're done
        if iCurrentData == iTarget and idx == len(pFactors):
            return True
        elif iCurrentData > iTarget or idx >= len(pFactors):
            return False
        
        # Try Left
        iNextFactor = pFactors[idx]
        iNextData = iCurrentData + iNextFactor
        pNextNode = self.makeNode(iNextData)
        self.setLeft(pNextNode)
        if pNextNode._rCanAchieveTarget(iTarget, pFactors, idx+1):
            return True
        
        # Try Right
        iNextData = iCurrentData * iNextFactor
        if iNextData > iTarget:
            return False
        pNextNode = self.makeNode(iNextData)
        self.setRight(pNextNode)
        return pNextNode._rCanAchieveTarget(iTarget, pFactors, idx+1)

class XTrinaryTreeNode(XBinaryTreeNode):

    def __init__(self, vData):
        super().__init__(vData)
        self._pThird = None

    def getThird(self):
        return self._pThird

    def setThird(self, pNode):
        self._pThird = pNode
        pNode._setParent(self)
    
    # Override
    def makeNode(self, vData):
        return XTrinaryTreeNode(vData)

    # Override
    def _rCanAchieveTarget(self, iTarget, pFactors, idx):
        if super()._rCanAchieveTarget(iTarget, pFactors, idx):
            return True
        elif idx >= len(pFactors):
            return False
        
        # Try third
        iCurrentData = self.getData()
        iNextFactor = pFactors[idx]
        sNextData = str(iCurrentData) + str(iNextFactor)
        iNextData = int(sNextData)
        if iNextData > iTarget:
            return False
        pNextNode = self.makeNode(iNextData)
        self.setThird(pNextNode)
        return pNextNode._rCanAchieveTarget(iTarget, pFactors, idx+1)

def Alg1(sFileName):
    pInput = getInput(sFileName)
    fpTargetChecker = lambda iTarget, pFactors : XBinaryCanAchieveTarget(iTarget, pFactors)
    return processEquations(pInput, fpTargetChecker)

def getInput(sFileName):
    with open(sFileName, 'r') as f:
        return f.read().split('\n')
    
def XBinaryCanAchieveTarget(iTarget, pFactors):
    pCurrent = XBinaryTreeNode(pFactors[0])
    return pCurrent.CanAchieveTarget(iTarget, pFactors)

def processEquations(pInput, fpTargetChecker):
    iSum = 0
    for sLine in pInput:
        pArr = sLine.split(': ')
        iTarget = int(pArr[0])
        pFactors = [int(s) for s in pArr[1].split(' ')]
        if fpTargetChecker(iTarget, pFactors):
            iSum += iTarget
    return iSum

def Alg2(sFileName):
    sInput = getInput(sFileName)
    fpTargetChecker = lambda iTarget, pFactors: XTrinaryCanAchieveTarget(iTarget, pFactors)
    return processEquations(sInput, fpTargetChecker)

def XTrinaryCanAchieveTarget(iTarget, pFactors):
    pCurrent = XTrinaryTreeNode(pFactors[0])
    return pCurrent.CanAchieveTarget(iTarget, pFactors)

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()