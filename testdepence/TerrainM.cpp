#include "pch.h"
#include "TerrainM.h"
#include "CheatCompile.h"
#include "TerrainM.h"
#include <set>
#include <unordered_set>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <queue>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
namespace fs = std::filesystem;

namespace testdependence {

    //copy the precompile headers

    //safe
    TerrainM::TerrainM() {
        //Load terrain layout file and fill grid based on tiletypes
        std::filesystem::path terrain_file_path{ "assets/terrain.txt" };

        //open path to terrain
        std::ifstream terrain_file(terrain_file_path);
        //std::ifstream::getline(terrain_file, "");
        //check if stream is open
        if (terrain_file.is_open())
        {
            //read stuff
            std::string terrain_line;

            getline(terrain_file, terrain_line);
            std::getline(terrain_file, terrain_line);
            //std::getline
            std::istringstream lineStream(terrain_line);
            //std::getline(terrain_file, terrain_line);
           // std::getline(terrain_file, terrain_line);
            //std::istringstream lineStream(terrain_line);
            int rows;

            lineStream >> rows;

            for (size_t row = 0; row < rows; row++)
            {
                std::getline(terrain_file, terrain_line);

                for (size_t collumn = 0; collumn < terrain_line.size(); collumn++)
                {
                    switch (std::toupper(terrain_line.at(collumn)))
                    {
                        //Never uncomment these lines, but keep them here to be sure
                        //just call device first when you do the dirty
                    case 'G':
                        tiles.at(row).at(collumn).tile_type = TileType::GRASS;
                        //tiles.at(row).at(collumn).Pic = tile_grass2.get();
                        break;
                    case 'F':
                        tiles.at(row).at(collumn).tile_type = TileType::FORREST;
                        //tiles.at(row).at(collumn).Pic = tile_forest2.get();
                        break;
                    case 'R':
                        tiles.at(row).at(collumn).tile_type = TileType::ROCKS;
                        //tiles.at(row).at(collumn).Pic = tile_rocks2.get();
                        break;
                    case 'M':
                        tiles.at(row).at(collumn).tile_type = TileType::MOUNTAINS;
                        //tiles.at(row).at(collumn).Pic = tile_mountains2.get();
                        break;
                    case 'W':
                        tiles.at(row).at(collumn).tile_type = TileType::WATER;
                        //tiles.at(row).at(collumn).Pic = tile_water2.get();
                        break;
                    default:
                        tiles.at(row).at(collumn).tile_type = TileType::GRASS;
                        //tiles.at(row).at(collumn).Pic = tile_grass2.get();
                        break;
                    }
                }
            }
        }
        else
        {
            std::cout << "Could not open terrain file! Is the path correct? Defaulting to grass.." << std::endl;
            std::cout << "Path was: " << terrain_file_path << std::endl;
        }
        //Instantiate tiles for path planning
        for (int y = 0; y < tiles.size(); y++)
        {
            for (int x = 0; x < tiles.at(y).size(); x++)
            {
                //beetje raar maar ik even niks beters bedenken
                //signed and unsigned bende
                tiles.at(y).at(x).position_x = x;
                tiles.at(y).at(x).position_y = y;
                tiles.at(y).at(x).Pos = vec2(x, y);
            }
        }

    }

    //to safe out mother earth from many
    void TerrainM::IloveWindows(const TerrainTile& vista) {

        vec2& vist = vec2(vista.position_x, vista.position_y);
        int y = vist.y;
        int x = vist.x;
        if (is_accessible(y, x + 1)) { tiles.at(y).at(x).exits.push_back(&tiles.at(y).at(x + 1)); }
        if (is_accessible(y, x - 1)) { tiles.at(y).at(x).exits.push_back(&tiles.at(y).at(x - 1)); }
        if (is_accessible(y + 1, x)) { tiles.at(y).at(x).exits.push_back(&tiles.at(y + 1).at(x)); }
        if (is_accessible(y - 1, x)) { tiles.at(y).at(x).exits.push_back(&tiles.at(y - 1).at(x)); }
    }

