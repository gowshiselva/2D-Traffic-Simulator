#include "node.hpp"
#include "map.h"
Node::Node()
{

}
Node::Node( Point* curr, Point* next, Point* prev): next_(next), previous_(prev), current_(curr)
{

}
