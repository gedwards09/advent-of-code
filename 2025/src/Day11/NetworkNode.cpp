#include "NetworkNode.h"

NetworkNode::NetworkNode(nodeName_t* pNodeName, int data)
    : _data(data), _pNodes(new Array<node_t>()) { name[3] = '\0'; memcpy(this->name, pNodeName->String(), 3); }

NetworkNode::~NetworkNode()
{
    delete this->_pNodes;
    this->_pNodes = NULL;
}

long long NetworkNode::GetData() const
{
    return this->_data;
}

void NetworkNode::SetData(long long data)
{
    this->_data = data;
}

Array<node_t>* NetworkNode::GetNodes() const
{
    return this->_pNodes;
}

void NetworkNode::AppendNode(node_t* pNode)
{
    this->_pNodes->Append(pNode);
}

void NetworkNode::PrintName() { std::cout << name << std::endl; }