    void TerrainM::GenerateMap()
    {


        ////Load terrain layout file and fill grid based on tiletypes

        //open path to terrain
        std::ifstream terrain_directfile("terrain.txt");
        std::ifstream terrain_file;

        terrain_file.open("terrain.txt");
        //std::ifstream::getline(terrain_file, "");
        //check if stream is open
        if (terrain_file.is_open())
        {
            //read stuff
            std::string terrain_line;

            std::getline(terrain_file, terrain_line);
            //std::getline
            std::istringstream lineStream(terrain_line);
            int rows;

            lineStream >> rows;
            for (size_t row = 0; row < rows; row++)
            {
                std::getline(terrain_file, terrain_line);

                for (size_t collumn = 0; collumn < terrain_line.size(); collumn++)
                {
                    switch (std::toupper(terrain_line.at(collumn)))
                    {
                    case 'G':
                        tiles.at(row).at(collumn).tile_type = TileType::GRASS;
                        break;
                    case 'F':
                        tiles.at(row).at(collumn).tile_type = TileType::FORREST;
                        break;
                    case 'R':
                        tiles.at(row).at(collumn).tile_type = TileType::ROCKS;
                        break;
                    case 'M':
                        tiles.at(row).at(collumn).tile_type = TileType::MOUNTAINS;
                        break;
                    case 'W':
                        tiles.at(row).at(collumn).tile_type = TileType::WATER;
                        break;
                    default:
                        tiles.at(row).at(collumn).tile_type = TileType::GRASS;
                        break;
                    }
                }
            }
        }

    }

    //safe too
    //make use of resourches
    TerrainM::TerrainM(ID2D1DeviceContext2* d2dContext, IWICImagingFactory2* wicFactory)
    {
       
        tile_grass2 = std::make_unique<Sprite>(std::wstring(L"assets/tile_grass.png"), 1, d2dContext, wicFactory);
        tile_forest2 = std::make_unique<Sprite>(std::wstring(L"assets/tile_forest.png"), 1, d2dContext, wicFactory);
        tile_rocks2 = std::make_unique<Sprite>(std::wstring(L"assets/tile_rocks.png"), 1, d2dContext, wicFactory);
        tile_water2 = std::make_unique<Sprite>(std::wstring(L"assets/tile_water.png"), 1, d2dContext, wicFactory);
        tile_mountains2 = std::make_unique<Sprite>(std::wstring(L"assets/tile_mountains.png"), 1, d2dContext, wicFactory);

        //Load terrain layout file and fill grid based on tiletypes
        std::filesystem::path terrain_file_path{ "assets/terrain.txt" };

        //open path to terrain
        std::ifstream terrain_file(terrain_file_path);
        //std::ifstream::getline(terrain_file, "");
        //check if stream is open
        if (terrain_file.is_open())
        {
            //read stuff
            std::string terrain_line;

            std::getline(terrain_file, terrain_line);
            //std::getline
            std::istringstream lineStream(terrain_line);
            int rows;

            lineStream >> rows;

            for (size_t row = 0; row < rows; row++)
            {
                std::getline(terrain_file, terrain_line);

                for (size_t collumn = 0; collumn < terrain_line.size(); collumn++)
                {
                    switch (std::toupper(terrain_line.at(collumn)))
                    {
                    case 'G':
                        tiles.at(row).at(collumn).tile_type = TileType::GRASS;
                        tiles.at(row).at(collumn).Pic = tile_grass2.get();
                        break;
                    case 'F':
                        tiles.at(row).at(collumn).tile_type = TileType::FORREST;
                        tiles.at(row).at(collumn).Pic = tile_forest2.get();
                        break;
                    case 'R':
                        tiles.at(row).at(collumn).tile_type = TileType::ROCKS;
                        tiles.at(row).at(collumn).Pic = tile_rocks2.get();
                        break;
                    case 'M':
                        tiles.at(row).at(collumn).tile_type = TileType::MOUNTAINS;
                        tiles.at(row).at(collumn).Pic = tile_mountains2.get();
                        break;
                    case 'W':
                        tiles.at(row).at(collumn).tile_type = TileType::WATER;
                        tiles.at(row).at(collumn).Pic = tile_water2.get();
                        break;
                    default:
                        tiles.at(row).at(collumn).tile_type = TileType::GRASS;
                        tiles.at(row).at(collumn).Pic = tile_grass2.get();
                        break;
                    }
                }
            }
        }
        else
        {
            std::cout << "Could not open terrain file! Is the path correct? Defaulting to grass.." << std::endl;
            std::cout << "Path was: " << terrain_file_path << std::endl;
        }


        //Instantiate tiles for path planning
        for (size_t y = 0; y < tiles.size(); y++)
        {
            for (size_t x = 0; x < tiles.at(y).size(); x++)
            {
                //beetje raar maar ik even niks beters bedenken
                tiles.at(y).at(x).position_x = x;
                tiles.at(y).at(x).position_y = y;
                tiles.at(y).at(x).Pos = vec2(x, y);
                //tiley[y][x];

            }
        }
    }

