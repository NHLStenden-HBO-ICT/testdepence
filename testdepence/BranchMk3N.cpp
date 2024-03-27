#include "pch.h"
#include "BranchMk3N.h"
#include "DirectXmath.h"

void testdependence::BranchMk3::BranchInsertion(BranchMk3& branch, Tank& tank)
{

	//check if it fits inside
	if (CollisionCheckMk2(branch, tank)) {

		//check if flagged
		if (branch.flag) {
			//go down
			for (BranchMk3* branc : branch.branches) {

				//kids list
				//lets try a normal loop out first
				//check if tank fits in kids and return true if true
				branc->BranchInsertion(*branc, tank);
			}
		}
		else
		{
			//geen flag node kan gevuld worden
			//plenty of parking room
			InsertInBranch(branch, tank);
			//now check for size
			if (this->itemCap > TanksInBranch) {

				MakeBranch(branch, branch.level);
				//subdivede
				//move all down and hash leftovers
				passOn(branch);
			}
		}
	}
	//get the current branch and check if there arn't any child nodes
	//if there are pass this tank down to one of them
	//if not just add the tank to this node 
	//if adding the tank to the node exceeds the tank cap, split the branch and pass down the list
	//check if we can fit the node

}


//not really perfect but it can be pretty good 
//just return a bool so that we can remove the list
bool testdependence::BranchMk3::BranchInsertionM2(BranchMk3& branch, Tank& tank)
{

	if (CollisionCheckMk2(branch, tank)) {

		//check if flagged
		if (branch.flag) {
			//go down
			for (BranchMk3* branc : branch.branches) {

				//kids list
				//lets try a normal loop out first
				//check if tank fits in kids and return true if true
				branc->BranchInsertion(*branc, tank);
			}
		}
		else
		{
			//geen flag node kan gevuld worden
			//plenty of parking room
			InsertInBranch(branch, tank);
			//now check for size
			if (this->itemCap > TanksInBranch) {


				//subdivede
			}
			else
			{
				//we won
				return true;
			}
		}
	}
	//we failed hard
	return false;
}



//node should split when it gets more then 2 elements

bool testdependence::BranchMk3::CollisionCheckMk2(BranchMk3& branch, Tank& tank)
{
	//BoundingBox box(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 0.0f));
	// Create a 2D bounding box with center (0, 0, 0) and extents (1, 1, 0)

	//switch (branch.bound.Contains(tank.hitBox))
	//{
	//case CONTAINS:	//ziter in
	//	return true;
	//case INTERSECTS:	//zit er niet helemaal in
	//	//make a external container to store the item in 
	//	//one extra call can't kill us
	//	break;
	//case DISJOINT:
	//	break;
	//default:s
	//	break;
	//}

	return false;
}
//raise the flag
void testdependence::BranchMk3::raiseFlag(BranchMk3& branch)
{
	//true is not false
	branch.flag = true;
	//add this to hashmap for toggle
}

//if this method is called it means we need to flush down bad and fast!!!
void testdependence::BranchMk3::passOn(BranchMk3& branch)
{
	//wait we need to delete that freaking list tooo
	//branches already have been made
	//i know its a waste of memory, but sadly everone seems to make mistakes
	std::vector<Tank*> leftovers;
	//declare first to put in chache and then to avoid crash by bad code practice
	int iterateor = branch.tanks.size();
	//reverse and cash iterator to keep a semi safe loop
	for (int i = iterateor; i < 0; i--) {

		for (BranchMk3* mikkay : branch.branches) {

			//check if they fit
			if (BranchInsertionM2(*mikkay, *branch.tanks.at(i))) {
				//remove the item
				branch.tanks.pop_back();

			}

		}

	}
	//left overs get free hashmap
}

//put it inside
void testdependence::BranchMk3::InsertInBranch(BranchMk3& branch, Tank& tank)
{
	//all checks have been made we did it boys

	branch.tanks.push_back(&tank);
}





