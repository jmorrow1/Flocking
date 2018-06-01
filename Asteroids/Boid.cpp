#pragma once;

#include <iostream>

#include "Boid.h"
#include "vector_math.h"

const float PI = 3.14159265359f;
const float TWO_PI = PI * 2;
const float RAD_TO_DEG = 360.0f / TWO_PI;

const float desiredSeparation = 25.0f;

Boid::Boid()
{
	
}

Boid::Boid(float x, float y, float r, Color color)
{
	this->color = color;

	this->pos = Vector2f(x, y);

	float vx = -1 + (rand() % 3);
	float vy = -1 + (rand() % 3);

	this->vel = Vector2f(vx, vy);
	this->acc = Vector2f(0, 0);
	this->shape = ConvexShape();
	this->radius = r;

	this->maxForce = 0.05f;
	this->maxSpeed = 3.0f;

	shape.setPointCount(3);
	shape.setPoint(0, Vector2f(r, 0));
	shape.setPoint(1, Vector2f(r * cos(0.75f * PI), r * sin(0.75f * PI)));
	shape.setPoint(2, Vector2f(r * cos(1.25f * PI), r * sin(1.25f * PI)));
	shape.setFillColor(color);
	shape.setOutlineColor(Color::White);
	shape.setOutlineThickness(1.5f);

	blob.setRadius(2);
	blob.setFillColor(color);
	blob.setOrigin(Vector2f(0, 0));
}

Boid::~Boid()
{

}

void Boid::seek(const Vector2f& target, float weight)
{
	Vector2f desiredVelocity = target - pos;
	normalize(desiredVelocity);
	desiredVelocity *= maxSpeed;
	
	Vector2f steering = desiredVelocity - vel;
	limit(steering, maxForce);

	acc += steering * weight;
}

void Boid::wrapToWindow(RenderWindow& window)
{
	Transform transform = shape.getTransform();
	float windowWidth = window.getSize().x;
	float windowHeight = window.getSize().y;

	// wrap shape w/r/t walls
	bool pastLeftWall = pos.x - radius < 0;
	bool pastRightWall = pos.x + radius > windowWidth;
	bool pastTopWall = pos.y - radius < 0;
	bool pastBottomWall = pos.y + radius > windowHeight;

	// left and right walls
	if (pastLeftWall)
	{
		shape.setPosition(pos + Vector2f(windowWidth, 0));
		window.draw(shape);
	}
	else if (pastRightWall)
	{
		shape.setPosition(pos + Vector2f(-windowWidth, 0));
		window.draw(shape);
	}

	// top and bottom walls
	if (pastTopWall)
	{
		shape.setPosition(pos + Vector2f(0, windowHeight));
		window.draw(shape);
	}
	else if (pastBottomWall)
	{
		shape.setPosition(pos + Vector2f(0, -windowHeight));
		window.draw(shape);
	}
	
	// corner walls
	if (pastLeftWall && pastTopWall)
	{
		shape.setPosition(pos + Vector2f(windowWidth, windowHeight));
		window.draw(shape);
	}
	else if (pastRightWall && pastTopWall)
	{
		shape.setPosition(pos + Vector2f(-windowWidth, windowHeight));
		window.draw(shape);
	}
	else if (pastRightWall && pastBottomWall)
	{
		shape.setPosition(pos + Vector2f(-windowWidth, -windowHeight));
		window.draw(shape);
	}
	else if (pastLeftWall && pastBottomWall)
	{
		shape.setPosition(pos + Vector2f(windowWidth, -windowHeight));
		window.draw(shape);
	}

	// wrap position
	if (pos.x + radius < 0)
	{
		pos.x += windowWidth;
	}
	else if (pos.x - radius > windowWidth)
	{
		pos.x -= windowWidth;
	}
	if (pos.y + radius < 0)
	{
		pos.y += windowHeight;
	}
	else if (pos.y - radius > windowHeight)
	{
		pos.y -= windowHeight;
	}

}

void Boid::flockWith(std::vector<Boid*>& boids)
{
	separateFrom(boids);
	alignWith(boids);
	cohereWith(boids);
}

void Boid::separateFrom(std::vector<Boid*>& boids)
{
	float sqDesiredSeparation = separationRadius * separationRadius;

	Vector2f steering = Vector2f(0, 0);
	int neighborCount = 0;
	for (int i = 0; i < boids.size(); i++)
	{
		float sqDist = squareDistance(boids[i]->pos, pos);
		if (0 < sqDist && sqDist <= sqDesiredSeparation)
		{
			float dist = sqrt(sqDist);

			Vector2f fromBoid = pos - boids[i]->pos;
			normalize(fromBoid);
			fromBoid /= dist;
			steering += fromBoid;

			neighborCount++;
		}
	}

	if (steering.x != 0 || steering.y != 0)
	{
		normalize(steering);
		steering *= maxSpeed;
		steering -= vel;
		limit(steering, maxForce);

		acc += separationWeight * steering;
	}

	
}

void Boid::alignWith(std::vector<Boid*>& boids)
{
	float sqNeighborDist = alignRadius * alignRadius;
	Vector2f sum(0, 0);

	int neighborCount = 0;
	for (int i = 0; i < boids.size(); i++)
	{
		float sqDist = squareDistance(boids[i]->pos, pos);
		if (0 < sqDist && sqDist <= sqNeighborDist)
		{
			sum += boids[i]->vel;
			neighborCount++;
		}
	}

	if (sum.x != 0 || sum.y != 0)
	{
		normalize(sum);
		sum *= maxSpeed;
		Vector2f steering = sum - vel;
		limit(steering, maxForce);

		acc += alignmentWeight * steering;
	}
}

void Boid::cohereWith(std::vector<Boid*>& boids)
{
	float sqNeighborDist = cohereRadius * cohereRadius;

	Vector2f sum(0, 0);

	int neighborCount = 0;
	for (int i = 0; i < boids.size(); i++)
	{
		float sqDist = squareDistance(boids[i]->pos, pos);
		if (0 < sqDist && sqDist < sqNeighborDist)
		{
			sum += boids[i]->pos;
			neighborCount++;
		}
	}

	if (sum.x != 0 || sum.y != 0)
	{
		sum /= (float) neighborCount;
		seek(sum, coherenceWeight);
	}
}

void Boid::update()
{
	float head = heading(vel);
	shape.setRotation(head * RAD_TO_DEG);
	shape.setPosition(pos);

	vel += acc;
	pos += vel;
	acc *= 0.0f;
}

void Boid::draw(RenderWindow& window)
{
	window.draw(shape);
	wrapToWindow(window);	
}

void Boid::paint(RenderTexture* offscreenCanvas)
{
	blob.setPosition(pos);
	offscreenCanvas->draw(blob);
}

float Boid::getX()
{
	return pos.x;
}

float Boid::getY()
{
	return pos.y;
}