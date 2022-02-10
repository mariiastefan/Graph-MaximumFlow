#include "graph.h"
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <QDebug>
#include <queue>

std::vector<Arc> Graph::GetArce()
{
    return arce;
}

std::vector<Node> Graph::GetNoduri()
{
    return noduri;
}


void Graph::AddNod(Node n)
{
    n.setNumber(noduri.size());
    noduri.push_back(n);
}

void Graph::AddArc(Arc n)
{
    for(auto index:arce)
    {
        if(index.getFirstPoint().getNumber()==n.getFirstPoint().getNumber()&&index.getSecondPoint().getNumber()==n.getSecondPoint().getNumber())
        {
            return;
           }
    }
    arce.push_back(n);
}
void Graph::topologicalSortVerif(int nod, bool visited[], std::stack<int>& stack)
{

    visited[nod] = true;

    std::list<int>::iterator i;
    for (i = adj[nod].begin(); i != adj[nod].end(); ++i)
        if (!visited[*i])
            topologicalSortVerif(*i, visited, stack);
    stack.push(nod);
}
bool Graph::hasCycleVerif(int nod, bool visited[], bool* recStack)
{
    if (visited[nod] == false)
    {
        visited[nod] = true;
        recStack[nod] = true;
        std::list<int>::iterator i;
        for (i = adj[nod].begin(); i != adj[nod].end(); ++i)
        {
            if (!visited[*i] && hasCycleVerif(*i, visited, recStack))
                return true;
            else if (recStack[*i])
                return true;
        }

    }
    recStack[nod] = false;
    return false;
}


bool Graph::hasCycle()
{
    int nr=getNumberofNodes();
    bool* visited = new bool[nr];
    bool* recStack = new bool[nr];
    for (int i = 0; i < nr; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < nr; i++)
        if (hasCycleVerif(i, visited, recStack))
            return true;

    return false;
}

void Graph::GenerareMatriceCosturi()
{
    std::vector<int>line;
    for(int ind=0;ind<getNumberofNodes();ind++)
        line.push_back(0);
    for(int index=0;index<getNumberofNodes();index++)
    {
        matrCosturi.push_back(line);
    }
    for(auto &ind1:arce)
    {
        matrCosturi[ind1.getFirstPoint().getNumber()][ind1.getSecondPoint().getNumber()]=ind1.GetCapacitate();
    }
}

bool Graph::bfs(std::vector<std::vector<int> > &rGraph, int s, int t, std::vector<int> &parent)
{
        std::vector<bool> visited;
        for(int index=0;index< getNumberofNodes();index++)
            visited.push_back(false);

        std::queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v = 0; v < getNumberofNodes(); v++) {
                if (visited[v] == false && rGraph[u][v] > 0)
                {
                    if (v == t)
                    {
                        parent[v] = u;
                        return true;
                    }
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
        return false;
}

int Graph::fordFulkerson(int s, int t)
{
        int u, v;
        std::vector<std::vector<int>> copie;
        copie=matrCosturi;

        std::vector<int>parent;
        for(int ind=0;ind<getNumberofNodes();ind++)
            parent.push_back(-1);
        int max_flow = 0;

        while (bfs(copie, s, t, parent)) {

            int path_flow = INT_MAX;
            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                path_flow = std::min(path_flow, copie[u][v]);
            }

            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                copie[u][v] -= path_flow;
                copie[v][u] += path_flow;
            }

            max_flow += path_flow;
        }

       std::vector<bool> visited;
       for(int index=0;index<getNumberofNodes();index++)
           visited.push_back(false);
         dfs(copie, s, visited);

         for (int i = 0; i < getNumberofNodes(); i++)
           for (int j = 0; j < getNumberofNodes(); j++)
               if (visited[i] && !visited[j] && matrCosturi[i][j])
               {
                   for(auto& it:arce)
                   {
                       if(it.getFirstPoint().getNumber()==i &&it.getSecondPoint().getNumber()==j)
                       {
                           it.SetColour("red");
                       }
                   }
               }
        return max_flow;
}

void Graph::dfs(std::vector<std::vector<int> > &rGraph, int s, std::vector<bool>& visited)
{
    visited[s] = true;
      for (int i = 0; i < getNumberofNodes(); i++)
         if (rGraph[s][i] && !visited[i])
             dfs(rGraph, i, visited);
}



void Graph::topologicalSort(std::vector<int>&topo)
{
    std::stack<int> stack;
    int nr=getNumberofNodes();
    bool* visited = new bool[nr];
    for (int index2 = 0; index2 < nr; index2++)
        visited[index2] = false;

    for (int index = 0; index < nr; index++)
        if (visited[index] == false)
            topologicalSortVerif(index, visited, stack);

    while (stack.empty() == false) {
        topo.push_back(stack.top());
        stack.pop();
    }
}



Node Graph::GetLastNode()
{
    return noduri[noduri.size()-1];
}

int Graph::getNumberofNodes()
{
    return noduri.size();
}

void Graph::setNrOfNodes(int x)
{
    nr_noduri=x;
}


void Graph::GenerareMatriceAdiacenta()
{

}

void Graph::GenerareListaAdiacenta()
{
    listaAdiacenta=GetArce();

}


