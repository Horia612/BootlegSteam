#include "menu.h"

void menu::display(const bool& clear_screen,
	const std::function<void()>& function)
{
	if (clear_screen)
	{
		core::clear_screen();
	}
	print(tab_name, '\n');
	for (auto row : *rows.get())
	{
		print(row, '\n');
	}
}