    //attempt a voronoi 

    bool TerrainM::IsInBounds(vec2& pos) {
        if ((pos.x >= 0 && pos.x < terrain_width) && (pos.y >= 0 && pos.y < terrain_height)) {
            return true;
        }
        return false;
    }


    bool TerrainM::is_accessible(int y, int x) {

        //Bounds check
        if ((x >= 0 && x < terrain_width) && (y >= 0 && y < terrain_height))
        {
            //Inaccessible terrain check
            if (tiles.at(y).at(x).tile_type != TileType::MOUNTAINS && tiles.at(y).at(x).tile_type != TileType::WATER)
            {
                return true;
            }
        }
        return false;
    }


    vector<vec2> TerrainM::get_route(const Tank& tank, const vec2& target)
    {
        //Find start and target tile
        const size_t pos_x = tank.position.x / sprite_size;
        const size_t pos_y = tank.position.y / sprite_size;

        const size_t target_x = target.x / sprite_size;
        const size_t target_y = target.y / sprite_size;

        //Init queue with start tile
        std::queue<vector<TerrainTile*>> queue;
        queue.emplace();
        queue.back().push_back(&tiles.at(pos_y).at(pos_x));

        std::vector<TerrainTile*> visited;

        bool route_found = false;
        std::vector<TerrainTile*> current_route;
        while (!queue.empty() && !route_found)
        {
            current_route = queue.front();
            queue.pop();
            TerrainTile* current_tile = current_route.back();

            //Check all exits, if target then done, else if unvisited push a new partial route
            for (TerrainTile* exit : current_tile->exits)
            {
                if (exit->position_x == target_x && exit->position_y == target_y)
                {
                    current_route.push_back(exit);
                    route_found = true;
                    break;
                }
                else if (!exit->visited)
                {
                    exit->visited = true;
                    visited.push_back(exit);
                    queue.push(current_route);
                    queue.back().push_back(exit);
                }
            }
        }

        //Reset tiles
        for (TerrainTile* tile : visited)
        {
            tile->visited = false;
        }

        if (route_found)
        {
            //Convert route to vec2 to prevent dangling pointers
            std::vector<vec2> route;
            for (TerrainTile* tile : current_route)
            {
                route.push_back(vec2((float)tile->position_x * sprite_size, (float)tile->position_y * sprite_size));
            }
            return route;
        }
        else
        {
            return  std::vector<vec2>();
        }

    }
    float TerrainM::getDistanceFromPoint(vec2 start, vec2 end) {
        // Calculate the difference vector between points
        vec2 diff = (start - end);
        // Use Pythagoras' theorem to calculate the distance
        return std::sqrt(diff.x * diff.x + diff.y * diff.y);
    }
    vec2 round_vec2(const vec2& v) {
        // Use std::round to round each component of the vector
        return vec2(std::round(v.x), std::round(v.y));
    }

