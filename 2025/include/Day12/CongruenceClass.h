#ifndef __CONGRUENCE_CLASS_H__
#define __CONGRUENCE_CLASS_H__

#include "Array.h"
#include "GiftShape.h"

#define ROT_ELEM_ORDER (4)
#define DIHEDRAL_GROUP_ORDER (8)

typedef GiftShape shape_t;

class CongruenceClass
{
    public:
        CongruenceClass(shape_t* pShape);
        int Size() const;
        int Area() const;
        shape_t* Get(int i) const;
        int First() const;
        bool HasNext(int i) const;
        int Next(int i) const;
        static Array<shape_t>* GenerateCongruentShapes(shape_t* pShape);
        void Print() const;

    private:
        static const int s_firstIdx;

        int _szMembers;
        Array<shape_t>* _members;
        int _area;

        static void RotateData(uint8_t o_data[][GIFT_SHAPE_WIDTH]);
        static void FlipData(uint8_t o_data[][GIFT_SHAPE_WIDTH]);
        static bool IdentIsInArray(int shapeIdent, int* pArray, int szArray);
};

#endif // __CONGRUENCE_CLASS_H__