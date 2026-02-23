#ifndef __I_SORTABLE_H__
#define __I_SORTABLE_H__

class ISortable
{
    public:
        virtual ~ISortable() = default;
        virtual void Sort() = 0;
};

#endif // __I_SORTABLE_H__