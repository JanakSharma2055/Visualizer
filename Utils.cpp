#include "Utils.h"
#include<iostream>

std::vector<RectangleShape> Utils::genArray(int n, sf::RenderWindow* window)
{
	// Store the window's dimensions
	sf::Vector2u windowSize = window->getSize();
	int width = windowSize.x;
	int height = windowSize.y;

	// Create a vector for all RectangleShapes to be stored in
	std::vector<RectangleShape> rects;
	rects.reserve(n);

	// Generate n number of rectangles
	for (int i = 1; i <= n; i++)
	{
		RectangleShape rect(sf::Vector2f(((float)width / n), (((float)height / n) * i)));

		// Set their color, origin position (bottom left of rectangle)
		// and set their position according to the width and height of the window
		rect.setFillColor(sf::Color(200, 200, 200, 255));
		rect.setOrigin(sf::Vector2f(0.0f, ((float)height / n) * i));//origin set to bottom left
		//std::cout << "0 " << (((float)height / n) * i)<< std::endl;
		rect.setPosition(sf::Vector2f((((float)width / n)) * (i - 1) + 1, (float)height));
		//std::cout << "setp:" << (((float)width / n) - 1) * (i - 1) << std::endl;
		// Set the value for each rectangle (this actually gets sorted).
		rect.value = i;

		// Store the rect in the temp vector
		rects.push_back(rect);
	}

	return rects;
}

void Utils::shuffleArray(std::vector<RectangleShape>& arr)
{
	// Size of the array
	int sz = arr.size();

	for (int i = 0; i < sz; i++)
	{
		int index = i + rand() % (sz - i);

		sf::Vector2f firstPos = arr[i].getPosition();
		sf::Vector2f secondPos = arr[index].getPosition();

		std::iter_swap(arr.begin() + i, arr.begin() + index);

		arr[i].setPosition(firstPos);
		arr[index].setPosition(secondPos);
	}

}

