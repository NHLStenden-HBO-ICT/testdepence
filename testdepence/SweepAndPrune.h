#pragma once

#include <vector>
#include <ostream>
#include <iostream>
namespace testdependence {
    // A struct to represent a circle
    struct CircleS {
        float x; // x-coordinate of the center
        float y; // y-coordinate of the center
        float r; // radius
    };

    // A struct to represent an endpoint of a circle along an axis
    struct Endpoint {
        double value; // the coordinate value of the endpoint
        int index; // the index of the circle in the vector
        bool isMin; // true if the endpoint is the minimum, false if the endpoint is the maximum
    };


        // A function to compare two endpoints by their value
        static bool compareEndpoints(const Endpoint& a, const Endpoint& b) {
            return a.value < b.value;
        }

        // A function to check if two circles collide
        static bool checkCollisionSweep(const CircleS& a, const CircleS& b) {
            // Calculate the distance between the centers
            double dx = a.x - b.x;
            double dy = a.y - b.y;
            double dist = sqrt(dx * dx + dy * dy);
            // Compare the distance with the sum of the radii
            return dist <= a.r + b.r;
        }




        // A function to perform sweep and prune on a vector of circles
        static void sweepAndPrune(std::vector<CircleS>& circles) {
            // Create a vector of endpoints
            std::vector<Endpoint> endpoints;
            // For each circle, create two endpoints (min and max) along the x-axis
            for (int i = 0; i < circles.size(); ++i) {
                endpoints.push_back({ circles[i].x - circles[i].r, i, true }); // min endpoint
                endpoints.push_back({ circles[i].x + circles[i].r, i, false }); // max endpoint
            }
            // Sort the endpoints by their value
            std::sort(endpoints.begin(), endpoints.end(), compareEndpoints);
            // Create a vector of active circles
            std::vector<int> active;
            // Sweep a line along the x-axis and update the active circles
            for (const Endpoint& e : endpoints) {
                // If the endpoint is a minimum, add the circle to the active list
                if (e.isMin) {
                    active.push_back(e.index);
                }
                // If the endpoint is a maximum, remove the circle from the active list
                else {
                    active.erase(std::find(active.begin(), active.end(), e.index));
                }
                // For each pair of active circles, check if they collide
                for (int i = 0; i < active.size(); ++i) {
                    for (int j = i + 1; j < active.size(); ++j) {
                        if (checkCollisionSweep(circles[active[i]], circles[active[j]])) {
                            std::cout << "Circle " << active[i] << " and circle " << active[j] << " collide." << std::endl;
                        }
                    }
                }
            }
        }


}