
#pragma once
#include "TerrainM.h"
//this class is a inbetween for the terrain and tank collection to avoid compile conflicts

namespace testdependence
{


	class PathFinder
	{


	public:

		//PathFinder() = default;
		//constructer
		PathFinder(testdependence::TerrainM& worldMap);
		//the world map filled with tiles
		TerrainM& map;
		//get the new path for the given tanks
		void getPath(std::vector<Tank>& tanks);
		void getPath(std::vector<Tank*> tanks);

	};

}