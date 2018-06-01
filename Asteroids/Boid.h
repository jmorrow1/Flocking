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
	float alignRadius = 40;
	float separationRadius = 30;
	float cohereRadius = 25;

	float alignmentWeight = 1.0f;
	float separationWeight = 1.05f;
	float coherenceWeight = 1.0f;

	Color color;

	Vector2f pos, vel, acc;
	float radius;
	float maxForce;
	float maxSpeed;
	CircleShape blob;

	ConvexShape shape;

	void wrapToWindow(RenderWindow& window);

public:
	Boid();
	Boid(float x, float y, float r, Color color);
	~Boid();

	void seek(const Vector2f& target, float weight);
	
	void flockWith(std::vector<Boid*>& boids);
	void separateFrom(std::vector<Boid*>& boids);
	void alignWith(std::vector<Boid*>& boids);
	void cohereWith(std::vector<Boid*>& boids);

	void update();
	void draw(RenderWindow& window);
	void paint(RenderTexture* offscreenCanvas);
	
	float getX();
	float getY();
};

