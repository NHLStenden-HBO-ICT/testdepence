
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
			//get the route to the inbuild target
			//map.get_route(t, t.target);
			//set and get a route 
			//this is still a bread search
			//crash at id 613
			//t.set_route(map.a_star(map.GetRealWorldTilePos(t.position, true), map.GetRealWorldTilePos(t.target, true)));
			StarAndPath uiy;
			t.set_route(uiy.aStar(map.GetRealWorldTilePos(t.position, true), map.GetRealWorldTilePos(t.target, true)));
			//t.set_route(map.get_route(t, t.target));
			//t.set_route(map.searchWander(t.position, t.target, t));
			//t.set_route(map.get_route(t, t.target));
			if (t.target != t.position) {
				tanksWithRoute.push_back(t);
			}

		}

	}
}