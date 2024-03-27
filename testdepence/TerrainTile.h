#pragma once

#include <vector>
#include <ContainerTypes.h>
#include <TileType.h>
#include <Sprite.h>

namespace testdependence {




    class TerrainTile
    {



    public:
        //TerrainTile *up, *down, *left, *right;
        std::vector<TerrainTile*> exits;
        bool visited = false;
        vec2 Pos;
        float position_x;
        float position_y;
        float feramonen;
        Sprite* Pic = nullptr;
        TileType tile_type;
        float estimationCost;
        TerrainTile* Papa;

        // Default constructor
        TerrainTile::TerrainTile() {
            position_x = 0;
            position_y = 0;
            //Pic = nullptr;
        }

        // Constructor with parameters
        TerrainTile::TerrainTile(float x, float y, TileType type, Sprite* pic) {
            position_x = x;
            position_y = y;
            tile_type = type;
            Pic = pic;
        }
        //void getExi(TerrainM ter);

    private:
    };

}