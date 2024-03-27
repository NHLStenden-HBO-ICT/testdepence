#pragma once

#include "CheatCompile.h"
#include <vector>
#include <array>
#include <Surface.h>
#include <Sprite.h>
#include <tank.h>
#include <TerrainTile.h>

namespace testdependence {

    using namespace std;
    class TerrainM
    {
    public:

        TerrainM();
        TerrainM(ID2D1DeviceContext2* d2dContext, IWICImagingFactory2* wicFactory);
        void GenerateMap();
        void draw()const;
        void draw(Surface* target) const;
        float getDistanceFromPoint(vec2 start, vec2 end);
        float angleChecker(vec2 hit, vec2 dir, vec2& target, TerrainTile* player_Tile);
        vec2 incrementAngle(float degrees, vec2 rotationVec);
        std::vector<vec2>& revertRoute(std::vector<vec2>& route);
        std::vector<vec2> searchWander(vec2 start, vec2 end, Tank& t);
        std::vector<std::pair<vec2, float>> CheckAngle(vec2& currentPoint, vec2& dir, vec2& target, TerrainTile* player_Tile);
        vec2 getDirection(vec2 start, vec2 end);
        void toggleTile(vec2 tpos);
        bool checkTile(vec2& tpos, TerrainTile* player_Tile);
        TerrainTile getTile(vec2 tpos);
        void ClearTiles(std::vector<TerrainTile*> tileset);
        TerrainTile* GetRealWorldTilePos(vec2& pos, bool firstTime);
        std::pair <vec2, float> findSmallest(std::vector<std::pair<vec2, float>>& anglesAndDistance);
        //std::array<std::array<TerrainTile, terrain_width>, terrain_height> getTiles()
        //Use Breadth-first search to find shortest route to the destination
        vector<vec2> get_route(const Tank& tank, const vec2& target);

        bool IsInBounds(vec2& pos);

        Sprite getCoord(int x, int y);
        static constexpr int sprite_size = 16;
        //the sizes very important
        static constexpr size_t terrain_width = 80;
        static constexpr size_t terrain_height = 45;
        std::unique_ptr<Sprite> tile_grass2;
        std::unique_ptr<Sprite> tile_forest2;
        std::unique_ptr<Sprite> tile_rocks2;
        std::unique_ptr<Sprite> tile_mountains2;
        std::unique_ptr<Sprite> tile_water2;
        std::array<std::array<TerrainTile, terrain_width>, terrain_height> tiles;
        //45 80
        void IloveWindows(const TerrainTile& vista);
        bool is_accessible(int y, int x);



    private:

        std::unique_ptr<Surface> grass_img;
        std::unique_ptr<Surface> forest_img;
        std::unique_ptr<Surface> rocks_img;
        std::unique_ptr<Surface> mountains_img;
        std::unique_ptr<Surface> water_img;

        //create sprites
        std::unique_ptr<Sprite> tile_grass;
        std::unique_ptr<Sprite> tile_forest;
        std::unique_ptr<Sprite> tile_rocks;
        std::unique_ptr<Sprite> tile_mountains;
        std::unique_ptr<Sprite> tile_water;

    };

}