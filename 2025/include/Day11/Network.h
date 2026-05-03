#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <string>

#include "HashTable.h"
#include "HashableString.h"
#include "NetworkNode.h"

typedef NetworkNode node_t;
typedef HashableString nodeName_t;
typedef HashTable<nodeName_t,int> table_t;

class Network
{
    public:
        ~Network();
        Network(std::string contents[], size_t szContents);
        virtual int Solve();
        int PathCount(node_t* pNode);
        static nodeName_t* CreateNodeName(const char* pStr);
        node_t* GetNode(table_t* pTable, nodeName_t* pNodeName);
        long long SolveComplex();
        long long PathCountComplex(node_t* pNode, bool isFftVisited, bool isDacVisited);
        static void ClearChildren(node_t* pNode);
        static long long CountPaths(node_t* pSource, node_t* pDest);

    protected:
        virtual void SaveNodes(table_t* pTable);
        void initNetwork(std::string contents[], size_t szContents);

    private:
        static const char s_originDelim;
        static const char s_destDelim;
        static const int s_szNodeName;
        static const int s_visitedNodeValue;
        static const int s_unvisitedNodeValue;
        static const int s_singlePathNodeValue;
        static const int s_tailPathCount;
        
        static const char* s_headNodeNameRaw;
        static const char* s_tailNodeNameRaw;
        static const char* s_pSvrNodeNameRaw;
        static const char* s_pFftNodeNameRaw;
        static const char* s_pDacNodeNameRaw;

        static nodeName_t* s_pYouNodeName;
        static nodeName_t* s_pOutNodeName;
        static nodeName_t* s_pSvrNodeName;
        static nodeName_t* s_pFftNodeName;
        static nodeName_t* s_pDacNodeName;

        node_t* _pSvrNode;
        node_t* _pFftNode;
        node_t* _pDacNode;

        int _id;
        Array<node_t>* _pNodeList;
        node_t* _pYouNode;
        node_t* _pOutNode;

        static node_t* CreateNode(nodeName_t* pNodeName);

        node_t* GetOrCreateNode(table_t* pTable, const char* pStr);
        node_t* GetOrCreateNode(table_t* pTable, nodeName_t* pNodeName);
        node_t* CreateAndAddNode(table_t* pTable, nodeName_t* pNodeName);

};

#endif // __NETWORK_H__