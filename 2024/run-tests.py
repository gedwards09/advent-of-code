import os
from utils.AocArgs import AocArgs

def _runAndCheck(iDayNumber):
    sDayNumber = str(iDayNumber)
    iTestNumber = 1
    while True:
        bDoContinue = False
        for iPartNumber in range(1,3):
            sPartNumber = str(iPartNumber)
            sTestNumber = str(iTestNumber)
            sScriptFileName = AocArgs.makeScriptFileName(sDayNumber)
            sOutputFileName = AocArgs.makeOutputFileName(sDayNumber, sPartNumber, sTestNumber)
            if os.path.exists(sOutputFileName):
                bDoContinue = True
                sCommand = _makeTesterCommand(sScriptFileName, sPartNumber, sTestNumber)
                rc = os.system(sCommand)
                if rc != 0:
                    print("Day {:d}, Test {:d}, Part {:d} failed: {:d}-{:d}.in incorrect"\
                        .format(iDayNumber, iTestNumber, iPartNumber,iDayNumber, iTestNumber))
                    print("Expected results: {:d}-{:d}-{:d}.out".format(iDayNumber, iTestNumber, iPartNumber))
                    return 1
        if not bDoContinue:
            break
        iTestNumber += 1
    return 0

def _makeTesterCommand(sScriptFileName, sPartNumber, sTestNumber):
    return ' '.join(['python3', sScriptFileName, sPartNumber, AocArgs.getTestFlag(), AocArgs.getAltFlag(), sTestNumber])

def __main__():
    iTestNumber = 1
    while iTestNumber <= 25:
        rc = _runAndCheck(iTestNumber)
        if rc != 0:
            return
        iTestNumber += 1
    return

if __name__ == '__main__':
    __main__()