#include <vector>
#include <TerrainTile.h>

#pragma once
class Anthhill
{


	//aantal mieren
	int nrAnt;

	//for each ant start in een andere stad


	//hoelang relevant op tile
	float decayRate;

	float maximaIteration;


	std::vector<vec2> findPathAnt(int ants, testdependence::TerrainTile& start, testdependence::TerrainTile& goal);

	


};

