#pragma once
#include <ContainerTypes.h>
#include <tank.h>
#include <ThreadPoolN.h>
#include <BranchMk3N.h>


namespace testdependence {
	//high command will oversee and manage the logistics needed to run the forces
	static class HightCommand
	{
	public:


		static void Setup();

		//check if the thread pool has been made

		//method for reading workers 

		//method to assign tasks to the pool

		//assign task
		//static void RunCommand(std::future);
		static ThreadPool getThread();
		static ThreadPool ThreadLogistics;

		//method to get a target
		static vec2 getTarget(Tank& me, std::vector<Tank*> enemyTeam);

		static std::vector<BranchMk3*> toreset;





	private:


		//static ThreadPool ThreadLogistics;


	};
}