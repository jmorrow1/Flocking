#pragma once;

#include <iostream>

#include "Flock.h"

#include "vector_math.h"

Flock::Flock(RenderWindow* window)
{
	this->window = window;
}

Flock::~Flock()
{
}

void Flock::update()
{
	for (int i = 0; i < boidList.size(); i++)
	{
		boidList[i].flockWith(boidList);
		boidList[i].update();
	}
	//std::cout << boidList.size() << std::endl;
}

void Flock::draw()
{
	for (int i = 0; i < boidList.size(); i++)
	{
		boidList[i].draw(*window);
	}
}

Boid& Flock::getBoid(int i)
{
	return boidList[i];
}

int Flock::getBoidCount()
{
	return boidList.size();
}

void Flock::addBoid(Boid boid)
{
	boidList.push_back(boid);
}