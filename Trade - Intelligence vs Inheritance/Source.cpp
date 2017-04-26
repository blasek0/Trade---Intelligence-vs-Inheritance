/*
Author: Jacob Smith
Class: ECN 499 - Agent Based Computational Economics

This program will run an agent based model where agents with simulated attributes 
trade with each other, in an imbalanced trade model.
*/

#include <Windows.h>
#include "Manager.h"
#include <fstream>
#include <iostream>

#pragma warning(disable:4996)

using namespace std;

int main()
{
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	double frequency = li.QuadPart;
	double initialClock, finalClock;
	QueryPerformanceCounter(&li);
	initialClock = li.QuadPart;
	Manager *managerObject = new Manager();
	managerObject->Run();
	QueryPerformanceCounter(&li);
	finalClock = li.QuadPart;
	double timeTaken = finalClock - initialClock;
	timeTaken = timeTaken / frequency;
	delete managerObject;
/*	fstream outfile;
	char temp[65];
	strcpy(temp, "");
	outfile.open("TimeTaken.txt", ios::app);
	itoa((int)timeTaken, temp, 10);
	outfile.write(temp, strlen(temp));
	outfile.write("\n", 1);
	outfile.close();
	cout << timeTaken << "\n";
//	system("pause");
*/	return 0;
}