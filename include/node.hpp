#ifndef NODE_H
#define NODE_H

#include <limits>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <map.h>
#include <vector>
#include <ostream>
struct Point {
        double x = 0.f;
        double y = 0.f;
    };

class Node{
    public:
        Node();
        Node(Point* point);
        //Node(const Node& node); // copy constructor
      //  Node &operator=(const Node& node); // copy assignment
       // Node(Node && node); // move constructor
      //  Node &operator=(Node && node); // move assignment
        bool operator==(Node& a);
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.0;
        bool visited= false;
       // mutable std::vector<std::shared_ptr<Node>> neighbors_;

        //void findNeighbours();// find neighbout nodes
        float findDistance(const Node& other) const;
        float findDistance(Node& other) const; // find distance between two points
        std::vector<Node> neighbors;
        Node * parent = nullptr;
        Point* next_;
        Point* current_;
    private:
        int index;
        Node * FindNeighbor(std::vector<int> node_indices); // pass list of nodes to find the neighbour
        //Node * FindNeighbor(std::vector<int> nodes);
};
std::ostream &operator<<(std::ostream &os, const Node *node);



#endif