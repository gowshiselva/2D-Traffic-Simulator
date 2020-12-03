#include "node.hpp"
#include "map.h"
#include <cmath>
Node::Node():next_(nullptr), current_(nullptr)
{

}
Node::Node( Point* curr): next_(nullptr),  current_(curr)
{

}

bool Node::operator==(Node& a)
{
    return current_->x== a.current_->x && current_->y== a.current_->y ? true :false;
}


float Node::findDistance(const Node& other) const
{   
    float x=other.current_->x -this->current_->x;
    float y=other.current_->y- this->current_->y;

    return std::sqrt(std::pow(x,2)+ std::pow(y,2));
}
float Node::findDistance(Node& other) const
{   
    float x=other.current_->x -this->current_->x;
    float y=other.current_->y- this->current_->y;

    return std::sqrt(std::pow(x,2)+ std::pow(y,2));
}

std::ostream& operator<<(std::ostream &os, const Node *node)
{
    if(node)
    {
    os << "X :" << node->next_->x << "Y :" << node->next_->y << std::endl;
    }
    else
    {
        os << "null ptr " << std::endl;;
    }
    
  return os;
}