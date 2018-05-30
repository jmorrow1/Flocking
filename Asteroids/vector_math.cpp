#pragma once;

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include "vector_math.h"

using namespace sf;

float squareMagnitude(const Vector2f& vector)
{
	return (vector.x * vector.x) + (vector.y * vector.y);
}

float magnitude(const Vector2f& vector)
{
	return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

void normalize(Vector2f& vector)
{
	float mag = magnitude(vector);
	vector.x /= mag;
	vector.y /= mag;
}

Vector2f getNormalized(const Vector2f& vector)
{
	return vector / magnitude(vector);
}

float angleBetween(const Vector2f& a, const Vector2f& b)
{
	return atan2(b.y - a.y, b.x - a.x);
}

float dot(const Vector2f& a, const Vector2f& b)
{
	return cos(angleBetween(a, b)) * magnitude(a) * magnitude(b);
}

void limit(Vector2f& vector, float maxMagnitude)
{
	float sqMag = squareMagnitude(vector);
	if (sqMag > maxMagnitude * maxMagnitude)
	{
		normalize(vector);
		vector *= maxMagnitude;
	}
}

Vector2f getLimited(const Vector2f& vector, float maxMagnitude)
{
	float sqMag = squareMagnitude(vector);
	if (sqMag > maxMagnitude * maxMagnitude)
	{
		Vector2f normalVector = getNormalized(vector);
		return normalVector * maxMagnitude;
	}
}

Vector2f toVector2f(const Vector2i& vector)
{
	return Vector2f(vector.x, vector.y);
}

float heading(const Vector2f& vector)
{
	return atan2(vector.y, vector.x);
}

float squareDistance(const Vector2f& a, const Vector2f& b)
{
	float x = a.x - b.x;
	float y = a.y - b.y;
	return x*x + y*y;
}

float distance(const Vector2f& a, const Vector2f& b)
{
	float x = a.x - b.x;
	float y = a.y - b.y;
	return sqrt(x*x + y*y);
}