    vec2 TerrainM::getDirection(vec2 start, vec2 end) {
        return (end - start).normalized();
    }

    std::vector<vec2>& TerrainM::revertRoute(std::vector<vec2>& route) {


        for (vec2& pos : route) {
            pos.x = std::round(static_cast<float>(static_cast<float>(pos.x) * static_cast<float>(16)));
            pos.y = std::round(static_cast<float>(static_cast<float>(pos.y) * static_cast<float>(16)));
        }

        return route;
    }


    //afronding opgelost
    //potentie voor hashmap:

    //this is a breakpoint class which will be called when bad things happen
    void pointStopTest() {
        int stophere = 90;
    }
    //this method is for big numbers and return a needed tile
    //the big number will be divided.
    //after the devide the pathfinding will work in a more normilized way.
    TerrainTile* TerrainM::GetRealWorldTilePos(vec2& pos, bool firstTime) {

        //this means we need to convert big numbers to small numbers
        //first time is the way to check what kind of values will be used
        //fist time means that the pathfinding has not yet and needs to find one first using the start vector
        if (firstTime) {
            //attempt safe conversion by casting
            short net_x = std::round(static_cast<short>(static_cast<float>(pos.x) / static_cast<float>(sprite_size)));
            short net_y = std::round(static_cast<short>(static_cast<float>(pos.y) / static_cast<float>(sprite_size)));
            //check if the position is within a the map range 
            if (IsInBounds(vec2(net_x, net_y))) {
                //return a the tile at the rounded position
                //possible data loss
                return &tiles.at(std::round(net_y)).at(std::round(net_x));
            }
            //the request is out of range
            else {
                return nullptr;
            }
        }
        //if the first time is false it mean that the position coordinates are already divided
        //we can check directy if the pos is within the bounds
        if (IsInBounds(pos)) {
            //return a terraintaile at the rounded position
            return &tiles.at(std::round(pos.y)).at(std::round(pos.x));
        }
        return nullptr;

    }

    // Define a function that takes a vec2 as a parameter and returns a rounded vec2
    //converted to new system
    // will crash
    //check if we can go to this tile
    //returns true if we can pass on
    bool TerrainM::checkTile(vec2& tpos, TerrainTile* player_Tile) {
        if (IsInBounds(tpos)) {
            //make var to avoid so many duplicate calls
            TerrainTile c_tile = *GetRealWorldTilePos(vec2(std::round(tpos.x), std::round(tpos.y)), false);
            if (&c_tile.Pos == &player_Tile->Pos) {
                int hanstest = 90;
                return true;
            }
            else {

                if (c_tile.tile_type != TileType::MOUNTAINS && c_tile.tile_type != TileType::WATER && !c_tile.visited)
                {
                    return true;
                }
            }


        }
        return false;
    }

