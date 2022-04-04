#pragma once

#include "pch.h"
#include <core.h>
#include <fstream>

namespace file_op
{
	enum op
	{
		read,
		write,
		append
	};
}

class csv_error : public std::exception
{
public:
	const char* what() const noexcept override;
};

class access_denied : public csv_error
{
public:
	const char* what() const noexcept override;
};

class bad_row_count : public csv_error
{
public:
	const char* what() const noexcept override;
};

class csv_closed : public access_denied
{
public:
	const char* what() const noexcept override;
};

class csv
{
	std::string filename;
	std::fstream file;
	file_op::op operation;
	bool _open{ false };
	unsigned row_count;
	std::vector<std::string> head;	

	int check_row_count(const std::string& filename);
public:
	csv(){}
	csv(const csv& other);
	csv(const std::string& filename);
	csv(const std::string& filename,const file_op::op& operation,
		const int& field_count);
	csv(const std::string& filename, const file_op::op& operation,
		const std::vector<std::string>& fields = {});

	inline const bool is_open() const { return this->_open; }

	inline const std::vector<std::string> get_head() const
	{ return this->head; }

	void write_row(const std::vector<std::string>& row);

	std::vector<std::string> read_row();
	std::shared_ptr<std::vector<std::vector<std::string>>> read_rows();

	void open(file_op::op operation = file_op::read);

	void close();


	~csv();

	//functions
};
