#pragma once
#include <vector> 
#include "RectangleShape.h"
#include <chrono>
#include <thread>
#include<iostream>
#include<string>

namespace BubbleSort
{
	void runSort(std::vector<RectangleShape>& arr, sf::RenderWindow* window, int delay)
	{
		std::cout << "performing bubble sort" << std::endl;
		int n = arr.size();
		for (int i = 0; i < n - 1; i++)
			for (int j = 0; j < n - 1 - i; j++)
			{
				if (arr[j].value > arr[j + 1].value)
				{
					sf::Vector2f firstPos = arr[j].getPosition();
					sf::Vector2f secondPos = arr[j + 1].getPosition();

					std::iter_swap(arr.begin() + j, arr.begin() + j + 1);

					arr[j].setPosition(firstPos);
					arr[j + 1].setPosition(secondPos);

					arr[j + 1].setFillColor(sf::Color(255, 0, 0, 255));

					window->clear(sf::Color(51, 51, 51, 255));


					for (unsigned int k = 0; k < arr.size(); k++)
					{
						window->draw(arr[k]);
					}

					window->display();

					arr[j + 1].setFillColor(sf::Color(200, 200, 200, 255));

					std::this_thread::sleep_for(std::chrono::milliseconds(delay));
				}
			}


		// Clear unwanted red colored rectangles after the sorting is finished
		window->clear(sf::Color(51, 51, 51, 255));
		for (int i = 0; i < n; i++)
		{
			arr[i].setFillColor(sf::Color(200, 200, 200, 255));
			window->draw(arr[i]);
		}
		window->display();
	}
}

namespace InsertionSort
{
	void runSort(std::vector<RectangleShape>& arr, sf::RenderWindow* window, int delay)
	{
		int n = arr.size();
		for (int i = 0; i < n; i++)
			for (int j = i; j > 0; j--)
			{
				if (arr[j - 1].value > arr[j].value)
				{
					sf::Vector2f firstPos = arr[j - 1].getPosition();
					sf::Vector2f secondPos = arr[j].getPosition();

					std::iter_swap(arr.begin() + j, arr.begin() + j - 1);

					arr[j - 1].setPosition(firstPos);
					arr[j].setPosition(secondPos);

					arr[j - 1].setFillColor(sf::Color(255, 0, 0, 255));

					window->clear(sf::Color(51, 51, 51, 255));
					for (unsigned int k = 0; k < arr.size(); k++)
					{
						window->draw(arr[k]);
					}
					window->display();

					arr[j - 1].setFillColor(sf::Color(200, 200, 200, 255));

					std::this_thread::sleep_for(std::chrono::milliseconds(delay));
				}
			}

		// Clear unwanted red colored rectangles after the sorting is finished
		window->clear(sf::Color(51, 51, 51, 255));
		for (int i = 0; i < n; i++)
		{
			arr[i].setFillColor(sf::Color(200, 200, 200, 255));
			window->draw(arr[i]);
		}
		window->display();
	}
}

namespace SelectionSort
{
	void runSort(std::vector<RectangleShape>& arr, sf::RenderWindow* window, int delay)
	{
		int n = arr.size();

		for (int i = 0; i < n - 1; i++)
		{
			int min = i;

			for (int j = i + 1; j < n; j++)
				if (arr[j].value < arr[min].value)
					min = j;

			if (min != i)
			{
				sf::Vector2f firstPos = arr[i].getPosition();
				sf::Vector2f secondPos = arr[min].getPosition();

				std::iter_swap(arr.begin() + min, arr.begin() + i);

				arr[i].setPosition(firstPos);
				arr[min].setPosition(secondPos);

				arr[i].setFillColor(sf::Color(255, 0, 0, 255));

				window->clear(sf::Color(51, 51, 51, 255));
				for (unsigned int k = 0; k < arr.size(); k++)
				{
					window->draw(arr[k]);
				}
				window->display();

				arr[i].setFillColor(sf::Color(200, 200, 200, 255));

				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			}
		}
	}
}
namespace QuickSort {
	int partition(std::vector<RectangleShape>& arr, sf::RenderWindow* window, int delay, int start, int end)
	{
		int pivot = arr[end].value; // pivot
		int boundary = start - 1;

		for (int i = start; i <= end; i++) {
			if (arr[i].value <= pivot) {
				boundary++;
				sf::Vector2f firstPos = arr[i].getPosition();
				sf::Vector2f secondPos = arr[boundary].getPosition();//pivot element position

				std::iter_swap(arr.begin() + boundary, arr.begin() + i);


				arr[i].setPosition(firstPos);
				arr[boundary].setPosition(secondPos);

				arr[boundary].setFillColor(sf::Color(255, 0, 0, 255));
				arr[i].setFillColor(sf::Color(255, 0, 0, 255));

				window->clear(sf::Color(51, 51, 51, 255));


				for (unsigned int k = 0; k < arr.size(); k++)
				{
					window->draw(arr[k]);
				}

				window->display();

				arr[boundary].setFillColor(sf::Color(200, 200, 200, 255));
				arr[i].setFillColor(sf::Color(200, 200, 200, 255));

				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			}
		}

		return boundary;

	}


