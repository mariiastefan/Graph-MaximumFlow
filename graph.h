#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include "arc.h"
#include <QFile>
#include <stack>
#include <QMatrix>
class Graph
{
    std::vector<Node> noduri;
    std::vector<Arc> arce;
    std::vector<std::vector<int>> matriceAdiacenta;
    std::vector<std::vector<int>> lista;
    std::vector<Arc>listaAdiacenta;
    std::vector<std::vector<int>> matr;
     std::vector<std::vector<int>> lista_ad;
    void topologicalSortVerif(int nod, bool visited[],std::stack<int>& stack);
    bool hasCycleVerif(int nod, bool visited[], bool* recStack);
    int nr_noduri;
    int nr_linii;
    int nr_coloane;
    std::vector<std::vector<int>> matrCosturi;

public:
    void GenerareMatriceAdiacenta();
    void GenerareListaAdiacenta();
    std::vector<Arc> GetArce();
    std::vector<Node> GetNoduri();
    bool Add(Node n);
    void AddNod(Node n);
    void AddArc(Arc a);
    void DrawGraf(QPainter *p);
    void AdListCreating();
    Node GetLastNode();
    int getNumberofNodes();
    QVector<int> iesiri;
    void setNrOfNodes(int x);
    void readAdjList(QFile& f,std::vector<std::vector<int>> arce_int);
    void ListaAdiacenta();
    void topologicalSort(std::vector<int>&topo);
    bool hasCycle();
    void GenerareMatriceCosturi();
    std::list<int>* adj;
    bool bfs(std::vector<std::vector<int>> &rGraph,int s, int t, std::vector<int> &parent);
    int fordFulkerson(int s, int t);
    void dfs(std::vector<std::vector<int>> &rGraph, int s, std::vector<bool>&visited);

  };


#endif // GRAPH_H
