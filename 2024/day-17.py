import sys
from utils.AocController import AocController

class XCPU:

    def __init__(self, sFileName):
        with open(sFileName, 'r') as f:
            pLines = f.read().split('\n')
        self._pLines = pLines
        self._iA = int(pLines[0][12:])
        self._iB = int(pLines[1][12:])
        self._iC = int(pLines[2][12:])
        self._pProgram = [int(s) for s in pLines[4][9:].split(',')]
        self._iSzProgram = len(self._pProgram)
        self._iIP = 0
        self._pOutput = []

    def GetProgram(self):
        return self._pProgram
    
    def SetRegisterA(self, i):
        self._iA = i

    def Reset(self):
        pLines = self._pLines
        self._iA = int(pLines[0][12:])
        self._iB = int(pLines[1][12:])
        self._iC = int(pLines[2][12:])
        self._iIP = 0
        self._pOutput = []

    def GetOutput(self):
        return ','.join([str(i) for i in self._pOutput])

    def ExecuteProgram(self):
        while self._iIP < self._iSzProgram:
            iInstr = self.__read()
            iArg = self.__read()
            self.__executeInstruction(iInstr, iArg)
            # print("A:", self._iA, "B:", self._iB, "C:", self._iC)

    def __read(self):
        i = self._pProgram[self._iIP]
        self._iIP += 1
        return i
    
    def __executeInstruction(self, iInstr, iArg):
        if iInstr == 0:
            self.__adv(iArg)
        elif iInstr == 1:
            self.__bxl(iArg)
        elif iInstr == 2:
            self.__bst(iArg)
        elif iInstr == 3:
            self.__jnz(iArg)
        elif iInstr == 4:
            self.__bxc(iArg)
        elif iInstr == 5:
            self.__out(iArg)
        elif iInstr == 6:
            self.__bdv(iArg)
        elif iInstr == 7:
            self.__cdv(iArg)
        else:
            return
        
    def __combo(self, i):
        if i < 4:
            return i
        elif i == 4:
            return self._iA
        elif i == 5:
            return self._iB
        elif i == 6:
            return self._iC
        else:
            return
    
    def __adv(self, i):
        self._iA = self.__dv(i)

    def __bxl(self, i):
        self._iB ^= i

    def __bst(self, i):
        self._iB = self.__combo(i) & 0x07

    def __jnz(self, i):
        if self._iA != 0:
            self._iIP = i

    def __bxc(self, i):
        self._iB ^= self._iC

    def __out(self, i):
        i = self.__combo(i) & 0x07
        self._pOutput.append(i)

    def __bdv(self, i):
        self._iB = self.__dv(i)

    def __cdv(self, i):
        self._iC = self.__dv(i)

    def __dv(self, i):
        i = self.__combo(i)
        return self._iA >> i
    

class XDecoder:

    def __init__(self, sFileName):
        self._pCPU = XCPU(sFileName)
        self._pProgram = self._pCPU.GetProgram()
        self._pA = [0]

    def Solve(self):
        for iStep in range(len(self._pProgram)-1, -1, -1):
            iTarget = self._pProgram[iStep]
            pNextA = []
            for iA in self._pA:
                iA <<= 3
                for iSource in range(8):
                    self._pCPU.Reset()
                    self._pCPU.SetRegisterA(iA + iSource)
                    self._pCPU.ExecuteProgram()
                    sOutput = self._pCPU.GetOutput()
                    if sOutput[0] == str(iTarget):
                        pNextA.append(iA + iSource)
            self._pA = pNextA
        return min(self._pA)

def Alg1(sFileName):
    pCPU = XCPU(sFileName)
    pCPU.ExecuteProgram()
    return pCPU.GetOutput()

def Alg2(sFileName):
    pDecoder = XDecoder(sFileName)
    return pDecoder.Solve()

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()