	void runSort(std::vector<RectangleShape>& arr, sf::RenderWindow* window, int delay, int start, int end)
	{
		for (unsigned int k = 0; k < arr.size(); k++)
		{
			std::cout << arr[k].value << " ";
		}
		std::cout << std::endl;

		if (start >= end) {
			return;
		}
		int boundary = partition(arr, window, delay, start, end);
		runSort(arr, window, delay, start, boundary - 1);
		runSort(arr, window, delay, boundary + 1, end);

	}
}
namespace ShellSort {
	void shellSort(std::vector<RectangleShape>& arr, sf::RenderWindow* window, int delay)
	{
		// Start with a big gap, then reduce the gap 
		for (int gap = arr.size() / 2; gap > 0; gap /= 2)
		{

			for (int i = gap; i < arr.size(); i += 1)
			{

				int j;
				for (j = i - gap; j >= 0; j -= gap) {

					if (arr[j + gap].value > arr[j].value) {
						break;
					}
					else {
						sf::Vector2f secondPos = arr[j].getPosition();
						sf::Vector2f firstPos = arr[j + gap].getPosition();

						std::iter_swap(arr.begin() + j, arr.begin() + j + gap);

						arr[j].setPosition(secondPos);
						arr[j + gap].setPosition(firstPos);

						arr[j + gap].setFillColor(sf::Color(255, 0, 0, 255));

						window->clear(sf::Color(51, 51, 51, 255));


						for (unsigned int k = 0; k < arr.size(); k++)
						{
							window->draw(arr[k]);
						}

						window->display();

						arr[j + gap].setFillColor(sf::Color(200, 200, 200, 255));

						std::this_thread::sleep_for(std::chrono::milliseconds(delay));

					}
					//for checking output in console
					std::cout << "shell sort" << std::endl;
					for (unsigned int k = 0; k < arr.size(); k++)
					{
						std::cout << arr[k].value << " ";
					}
					std::cout << std::endl;

				}

			}
		}

	}

}

namespace HeapSort {
	void heapify(std::vector<RectangleShape>& arr, sf::RenderWindow* window, int delay, int n, int i)
	{
		int largest = i; // Initialize largest as root 
		int l = 2 * i + 1; // left = 2*i + 1 
		int r = 2 * i + 2; // right = 2*i + 2 

		// If left child is larger than root 
		if (l < n && arr[l].value > arr[largest].value)
			largest = l;

		// If right child is larger than largest so far 
		if (r < n && arr[r].value > arr[largest].value)
			largest = r;

		//for checking output in console
		std::cout << "heap sort" << std::endl;
		for (unsigned int k = 0; k < arr.size(); k++)
		{
			std::cout << arr[k].value << " ";
		}
		std::cout << std::endl;
		//-----------------------------------------------

		// If largest is not root 
		if (largest != i)
		{
			//swap(arr[i], arr[largest]);
			sf::Vector2f secondPos = arr[i].getPosition();
			sf::Vector2f firstPos = arr[largest].getPosition();

			std::iter_swap(arr.begin() + i, arr.begin() + largest);

			arr[i].setPosition(secondPos);
			arr[largest].setPosition(firstPos);

			arr[largest].setFillColor(sf::Color(255, 0, 0, 255));

			window->clear(sf::Color(51, 51, 51, 255));


			for (unsigned int k = 0; k < arr.size(); k++)
			{
				window->draw(arr[k]);
			}

			window->display();

			arr[largest].setFillColor(sf::Color(200, 200, 200, 255));

			std::this_thread::sleep_for(std::chrono::milliseconds(delay));

			// Recursively heapify the affected sub-tree 
			heapify(arr, window, delay, n, largest);
		}
	}

