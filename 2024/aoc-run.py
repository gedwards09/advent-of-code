import os
import sys
from utils.AocArgs import AocArgs

g_sInputFileDirectoryName = 'inputs'
g_sScriptFileNamePrefix = 'day-'
g_sScriptFileNameSuffix = '.py'
g_sPartArg = '--part'
g_sTestArg = '--test'
g_sFormatExceptionString = 'format: ./aoc-run.py day-number [' + g_sPartArg + '=(1|2); default=1]'
g_sInputTextFileNameSuffix = '.txt'

def _getPartArg(argv):
    argc = len(argv)
    if argc < 3:
        return '1'
    if argc > 3:
        raise Exception(g_sFormatExceptionString)
    arr = argv[2].split("=")
    if len(arr) != 2 or arr[0] != g_sPartArg or (arr[1] != '1' and arr[1] != '2'):
        raise Exception(g_sFormatExceptionString)
    return arr[1]

def __main__():
    argc = len(sys.argv)
    if argc < 2 or argc > 3:
        raise Exception(g_sFormatExceptionString)
    sDayNumber = sys.argv[1]
    try:
        iDayNumber = int(sDayNumber)
        if iDayNumber < 1 or iDayNumber > 25:
            raise Exception()
    except Exception:
        raise Exception('argument day-number must be an integer from 1 to 25')
    sScriptFileName =  './' + AocArgs.g_sScriptFileNamePrefix + sDayNumber + AocArgs.g_sScriptFileNamePostfix
    sPartArg = _getPartArg(sys.argv)
    cmd = ' '.join(['python3', sScriptFileName, sPartArg])
    rc = os.system(cmd)

if __name__ == "__main__":
    __main__()