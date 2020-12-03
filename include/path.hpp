/*
* The path class is responsible for constrcuting for paths. it also 
* perform subfunctions to find the neighbours, AStarsearch, findtheHvalue, findDistance
*
*/
#include <iostream>
#include <vector>
#include <string>
#include <node.hpp>
#include <list>
#include <map>
class Path{
    public:
        Path(float startx, float starty, float endx, float endy);
        Path(const Path& path)=delete;
     //   float findDistance(); // find distance between two points
        void AStarSearch(Node &curr, Node &dest); // perform a shortest path algorithm to find the closes route betwwen two points

      //  void findNeighbors(Node* curr);
     //   float findHvalue(const Node* node) const;
     //   auto &Nodes() const noexcept { return m_Nodes; }
        void updateNodes(); // update the node list
        std::vector<Node *> neighbors;
        Node start_;
        Node end_;

    private:       
     
     //   Node::Point *start_point_; //starting point
      //  Node::Point *end_point_; // ending point of path
       // std::vector<Node> m_Nodes; // contains the list of nodes in a path
       //std::unordered_map<int, std::vector<const Path *>> node_to_road;
       std::list<Node> path;
       std::vector<Node> m_Nodes;
};

