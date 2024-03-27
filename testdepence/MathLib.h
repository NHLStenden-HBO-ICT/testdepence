
#pragma once
#include <vector>
#include <TerrainTile.h>
namespace testdependence {





	//this static class handles math operations
	static class MathLib
	{


	public:

		static std::vector<vec2*> ConvertTovec2(std::vector<TerrainTile*> tiles);

		static float heuristic(TerrainTile* tile, TerrainTile* goal);


	};


}