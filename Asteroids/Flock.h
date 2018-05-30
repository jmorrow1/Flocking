#pragma once

#include "Boid.h";

using namespace std;

class Flock
{
private:
	// master list of boids
	vector<Boid> boidList;

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

