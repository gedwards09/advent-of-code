
#include <iostream>
#include <string>

#include "Coordinate.h"
#include "StringSplitter.h"

#include "TileRedecorator.h"

TileRedecorator::~TileRedecorator()
{
    delete this->_x;
    this->_x = NULL;
    delete this->_y;
    this->_y = NULL;
}

TileRedecorator::TileRedecorator(std::string contents[], size_t szContents) :
        _sz(szContents), _x(new int[szContents]()), _y(new int[szContents]())
{
    std::string line;
    std::vector<std::string> vec;
    int val;

    for (size_t i = 0; i < szContents; i++)
    {
        line = contents[i];
        vec = StringSplitter::Split(line, TileRedecorator::s_comma);
        assert(vec.size() == DIM_2);
        val = std::atoi(vec[0].c_str());
        this->_x[i] = val;
        val = std::atoi(vec[1].c_str());
        this->_y[i] = val;
    }
}

long long TileRedecorator::BiggestRectangleArea()
{
    long long max;
    long long current;

    max = 0;
    for (int i = 0; i < this->_sz; i++)
    {
        for (int j = i + 1; j < this->_sz; j++)
        {
            current = this->area(i, j);
            if (max < current)
            {
                max = current;
            }
        }
    }

    return max;
}

long long TileRedecorator::area(int i, int j)
{
    assert(0 <= i && i < this->_sz && 0 <= j && j<= this->_sz);
    return Coordinate::InclusiveDistance(this->_x[i], this->_x[j]) 
            * (long long)Coordinate::InclusiveDistance(this->_y[i], this->_y[j]);
}

long long TileRedecorator::BiggestRectangleWithinArea()
{
    long long max;
    long long current;
    long long theory;

    max = 0;
    for (int i = 0; i < this->_sz; i++)
    {
        for (int j = i + 1; j < this->_sz; j++)
        {
            current = this->area(i, j);
            if (current <= max)
            {
                continue;
            }
            
            theory = this->calculateIntegrationArea(i, j);
            if (theory == current)
            {
                max = current;
            }
        }
    }

    return max;
}

long long TileRedecorator::calculateIntegrationArea(int home, int corner)
{
    int xMin;
    int xMax;
    int yMin;
    int yMax;
    long long sum;
    int cur;
    int next;
    int nextNext;
    int deltaX;
    int lastDeltaX;
    int nextDeltaX;
    long long delta;

    TileRedecorator::SetMinMax(this->_x[home], this->_x[corner], &xMin, &xMax);
    TileRedecorator::SetMinMax(this->_y[home], this->_y[corner], &yMin, &yMax);

    sum = 0;
    cur = 0;
    next = 1;
    nextNext = 2;
    deltaX = 0;
    lastDeltaX = 0;
    nextDeltaX = 0;
    for (int i = 0; i < this->_sz; i++)
    {
        cur = next;
        next = nextNext;
        nextNext = i + 2;
        if (nextNext >= this->_sz)
        {
            nextNext -= this->_sz;
        }

        deltaX = this->deltaX(cur, next);
        if (deltaX != 0) // direction horizontal
        {
            lastDeltaX = deltaX;
            delta = this->integrateHorizontalPath(cur, next, xMin, xMax, yMin, yMax);
        }
        else
        {
            nextDeltaX = this->deltaX(next, nextNext);
            delta = this->integrateVerticalPath(cur, next, xMin, xMax, yMin, yMax, lastDeltaX, nextDeltaX);
        }

        sum += delta;
    }

    return (sum >= 0 ? sum : -sum);
}

void TileRedecorator::SetMinMax(int thisNum, int thatNum, int* pMin, int* pMax)
{
    if (thisNum >= thatNum)
    {
        *pMax = thisNum;
        *pMin = thatNum;
    }
    else
    {
        *pMax = thatNum;
        *pMin = thisNum;
    }
}

int TileRedecorator::deltaX(int cur, int next)
{
    return this->_x[next] - this->_x[cur];
}

long long TileRedecorator::integrateHorizontalPath(int cur, int next, int xMin, int xMax, int yMin, int yMax)
{
    int xCur;
    int xNext;
    int deltaX;
    int yCur;

    xCur = this->_x[cur];
    yCur = this->_y[cur];
    xNext = this->_x[next];

    // add one to the higher coordinate
    if (xCur > xNext)
    {
        xCur++;
    }
    else
    {
        xNext++;
        // subract one from height if we're moving "left"
        yCur--;
    }

    if (yCur < yMin
            || (xCur <= xMin && xNext <= xMin)
            || (xMax < xCur && xMax < xNext))
    {
        return 0;
    }

    deltaX = TileRedecorator::MinMaxCap(xNext, xMin, xMax + 1) - TileRedecorator::MinMaxCap(xCur, xMin, xMax + 1);
    yCur = TileRedecorator::MinMaxCap(yCur, yMin - 1, yMax) - (yMin - 1);

    return yCur * (long long)deltaX;
}

long long TileRedecorator::MinMaxCap(int t, int tMin, int tMax)
{
    if (t >= tMax)
    {
        return tMax;
    }
    else if (t <= tMin)
    {
        return tMin;
    }
    else
    {
        return t;
    }
}

long long TileRedecorator::integrateVerticalPath(int cur, int next, int xMin, int xMax, int yMin, int yMax, int lastDeltaX, int nextDeltaX)
{
    if ((lastDeltaX <= 0 && 0 <= nextDeltaX)
            || (nextDeltaX <= 0 && 0 <= lastDeltaX))
    {
        // do nothing
        return 0;
    }
    
    // else continuation
    if (this->_x[cur] < xMin || xMax < this->_x[cur])
    {
        // do nothing
        return 0;
    } 

    if (lastDeltaX > 0)
    {
        return TileRedecorator::integrateVerticalPathContinuationRight(cur, yMin, yMax);
    }
    else
    {
        return TileRedecorator::integrateVerticalPathContinuationLeft(next, yMin, yMax);
    }
}

long long TileRedecorator::integrateVerticalPathContinuationRight(int cur, int yMin, int yMax)
{
    return (long long)(yMin - 1) - TileRedecorator::MinMaxCap(this->_y[cur] - 1, yMin - 1, yMax);
}

long long TileRedecorator::integrateVerticalPathContinuationLeft(int next, int yMin, int yMax)
{
    return (long long)TileRedecorator::MinMaxCap(this->_y[next], yMin - 1, yMax) - (yMin - 1);
}