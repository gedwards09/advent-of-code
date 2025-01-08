import os
from utils.AocArgs import AocArgs

def _runAndCheck(iDayNumber):
    sDayNumber = str(iDayNumber)
    for i in range(2):
        sPartNumber = str(i+1)
        sScriptFileName = AocArgs.makeScriptFileName(sDayNumber)
        sOutputFileName = AocArgs.makeOutputFileName(sDayNumber, sPartNumber)
        if os.path.exists(sOutputFileName):
            sCommand = _makeTesterCommand(sScriptFileName, sPartNumber)
            rc = os.system(sCommand)

def _makeTesterCommand(sScriptFileName, sPartNumber):
    return ' '.join(['python3', sScriptFileName, sPartNumber, AocArgs.getTestFlag()])

def __main__():
    iTestNumber = 1
    while iTestNumber <= 25:
        _runAndCheck(iTestNumber)
        iTestNumber += 1
    return

if __name__ == '__main__':
    __main__()