void testdependence::BranchMk3::MakeBranch(BranchMk3& dads, int lvl) {
	//raise the flag boys
	//time to pass all down
	dads.raiseFlag(dads);

	XMFLOAT3 halfsize = dads.bound.Extents;
	XMFLOAT3 supersize = dads.bound.Center;
	XMVECTOR va = XMLoadFloat3(&halfsize); // load a into an XMVECTOR
	XMVECTOR vb = XMLoadFloat3(&supersize); // load b into an XMVECTOR

	XMVECTOR min = vb - va;
	XMVECTOR max = vb + va;
	XMFLOAT3 mini; // declare a XMFLOAT3 to store the result
	XMFLOAT3 maxi; // declare another XMFLOAT3 to store the result
	XMStoreFloat3(&mini, min); // store the result into mini
	XMStoreFloat3(&maxi, max); // store the result into maxi
	//let maar op
	//gerbuik v2cc 


	// Get the center point of the current bounding box
	XMVECTOR vcenter = (min + max) * 0.5f; // add the two XMVECTORs and multiply by 0.5f
	XMFLOAT3 center; // declare a XMFLOAT3 to store the result
	XMStoreFloat3(&center, vcenter); // store the result into center
	std::vector<BoundingBox> smallerBoxes = {

		BoundingBox(plus(center, mini, 0.5f), minus(center, mini, 0.5f)),
		BoundingBox(plus(XMFLOAT3(center.x, mini.y, maxi.z),XMFLOAT3(maxi.x, center.y, mini.z), 0.5f),minus(XMFLOAT3(maxi.x, center.y, mini.z), XMFLOAT3(center.x, mini.y, maxi.z), 0.5f)),
		BoundingBox(plus(XMFLOAT3(mini.x, center.y, maxi.z),XMFLOAT3(center.x, maxi.y, mini.z), 0.5f),minus(XMFLOAT3(center.x, maxi.y, mini.z), XMFLOAT3(mini.x, center.y, maxi.z), 0.5f)),
		BoundingBox(plus(center, maxi, 0.5f),(minus(maxi, center, 0.5f)))
	};

	//for every kid
	for (int i = 0; i < 4; ++i) {
		dads.branches.push_back(new BranchMk3(lvl, dads, smallerBoxes.at(i)));
	};


}
//minus
DirectX::XMFLOAT3 testdependence::BranchMk3::minus(XMFLOAT3 a, XMFLOAT3 b)
{

	XMVECTOR va = XMLoadFloat3(&a); // load a into an XMVECTOR
	XMVECTOR vb = XMLoadFloat3(&b); // load b into an XMVECTOR
	XMVECTOR min = vb - va;
	XMFLOAT3 mini;
	XMStoreFloat3(&mini, min); // store the result into c
	return mini;
}
//plus
DirectX::XMFLOAT3 testdependence::BranchMk3::plus(XMFLOAT3 a, XMFLOAT3 b)
{

	XMVECTOR va = XMLoadFloat3(&a); // load a into an XMVECTOR
	XMVECTOR vb = XMLoadFloat3(&b); // load b into an XMVECTOR
	XMVECTOR max = vb - va;
	XMFLOAT3 maxi;
	XMStoreFloat3(&maxi, max); // store the result into c
	return maxi;
}

DirectX::XMFLOAT3 testdependence::BranchMk3::plus(XMFLOAT3 a, XMFLOAT3 b, float f)
{

	XMVECTOR va = XMLoadFloat3(&a); // load a into an XMVECTOR
	XMVECTOR vb = XMLoadFloat3(&b); // load b into an XMVECTOR
	XMVECTOR max = (vb - va) * f;
	XMFLOAT3 maxi;
	XMStoreFloat3(&maxi, max); // store the result into c
	return maxi;
}

DirectX::XMFLOAT3 testdependence::BranchMk3::minus(XMFLOAT3 a, XMFLOAT3 b, float f)
{

	XMVECTOR va = XMLoadFloat3(&a); // load a into an XMVECTOR
	XMVECTOR vb = XMLoadFloat3(&b); // load b into an XMVECTOR
	XMVECTOR max = (vb + va) * f;
	XMFLOAT3 maxi;
	XMStoreFloat3(&maxi, max); // store the result into c
	return maxi;
}

DirectX::XMFLOAT3 testdependence::BranchMk3::keer(XMFLOAT3 a, float b)
{
	XMVECTOR va = XMLoadFloat3(&a); // load a into an XMVECTOR
	XMVECTOR max = va * b;
	XMFLOAT3 maxi;
	XMStoreFloat3(&maxi, max); // store the result into c
	return maxi;
}
