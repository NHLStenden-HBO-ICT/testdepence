
#include "pch.h"
#include "TankCollection.h"
#include <HightCommand.h>


namespace testdependence {
    TankCollection::TankCollection() {

    }
    TankCollection::TankCollection(vec2 tank_size) {

        Total_Red_Tanks = 2048;
        Total_Blue_Tanks = 2048;
        max_rows = 24;

        start_blue_x = tank_size.x + 40.0f;
        start_blue_y = tank_size.y + 30.0f;

        start_red_x = 1088.0f;
        start_red_y = tank_size.y + 30.0f;


        spacing = 7.5f;

    }
    //a loop to get all ze targets 
    //the memory overhead might be insane
    void TankCollection::SetTargets(Tank& t)
    {
        //(t.allignment == RED)? 
        if (t.allignment == RED) {
            float closest_distance = 9000;
            int closest_index = 0;

            for (int i = 0; i < bluetanks.size(); i++)
            {
                if (bluetanks.at(i).allignment != t.allignment)
                {
                    float sqr_dist = fabsf((bluetanks.at(i).get_position() - t.get_position()).sqr_length());
                    if (sqr_dist < closest_distance)
                    {
                        closest_distance = sqr_dist;
                        closest_index = i;
                    }
                }
            }

            //return bluetanks.at(closest_index);

        }
        else {
            float closest_distance = 9000;
            int closest_index = 0;

            for (int i = 0; i < redTanks.size(); i++)
            {
                if (redTanks.at(i).allignment != t.allignment)
                {
                    float sqr_dist = fabsf((redTanks.at(i).get_position() - t.get_position()).sqr_length());
                    if (sqr_dist < closest_distance)
                    {
                        closest_distance = sqr_dist;
                        closest_index = i;
                    }
                }
                //return redTanks.at(closest_index);
            }
        }

    }

    //put in the list with the limits given by the start and end
    ///tanklist1 is for the element to search two is a comparison list
    void TankCollection::SearchTargets(std::vector<Tank>& tankList, int start, int end)
    {
        for (int i = start; i < end; i++) {
            {
                Tank& current_tank = tankList.at(i);
                if (current_tank.rocket_reloaded()) {
                    //check for targets
                    // spawn rocket
                   //current_tank.target = SetTargets(current_tank).position;

                }
            }
        }

    }

    void TankCollection::ThreadTargetSeek(std::vector<Tank>& tankslist)
    {

        const int num_workers = (HightCommand::ThreadLogistics.CountWorkers() / 2);
        // Get the number of elements in each partition
        const int num_elements = tankslist.size() / num_workers;
        // Get the number of remaining elements after dividing by num_workers
        const int num_remainder = tankslist.size() % num_workers;
        // Initialize an empty vector to store the futures returned by the pool
        std::vector<std::future<void>> futures;
        // Loop through each worker thread
        for (int i = 0; i < num_workers; i++) {
            // Calculate the start index of the partition for this thread
            int start = i * num_elements;
            // Calculate the end index of the partition for this thread
            int end = start + num_elements;
            // If this is the last thread, add the remaining elements to its partition
            if (i == num_workers - 1) {
                end += num_remainder;
            }
            // Enqueue a task to the pool that calls TankDistanceLoops with the red tanks, blue tanks, start index and end index
            futures.push_back(HightCommand::ThreadLogistics.enqueue([this, &tankslist, start, end] {
                SearchTargets(tankslist, start, end);
                }));
        }
        // Loop through each future in the vector
        for (auto& f : futures) {
            // Wait for the task to finish
            f.wait();
        }
    }


    void TankCollection::Init(vec2 sz, int tank_radius, int tank_max_health, int tank_max_speed, Sprite& tank_blue, Sprite& tank_red, Sprite smoke) {

        Total_Red_Tanks = 2048;
        Total_Blue_Tanks = 2048;
        max_rows = 24;

        start_blue_x = tank_size.x + 40.0f;
        start_blue_y = tank_size.y + 30.0f;

        start_red_x = 1088.0f;
        start_red_y = tank_size.y + 30.0f;


        spacing = 7.5f;

        for (int i = 0; i < Total_Blue_Tanks; i++)
        {
            vec2 position{ start_blue_x + ((i % max_rows) * spacing), start_blue_y + ((i / max_rows) * spacing) };
            Tank nTank(position.x, position.y, BLUE, &tank_blue, &smoke, 1100.f, position.y + 16, tank_radius, tank_max_health, tank_max_speed, vec2(sz.x, sz.y));
            nTank.id = i;

            //tanks.push_back(nTank);
            //bluetanks.push_back(new Tank(nTank));
            bluetanks.push_back(nTank);      
            blueColsTest.push_back(CircleS{std::ref(bluetanks.at(i).position.x), std::ref(bluetanks.at(i).position.y), 3.f });
           
            //nTank.setUpHull(tank_size);
        }
        //Spawn red tanks
        for (int i = 0; i < Total_Red_Tanks; i++)
        {
            vec2 position{ start_red_x + ((i % max_rows) * spacing), start_red_y + ((i / max_rows) * spacing) };
            Tank nTank(position.x, position.y, RED, &tank_red, &smoke, 100.f, position.y + 16, tank_radius, tank_max_health, tank_max_speed, vec2(sz.x, sz.y));
            nTank.id = i;
            //redTanks.push_back(new Tank(nTank));
            redTanks.push_back(nTank);
            //nTank.setUpHull(tank_size);
        }
        sweepAndPrune(blueColsTest);
        
    }

