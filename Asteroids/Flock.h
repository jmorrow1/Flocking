#pragma once

#include "Boid.h";

using namespace std;

class Flock
{
private:
	// bins of boids
	int binSqrt = 100;
	int w = 12;
	int h = 8;
	vector<Boid*>* boidBins[8][12];

	// master list of boids
	int boidCapacity = 1000;
	Boid boidList[1000];
	int boidCount;

	// render window
	RenderWindow* window;

public:
	Flock(RenderWindow* window);
	~Flock();

	void update();
	void draw();

	Boid& getBoid(int i);
	int getBoidCount();
	void addBoid(Boid boid);
};

