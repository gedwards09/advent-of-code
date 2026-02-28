#include "QuantumTachMap.h"

QuantumTachMap::~QuantumTachMap()
{
    this->_pArray->DeleteAllAndClear();
}

QuantumTachMap::QuantumTachMap(std::string contents[], size_t szContents) : 
        TachMap(contents, szContents),
        _pArray(NULL) {  }

int QuantumTachMap::Init()
{
    this->_pArray = new array_t();
    for (size_t xCoord = 0; xCoord < this->GetSizeX(); xCoord++)
    {
        if (this->HasStartIndicator(xCoord))
        {
            this->_pArray->Append(new long long(RBIT)); // 0x01
        }
        else
        {
            this->_pArray->Append(new long long(NIL)); // 0x00
        }
    }

    // the initial number of beams (1)
    return 1;
}

bool QuantumTachMap::HasBeam(size_t xCoord)
{
    return *(this->_pArray->Get(xCoord));
}

long long QuantumTachMap::SplitBeamCount(size_t xCoord)
{
    long long* pInt;
    long long out;

    pInt = this->_pArray->Get(xCoord);
    out = *pInt;
    *pInt = NIL;
    *(this->_pArray->Get(xCoord - 1)) += out;
    *(this->_pArray->Get(xCoord + 1)) += out;

    return out;
}