    std::vector<vec2> TerrainM::searchWander(vec2 start, vec2 target, Tank& t) {

        vec2 ty(0, 0);
        ty = incrementAngle(30, vec2(1, 1));

        TerrainTile* currentTile = GetRealWorldTilePos(start, true);
        TerrainTile* tileTarget = GetRealWorldTilePos(target, true);
        if (tileTarget == nullptr) {
            return {};
        }
        //these are way less intensive
        vec2 currentPos = vec2(currentTile->position_x, currentTile->position_y);
        vec2 targetT = vec2(tileTarget->position_x, tileTarget->position_y);

        std::vector<vec2> backlog;
        std::vector<TerrainTile>* bath;

        //std::vector<vec2*> path = a_star(currentTile, tileTarget);
        std::vector<std::reference_wrapper<TerrainTile>> tilesToReset; // Use a vector of Tile pointers to keep track of which tiles to reset
        while (currentPos != targetT && getDistanceFromPoint(currentPos, targetT) >= 1) { // Simplify the check for reaching the target
            vec2 dir = getDirection(currentPos, targetT);
            //fix this, the toggle is way too big
            //after 23 frame duplication tends to happen alot
            if (checkTile(vec2(currentPos + dir), currentTile)) {
                currentPos += dir;
                backlog.push_back(currentPos);
                tilesToReset.push_back(*currentTile);
                currentTile = GetRealWorldTilePos((currentPos), false);

                //tilesToReset.push_back(*currentTile);
            }
            else {
                // We can't move in the desired direction, so find the smallest angle and distance to the target
                std::pair<vec2, float> anglesAndDistance = findSmallest(CheckAngle(currentPos, (currentPos + dir), targetT, currentTile));

                if (anglesAndDistance.second == 9000) {
                    // If we can't find a valid angle and distance, backtrack to the previous tile in the backlog
                    if (backlog.empty()) {
                        int pad = 10;
                        // If the backlog is empty, there is no valid path to the target
                        return {};
                    }
                    currentTile->visited = true;
                    backlog.pop_back();


                    currentPos = backlog.back();

                }
                else {
                    // We found a valid angle and distance, so add the current position to the backlog and move to the next tile
                    //get the wrong direction
                    currentTile = GetRealWorldTilePos(currentPos + anglesAndDistance.first, false);
                    currentPos = currentPos + anglesAndDistance.first;
                    backlog.push_back(currentPos);
                    tilesToReset.push_back(*currentTile);
                    //currentTile->visited = true;

                }
            }

        }

        // Reset any remaining toggled tiles
        for (TerrainTile& tile : tilesToReset) {
            tile.visited = false;
        }
        backlog = revertRoute(backlog);
        return std::ref(backlog);
    }

    void TerrainM::ClearTiles(std::vector<TerrainTile*> tileset) {

        //reset all
        for (TerrainTile* tile : tileset) {
            tile->visited = false;
        }
    }

    void TerrainM::toggleTile(vec2 tpos) {
        const size_t pos_x = tpos.x / sprite_size;
        const size_t pos_y = tpos.y / sprite_size;
        //tiles.at(pos_y).at(pos_x).visited = true;
        if ((pos_x >= 0 && pos_x < terrain_width) && (pos_y >= 0 && pos_y < terrain_height))
        {
            //Inaccessible terrain check
            //als er gevisit is kunnen wij niet meer verder
            if (tiles.at(pos_y).at(pos_x).tile_type != TileType::MOUNTAINS && tiles.at(pos_y).at(pos_x).tile_type != TileType::WATER || !tiles.at(pos_y).at(pos_x).visited)
            {
                //return true;
                tiles.at(pos_y).at(pos_x).visited = true;
            }
        }
    }
    //bad mehtod

    TerrainTile TerrainM::getTile(vec2 tpos) {
        //const size_t pos_x = tpos.x / sprite_size;
        //const size_t pos_y = tpos.y / sprite_size;
        try
        {
            return tiles.at(tpos.y).at(tpos.x);
        }
        catch (const std::exception&)
        {

        }
        //return tiles.at(pos_y).at(pos_x);
    }
    //begin to move a tile up
    //void TerrainM::WanderSearch(std::vector<vec2*> backlog, vec2& nextPoint, vec2& target) {

    //    //dit is de basis van de loop
    //    //zoek een richting
    //    vec2 dir = getDirection(nextPoint, target);
    //    if (nextPoint == target) {
    //        //target reached
    //        backlog.push_back(&nextPoint);
    //        //breakout(backlog);
    //    }
    //    //dan check de richting
    //    // 
    //    //take one step into that direction
    //    if (checkTile(nextPoint + dir)) {
    //        //go to the next tile
    //        //backlog.push_back(&getTile(nextPoint + dir));
    //        backlog.push_back(&nextPoint);
    //        WanderSearch(backlog, vec2(nextPoint + dir), target);
    //    }
    //    else {
    //        //there is a obstacle inside 
    //        //dir.length = magnitude
    //        // dir.normilize = normal
    //        //run a few casts around the collision point and then compare distance to the target, the lowest wins


