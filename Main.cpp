//Anthony Sarabia - Lab 33

//NEW REQUIREMENTS
//1. Add More Lanes : There are now 4 toll booth lanes at play. Use an array to hold the lanes. The array will be of type deque<Car>. 
// When the simulation starts, pre-populate the lanes with 1-3 cars like before.Each time period will now have operations happening on all lines.
//2. Add Switching Lanes : Any car at the end of any queue can switch lanes to a random lane that's not their original lane.
//3. Probabilities : 46% probability that the car at the head of the queue pays its toll and leaves the queue
//39 % probability that another car joins the queue
//15 % probability that the rear car will shift lanes
//4. Termination Criteria: Run the simulation for 20 time periods.

#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include "Car.h"
using namespace std;

//UPDATED CONSTANTS
const int QUEUE_SIZE = 2;
const int PAY_PROB = 55;
const int JOIN_PROB = 45;
const int NUMBER_LANES = 4;
const int SIMULATION_PERIOD = 20;

//FUNCTION PROTOTYPES
int randomNumber();
void seedRandom();
void intializeLanes(deque<Car> lanes[], int initalSize); //initalizes all lanes w specifced # of randomly generated cars
void simulateCycle(deque<Car>& tollQueue, int cycle);
void runSimulation();
void displayLanes(deque<Car> lanes[]);
void displayLaneQueue(int laneNumber, deque<Car>& laneDeque);
//need a function for both lane switching and selecting a random lane
int selectRandomLane(int currentLane); // return random int index of selected lane
void laneSwtiching(deque<Car> lanes[], int currentLane); // Handles lane switching for the rear car 
// based on updated probabilities

int main() {
	//Seed
	seedRandom();

	//& run simulation (all i need for main)
	runSimulation();

	return 0;
}

int randomNumber() {
	return rand() % 100 + 1; // random num between 1-100
}
void seedRandom() {
	srand(static_cast<unsigned int>(time(0)));
}
void intializeLanes(deque<Car> lanes[], int initalSize) {
	//Use a nested loop to intialize lanes
	for (int i = 0; i < NUMBER_LANES; ++i) {
		for (int j = 0; j < initalSize; ++j) {
			Car car;
			lanes[i].push_back(car);
		}
	}	
}
void simulateCycle(deque<Car>& tollQueue, int cycle) {
	//starting from scratch
}
void runSimulation() {
	//starting from scratch (rough layout)
	int i = 0;

	//1. array of deques

	//2. populate each lane using initalizeLanes

	//3. display initial state

	//4. create some sort of while loop that will continue the simulation until defined time is reached

	//5. final display here
}
void displayLanes(deque<Car>lanes[]) {
	for (int i = 0; i < NUMBER_LANES; ++i) {
		cout << "Lane " << (i + 1) << ":" << endl;
		//if/else to check if empty or not
		if (lanes[i].empty()) {
			cout << " EMPTY!" << endl;
		}
		else {
			for (auto& car : lanes[i]) {
				cout << " " << endl;
				car.print();
			}
		}
	}
}
int selectRandomLane(int currentLane) {
	int target = currentLane;
	while (target == currentLane) {
		target = rand() % NUMBER_LANES;
	}
	return target;
}
void laneSwtiching(deque<Car> lanes[], int currentLane) {
	//I think I'll leave this empty since the function is going to be handled directly in simulateCycle function
}
void displayLaneQueue(int laneNumber, deque<Car>& laneDeque) {
	cout << "Lane " << laneNumber << "Queue: " << endl;
	if (laneDeque.empty()) {
		cout << "EMPTY" << endl;
		return;
	}
	for (auto& car : laneDeque) {
		cout << " " << endl;
		car.print();
	}
}