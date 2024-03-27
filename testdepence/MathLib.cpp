
#include "pch.h"
#include "MathLib.h"



namespace testdependence {


    std::vector<vec2*> MathLib::ConvertTovec2(std::vector<TerrainTile*> tiles) {
        std::vector<vec2*> toReturn;
        for (TerrainTile* panzaar : tiles) {

            toReturn.push_back(&panzaar->Pos);

        }

        return toReturn;
    }

    // A function to calculate the heuristic cost of a tile based on its distance to the goal
    float MathLib::heuristic(TerrainTile* tile, TerrainTile* goal) {
        return hypot(tile->position_x - goal->position_x, tile->position_y - goal->position_y);
    }

}