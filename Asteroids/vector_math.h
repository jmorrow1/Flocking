#pragma once;

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

float squareMagnitude(const Vector2f& vector);

float magnitude(const Vector2f& vector);

void normalize(Vector2f& vector);

Vector2f getNormalized(const Vector2f& vector);

float angleBetween(const Vector2f& a, const Vector2f& b);

float dot(const Vector2f& a, const Vector2f& b);

void limit(Vector2f& vector, float maxMagnitude);

Vector2f getLimited(const Vector2f& vector, float maxMagnitude);

Vector2f toVector2f(const Vector2i& vector);

float heading(const Vector2f& vector);

float squareDistance(const Vector2f& a, const Vector2f& b);

float distance(const Vector2f& a, const Vector2f& b);