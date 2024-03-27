#pragma once
#include <vector>
#include <tank.h>

namespace testdependence {

    //check dit
    //https://stackoverflow.com/questions/41946007/efficient-and-well-explained-implementation-of-a-quadtree-for-2d-collision-det
    class CollisionGrid
    {

    private:
        // The size of each cell in the grid
        float cell_size;

        // The number of rows and columns in the grid
        int rows;
        int cols;

        // The vector of vectors to store objects in each cell
        std::vector<std::vector<Tank*>> cells;

    public:
        // Constructor
        CollisionGrid(float cell_size) {
            this->cell_size = cell_size;
            this->rows = ceil(4000 / cell_size);
            this->cols = ceil(4000 / cell_size);
            cells.resize(rows * cols);
        }

        // Destructor
        ~CollisionGrid() {
            cells.clear();
        }

        // Add an object to the grid
        void add(Tank* tank) {
            // Get the row and column index of the object's position
            int row = floor(tank->get_position().y / cell_size);
            int col = floor(tank->get_position().x / cell_size);
            // Clamp the row and column index to be within bounds
            row = max(0, min(row, rows - 1));
            col = max(0, min(col, cols - 1));

            // Add the object to the corresponding cell
            cells[row * cols + col].push_back(tank);
        }

        void remove(Tank* tank) {
            // Get the row and column index of the object's position
            int row = floor(tank->get_position().y / cell_size);
            int col = floor(tank->get_position().x / cell_size);

            // Clamp the row and column index to be within bounds
            row = max(0, min(row, rows - 1));
            col = max(0, min(col, cols - 1));

            // Find and erase the object from the corresponding cell
            auto& cell = cells[row * cols + col];
            auto it = find(cell.begin(), cell.end(), tank);
            if (it != cell.end()) {
                cell.erase(it);
            }
        }

        // Query objects in a given range
        std::vector<Tank*> query(float x1, float y1, float x2, float y2) {
            // Create an empty vector to store the result
            std::vector<Tank*> result;

            // Get the row and column index of the range corners
            int row1 = floor(y1 / cell_size);
            int col1 = floor(x1 / cell_size);
            int row2 = floor(y2 / cell_size);
            int col2 = floor(x2 / cell_size);
            // Clamp the row and column index to be within bounds
            row1 = max(0, min(row1, rows - 1));
            col1 = max(0, min(col1, cols - 1));
            row2 = max(0, min(row2, rows - 1));
            col2 = max(0, min(col2, cols - 1));

            // Loop through all cells in the range and add their objects to the result
            for (int i = row1; i <= row2; i++) {
                for (int j = col1; j <= col2; j++) {
                    auto& cell = cells[i * cols + j];
                    result.insert(result.end(), cell.begin(), cell.end());
                }
            }

            // Return the result vector
            return result;
        }
    };
};
