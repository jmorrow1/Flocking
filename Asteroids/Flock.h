#pragma once

#include "Boid.h";

using namespace std;

class Flock
{
private:
	// bins of boids
	int binSqrt = 50;
	int w = 24;
	int h = 16;
	vector<Boid*>* boidBins[16][24];

	// master list of boids
	int boidCapacity = 1000;
	Boid boidList[1000];
	int boidCount;

	// rendering
	RenderWindow* window;
	RenderTexture* offscreenCanvas;

public:
	Flock(RenderWindow* window, RenderTexture* offscreenCanvas);
	~Flock();

	void update();
	void draw();

	Boid& getBoid(int i);
	int getBoidCount();
	void addBoid(Boid boid);
};