	// main function to do heap sort 
	void heapSort(std::vector<RectangleShape>& arr, sf::RenderWindow* window, int delay, int n)
	{
		// Build heap (rearrange array) 
		for (int i = n / 2 - 1; i >= 0; i--)
			heapify(arr, window, delay, n, i);

		// One by one extract an element from heap 
		for (int i = n - 1; i > 0; i--)
		{
			// Move current root to end 
			//swapping here----------------------------
			//swap(arr[0], arr[i]);
			sf::Vector2f secondPos = arr[0].getPosition();
			sf::Vector2f firstPos = arr[i].getPosition();

			std::iter_swap(arr.begin(), arr.begin() + i);

			arr[0].setPosition(secondPos);
			arr[i].setPosition(firstPos);

			arr[i].setFillColor(sf::Color(255, 0, 0, 255));

			window->clear(sf::Color(51, 51, 51, 255));


			for (unsigned int k = 0; k < arr.size(); k++)
			{
				window->draw(arr[k]);
			}

			window->display();

			arr[i].setFillColor(sf::Color(200, 200, 200, 255));

			std::this_thread::sleep_for(std::chrono::milliseconds(delay));



			//------------------------------------------
			//for checking output in console
			std::cout << "heap sort" << std::endl;
			for (unsigned int k = 0; k < arr.size(); k++)
			{
				std::cout << arr[k].value << " ";
			}
			std::cout << std::endl;
			//-----------------------------------------------



			// call max heapify on the reduced heap 
			heapify(arr, window, delay, i, 0);
		}
	}

}
/*
namespace BST {
	void drawTree(sf::RenderWindow* window, int delay, std::vector<BinaryTree>& btree) {
		window->clear(sf::Color(51, 51, 51, 255));
		sf::Font font;
		if (!font.loadFromFile("KOMIKAP_.ttf"))
		{
			// handle error
		}
		sf::Vector2u windowSize = window->getSize();
		int width = windowSize.x;
		int height = windowSize.y;
		int k = 100;
		for (int i = 0; i < btree.size(); i++) {
			sf::Text text;
			int nodeval = btree[i].getValue();
			std::string s = std::to_string(nodeval);
			std::cout << btree[i].getheadnodeIndex() << std::endl;

			text.setString(s);
			text.setFont(font);
			text.setFillColor(sf::Color::Red);

			if (i == 0) {
				btree[i].setPosition(sf::Vector2f(width/2, 0));

			}
			else {
				if (i % 2 != 0) {
					int headnode = btree[i].getheadnodeIndex();
					btree[i].setPosition(sf::Vector2f(btree[headnode].getPosition().x - k, btree[headnode].getPosition().y + k));

				}
				else {
					int headnode = btree[i].getheadnodeIndex();
					btree[i].setPosition(sf::Vector2f(btree[headnode].getPosition().x + k, btree[headnode].getPosition().y + k));


				}
			}
			text.setPosition(btree[i].getPosition());

			window->draw(text);
			window->display();



		}

		std::this_thread::sleep_for(std::chrono::milliseconds(delay));

	}


	void binaryTree(sf::RenderWindow* window, int delay) {
		int count = 0;
		sf::Vector2u windowSize = window->getSize();
		int width = windowSize.x;
		int height = windowSize.y;
		std::vector<BinaryTree>btree;
		while (count < 8) {
			int nodeVal;
			std::cout << "enter value for node:";
			std::cin >> nodeVal;
			BinaryTree b(nodeVal);
			b.setIndex(count);
			b.setheadnodeIndex(int(count / 2));

			btree.push_back(b);
			drawTree(window, delay, btree);



		}


	}

}*/