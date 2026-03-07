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

        int _sz;
        int* _x;
        int* _y;

        long long area(int i, int j);
        long long calculateIntegrationArea(int i, int j);
        static void SetMinMax(int thisNum, int thatNum, int* pMin, int* pMax);
        int deltaX(int cur, int next);
        long long integrateHorizontalPath(
                int cur, int next, int xMin, int xMax, int yMin, int yMax);
        static long long MinMaxCap(int t, int tMin, int tMax);
        long long integrateVerticalPath(
                int cur, int next, int xMin, int xMax, int yMin, int yMax, 
                int lastHDir, int nextHDir);
        long long integrateVerticalPathContinuationRight(int cur, int yMin, int yMax);
        long long integrateVerticalPathContinuationLeft(int next, int yMin, int yMax);
};

#endif // __TILE_REDECORATOR_H__