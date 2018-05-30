#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include <iostream>

#include "Boid.h"
#include "Flock.h"

using namespace sf;

// time
const int FPS = 60;
const float SPF = 1.0f / FPS;
const int MSPF = (int) (SPF * 1000);

// rendering window
RenderWindow window(VideoMode(600, 600), "Flocking");

// function prototypes
void setup();
void update();
void draw();

void mousePressed();
void mouseMoved();

/********************
 **** Game Loop *****
 ********************/

int main()
{
	sf::Clock clock = sf::Clock();
	int frameCount = 0;

	// setup
	setup();

	// game loop
	while (window.isOpen())
	{
		clock.restart();

		// poll events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed: window.close(); break;
				case Event::MouseButtonPressed: mousePressed(); break;
				case Event::MouseMoved: mouseMoved(); break;
			}
		}

		// update
		update();
			
		// draw
		draw();

		//std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;

		// ensure frame rate will be no less than a fixed amount
		int frameTimeLeft = MSPF - clock.getElapsedTime().asMilliseconds();
		if (frameTimeLeft >= 0)
		{
			Sleep(frameTimeLeft);
		}

	}

	return 0;
}

Flock boidContainer = Flock(&window);
float boidRadius = 8;

/*************************
 **** Initialization *****
 *************************/

void setup()
{
	boidContainer.addBoid(Boid(100, 100, boidRadius));
}

/*****************
 **** Update *****
 *****************/

void update()
{
	boidContainer.update();
}

/***************
 **** Draw *****
 ***************/

void draw()
{
	window.clear();	
	boidContainer.draw();
	window.display();
}

/*****************
 **** Events *****
 *****************/

void mousePressed()
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		Vector2i mousePosition = Mouse::getPosition(window);
		boidContainer.addBoid(Boid(mousePosition.x, mousePosition.y, boidRadius));
	}
}

void mouseMoved()
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		Vector2i mousePosition = Mouse::getPosition(window);
		boidContainer.addBoid(Boid(mousePosition.x, mousePosition.y, boidRadius));
	}
}