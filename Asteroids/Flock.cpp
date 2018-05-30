#pragma once;

#include <iostream>

#include "Flock.h"

#include "vector_math.h"

Flock::Flock(RenderWindow* window)
{
	this->window = window;

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
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

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			vector<Boid*> boidList = vector<Boid*>();

			int x1 = (i - 1 >= 0) ? i-1 : 0;
			int x2 = (i + 1 < 12) ? i+1 : 11;
			int y1 = (j - 1 >= 0) ? j-1 : 0;
			int y2 = (j + 1 < 12) ? j+1 : 11;

			//if (i == 0 && j == 0)
			//{
			//	std::cout << x1 << "," << y1 << "," << x2 << "," << y2 << std::endl;
			//}

			for (int x = x1; x < x2; x++)
			{
				for (int y = y1; y < y2; y++)
				{
					boidList.insert(boidList.end(),
						boidBins[y][x]->begin(), boidBins[y][x]->end());
				}
			}

			//std::cout << boidList.size() << std::endl;

			for (int n = 0; n < boidBins[j][i]->size(); n++)
			{
				boidBins[j][i]->at(n)->flockWith(boidList);
				boidBins[j][i]->at(n)->update();
				
			}
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
	int i = boid.getX() / 50;
	int j = boid.getY() / 50;

	if (0 <= i && i < 12 && 0 <= j && j < 12)
	{
		// add to master list
		boidList[boidCount] = boid;
		Boid* boidptr = &boidList[boidCount];
		boidCount++;

		// add to bin
		boidBins[j][i]->push_back(boidptr);
	}
}