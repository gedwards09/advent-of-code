#ifndef __QUANTUM_TACH_MAP_H__
#define __QUANTUM_TACH_MAP_H__

#include "Array.h"
#include "TachMap.h"

#define NIL (0)

typedef Array<long long> array_t;
typedef array_t* p_array_t;

class QuantumTachMap : public TachMap
{
    public:
        virtual ~QuantumTachMap() override;
        QuantumTachMap(std::string contents[], size_t szContents);

    protected:
        virtual int Init() override;
        virtual bool HasBeam(size_t xCoord) override;
        virtual long long SplitBeamCount(size_t xCoord);

    private:
        p_array_t _pArray;
};

#endif // __QUANTUM_TACH_MAP_H__