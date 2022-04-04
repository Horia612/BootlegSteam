#include <csv.h>
#include <core.h>
#include "client.h"
#include "menu.h"
void wallet(menu& cl,client& cli);
void show_store(menu& cl, client& cli);
void show_library(menu& cl, client& cli);

std::vector<std::string> main_menu_op{
	"Choose an option:",
	"1.Store",
	"2.My library",
	"3.My wallet",
	"4.Sign out"
};

void show_main_menu(menu& Menu)
{
	Menu.get_rows()->clear();
	Menu.set_tab_name("Welcome");
	//for(auto el : main_menu_op)
	//{

	//}
	*Menu.get_rows() = main_menu_op;
	Menu.display();
}

void setup(client& cli)
{
	csv file("client");
	//print(file.get_head()[0], '\n');
	cli.set_money(std::stof(file.get_head()[0]));
	file.close();
}


int main()
{
	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(2);
	//print("Hello world ", 23, '\n');
	client cli("user");
	setup(cli);
	menu show;
	int opt;
	show_main_menu(show);
	print("Choose an option number: ");
	std::cin >> opt;
	while ((opt > 0 and opt < 4) or opt >= 16)
	{
		switch (opt)
		{
		case 1:
		{
			show_store(show, cli);
			break;
		}
		case 2:
		{
			show_library(show, cli);
			break;
		}
		case 3:
		{
			wallet(show, cli);
			break;
		}
		case 16:
		{
			core::clear_screen();
			print("Are you dumb? There are only 4 options.\n");
			system("pause");
			break;
		}
		case 17:
		{
			core::clear_screen();
			print("You're persistent, aren't you?\n");
			system("pause");
			break;
		}
		case 18:
		{
			core::clear_screen();
			print("You really are bored, huh?\n");
			system("pause");
			break;
		}
		default:
		{
			if (opt > 18) 
			{
				core::clear_screen();
				print("I don't have as much time as you to come up with these, you know?\n");
				system("pause");
				break;
			}
			break;
		}
		}
		show_main_menu(show);
		print("Choose an option number: ");
		std::cin >> opt;
	}
}

void wallet(menu& cl,client& cli)
{
	int alg;
	float sum;
	cl.set_tab_name("Wallet");
	cl.get_rows()->clear();
	cl.get_rows()->push_back({ 
		"You currently have $" +
		std::to_string(cli.get_money()) + "\n" 
		});
	cl.get_rows()->push_back("If you wish to add more money to your account press 1, else press 0 :");
	cl.display();
	std::cin >> alg;	
	if (alg)
	{
		csv file("client", file_op::write, 1);
		print("To add money to the account write down the amount of money: ");
		std::cin >> sum;
		if (sum == 666)
		{
			print("That can't be clean money, but I'll take it.\n");
		}
		if (sum == 69)
		{
			print("Haha sixty-nice funny!!!!:)))==)\n");
		}
		cli.set_money(cli.get_money() + sum);
		print("You now have $",	cli.get_money(), '\n');
		file.write_row({ std::to_string(cli.get_money()) });
		file.close();
	}
	system("pause");
}

void show_store(menu& cl, client& cli)
{
	std::string game_choice;
	cl.get_rows()->clear();
	//core::clear_screen();
	cl.set_tab_name("Store");
	csv file("GameStore");
	auto data = *file.read_rows();
	file.close();
	for (auto row : data)
	{
		std::string buffer = "";
		buffer += ("Title: " + row[0] + "\n");
		buffer += ("Price: " + row[1] + "\n");
		buffer += ("Description: " + row[2] + "\n");
		cl.get_rows()->push_back(buffer);
	}
	cl.display();	
	print("Write the name of the game you'd like to buy: ");
	std::cin.ignore();
	std::getline(std::cin, game_choice);
	auto capitalize = [](std::string str)->std::string
	{
		for (auto& chr : str)
		{
			chr = std::toupper(chr);
		}
		//print(str, "\n");
		return str;
	};
	game_choice = capitalize(game_choice);
	auto find_row = [&]()
	{
		for (auto row : data)
		{
			if (game_choice == capitalize(row[0]))
			{
				return row;
			}
		}
		return std::vector<std::string>{};
	};
	auto option = find_row();
	if (!option.size())
	{
		print("We don't have that game\n");
	}
	else if(std::stof(option[1])>cli.get_money())
	{
		print("Insufficient funds.\n");
	}
	else
	{
		csv library("Library");
		auto games = *library.read_rows();
		library.close();
		for (auto row : games)
		{
			if(row[0]==option[0])
			{
				print("You already have this game!\n");				
				system("pause");
				return;
			}
		}
		cli.set_money(cli.get_money() - std::stof(option[1]));		
		csv file("client", file_op::write, 1);
		if (!cli.get_money())
		{
			file.write_row({ "0" });
		}
		else
		{
			file.write_row({ std::to_string(cli.get_money()) });
		}
		file.close();
		csv collection("Library", file_op::append, 2);
		collection.write_row({ option[0], option[2] });
		collection.close();
		print("You have succesfully bought the game!\n");
	}
	//code
	//std::string upper_title = 
	system("pause");			
}

void show_library(menu& cl, client& cli)
{
	cl.get_rows()->clear();
	cl.set_tab_name("My Library");
	core::clear_screen();
	csv file("Library");
	auto afis = file.read_rows();
	for (auto row : *afis)
	{
		std::string buffer = "";
		buffer += ("Title: " + row[0] + "\n");
		buffer += ("Description: " + row[1] + "\n");
		cl.get_rows()->push_back(buffer);
	}
	cl.display();
	system("pause");
}
