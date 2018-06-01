#pragma once

#include "Boid.h";

using namespace std;

class Flock
{
private:
	// bins of boids
	int binSqrt = 75;
	int w = 16;
	int h = 9;
	vector<Boid*>* boidBins[9][16];

	// master list of boids
	int boidCapacity = 1000;
	Boid boidList[1000];
	int boidCount;

	// rendering
	RenderWindow* window;
	RenderTexture* offscreenCanvas;

public:
	bool separate = true;
	bool align = true;
	bool cohere = true;

	Flock(RenderWindow* window, RenderTexture* offscreenCanvas);
	~Flock();

	void update();
	void draw();

	Boid& getBoid(int i);
	int getBoidCount();
	void addBoid(Boid boid);
	void removeBoidFromEnd();
};

