#ifndef __TILE_REDECORATOR_H__
#define __TILE_REDECORATOR_H__

#include <iostream>
#include <string>

#include "Array.h"
#include "ICoordinate.h"

#define DIM_2 (2)

class TileRedecorator
{
    public:
        ~TileRedecorator();
        TileRedecorator(std::string contents[], size_t szContents);
        long long BiggestRectangleArea();
        long long BiggestRectangleWithinArea();

    private:
        static const char s_comma = ',';

        Array<ICoordinate>* _array;

        long long calculateIntegrationArea(ICoordinate* pCoordHome, ICoordinate* pCoordCorner);
        static void SetMinMax(int thisNum, int thatNum, int* pMin, int* pMax);
        int getIndex(int i);
        static bool IsVerticalLine(ICoordinate* pHere, ICoordinate* pThere);
        static int HorizontalDirection(ICoordinate* pCoordCur, ICoordinate* pCoordNext);
        static long long IntegrateHorizontalPath(ICoordinate* pCoordCur, ICoordinate* pCoordNext, int xMin, int xMax, int yMin, int yMax);
        static long long MinMaxCap(int t, int tMin, int tMax);
        static long long IntegrateVerticalPath(ICoordinate* pCoordCur, ICoordinate* pCoordNext, int xMin, int xMax, int yMin, int yMax, int lastHorizontalDirection, int nextHorizontalDirection);
        static long long IntegrateVerticalPathContinuationRight(ICoordinate* pCoordCur, int yMin, int yMax);
        static long long IntegrateVerticalPathContinuationLeft(ICoordinate* pCoordNext, int yMin, int yMax);
};

#endif // __TILE_REDECORATOR_H__