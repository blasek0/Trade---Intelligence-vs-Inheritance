/*
Author: Jacob Smith
Class: ECN 499 - Agent Based Computational Economics

This program will run an agent based model where agents with simulated attributes 
trade with each other, in an imbalanced trade model.
*/

#include <Windows.h>
#include "Manager.h"

using namespace std;

int main()
{
	Manager *managerObject = new Manager();
	managerObject->Run();
	delete managerObject;
	return 0;
}