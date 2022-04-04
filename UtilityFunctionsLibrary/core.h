#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>

template<class T>
void print(const T& t)
{
	std::cout << t;
}

inline void print() { std::cout << '\n'; }

template<class T, class... Ts>
void print(const T& t, const Ts&... ts)
{
	std::cout << t;
	print(ts...);
}


namespace core
{
	namespace string
	{
		std::shared_ptr<std::vector<std::string>> split_str(
			const std::string& str,
			const std::string& delimiter = { " " }
		);
	}

	void clear_screen();
}
