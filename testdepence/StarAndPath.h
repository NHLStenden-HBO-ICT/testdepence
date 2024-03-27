
#pragma once
#include <TerrainM.h>
#include <unordered_set>
#include <TerrainTile.h>
namespace testdependence {



	//this will be fun
	class StarAndPath
	{


	public:

		std::vector<vec2*> aStar(TerrainTile* start, TerrainTile* goal);

		TerrainTile* buurtCheck(TerrainTile* current, TerrainTile* target, unordered_set<TerrainTile*> closed, std::vector<TerrainTile*> oldPath);


	private:


	};

}