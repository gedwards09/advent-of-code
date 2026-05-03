#ifndef __NETWORK_NODE_H__
#define __NETWORK_NODE_H__

#include <iostream>

#include "Array.h"

class NetworkNode;
typedef NetworkNode node_t;

#include "HashableString.h"
typedef HashableString nodeName_t;

class NetworkNode
{
    public:
        ~NetworkNode();
        NetworkNode(nodeName_t* pNodeName, int data);
        long long GetData() const;
        void SetData(long long data);
        Array<node_t>* GetNodes() const;
        void AppendNode(node_t* pNode);
        void PrintName();

    private:
        char name[4];
        long long _data;
        Array<node_t>* _pNodes;
};

#endif // __NETWORK_NODE_H__