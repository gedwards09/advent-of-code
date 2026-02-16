#ifndef __I_FACTORY_H__
#define __I_FACTORY_H__

template <typename T, typename S>
class IFactory
{
    public:
        virtual ~IFactory();
        virtual T* Build(int type, S* args) = 0;
};

template <typename T, typename S>
IFactory<T,S>::~IFactory() {  }

#endif // __I_FACTORY_H__