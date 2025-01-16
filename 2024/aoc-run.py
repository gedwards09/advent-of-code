import os
import sys
from utils.AocArgs import AocArgs

g_sDefaultPartNumber = '1'
g_sDefaultTestNumber = '1'
g_sPartArg = '--part'
g_sTestArg = '--test'
g_sFormatError = 'aoc-run.py:format: ./aoc-run.py day-number [' + g_sPartArg + '=(1|2); default=1] [' + g_sTestArg + '=TESTNUMBER]'

def _parseArgs(argv):
    argc = len(argv)
    if argc < 2 or argc > 4:
        raise Exception(g_sFormatError)
    kw = {}
    kw['day'] = argv[1]
    kw['part'] = None
    kw['test'] = None
    for idx in range(2, len(argv)):
        arg = argv[idx]
        if '=' not in arg:
            continue
        parg = arg.split('=')
        if parg[0] == g_sPartArg:
            if kw['part'] == None and (parg[1] == '1' or parg[1] == '2'):
                kw['part'] = parg[1]
            else:
                raise Exception(g_sFormatError)
        elif parg[0] == g_sTestArg:
            if kw['test'] == None:
                try:
                    kw['test'] = parg[1]
                    _ = int(kw['test'])
                except:
                    raise Exception(g_sFormatError)
            else:
                raise Exception(g_sFormatError)
    if kw['part'] == None:
        kw['part'] = g_sDefaultPartNumber
    if kw['test'] == None:
        kw['test'] = g_sDefaultTestNumber
    return kw

def __main__():
    kw = _parseArgs(sys.argv)
    sDayNumber = kw['day']
    sTestNumber = kw['test']
    sPartNumber = kw['part']
    sScriptFileName =  AocArgs.makeScriptFileName(sDayNumber)
    cmd = ' '.join(['python3', sScriptFileName, sPartNumber, '-a', sTestNumber])
    rc = os.system(cmd)

if __name__ == "__main__":
    __main__()