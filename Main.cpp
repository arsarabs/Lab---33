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
#include <string>
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
void simulateCycle(deque<Car> lanes[], int cycle);
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
void simulateCycle(deque<Car> lanes[], int cycle) {
	
	//ROUGH LAYOUT OF THE COMPLICATED FUNCTION
	
	//array of strings to store operation performed in each lane
	string operations[NUMBER_LANES] = { "", "", "" };

	//We need to iterate over each lane to perform operations
	for (int i = 0; i < NUMBER_LANES; ++i) {

		int randNum = randomNumber();

		//46%
		if (randNum <= PAY_PROB) {
			Car car = lanes[i].front(); //retrieve car from front of the lane
			lanes[i].pop_front();
			//RECORD OPERATION HERE
			operations[i] = "Paid: [" + to_string(car.getYear()) + " " + car.getMake()
				+ " (" + to_string(car.getTransponder()) + ")]";
		}
		//39%
		else if (randNum <= PAY_PROB + JOIN_PROB) {
			Car newCar;
			lanes[i].push_back(newCar); //add new car to rear of current lane
			//RECORD OPERATION HERE
			operations[i] = "Joined Lane: [" + to_string(newCar.getYear()) + " " + newCar.getMake()
				+ " (" + to_string(newCar.getTransponder()) + ")]";
		}
		//15%
		else { 
			if (NUMBER_LANES > 1) {
				Car rearCar = lanes[i].back();
				lanes[i].pop_back(); //remove car from rear of lane as its switching
				int target = selectRandomLane(i);
				lanes[target].push_back(rearCar); //add car to rear of selected car lane
				operations[i] = "Switched: [" + to_string(rearCar.getYear()) + " "
					+ rearCar.getMake() + " (" + to_string(rearCar.getTransponder())
					+ ")] to Lane " + to_string(target + 1);
			}
			else {
				operations[i] = "No operation";
			}
		}


		//display operations peformed in each lane
		for (int i = 0; i < NUMBER_LANES; ++i) {
			cout << "Lane " << (i + 1) << ": ";
			if (operations[i].empty()) {
				// If no operation was recorded, indicate 'No Operation'
				cout << "No Operation" << endl;
			}
			else {
				cout << operations[i] << endl;
			}
		}

		//display current state
		cout << "Queue:" << endl;
		for (int i = 0; i < NUMBER_LANES; ++i) {
			displayLaneQueue(i + 1, lanes[i]);
		}
	}

















}
void runSimulation() {
	//starting from scratch (rough layout)
	int cycle = 0;

	//1. array of deques
	deque<Car> lanes[NUMBER_LANES];

	//2. populate each lane using initalizeLanes
	intializeLanes(lanes, QUEUE_SIZE);

	//3. display initial state using disaplyLanes
	cout << "Initial  Queue: " << endl;
	displayLanes(lanes); 

	//4. create some sort of while loop that will continue the simulation until defined time is reached
	while (cycle < SIMULATION_PERIOD) {
		cycle++; //increment to represent next time period
		cout << "TIME: " << cycle << endl;
		simulateCycle(lanes, cycle); //simulate for all lanes during cycle
	}
	//5. final display here
	cout << "Simulation complete after " << SIMULATION_PERIOD << " time periods." << endl;
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