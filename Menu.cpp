#include "Menu.h"
#include<string>


Menu::Menu(float width, float height, int state)
{
	std::string sortType[] = { "INSTRUCTIONS TO FOLLOW","Press S to mark source", "Press T to mark Target", "Press W to add wall",
		"Press C to clear Grid","Press R to Run" ,"Press Enter to Continue" };



	if (state == 0) {
		if (!font.loadFromFile("a.ttf"))
		{
			// handle error
		}
		int count = 1;
		for (int i = 0; i <= 6; i++) {
			menu[i].setFont(font);
			menu[i].setFillColor(sf::Color(0, 255, 0, 255));
			menu[i].setString(sortType[i]);
			menu[i].setPosition(sf::Vector2f((width / 2), height / (MAX_NUMBER_OF_ITEMS + 1) * count));
			menu[i].setOrigin(menu[i].getGlobalBounds().width / 2, menu[i].getGlobalBounds().height / 2);
			count++;


		}
		menu[0].setFillColor(sf::Color::Red);//selected item



		selectedItemIndex = 0;
	}

}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 8; i++)
	{
		window.draw(menu[i]);
	}
}




