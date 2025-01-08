class AocArgs:
    
    g_iDefaultPartNumber = 1
    g_sDayNumberError = 'AocArgs.py:day-<number>.py:Number must be an integer from 1 to 25'
    g_sDefaultPartNumber = str(g_iDefaultPartNumber)
    g_sInputFilePostfix = '.in'
    g_sOutputFilePostfix = '.out'
    g_sPartNumberError = 'AocArgs.py:Part number must be 1 or 2'
    g_sScriptFileNamePrefix = 'day-'
    g_sScriptFileNamePostfix = '.py'
    g_sTestFlag = '-t'
    g_sTestsDirectoryName = './tests/'
    g_sFormatError = 'AocArgs.py:format:./day-NUMBER.py [{1|2} ['\
        + g_sTestFlag + ']; default=' + g_sDefaultPartNumber + ']'

    def __init__(self, argv):
        argc = len(argv)
        if argc > 3:
            raise Exception(AocArgs.g_sFormatError)
        self.ScriptFileName = AocArgs._initScriptFileName(argv)
        self.DayNumber = AocArgs._initDayNumber(argv)
        self.InputFileName = AocArgs._initInputFileName(argv)
        self.PartNumber = AocArgs._initPartNumber(argv)
        self._output = AocArgs._initOutput(argv)
        self._verbose = AocArgs._initVerbose(argv)
        self._argc = argc

    def _initScriptFileName(argv):
        return AocArgs._parseScriptFileName(argv)
    
    def _parseScriptFileName(argv):
        return argv[0]
    
    def _initDayNumber(argv):
        try:
            iDayNumber = int(AocArgs._parseDayNumber(argv))
            if not AocArgs._isValidDayNumber(iDayNumber):
                raise Exception()
        except Exception:
            raise Exception(AocArgs.g_sDayNumberError)
        
    def _isValidDayNumber(iDayNumber):
        return iDayNumber >= 1 and iDayNumber <= 25
        
    def _parseDayNumber(argv):
        return AocArgs._parseScriptFileName(argv)\
            .split('/')[-1]\
            .replace(AocArgs.g_sScriptFileNamePrefix,'')\
            .replace(AocArgs.g_sScriptFileNamePostfix, '')
    
    def _initInputFileName(argv):
        sDayNumber = AocArgs._parseDayNumber(argv)
        return AocArgs.makeInputFileName(sDayNumber)

    def _initPartNumber(argv):
        argc = len(argv)
        if argc < 2:
             return AocArgs.g_iDefaultPartNumber
        try:
             iPartNumber = int(argv[1])
             if not AocArgs._isValidPartNumber(iPartNumber):
                 raise Exception()
        except Exception:
             raise Exception(AocArgs.g_sPartNumberError)
        return iPartNumber
    
    def _isValidPartNumber(iPartNumber):
        return iPartNumber == 1 or iPartNumber == 2
    
    def _initOutput(argv):
        if len(argv) < 3:
            return None
        sDayNumber = AocArgs._parseDayNumber(argv)
        sPartNumber = argv[1]
        sFlag = argv[2]
        if sFlag != AocArgs.g_sTestFlag:            
            raise Exception(AocArgs.g_sFormatError)
        sOutputFileName = AocArgs.makeOutputFileName(sDayNumber, sPartNumber)
        with open(sOutputFileName, 'r') as file:
            return int(file.read())
    
    def _initVerbose(argv):
        return len(argv) < 3
    
    def isVerbose(self):
        return self._verbose
    
    def getOutput(self):
        return self._output
    
    def makeScriptFileName(sDayNumber):
        return './' + AocArgs.g_sScriptFileNamePrefix + sDayNumber\
            + AocArgs.g_sScriptFileNamePostfix
    
    def makeInputFileName(sDayNumber):
        return AocArgs.g_sTestsDirectoryName + sDayNumber\
            + AocArgs.g_sInputFilePostfix
    
    def makeOutputFileName(sDayNumber, sPartNumber):
        return AocArgs.g_sTestsDirectoryName + sDayNumber + '-' + sPartNumber\
            + AocArgs.g_sOutputFilePostfix