    // Method to find the smallest distance in the vector of pairs and print it or a message if blocked
    std::pair <vec2, float> TerrainM::findSmallest(std::vector<std::pair<vec2, float>>& anglesAndDistance) {

        std::pair <vec2, float>  smallest = anglesAndDistance[0]; // Use [] instead of at()
        for (auto& pair : anglesAndDistance) { // Use a range-based for loop
            if (pair.second < smallest.second && pair.second != 9000) {
                smallest = pair;
            }
        }

        return smallest;
        // Check if vector is not empty

            // Print smallest distance or message if blocked
        if (smallest.second != 9000) {
            return smallest;
        }
        else {
            std::cout << "All distances are blocked.\n";
            return std::make_pair(vec2(), 9000); // Return a special value;
        }

        // return std::make_pair(vec2(), 9000.f);

    }


    // This code is based on an example from Microsoft Bing chat mode
    // I gave it the command to extract a few methods from my code
    // Author: Microsoft Bing chat mode
    // Date: 2023-03-20
    // URL: https://www.bing.com/chat
    std::vector<std::pair<vec2, float>> TerrainM::CheckAngle(vec2& currentPoint, vec2& dir, vec2& target, TerrainTile* player_Tile) {

        std::vector<std::pair<vec2, float>> anglesAndDistance;

        //vec2 att1 = incrementAngle(30, vec2(1,1));
        vec2 att1 = incrementAngle(30, currentPoint);
        att1 = getDirection(currentPoint, currentPoint + att1);
        float angle = angleChecker(currentPoint, att1, target, player_Tile);
        anglesAndDistance.emplace_back(att1.normalized(), angle);
        //int i = 0;

        for (int i = 0; i < 8; i++) { // Loop from 0 to 7
            // Calculate the next angle to check.
            //att1 = incrementAngle(30 + (i * 30), vec2(1,1));
            att1 = incrementAngle(30 + (i * 30), currentPoint);
            att1 = getDirection(currentPoint, att1);
            // Calculate the angle and distance to the target for this angle.
            float angle = angleChecker(currentPoint, att1, target, player_Tile);
            anglesAndDistance.emplace_back(att1, angle);

        }

        //return anglesAndDistance;
        //there still is need to check for valid data
        return anglesAndDistance;
    }


    //still need a way to check if we don't go back by accident
    float TerrainM::angleChecker(vec2 hit, vec2 dir, vec2& target, TerrainTile* player_Tile) {
        //just check if the tile is safe
        if (checkTile(vec2(hit + dir), player_Tile)) {
            return getDistanceFromPoint(hit + dir, target);

        }
        else
        {
            return 9000;
        }
    }



    // A method to get the direction (angle in radians) of the vector
    float direction(vec2& vec) {
        return std::atan2(vec.y, vec.x);
    }

    // A method to increment the angle of the vector by certain degrees
    vec2 TerrainM::incrementAngle(float degrees, vec2 rotationVec) {
        // Get the current angle and magnitude of the vector
        float angle = direction(rotationVec);
        //get the lenght of the vector
        float mag = rotationVec.length();
        angle += degrees;
        return vec2(mag * std::cos(angle), mag * std::sin(angle));
    }




