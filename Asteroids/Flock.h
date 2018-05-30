#pragma once

#include "Boid.h";

using namespace std;

class Flock
{
private:
	// bins of boids
	vector<Boid*>* boidBins[12][12];

	// master list of boids
	Boid boidList[500];
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

