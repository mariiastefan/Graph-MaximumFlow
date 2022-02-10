#ifndef ARC_H
#define ARC_H

#include "node.h"
#include <time.h>
class Arc
{
    Node firstNode, secondNode;
    int capacitate;
    std::string colour;
public:
    Arc(Node n1, Node n2);
    Node getFirstPoint();
    Node getSecondPoint();
    int GetCapacitate();
    std::string GetColour();
    void SetColour(std::string colour1);
};
#endif // ARC_H
