#include "pch.h"
#include "CollisionsN.h"
#include <HightCommand.h>


void testdependence::Collisions::addTankToGrid(Tank* tank)
{

    Colgrid.add(tank);
}

void testdependence::Collisions::removeTankFromGrid(Tank* tank)
{
    Colgrid.remove(tank);
}

void testdependence::Collisions::CheckForCollisions(Tank& tank)
{
    vec2& tankpos = tank.position;
    float& collisionrad = tank.collision_radius;
    // Query the grid for potential colliding tanks in that range
    //make this a method and multithread it
    std::vector<Tank*> potential_colliders = Colgrid.query(tankpos.x - collisionrad, tankpos.y - collisionrad, tankpos.x + collisionrad, tankpos.y + collisionrad);
    //don't think threading would be safe here
    collide(tank, potential_colliders);
}

void testdependence::Collisions::collide(Tank& tank, std::vector<Tank*> potential_colliders)
{

    // Loop through the potential colliders and check for actual collisions
    for (Tank* other_tank : potential_colliders)
    {
        if (&tank == other_tank || !other_tank->active) continue;   //1


        // Get the direction vector between the centers of the circles
        vec2 dir = tank.get_position() - other_tank->get_position();

        // Calculate the squared distance between the centers
        float dist_squared = dir.sqr_length();

        // Calculate the squared sum of the radii
        float rad_sum_squared = (tank.get_collision_radius() + other_tank->get_collision_radius());
        rad_sum_squared *= rad_sum_squared;

        // Check if the squared distance is less than or equal to the squared sum of the radii
        if (dist_squared <= rad_sum_squared)
        {
            // The circles are colliding
            tank.push(dir.normalized(), 1.f);
        }
    }


}
