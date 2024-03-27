
#pragma once
#include <vector>
#include <tank.h>
#include <DirectXCollision.h>

namespace testdependence {

    using namespace DirectX;

    class BranchMk3
    {
    public:

        // Create a 2D bounding box with center (0, 0, 0) and extents (1, 1, 0)
        //BoundingBox box(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 0.0f));
        int level = 0;
        std::vector<BranchMk3*> branches;
        std::vector<Tank*> tanks;
        BoundingBox bound;
        static int TankCap;
        static int MaxDepth;
        int TanksInBranch = 0;
        short itemCap = 2;
        bool flag = false;

        BranchMk3() = default;

        BranchMk3(int lvl, const BoundingBox& boundingBox)
        {
            this->level = lvl++;
            this->bound = boundingBox;
        }

        BranchMk3(int lvl, BranchMk3& parent, const BoundingBox& boundingBox)
        {
            this->level = lvl + 1;
            this->bound = boundingBox;
            this->TanksInBranch = tanks.size();
        }

        void BranchInsertion(BranchMk3& branch, Tank& tank);

        bool BranchInsertionM2(BranchMk3& branch, Tank& tank);

    private:
        bool CollisionCheckMk2(BranchMk3& branch, Tank& tank);

        void raiseFlag(BranchMk3& branch);
        void passOn(BranchMk3& branch);
        void InsertInBranch(BranchMk3& branch, Tank& tank);

        void MakeBranch(BranchMk3& dads, int lvl);

        void ClearErrors(BranchMk3& branch);

        XMFLOAT3 minus(XMFLOAT3 a, XMFLOAT3 b);
        XMFLOAT3 plus(XMFLOAT3 a, XMFLOAT3 b);
        XMFLOAT3 plus(XMFLOAT3 a, XMFLOAT3 b, float f);
        XMFLOAT3 minus(XMFLOAT3 a, XMFLOAT3 b, float f);
        XMFLOAT3 keer(XMFLOAT3 a, float b);
    };


};

