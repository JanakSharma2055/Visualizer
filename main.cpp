#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "RectangleShape.h"
#include "Utils.h"
#include "Algorithms.h"
#include "Menu.h"
#include "ValueStore.cpp"
// All sorting algorithms stored in an enum
enum SortType
{
	BUBBLE_SORT,
	INSERTION_SORT,
	SELECTION_SORT,
	QUICK_SORT,
	SHELL_SORT,
	HEAP_SORT
};
enum class State {
	ALGO_CHOOSE,
	SPEED_CHOOSE,
	DATA_SIZE_CHOOSE

};

State state = State::ALGO_CHOOSE;
int main()
{
	int n, windowWidth, windowHeight, delay, sortType;
	bool sorted = false;


	sf::RenderWindow window(sf::VideoMode(900, 700), "Sorting");
	window.setFramerateLimit(60);

	std::vector<RectangleShape> bars = Utils::genArray(100, &window);
	Utils::shuffleArray(bars);
	Menu menu1(window.getSize().x, window.getSize().y, 0);
	Menu menu2(window.getSize().x, window.getSize().y, 1);
	Menu menu3(window.getSize().x, window.getSize().y, 2);
	valueStore value;

	// Render loop
	while (window.isOpen())
	{
		sf::Event event;
		window.clear();
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(800, 600));
		rectangle.setOutlineColor(sf::Color::Red);
		rectangle.setOutlineThickness(5);
		rectangle.setOrigin(rectangle.getGlobalBounds().width / 2, rectangle.getGlobalBounds().height / 2);
		rectangle.setPosition(450, 350);
		rectangle.setFillColor(sf::Color::Black);
		window.draw(rectangle);

		switch (state) {
		case State::ALGO_CHOOSE:
			menu1.draw(window);
			break;
		case State::DATA_SIZE_CHOOSE:

			menu2.draw(window);
			break;
		case State::SPEED_CHOOSE:
			menu3.draw(window);
			break;
		}


		window.display();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (state == State::ALGO_CHOOSE) menu1.MoveUp();
					else if (state == State::DATA_SIZE_CHOOSE) menu2.MoveUp();
					else if (state == State::SPEED_CHOOSE) menu3.MoveUp();
					break;

				case sf::Keyboard::Down:
					if (state == State::ALGO_CHOOSE) menu1.MoveDown();
					if (state == State::DATA_SIZE_CHOOSE) menu2.MoveDown();
					if (state == State::SPEED_CHOOSE) menu3.MoveDown();
					break;

				case sf::Keyboard::Return:
					if (state == State::ALGO_CHOOSE) {
						switch (menu1.GetPressedItem())
						{
						case BUBBLE_SORT:

							value.algorithmCode = BUBBLE_SORT;
							//BubbleSort::runSort(bars, &window, 500);
							//check for binary tree



							break;
						case INSERTION_SORT:
							value.algorithmCode = INSERTION_SORT;
							//InsertionSort::runSort(bars, &window, 500);
							break;
						case SELECTION_SORT:
							value.algorithmCode = SELECTION_SORT;
							//SelectionSort::runSort(bars, &window, 500);

							break;
						case QUICK_SORT:

							value.algorithmCode = QUICK_SORT;
							//BubbleSort::runSort(bars, &window, 500);

							break;
						case SHELL_SORT:
							value.algorithmCode = SHELL_SORT;
							//InsertionSort::runSort(bars, &window, 500);
							break;
						case HEAP_SORT:
							value.algorithmCode = HEAP_SORT;
							//SelectionSort::runSort(bars, &window, 500);

							break;
						}
						state = State::SPEED_CHOOSE;
						break;
					}


					if (state == State::SPEED_CHOOSE) {
						switch (menu3.GetPressedItem())
						{
						case 0:

							value.speedCode = 10;
							//BubbleSort::runSort(bars, &window, 500);

							break;
						case 1:
							value.speedCode = 100;
							//InsertionSort::runSort(bars, &window, 500);
							break;
						case 2:
							value.speedCode = 1000;
							//SelectionSort::runSort(bars, &window, 500);

							break;
						
						}
						state = State::DATA_SIZE_CHOOSE;
						break;
					}


					if (state == State::DATA_SIZE_CHOOSE) {
						switch (menu2.GetPressedItem())
						{
						case 0:

							value.dataCode = 20;
							bars = Utils::genArray(value.dataCode, &window);
							Utils::shuffleArray(bars);
							switch (value.algorithmCode) {
							case BUBBLE_SORT:
								BubbleSort::runSort(bars, &window, value.speedCode);
								break;
							case INSERTION_SORT:
								InsertionSort::runSort(bars, &window, value.speedCode);
								break;
							case SELECTION_SORT:
								SelectionSort::runSort(bars, &window, value.speedCode);
							case QUICK_SORT:
								QuickSort::runSort(bars, &window, value.speedCode, 0, bars.size() - 1);
								break;
							case SHELL_SORT:
								ShellSort::shellSort(bars, &window, value.speedCode);
								break;
							case HEAP_SORT:
								HeapSort::heapSort(bars, &window, value.speedCode, bars.size() - 1);
								break;

							}
							break;



						case 1:

							value.dataCode = 50;
							bars = Utils::genArray(value.dataCode, &window);
							Utils::shuffleArray(bars);
							switch (value.algorithmCode) {
							case BUBBLE_SORT:
								BubbleSort::runSort(bars, &window, value.speedCode);
								break;
							case INSERTION_SORT:
								InsertionSort::runSort(bars, &window, value.speedCode);
								break;
							case SELECTION_SORT:
								SelectionSort::runSort(bars, &window, value.speedCode);
							case QUICK_SORT:
								QuickSort::runSort(bars, &window, value.speedCode, 0, bars.size() - 1);
								break;
							case SHELL_SORT:
								ShellSort::shellSort(bars, &window, value.speedCode);
								break;
							case HEAP_SORT:
								HeapSort::heapSort(bars, &window, value.speedCode, bars.size() - 1);
								break;

							}
							break;

						case 2:

							value.dataCode = 100;
							bars = Utils::genArray(value.dataCode, &window);
							Utils::shuffleArray(bars);
							switch (value.algorithmCode) {
							case BUBBLE_SORT:
								BubbleSort::runSort(bars, &window, value.speedCode);


								break;
							case INSERTION_SORT:
								InsertionSort::runSort(bars, &window, value.speedCode);
								break;
							case SELECTION_SORT:
								SelectionSort::runSort(bars, &window, value.speedCode);
							case QUICK_SORT:
								QuickSort::runSort(bars, &window, value.speedCode, 0, bars.size() - 1);
								break;
							case SHELL_SORT:
								ShellSort::shellSort(bars, &window, value.speedCode);
								break;
							case HEAP_SORT:
								HeapSort::heapSort(bars, &window, value.speedCode, bars.size() - 1);
								break;

							}
							//QuickSort::runSort(bars, &window, 400, 0, bars.size()-1);
							//ShellSort::shellSort(bars, &window, value.speedCode);
							//HeapSort::heapSort(bars, &window,10, bars.size() - 1);


							break;
						}
						state = State::ALGO_CHOOSE;
						break;
					}


				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		Utils::shuffleArray(bars);


	}

	return 0;
}
//-----------------------------------------------------------------------------------------------
