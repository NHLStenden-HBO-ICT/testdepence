#pragma once

#include "tank.h"
#include "CollisionsN.h"
#include "ContainerTypes.h"
#include <SweepAndPrune.h>

namespace testdependence {


    class TankCollection
    {


    public:
        int Total_Red_Tanks;
        int Total_Blue_Tanks;
        


        Tank* testTank;

        std::vector<Tank> bluetanks;
        std::vector<Tank> redTanks;
        //blue tanks 
        std::vector<CircleS> blueColsTest;

        //SweepAndPrune sweep;


        
        vec2 tank_size;
        Collisions collider;

        //init
        void Init(vec2 sz, int tank_radius, int tank_max_health, int tank_max_speed, Sprite& tank_blue, Sprite& tank_red, Sprite smoke);
        void CreateCustomTank(vec2 sz, int tank_radius, int tank_max_health, int tank_max_speed, Sprite& better, Sprite smoke, vec2 Spawn);
        //calculate the new route for the tanks

        void TankTicks();
        void ThreadTick(Tank& tank);
        void ThreadParitionTick(std::vector<Tank>& tanklist);
        void ThreadPrepper();
        void TankInsertions(std::vector<Tank> &_blueTanks, std::vector<Tank> &_redTanks);
        void InsertTankList();

        TankCollection();
        TankCollection(vec2 tank_size);

        void SetTargets(Tank& t);

        void SearchTargets(std::vector<Tank>& tankList, int start, int end);
        void ThreadTargetSeek(std::vector<Tank>& tankslist);


    private:

        //the new places to init init
        int max_rows = 24;

        float start_blue_x;
        float start_blue_y;

        float start_red_x;
        float start_red_y;


        float spacing;


    };

}