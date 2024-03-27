
#pragma once
#include "CollisionGridN.h"

namespace testdependence {
	class Collisions
	{
	public:
		CollisionGrid Colgrid = CollisionGrid(50);

		//add a new tank to the grid
		void addTankToGrid(Tank* tank);
		//remove a tank from the grid
		void removeTankFromGrid(Tank* tank);
		//prepare to calculate collisions
		void CheckForCollisions(Tank& tank);

	private:

		void collide(Tank& tank, std::vector<Tank*> potential_colliders);


	};
}
