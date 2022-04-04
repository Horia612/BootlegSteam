#pragma once
#include <core.h>

class game
{
	std::string title{ "Mario" };
	unsigned price{ 50 };
	std::string description{ "What a cool fucking game!" };
public:
	game() {}
	game(const std::string& title,
		const int& price = 50,
		const std::string& description = {
		"What a cool fucking game!" });

	inline const std::string get_title() const
	{ return this->title; }

	inline const unsigned get_price() const
	{ return this->price; }

	inline const std::string get_description() const
	{ return this->description; }

	void set_price(const unsigned& price)
	{ this->price = price; }

	void set_description(const std::string& desc)
	{ this->description = desc;	}
};

