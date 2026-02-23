#include <concepts>

#include "Array.h"
#include "IComparable.h"
#include "ISortable.h"

template <typename T, typename S = T>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
class SortableArray : public Array<T>, public ISortable
{
    public:
        virtual void Sort() override;

    private:
        void quickSort(int lower, int upper);
};

template <typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
void SortableArray<T,S>::Sort()
{
    this->quickSort(0, this->Size() - 1);
}

template <typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
void SortableArray<T,S>::quickSort(int lower, int upper)
{
    T* pivot;
    int pivotIdx;
    int i;
    int j;

    if (upper <= lower)
    {
        return;
    }

    pivotIdx = upper;
    pivot = this->Get(pivotIdx);
    i = lower; // the next open lower index place
    j = lower; // the current index
    while (j < pivotIdx)
    {    
        if (pivot->CompareTo(this->Get(j)) > 0)
        {
            this->Swap(i, j);
            i++;
        }
        j++;
    }
    this->Swap(i, pivotIdx);
    this->quickSort(lower, i - 1);
    this->quickSort(i + 1, upper);
}
