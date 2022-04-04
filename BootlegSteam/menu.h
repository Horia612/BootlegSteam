#pragma once
#include <core.h>
#include <functional>

class menu
{
	std::string tab_name{ "Welcome" };
	std::shared_ptr<std::vector<std::string>> rows
	{
		new std::vector<std::string>
	};
public:
	std::shared_ptr<std::vector<std::string>> get_rows()
	{ return this->rows; }

	inline const std::string get_tab_name() const
	{ return this->tab_name; }

	void set_tab_name(const std::string& name)
	{ this->tab_name = name; }

	void display(const bool& clear_screen = true, 
		const std::function<void()>& function = {});
};

