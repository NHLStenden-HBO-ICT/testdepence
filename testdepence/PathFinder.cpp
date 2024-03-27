
#include "pch.h"
#include "PathFinder.h"
#include <StarAndPath.h>



namespace testdependence {



	PathFinder::PathFinder(TerrainM& worldMap) : map(worldMap) {
		for (int y = 0; y < map.tiles.size(); y++)
		{
			for (int x = 0; x < map.tiles.at(y).size(); x++)
			{

				map.IloveWindows(map.tiles.at(y).at(x));
			}
		}


		//map.IloveWindows();

	}

	std::vector<vec2>& reconvert_route(std::vector<vec2>& route) {

		for each (vec2 pos in route)
		{
			pos.x = std::round(static_cast<short>(static_cast<float>(pos.x) * static_cast<float>(16)));
			pos.y = std::round(static_cast<short>(static_cast<float>(pos.y) * static_cast<float>(16)));

		}
		return route;
	}

	//this is the new get path method
	void PathFinder::getPath(std::vector<Tank>& tanklist) {
		std::vector<std::reference_wrapper<Tank>> tanksWithRoute;
		//for each incomming tank
		for (Tank& t : tanklist) {
			StarAndPath uiy;
			//set the route by using hillclimb
			t.set_route(uiy.aStar(map.GetRealWorldTilePos(t.position, true), map.GetRealWorldTilePos(t.target, true)));
			if (t.target != t.position) {
				tanksWithRoute.push_back(t);
			}

		}

	}
}