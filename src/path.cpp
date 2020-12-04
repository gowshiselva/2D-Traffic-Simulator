#include "path.hpp"
#include <algorithm>
#include "map.h"

Path::Path(float startx, float starty, float endx, float endy)
{
  start_.current_->x=startx;
  start_.current_->y=starty;
  end_.current_->x=endx;
  end_.current_->y=endy;
}

void Path::updateNodes()
{

}

void Path::AStarSearch(Node &curr,  Node &dest)
{
    curr.visited=true;
    path.push_back(curr);

  if (curr == dest)
        return;
  std::sort(curr.neighbors.begin(), curr.neighbors.end(), [dest, curr](Node a, Node b){

      auto d1=curr.findDistance(a)+ a.findDistance(dest);
      auto d2= curr.findDistance(b)+ b.findDistance(dest);   
      return d1<d2;
      });

    for (size_t ind =0 ; ind <= curr.neighbors.size(); ++ind)
    {
         AStarSearch(curr.neighbors[ind], dest);
    }
   if (dest.visited)
   {
     path.pop_back();
   }
        
}
