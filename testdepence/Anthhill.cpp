#include "pch.h"
#include "Anthhill.h"
using namespace testdependence;

double r() { return (double)(rand() % RAND_MAX) / RAND_MAX; }



std::vector<vec2> Anthhill::findPathAnt(int ants, testdependence::TerrainTile& start, testdependence::TerrainTile& goal)
{



    std::vector<testdependence::TerrainTile*> tilestToclear;
    std::vector<testdependence::TerrainTile*> route;
    //dead points
    //store in a way that optimes the lookup
    //maybe add a sorting algo
    std::vector<testdependence::TerrainTile*> closedNodes;





    //first check if we reached the goal
    testdependence::TerrainTile& currentNode = start;

    while (&currentNode != &goal)
    {
        //magic random walk
        // 
        int randomStep = std::rand() % 2 == 0 ? 1 : -1;
        //pick random tile
        int totalexits = currentNode.exits.size();
        for (TerrainTile* exit : currentNode.exits)
        {
            if (exit == &goal)
            {
                break;
            }
            if (!exit->visited)
            {
                exit->visited = true;
                route.push_back(exit);
                currentNode = *exit;
            }
        }


    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int numSteps = 100; // Number of steps in the random walk
    int position = 0;         // Starting position

    std::cout << "Random Walk Simulation (1D):\n";

    for (int step = 1; step <= numSteps; ++step) {
        // Generate a random step (-1 or +1)
        int randomStep = std::rand() % 2 == 0 ? 1 : -1;

        // Update the position
        position += randomStep;

        // Print the current step and position
        std::cout << "Step " << step << ": " << (randomStep == 1 ? "Right" : "Left") << " (Position: " << position << ")\n";
    }


    //get the length of the path

    //feramone to add = 1/lengthofPath
    // 
    //add feramone to each tile in the route

    //let next actor join in




    return std::vector<vec2>();
}
//std::vector<vec2> Anthill::findPathAnt(int ants, testdependence::TerrainTile& start, testdependence::TerrainTile& goal)
//{
//    std::vector<testdependence::TerrainTile*> route;
//    std::vector<testdependence::TerrainTile*> closedNodes;
//
//    testdependence::TerrainTile* currentNode = &start;
//
//    while (currentNode != &goal)
//    {
//        bool foundExit = false;
//
//        // Loop through the exits of the current node.
//        for (testdependence::TerrainTile* exit : currentNode->exits)
//        {
//            // If the exit is the goal, we've found a path!
//            if (exit == &goal)
//            {
//                route.push_back(exit);
//                foundExit = true;
//                break;
//            }
//            // If the exit hasn't been visited yet, visit it.
//            else if (!exit->visited)
//            {
//                exit->visited = true;
//                route.push_back(exit);
//                currentNode = exit;
//                foundExit = true;
//                break;
//            }
//        }
//
//        // If no unvisited exit was found, backtrack.
//        if (!foundExit)
//        {
//            if (!route.empty())
//            {
//                route.pop_back();
//                if (!route.empty())
//                {
//                    currentNode = route.back();
//                }
//            }
//        }
//    }
//
//    // Convert the route from TerrainTiles to vec2s.
//    std::vector<vec2> path;
//    for (testdependence::TerrainTile* tile : route)
//    {
//        path.push_back(tile->Pos);  // Assuming each tile has a 'Pos' member of type vec2.
//    }
//
//    return path;
//}
//
//std::vector<vec2> Anthill::findPathAnt(int ants, testdependence::TerrainTile& start, testdependence::TerrainTile& goal)
//{
//    std::vector<testdependence::TerrainTile*> route;
//    std::vector<testdependence::TerrainTile*> closedNodes;
//
//    testdependence::TerrainTile* currentNode = &start;
//
//    while (currentNode != &goal)
//    {
//        bool foundExit = false;
//
//        // Loop through the exits of the current node.
//        for (testdependence::TerrainTile* exit : currentNode->exits)
//        {
//            // If the exit is the goal, we've found a path!
//            if (exit == &goal)
//            {
//                route.push_back(exit);
//                foundExit = true;
//                break;
//            }
//            // If the exit hasn't been visited yet, visit it.
//            else if (!exit->visited)
//            {
//                exit->visited = true;
//                route.push_back(exit);
//                currentNode = exit;
//                foundExit = true;
//                break;
//            }
//        }
//
//        // If no unvisited exit was found, backtrack.
//        if (!foundExit)
//        {
//            if (!route.empty())
//            {
//                route.pop_back();
//                if (!route.empty())
//                {
//                    currentNode = route.back();
//                }
//            }
//        }
//    }
//
//    // Add pheromone to each tile on the route based on 1/route length.
//    float pheromoneToAdd = 1.0f / route.size();
//    for (testdependence::TerrainTile* tile : route)
//    {
//        tile->feramonen += pheromoneToAdd;
//    }
//
//    // Convert the route from TerrainTiles to vec2s.
//    std::vector<vec2> path;
//    for (testdependence::TerrainTile* tile : route)
//    {
//        path.push_back(tile->Pos);  // Assuming each tile has a 'Pos' member of type vec2.
//    }
//
//    return path;
//}
//
//std::vector<vec2> Anthill::PheromoneGuidedSearch(int ants, testdependence::TerrainTile& start, testdependence::TerrainTile& goal)
//{
//    std::vector<testdependence::TerrainTile*> route;
//    std::vector<testdependence::TerrainTile*> closedNodes;
//
//    testdependence::TerrainTile* currentNode = &start;
//    float pheromoneInfluence = 0.5;  // Hoe sterk de feromonen de keuze van de mier beïnvloeden.
//
//    while (currentNode != &goal)
//    {
//        bool foundExit = false;
//
//        // Loop through the exits of the current node.
//        for (testdependence::TerrainTile* exit : currentNode->exits)
//        {
//            // If the exit is the goal, we've found a path!
//            if (exit == &goal)
//            {
//                route.push_back(exit);
//                foundExit = true;
//                break;
//            }
//            // If the exit hasn't been visited yet, visit it.
//            else if (!exit->visited)
//            {
//                // The chance to choose this exit is influenced by the amount of pheromone.
//                float randomValue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//                if (randomValue < exit->feramonen * pheromoneInfluence)
//                {
//                    exit->visited = true;
//                    route.push_back(exit);
//                    currentNode = exit;
//                    foundExit = true;
//                    break;
//                }
//            }
//        }
//
//        // If no unvisited exit was found, backtrack.
//        if (!foundExit)
//        {
//            if (!route.empty())
//            {
//                route.pop_back();
//                if (!route.empty())
//                {
//                    currentNode = route.back();
//                }
//            }
//        }
//    }
//
//    // Add pheromone to each tile on the route based on 1/route length.
//    float pheromoneToAdd = 1.0f / route.size();
//    for (testdependence::TerrainTile* tile : route)
//    {
//        tile->feramonen += pheromoneToAdd;
//    }
//
//    // Convert the route from TerrainTiles to vec2s.
//    std::vector<vec2> path;
//    for (testdependence::TerrainTile* tile : route)
//    {
//        path.push_back(tile->Pos);  // Assuming each tile has a 'Pos' member of type vec2.
//    }
//
//    return path;
//}
