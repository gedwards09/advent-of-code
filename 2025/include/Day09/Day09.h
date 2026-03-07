#ifndef __DAY_09_H__
#define __DAY_09_H__

#include "Solution.h"
#include "TileRedecorator.h"


class Day09 : public Solution
{
    public:
        virtual ~Day09() override;
        Day09(std::string filename);
        std::string SolveEasy() override;
        std::string SolveHard() override;

    private:
        TileRedecorator* _ptr;
};

#endif // __DAY_09_H__