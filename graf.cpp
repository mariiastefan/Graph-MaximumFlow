#include "graf.h"
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <vector>
std::vector<Arc> Graf::GetArce()
{
    return arce;
}

std::vector<Node> Graf::GetNoduri()
{
    return noduri;
}


void Graf::AddNod(Node n)
{
    n.setNumber(noduri.size());
    noduri.push_back(n);
}

void Graf::AddArc(Arc n)
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



int Graf::getNumberofNodes()
{
    return noduri.size();
}
void Graf::GenerareMatriceAdiacenta()
{

}

void Graf::GenerareListaAdiacenta()
{
    listaAdiacenta=GetArce();

}
