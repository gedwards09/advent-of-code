#ifndef __I_HASHABLE_COORDINATE_H__
#define __I_HASHABLE_COORDINATE_H__

#include "ICoordinate.h"
#include "IHashable.h"

class IHashableCoordinate : public ICoordinate, public IHashable {  };

#endif // __I_HASHABLE_COORDINATE_H__