#include "game.h"

game::game(const std::string& title, const int& price,
	const std::string& description)
{
	this->title = title;
	this->price = price;
	this->description = description;
}