    Sprite TerrainM::getCoord(int _x, int _y)
    {
        //crashed letterlijk 
        int posX = _x;
        int posY = _y;

        //moet om de sprite size een nieuw antwoord returnen
        switch (tiles.at(_y).at(_x).tile_type)
        {
        case TileType::GRASS:
            tile_grass2->drawMK2(posX, posY);
            return Sprite(*tile_grass2);
            break;
        case TileType::FORREST:
            tile_forest2->drawMK2(posX, posY);
            return Sprite(*tile_forest2);
            break;
        case TileType::ROCKS:
            tile_rocks2->drawMK2(posX, posY);
            return Sprite(*tile_rocks2);
            break;
        case TileType::MOUNTAINS:
            tile_mountains2->drawMK2(posX, posY);
            return Sprite(*tile_mountains2);
            break;
        case TileType::WATER:
            tile_water2->drawMK2(posX, posY);
            return Sprite(*tile_water2);
            break;
        default:
            tile_grass2->drawMK2(posX, posY);
            return Sprite(*tile_grass2);
            break;
        }
    }
    // A function to calculate the heuristic cost of a tile based on its distance to the goal
    float heuristic(TerrainTile* tile, TerrainTile* goal) {
        return hypot(tile->position_x - goal->position_x, tile->position_y - goal->position_y);
    }

    // A function to find the tile with the lowest f-cost in a hashmap of tiles
    TerrainTile* lowest_fcost(unordered_map<TerrainTile*, double> open_map) {
        TerrainTile* lowest = nullptr;
        float min_cost = numeric_limits<float>::infinity();
        for (auto& [tile, cost] : open_map) {
            if (cost < min_cost) {
                lowest = tile;
                min_cost = cost;
            }
        }
        return lowest;
    }

    // A function to reconstruct the path from the start to the goal by following the parent pointers
    vector<TerrainTile*> reconstruct_path(unordered_map<TerrainTile*, TerrainTile*> came_from, TerrainTile* current) {
        vector<TerrainTile*> path;
        path.push_back(current);
        while (came_from.find(current) != came_from.end()) {
            current = came_from[current];
            path.push_back(current);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    void TerrainM::draw() const
    {

        for (size_t y = 0; y < tiles.size(); y++)
        {
            for (size_t x = 0; x < tiles.at(y).size(); x++)
            {
                //crashed letterlijk 
                int posX = (x * sprite_size) + HEALTHBAR_OFFSET;
                int posY = y * sprite_size;

                switch (tiles.at(y).at(x).tile_type)
                {
                case TileType::GRASS:
                    tile_grass2->drawMK2(posX, posY);
                    break;
                case TileType::FORREST:
                    tile_forest2->drawMK2(posX, posY);
                    break;
                case TileType::ROCKS:
                    tile_rocks2->drawMK2(posX, posY);
                    break;
                case TileType::MOUNTAINS:
                    tile_mountains2->drawMK2(posX, posY);
                    break;
                case TileType::WATER:
                    tile_water2->drawMK2(posX, posY);
                    break;
                default:
                    tile_grass2->drawMK2(posX, posY);
                    break;
                }
            }
        }
    }

    void TerrainM::draw(Surface* target) const
    {

        for (size_t y = 0; y < tiles.size(); y++)
        {
            for (size_t x = 0; x < tiles.at(y).size(); x++)
            {
                //crashed letterlijk 
                int posX = (x * sprite_size) + HEALTHBAR_OFFSET;
                int posY = y * sprite_size;

                switch (tiles.at(y).at(x).tile_type)
                {
                case TileType::GRASS:
                    tile_grass2->drawMK2(posX, posY);
                    break;
                case TileType::FORREST:
                    tile_forest2->drawMK2(posX, posY);
                    break;
                case TileType::ROCKS:
                    tile_rocks2->drawMK2(posX, posY);
                    break;
                case TileType::MOUNTAINS:
                    tile_mountains2->drawMK2(posX, posY);
                    break;
                case TileType::WATER:
                    tile_water2->drawMK2(posX, posY);
                    break;
                default:
                    tile_grass2->drawMK2(posX, posY);
                    break;
                }
            }
        }
    }
}