#include "Menu.h"
#include<string>


Menu::Menu(float width, float height, int state)
{
	std::vector<std::string> sortType{ "Bubble Sort", "Insertion Sort", "Selection Sort",
		"Quick Sort","Shell Sort","Heap Sort" };



	if (state == 0) {
		if (!font.loadFromFile("KOMIKAP_.ttf"))
		{
			// handle error
		}
		int count = 1;
		for (int i = 0; i <= 5; i++) {
			menu[i].setFont(font);
			menu[i].setFillColor(sf::Color(0, 255, 0, 255));
			menu[i].setString(sortType[i]);
			menu[i].setOrigin(menu[i].getGlobalBounds().width / 2, menu[i].getGlobalBounds().height / 2);
			menu[i].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * count));
			count++;


		}
		menu[0].setFillColor(sf::Color(255, 0, 0, 255));//selected item



		selectedItemIndex = 0;
	}

	if (state == 2) {
		if (!font.loadFromFile("KOMIKAP_.ttf"))
		{
			// handle error
		}
		std::vector<std::string> speed{ "Speed 10ms","Speed 100 ms","Speed 1000 ms" };
		int count = 1;
		for (int i = 0; i <= 2; i++) {
			menu[i].setFont(font);
			menu[i].setFillColor(sf::Color(0, 255, 0, 255));
			menu[i].setString(speed[i]);
			menu[i].setOrigin(menu[i].getGlobalBounds().width / 2, menu[i].getGlobalBounds().height / 2);
			menu[i].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * count));
			count++;


		}
		menu[0].setFillColor(sf::Color(255, 0, 0, 255));//selected item




		selectedItemIndex = 0;
	}

	if (state == 1) {
		if (!font.loadFromFile("KOMIKAP_.ttf"))
		{
			// handle error
		}
		std::vector<std::string> dataCount{ "20 Data items","50 Data items","100 Data items","300 data items" };
		int count = 1;
		for (int i = 0; i <= 3; i++) {
			menu[i].setFont(font);
			menu[i].setFillColor(sf::Color(0, 255, 0, 255));
			menu[i].setString(dataCount[i]);
			menu[i].setOrigin(menu[i].getGlobalBounds().width / 2, menu[i].getGlobalBounds().height / 2);
			menu[i].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * count));
			count++;


		}
		menu[0].setFillColor(sf::Color(255, 0, 0, 255));//selected item

		selectedItemIndex = 0;
	}



}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color(0, 255, 0, 255));
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color(0, 255, 0, 255));
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
	}
}
