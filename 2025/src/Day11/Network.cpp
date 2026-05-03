#include <iostream>

#include "StringSplitter.h"

#include "Network.h"

const char Network::s_destDelim = ' ';

const char Network::s_originDelim = ':';

const int Network::s_visitedNodeValue = -1;

const int Network::s_unvisitedNodeValue = -2;

const int Network::s_singlePathNodeValue = 1;

const int Network::s_szNodeName = 3;

const char* Network::s_headNodeNameRaw = "you";

const char* Network::s_tailNodeNameRaw = "out";

const char* Network::s_pSvrNodeNameRaw = "svr";

const char* Network::s_pFftNodeNameRaw = "fft";

const char* Network::s_pDacNodeNameRaw = "dac";

nodeName_t* Network::s_pSvrNodeName = Network::CreateNodeName(Network::s_pSvrNodeNameRaw);

nodeName_t* Network::s_pFftNodeName = Network::CreateNodeName(Network::s_pFftNodeNameRaw);

nodeName_t* Network::s_pDacNodeName = Network::CreateNodeName(Network::s_pDacNodeNameRaw);

nodeName_t* Network::s_pYouNodeName = Network::CreateNodeName(Network::s_headNodeNameRaw);

nodeName_t* Network::s_pOutNodeName = Network::CreateNodeName(Network::s_tailNodeNameRaw);

const int Network::s_tailPathCount = 0;

Network::~Network()
{
    delete this->_pNodeList;
    this->_pNodeList = NULL;

    this->_pYouNode = NULL;
    this->_pOutNode = NULL;
}

Network::Network(std::string contents[], size_t szContents)
    : _id(0), _pNodeList(new Array<node_t>()), _pYouNode(NULL), _pOutNode(NULL)
{
    this->initNetwork(contents, szContents);
}

void Network::initNetwork(std::string contents[], size_t szContents)
{
    table_t table;
    std::string line;
    std::vector<std::string> originAndDests;
    std::string originRaw;
    node_t* pOriginNode;
    std::string destRaw;
    node_t* pDestNode;

    pOriginNode = NULL;
    for (size_t i = 0; i < szContents; i++)
    {
        line = contents[i];
        originAndDests = StringSplitter::Split(line, Network::s_destDelim);
        assert(originAndDests.size() >= 2);
        for (size_t i = 0; i < originAndDests.size(); i++)
        {
            if (i == 0)
            {
                originRaw = StringSplitter::Piece(originAndDests[i], Network::s_originDelim, 0);
                pOriginNode = this->GetOrCreateNode(&table, originRaw.c_str());
            }
            else
            {
                destRaw = originAndDests[i];
                pDestNode = this->GetOrCreateNode(&table, destRaw.c_str());
                pOriginNode->AppendNode(pDestNode);
            }
        }
    }

    this->SaveNodes(&table);
}

node_t* Network::GetOrCreateNode(table_t* pTable, const char* pStr)
{
    nodeName_t* pNodeName;
    node_t* pNode;
    
    pNodeName = Network::CreateNodeName(pStr);
    pNode = Network::GetOrCreateNode(pTable, pNodeName);

    delete pNodeName;
    pNodeName = NULL;

    return pNode;
}

node_t* Network::GetOrCreateNode(table_t* pTable, nodeName_t* pNodeName)
{
    int* pValue;
    node_t* pNode;

    if (pTable->Get(pNodeName, &pValue))
    {
        pNode = this->_pNodeList->Get(*pValue);
    }
    else
    {
        pNode = this->CreateAndAddNode(pTable, pNodeName);
    }

    return pNode;
}

nodeName_t* Network::CreateNodeName(const char* pStr)
{
    return new nodeName_t(pStr, Network::s_szNodeName);
}

node_t* Network::CreateAndAddNode(table_t* pTable, nodeName_t* pNodeName)
{
    node_t* pNode;

    assert(pTable->Set(pNodeName->Copy(), new int(this->_id)));
    pNode = Network::CreateNode(pNodeName);
    this->_pNodeList->Append(pNode);
    this->_id++;
    assert(this->_pNodeList->Size() == this->_id);

    return pNode;
}

node_t* Network::CreateNode(nodeName_t* pNodeName)
{
    return new NetworkNode(pNodeName, Network::s_unvisitedNodeValue);
}

void Network::SaveNodes(table_t* pTable)
{
    this->_pYouNode = this->GetNode(pTable, Network::s_pYouNodeName);
    this->_pOutNode = this->GetNode(pTable, Network::s_pOutNodeName);
    this->_pSvrNode = this->GetNode(pTable, Network::s_pSvrNodeName);
    this->_pFftNode = this->GetNode(pTable, Network::s_pFftNodeName);
    this->_pDacNode = this->GetNode(pTable, Network::s_pDacNodeName);
}

node_t* Network::GetNode(table_t* pTable, nodeName_t* pNodeName)
{
    int* pValue;

    if (pTable->Get(pNodeName, &pValue))
    {
        return this->_pNodeList->Get(*pValue);
    }
    else
    {
        return NULL;
    }
}

int Network::Solve()
{
    if (this->_pYouNode == NULL)
    {
        return 0;
    }
    
    return Network::CountPaths(this->_pYouNode, this->_pOutNode);
}

long long Network::SolveComplex()
{
    long long pathCount;
    long long total;

    if (this->_pSvrNode == NULL)
    {
        return 0;
    }

    // svr -> fft
    pathCount = Network::CountPaths(this->_pSvrNode, this->_pFftNode);
    Network::ClearChildren(this->_pSvrNode);
    
    // fft -> dac
    pathCount *= Network::CountPaths(this->_pFftNode, this->_pDacNode);
    Network::ClearChildren(this->_pFftNode);
    
    // dac -> out
    pathCount *= Network::CountPaths(this->_pDacNode, this->_pOutNode);
    Network::ClearChildren(this->_pDacNode);

    total = pathCount;

    
    // svr -> dac
    pathCount = Network::CountPaths(this->_pSvrNode, this->_pDacNode);
    Network::ClearChildren(this->_pSvrNode);

    // dac -> fft
    pathCount *= Network::CountPaths(this->_pDacNode, this->_pFftNode);
    Network::ClearChildren(this->_pDacNode);
    
    // fft -> out
    pathCount *= Network::CountPaths(this->_pFftNode, this->_pOutNode);

    total += pathCount;

    return total;
}

long long Network::CountPaths(node_t* pSource, node_t* pDest)
{
    int data;
    Array<node_t>* pNodes;
    long long pathCount;

    if (pSource == pDest)
    {
        return Network::s_singlePathNodeValue;
    }

    data = pSource->GetData();
    if (data >= 0)
    {
        return data;
    }

    pNodes = pSource->GetNodes();
    pathCount = 0;
    for (int i = 0; i < pNodes->Size(); i++)
    {
        pathCount += Network::CountPaths(pNodes->Get(i), pDest);
    }
    pSource->SetData(pathCount);

    return pathCount;
}

void Network::ClearChildren(node_t* pNode)
{
    int data;
    Array<node_t>* pNodes;

    data = pNode->GetData();
    if (data < 0)
    {
        return;
    }

    pNode->SetData(Network::s_unvisitedNodeValue);
    pNodes = pNode->GetNodes();
    for (int i = 0; i < pNodes->Size(); i++)
    {
        Network::ClearChildren(pNodes->Get(i));
    }
}