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
RenderWindow window(VideoMode(1200, 675), "Flocking");

// function prototypes
void setup();
void update();
void draw();

void mousePressed();
void mouseMoved();
void keyPressed();

Text createText(string str, float x, float y);

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
				case Event::KeyPressed: keyPressed(); break;
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

RenderTexture offscreenCanvas;
Sprite sprite;
Flock boidContainer = Flock(&window, &offscreenCanvas);
float boidRadius = 6;
Font font;
Text cohereText;
Text separateText;
Text alignText;

/*************************
 **** Initialization *****
 *************************/

void setup()
{
	offscreenCanvas.create(window.getSize().x, window.getSize().y);
	sprite.setTexture(offscreenCanvas.getTexture());

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "couldn't load font" << std::endl;
	}

	cohereText = createText("Cohere", 10, 10);
	separateText = createText("Separate", 10, 40);
	alignText = createText("Align", 10, 70);
}

Text createText(string str, float x, float y)
{
	Text text;
	text.setCharacterSize(14);
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setString(str);
	text.setPosition(x, y);
	window.draw(text);
	return text;
}

/*****************
 **** Update *****
 *****************/

void update()
{
	//std::cout << boidContainer.getBoidCount() << ", ";
	boidContainer.update();
	if (Mouse::isButtonPressed(Mouse::Button::Right))
	{
		boidContainer.removeBoidFromEnd();
	}
}

/***************
 **** Draw *****
 ***************/

void draw()
{
	window.clear();	

	//// background canvas (paint blobs)
	offscreenCanvas.display();
	window.draw(sprite);

	//// foreground canvas (boids)
	boidContainer.draw();

	// hud
	if (boidContainer.cohere) window.draw(cohereText);
	if (boidContainer.separate) window.draw(separateText);
	if (boidContainer.align) window.draw(alignText);
	
	window.display();
}

/*****************
 **** Events *****
 *****************/

int paletteSize = 6;
Color palette[] =
{
	Color(0xFFA535FF),
	Color(0xFC4F23FF),
	Color(0x7C382DFF),
	Color(0x56725BFF),
	Color(0x08717FFF),
	Color(0x000000FF)
};

void createBoid(float x, float y)
{
	//Color boidColor = Color(rand() % 100, 100 + rand() % 50, 150 + rand() % 50, 255);
	Color boidColor = palette[rand() % paletteSize];
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

void keyPressed()
{
	if (Keyboard::isKeyPressed(Keyboard::C))
	{
		boidContainer.cohere = !boidContainer.cohere;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A))
	{
		boidContainer.align = !boidContainer.align;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		boidContainer.separate = !boidContainer.separate;
	}
	
}