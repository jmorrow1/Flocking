#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class Boid
{
private:
	float alignRadius = 50;
	float separationRadius = 35;
	float cohereRadius = 25;

	Vector2f pos, vel, acc;
	float radius;
	float maxForce;
	float maxSpeed;
	
	void wrapToWindow(RenderWindow& window);

public:
	ConvexShape shape;
	Boid();
	Boid(float x, float y, float r);
	~Boid();

	void seek(const Vector2f& target);
	
	void flockWith(std::vector<Boid*>& boids);
	void separateFrom(std::vector<Boid*>& boids);
	void alignWith(std::vector<Boid*>& boids);
	void cohereWith(std::vector<Boid*>& boids);

	void update();
	void draw(RenderWindow& window);
	
	float getX();
	float getY();
};

