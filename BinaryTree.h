#pragma once
#include<SFML/Graphics.hpp>
class BinaryTree
{
private:
	int nodevalue;
	sf::Vector2f position;
	int index;
	int headnodeIndex;
public:
	BinaryTree(int node) {
		nodevalue = node;
	}
	void setPosition(sf::Vector2f pos) {
		position = pos;
	}
	sf::Vector2f getPosition() {
		return position;
	}
	void setIndex(int n) {
		index = n;
	}
	void setheadnodeIndex(int n) {
		headnodeIndex = n;
	}
	int getValue() {
		return nodevalue;
	}
	int getheadnodeIndex() {
		return headnodeIndex;
	}

};

