#include <string>

#include "Array.h"
#include "Coordinate.h"
#include "IComparable.h"
#include "Pair.h"
#include "StringSplitter.h"

#include <iostream>

#include "TileRedecorator.h"

TileRedecorator::~TileRedecorator()
{
    delete this->_array;
    this->_array = NULL;
}

TileRedecorator::TileRedecorator(std::string contents[], size_t szContents) :
        _array(new Array<ICoordinate>())
{
    std::string line;
    std::vector<std::string> vec;
    int xCoord;
    int yCoord;
    ICoordinate* pCoord;

    for (size_t i = 0; i < szContents; i++)
    {
        line = contents[i];
        vec = StringSplitter::Split(line, TileRedecorator::s_comma);
        assert(vec.size() == DIM_2);
        xCoord = std::atoi(vec[0].c_str());
        yCoord = std::atoi(vec[1].c_str());
        pCoord = new Coordinate(xCoord, yCoord);
        this->_array->Append(pCoord);
    }
}

long long TileRedecorator::BiggestRectangleArea()
{
    long long max;
    long long current;
    ICoordinate* pCoord;
    ICoordinate* pOther;

    max = 0;
    for (int i = 0; i < this->_array->Size(); i++)
    {
        pCoord = this->_array->Get(i);
        for (int j = 0; j < this->_array->Size(); j++)
        {
            pOther = this->_array->Get(j);
            current = pCoord->Area(pOther);
            if (current > max)
            {
                max = current;
            }
        }
    }

    return max;
}

long long TileRedecorator::BiggestRectangleWithinArea()
{
    int max;
    int sz;
    ICoordinate* pCoordHome;
    ICoordinate* pCoordCorner;
    int current;
    int theory;

    max = 0;
    sz = this->_array->Size();
    for (int i = 0; i < sz; i++)
    {
        // i = 2;
        pCoordHome = this->_array->Get(i);
        for (int j = i + 1; j < sz; j++)
        {
            // j = 4;
            pCoordCorner = this->_array->Get(j);
            current = pCoordHome->Area(pCoordCorner);
            if (current < max)
            {
                continue;
            }
            
            theory = this->calculateIntegrationArea(pCoordHome, pCoordCorner);
            if (theory == current)
            {
                max = current;
            }
        }
    }

    return max;
}

long long TileRedecorator::calculateIntegrationArea(ICoordinate* pCoordHome, ICoordinate* pCoordCorner)
{
    int xMin;
    int xMax;
    int yMin;
    int yMax;
    long long sum;
    ICoordinate* pCoordNext;
    ICoordinate* pCoordCur;
    int lastHorizontalDirection;
    long long delta;
    ICoordinate* pCoordNextNext;
    int nextHorizontalDirection;

    TileRedecorator::SetMinMax(pCoordHome->X(), pCoordCorner->X(), &xMin, &xMax);
    TileRedecorator::SetMinMax(pCoordHome->Y(), pCoordCorner->Y(), &yMin, &yMax);

    sum = 0;
    pCoordNext = this->_array->Get(0);
    for (int i = 0; i < this->_array->Size(); i++)
    {
        pCoordCur = pCoordNext;
        //loop around if we get to the end.
        pCoordNext = this->_array->Get(this->getIndex(i + 1));

        if (!TileRedecorator::IsVerticalLine(pCoordCur, pCoordNext))
        {
            lastHorizontalDirection = TileRedecorator::HorizontalDirection(pCoordCur, pCoordNext);
            delta = TileRedecorator::IntegrateHorizontalPath(pCoordCur, pCoordNext, xMin, xMax, yMin, yMax);
        }
        else
        {
            pCoordNextNext = this->_array->Get(this->getIndex(i+2));
            nextHorizontalDirection = TileRedecorator::HorizontalDirection(pCoordNext, pCoordNextNext);
            delta = TileRedecorator::IntegrateVerticalPath(pCoordCur, pCoordNext, xMin, xMax, yMin, yMax, lastHorizontalDirection, nextHorizontalDirection);
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

int TileRedecorator::getIndex(int i)
{
    if (i >= this->_array->Size())
    {
        return i % this->_array->Size();
    }
    else
    {
        return i;
    }
}

bool TileRedecorator::IsVerticalLine(ICoordinate* pHere, ICoordinate* pThere)
{
    if (pHere->X() == pThere->X())
    {
        return true;
    }
    else if (pHere->Y() == pThere->Y())
    {
        return false;
    }
    // unreachable
    pHere->Print(); pThere->Print();
    assert(false);
}

int TileRedecorator::HorizontalDirection(ICoordinate* pCoordCur, ICoordinate* pCoordNext)
{
    int deltaX;

    deltaX = pCoordNext->X() - pCoordCur->X();

    return (deltaX > 0) - (deltaX < 0);
}

long long TileRedecorator::IntegrateHorizontalPath(ICoordinate* pCoordCur, ICoordinate* pCoordNext, int xMin, int xMax, int yMin, int yMax)
{
    int xCur;
    int xNext;
    int deltaX;
    int y;

    xCur = pCoordCur->X();
    xNext = pCoordNext->X();

    // add one to the higher coordinate
    if (xCur > xNext)
    {
        xCur++;
    }
    else
    {
        xNext++;
    }

    deltaX = TileRedecorator::MinMaxCap(xNext, xMin, xMax + 1) - TileRedecorator::MinMaxCap(xCur, xMin, xMax + 1);

    y = pCoordCur->Y();
    if (xCur < xNext)
    {
        // subract one from height if we're moving "left"
        y--;
    }
    y = TileRedecorator::MinMaxCap(y, yMin - 1, yMax) - (yMin - 1);

    return y * (long long)deltaX;
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

long long TileRedecorator::IntegrateVerticalPath(ICoordinate* pCoordCur, ICoordinate* pCoordNext, int xMin, int xMax, int yMin, int yMax, int lastHorizontalDirection, int nextHorizontalDirection)
{
    if (lastHorizontalDirection != nextHorizontalDirection)
    {
        // do nothing
        return 0;
    }
    else // continuation
    {
        if (pCoordCur->X() < xMin || xMax < pCoordCur->X())
        {
            // do nothing
            return 0;
        } 

        if (lastHorizontalDirection > 0)
        {
            return TileRedecorator::IntegrateVerticalPathContinuationRight(pCoordCur, yMin, yMax);
        }
        else
        {
            return TileRedecorator::IntegrateVerticalPathContinuationLeft(pCoordNext, yMin, yMax);
        }
    }
}

long long TileRedecorator::IntegrateVerticalPathContinuationRight(ICoordinate* pCoordCur, int yMin, int yMax)
{
    return (long long)(yMin - 1) - TileRedecorator::MinMaxCap(pCoordCur->Y() - 1, yMin - 1, yMax);
}

long long TileRedecorator::IntegrateVerticalPathContinuationLeft(ICoordinate* pCoordNext, int yMin, int yMax)
{
    return (long long)TileRedecorator::MinMaxCap(pCoordNext->Y(), yMin - 1, yMax) - (yMin - 1);
}