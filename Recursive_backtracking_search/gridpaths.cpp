#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
// for pair
#include <functional>
#include <string>

using namespace std;

// typedef for X,Y pair
typedef std::pair<size_t, size_t> XYPair;

// Utility Prototypes
bool operator==(const XYPair& p1, const XYPair& p2);
void printPaths(const std::vector<std::vector<XYPair> >& results);

// Utility function to compare XY points
bool operator==(const XYPair& p1, const XYPair& p2)
{
  return p1.first == p2.first && p1.second == p2.second;
}


// Primary street grid function prototype
std::vector<std::vector<XYPair> > gridpaths(const XYPair& inter, const XYPair& final);
// Prototype any helper functions here
void gridpathsHelper(std::vector<std::vector<XYPair> > &solutions, std::vector<XYPair> path, std::vector<XYPair> choice, int dest);







// Implement your gridpaths and any helper functions below
std::vector<std::vector<XYPair> > gridpaths(
    const XYPair& inter, 
    const XYPair& final)
{
  std::vector<std::vector<XYPair> > solutions;
  if (final.first == 0 && final.second == 0)
  {
    return solutions;
  }

  std::vector<XYPair> temp;
  std::vector<XYPair> destinations;
  destinations.push_back(inter);
  destinations.push_back(final);
  temp.push_back({0, 0});
  gridpathsHelper(solutions, temp, destinations, 0);
  return solutions;

}

void gridpathsHelper(std::vector<std::vector<XYPair> > &solutions, std::vector<XYPair> path, std::vector<XYPair> choice, int dest)
{
  if (path[path.size()-1] == choice[1]) //first base case when reach final 
  {
    solutions.push_back(path);
    return;
  }

  else if (path[path.size()-1] == choice[dest]) //second base case when reach dest
  {
    gridpathsHelper(solutions, path, choice, 1);
  }

  else
  {
    if (path[path.size()-1].first < choice[dest].first) //recurse on next x value if less than inter x value
    {
      size_t new_x = path[path.size()-1].first+1; //new x value
      path.push_back({new_x, path[path.size()-1].second}); //push back next coordinate
      if (path[path.size()-1] == choice[dest]) //if we reached the intermediate, switch over to final dest
      {
        gridpathsHelper(solutions, path, choice, 1);
      }

      else //continue with current choice of dest
      {
        gridpathsHelper(solutions, path, choice, dest);
      }

      path.pop_back(); //pop back to explore other paths

    }

    if (path[path.size()-1].second < choice[dest].second) //recurse on next y value if less than inter y value
    {
      size_t new_y = path[path.size()-1].second+1; //new y value
      path.push_back({path[path.size()-1].first, new_y}); //push back next coordinate
      if (path[path.size()-1] == choice[dest]) //if we reached intermediate, switch over to final dest
      {
        gridpathsHelper(solutions, path, choice, 1);
      }

      else
      {
        gridpathsHelper(solutions, path, choice, dest); //continue with current choice of dest
      }

      path.pop_back();
      
    }

  }

}


// Complete - but can be changed for debugging purposes
int main(int argc, char* argv[])
{
  // Default to intermediate point of 2,3 and final location of 3,4
  size_t ix = 2, iy = 3, fx = 3, fy = 4;
  if(argc >= 5) {
    ix = atoi(argv[1]);
    iy = atoi(argv[2]);
    fx = atoi(argv[3]);
    fy = atoi(argv[4]);
  }
  vector<vector<XYPair> > results;
  results = gridpaths({ix,iy},{fx,fy});  
  printPaths(results);

  return 0;
}

// Prints the results in a clean fashion for human consumption / debugging
void printPaths(const vector<vector<XYPair> >& results)
{
  for( const auto& path : results) {
    for( size_t i = 0; i < path.size()-1; i++ ) 
    {      
      cout << path[i].first << "," << path[i].second << " -> ";
    }
    cout << path.back().first << "," << path.back().second << endl;
  }
  cout << results.size() << " solutions." << endl;

}
