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
RenderWindow window(VideoMode(1200, 800), "Flocking");

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

		std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;

		// ensure frame rate will be no less than a fixed amount
		int frameTimeLeft = MSPF - clock.getElapsedTime().asMilliseconds();
		if (frameTimeLeft >= 0)
		{
			Sleep(frameTimeLeft);
		}

	}

	return 0;
}

RenderTexture offscreenCanvas;
Sprite sprite;
Flock boidContainer = Flock(&window, &offscreenCanvas);
float boidRadius = 6;

/*************************
 **** Initialization *****
 *************************/

void setup()
{
	offscreenCanvas.create(window.getSize().x, window.getSize().y);
	sprite.setTexture(offscreenCanvas.getTexture());
}

/*****************
 **** Update *****
 *****************/

void update()
{
	std::cout << boidContainer.getBoidCount() << ", ";
	boidContainer.update();
}

/***************
 **** Draw *****
 ***************/

void draw()
{
	window.clear();	

	// background canvas (paint blobs)
	
	offscreenCanvas.display();
	window.draw(sprite);

	// foreground canvas (boids)
	boidContainer.draw();

	window.display();
	
}

/*****************
 **** Events *****
 *****************/

void createBoid(float x, float y)
{
	Color boidColor = Color(rand() % 100, 100 + rand() % 50, 150 + rand() % 50, 255);
	boidContainer.addBoid(Boid(x, y, boidRadius, boidColor));
}

void mousePressed()
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		Vector2i mousePosition = Mouse::getPosition(window);
		createBoid(mousePosition.x, mousePosition.y);
	}
}

void mouseMoved()
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		Vector2i mousePosition = Mouse::getPosition(window);
		createBoid(mousePosition.x, mousePosition.y);
	}
}