    void TankCollection::CreateCustomTank(vec2 sz, int tank_radius, int tank_max_health, int tank_max_speed, Sprite& better, Sprite smoke, vec2 Spawn)
    {

        Tank nTank(Spawn.x, Spawn.y, BLUE, &better, &smoke, 100.f, Spawn.y + 16, tank_radius, tank_max_health, tank_max_speed, vec2(sz.x, sz.y));
        nTank.id = 9000;
        //redTanks.push_back(new Tank(nTank));
        redTanks.push_back(nTank);
    }

    void TankCollection::TankTicks() {

        //call method to tick using multithreading
        ThreadPrepper();
        InsertTankList();
        //for (Tank& t : bluetanks) {
        //    //t.tick(); // Update the position of the tank first
        //    collider.removeTankFromGrid(&t); // Remove the tank from the old cell
        //    collider.addTankToGrid(&t); // Add the tank to the new cell
        //}
        for (Tank& t : bluetanks) {
            collider.CheckForCollisions(t); // Check for collisions with other tanks in the same or adjacent cells
        }
        //for (Tank& t : redTanks) {
        //    //t.tick(); // Update the position of the tank first
        //    collider.removeTankFromGrid(&t); // Remove the tank from the old cell
        //    collider.addTankToGrid(&t); // Add the tank to the new cell
        //}
        for (Tank& t : redTanks) {
            collider.CheckForCollisions(t); // Check for collisions with other tanks in the same or adjacent cells
        }

        //ThreadTargetSeek(redTanks);
        //ThreadTargetSeek(bluetanks);

    }


    //prepare the setup for the threads
    void TankCollection::ThreadPrepper() {


        for (Tank& t : bluetanks) {
            t.tick();
        }
        for (Tank& t : redTanks) {
            t.tick();
        }


        // Create a task list
        //std::vector<std::future<void>> futures;

        //for (Tank& t : bluetanks) {
        //    futures.push_back(std::async(std::launch::async, [this, &t] {
        //        ThreadTick(t);
        //        }));
        //}
        //for (Tank& t : redTanks) {
        //    futures.push_back(std::async(std::launch::async, [this, &t] {
        //        ThreadTick(t);
        //        }));
        //}

        //for (auto& f : futures) { // Wait for all tasks to finish
        //    f.wait();
        //}
        //create a task list
        std::vector<std::future<void>> future;

        //future.push_back(HightCommand::ThreadLogistics.enqueue([this]
        //    {
        //        ThreadParitionTick(redTanks);
        //    }));

        //future.push_back(HightCommand::ThreadLogistics.enqueue([this] 
        //    {
        //        ThreadParitionTick(redTanks);
        //    }));

        //future.push_back(HightCommand::ThreadLogistics.enqueue([this]
        //    {
        //        ThreadParitionTick(bluetanks);
        //    }));




        //for (Tank& t : bluetanks) {
        //    future.push_back(HightCommand::ThreadLogistics.enqueue([this, &t] {
        //        ThreadTick(t);
        //        }));
        //}
        //for (Tank& t : redTanks) {
        //    future.push_back(HightCommand::ThreadLogistics.enqueue([this, &t] {
        //        ThreadTick(t);
        //        }));
        //}

        //for (auto& f : future) { // Wait for all tasks to finish
        //    f.wait();
        //}
    }

    void TankCollection::TankInsertions(std::vector<Tank>& _blueTanks, std::vector<Tank>& _redTanks)
    {
        for (Tank& t : _redTanks) {
            //t.tick(); // Update the position of the tank first
            collider.removeTankFromGrid(&t); // Remove the tank from the old cell
            collider.addTankToGrid(&t); // Add the tank to the new cell
        }
        for (Tank& t : _blueTanks) {
            //t.tick(); // Update the position of the tank first
            collider.removeTankFromGrid(&t); // Remove the tank from the old cell
            collider.addTankToGrid(&t); // Add the tank to the new cell
        }

    }

    void TankCollection::InsertTankList()
    {
        std::vector<std::future<void>> future;

        future.push_back(HightCommand::ThreadLogistics.enqueue([this] {
            TankInsertions(bluetanks, redTanks);
            }));
        for (auto& f : future) { // Wait for all tasks to finish
            f.wait();
        }
    }


    void TankCollection::ThreadTick(Tank& tank)
    {
        tank.tick();
    }

    void TankCollection::ThreadParitionTick(std::vector<Tank>& tanklist)
    {

        for (Tank& t : tanklist) {
            t.tick();
        }

        int hp = redTanks.at(1).health;

    }


}