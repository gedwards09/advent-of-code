from utils.Map2D.Map2D import Map2D

class IntMap2D(Map2D):

    # Override
    def _initMap(self, sFileName, sRawText, cDelim):
        with open(sFileName,'r') as f:
            return [[int(el) for el in line.split()]\
                    for line in f.read().split('\n')]
