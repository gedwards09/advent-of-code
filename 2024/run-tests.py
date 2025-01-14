import os
from utils.AocArgs import AocArgs

def _runAndCheck(iDayNumber):
    sDayNumber = str(iDayNumber)
    iTestNumber = 1
    while True:
        bDoContinue = False
        for iPartNumber in range(2):
            sPartNumber = str(iPartNumber + 1)
            sTestNumber = str(iTestNumber)
            sScriptFileName = AocArgs.makeScriptFileName(sDayNumber)
            sOutputFileName = AocArgs.makeOutputFileName(sDayNumber, sPartNumber, sTestNumber)
            if os.path.exists(sOutputFileName):
                bDoContinue = True
                sCommand = _makeTesterCommand(sScriptFileName, sPartNumber, sTestNumber)
                rc = os.system(sCommand)
        if not bDoContinue:
            break
        iTestNumber += 1

def _makeTesterCommand(sScriptFileName, sPartNumber, sTestNumber):
    return ' '.join(['python3', sScriptFileName, sPartNumber, AocArgs.getTestFlag(), AocArgs.getAltFlag(), sTestNumber])

def __main__():
    iTestNumber = 1
    while iTestNumber <= 25:
        _runAndCheck(iTestNumber)
        iTestNumber += 1
    return

if __name__ == '__main__':
    __main__()