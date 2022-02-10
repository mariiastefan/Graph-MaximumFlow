#include "arc.h"

Arc::Arc(Node n1, Node n2)
{
    srand (time(NULL));
    firstNode = n1;
    secondNode = n2;
    capacitate=rand() % 100;
    colour="green";
}

Node Arc::getFirstPoint()
{
    return firstNode;
}
Node Arc::getSecondPoint()
{
    return secondNode;
}

int Arc::GetCapacitate()
{
    return capacitate;
}

std::string Arc::GetColour()
{
    return colour;
}

void Arc::SetColour(std::string colour1)
{
    colour=colour1;
}

