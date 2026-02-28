#ifndef __I_TACH_MAP_H__
#define __I_TACH_MAP_H__

class ITachMap
{
    public:
        virtual ~ITachMap() = default;
        virtual long long CountBeamSplits() = 0;
};

#endif // __I_TACH_MAP_H__