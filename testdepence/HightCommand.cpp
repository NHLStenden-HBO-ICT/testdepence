#include "pch.h"
#include "HightCommand.h"




namespace testdependence {

    ThreadPool HightCommand::ThreadLogistics(std::thread::hardware_concurrency());


    void testdependence::HightCommand::Setup()
    {
        //ThreadLogistics = ThreadPool(std::thread::hardware_concurrency());
    }
    //get closest target
    vec2 HightCommand::getTarget(Tank& me, std::vector<Tank*> enemyTeam)
    {
        float closest_distance = 9000;
        int closest_index = 0;

        for (int i = 0; i < enemyTeam.size(); i++)
        {

            float sqr_dist = (enemyTeam.at(i)->get_position() - me.get_position()).sqr_length();
            if (sqr_dist < closest_distance)
            {
                closest_distance = sqr_dist;
                closest_index = i;
            }


        }

        return enemyTeam.at(closest_index)->get_position();
    }

}