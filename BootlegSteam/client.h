#pragma once
#include <core.h>

class client
{
	float money{ 0 };
	std::string username;
public:
	client(const std::string & username);

	inline const float get_money() const { return this->money; }
	void set_money(const float& money) { this->money = money; }
};

