
#include "pch.h"
#include "StarAndPath.h"
#include <MathLib.h>
#include <map>



namespace testdependence {


    //controleer de buren 
    TerrainTile* StarAndPath::buurtCheck(TerrainTile* current, TerrainTile* target, unordered_set<TerrainTile*> closed, std::vector<TerrainTile*> oldPath) {
        float smallestDistanceKost = 300;
        TerrainTile* neighborWithSmallestDistanceKost = nullptr;
        if (oldPath.size() > 600) {
            int stioer = 0;
        }

        for (TerrainTile* neighbor : current->exits) {
            //check if this node is already contained in the closedset
            if (closed.find(neighbor) != closed.end() && !neighbor->visited || neighbor == current || neighbor->visited) {
                continue;
            }

            float currentDistanceKost = MathLib::heuristic(neighbor, target);
            //kies de kleinste
            if (currentDistanceKost < smallestDistanceKost) {
                smallestDistanceKost = currentDistanceKost;
                neighborWithSmallestDistanceKost = neighbor;
            }
        }
        return neighborWithSmallestDistanceKost;
    }


    //this is actually hilll climb
    vector<vec2*> StarAndPath::aStar(TerrainTile* start, TerrainTile* goal) {
        //check if they are dead
        //this actualy tends to happpen more then i'd like
        //check if the input is valid
        if (start == nullptr) {
            return vector<vec2*>();
        }
        if (goal == nullptr) {
            return vector<vec2*>();
        }


        std::vector<TerrainTile*> tilestToclear;
        std::vector<TerrainTile*> route;
        //dead points
        //store in a way that optimes the lookup
        //maybe add a sorting algo
        unordered_set<TerrainTile*> closedNodes;



        //first check if we reached the goal
        TerrainTile* currentNode = start;
        TerrainTile* smallestNode;
        bool pathFound = false;
        //while
        while (!pathFound)
        {
            //time to make the path 
            //get the tile and add it to a list
            //then get the neighnour from that path

            smallestNode = buurtCheck(currentNode, goal, closedNodes, route);
            int stopped = 90;
            //check if the buurtcheck didnt return null
            //node is valid
            if (smallestNode != nullptr) {

                //time to hop on en list the old node down
                tilestToclear.push_back(currentNode);
                currentNode->visited = true;
                route.push_back(currentNode);

                currentNode = smallestNode;
                //check if we are to the end
                if (currentNode == goal) {
                    pathFound = true;
                }


            }
            else {          //dead route move back
                //check if there is a route
                if (!route.empty()) {
                    //the the node that we are on to the list since all neighbours are dead anyway
                    closedNodes.insert(currentNode);

                    //check if the current node has already been step back
                    if (currentNode == route.back()) {  //we already stepped back so we need to popback the route
                        //remove the last node out of the route
                        route.pop_back();

                        if (route.empty()) {
                            //nothing left 
                            //the popback killed all hope
                            //return and kill
                            for (TerrainTile* tile : tilestToclear) {
                                tile->visited = false;
                            }
                            return vector<vec2*>();
                        }
                    }

                    //set the currentNode to the last node of the list
                    currentNode = route.back();
                }   //no route left
                else {

                    //return empty path
                    for (TerrainTile* tile : tilestToclear) {
                        tile->visited = false;
                    }
                    return vector<vec2*>();
                }

            }


        }

        if (route.empty()) {
            for (TerrainTile* tile : tilestToclear) {
                tile->visited = false;
            }

            return vector<vec2*>();
        }
        else {
            for (TerrainTile* tile : tilestToclear) {
                tile->visited = false;
            }
            return MathLib::ConvertTovec2(route);
        }

    }





}