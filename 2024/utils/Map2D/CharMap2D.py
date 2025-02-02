from utils.Map2D.Map2D import Map2D

class CharMap2D(Map2D):

    # Override
    def _parseRawText(self, sRawText, cDelim):
            return [list(sLine) for sLine in sRawText.split('\n')]
        
    def _set(self, iRowIndex: int, iColIndex: int, cSprite):
        if not self.isValid(iRowIndex, iColIndex) or len(cSprite) != 1:
            raise Exception('Map2D:_set:Invalid set command')
        self.getRow(iRowIndex)[iColIndex] = cSprite