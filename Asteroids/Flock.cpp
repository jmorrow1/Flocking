#pragma once;

#include <iostream>

#include "Flock.h"

#include "vector_math.h"

Flock::Flock(RenderWindow* window)
{
	this->window = window;

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			boidBins[j][i] = new vector<Boid*>();
		}
	}
}

Flock::~Flock()
{
	
}

void Flock::update()
{
	//for (int i = 0; i < boidCount; i++)
	//{
	//	boidList[i].update();		
	//}

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			vector<Boid*> boidList = vector<Boid*>();

			int x1 = (i - 1 >= 0) ? i-1 : 0;
			int x2 = (i + 1 < w) ? i+1 : w-1;
			int y1 = (j - 1 >= 0) ? j-1 : 0;
			int y2 = (j + 1 < h) ? j+1 : h-1;

			for (int x = x1; x < x2; x++)
			{
				for (int y = y1; y < y2; y++)
				{
					boidList.insert(boidList.end(),
						boidBins[y][x]->begin(), boidBins[y][x]->end());
				}
			}

			for (int n = 0; n < boidBins[j][i]->size(); n++)
			{
				boidBins[j][i]->at(n)->flockWith(boidList);
				boidBins[j][i]->at(n)->update();
			}

			
		}
	}

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			boidBins[j][i]->clear();
		}
	}

	for (int n= 0; n < boidCount; n++)
	{
		int i = boidList[n].getX() / binSqrt;
		int j = boidList[n].getY() / binSqrt;

		if (i < 0) i = 0;
		else if (i >= w) i = w - 1;
		if (j < 0) j = 0;
		else if (j >= h) j = h - 1;

		if (boidCount < boidCapacity)
		{
			boidBins[j][i]->push_back(&boidList[n]);
		}
	}


	//std::cout << boidList.size() << std::endl;
}

void Flock::draw()
{
	for (int i = 0; i < boidCount; i++)
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
	return boidCount;
}

void Flock::addBoid(Boid boid)
{
	int i = boid.getX() / binSqrt;
	int j = boid.getY() / binSqrt;

	if (boidCount < boidCapacity && 
		0 <= i && i < w && 0 <= j && j < h)
	{
		// add to master list
		boidList[boidCount] = boid;
		Boid* boidptr = &boidList[boidCount];
		boidCount++;

		// add to bin
		boidBins[j][i]->push_back(boidptr);
	}
}