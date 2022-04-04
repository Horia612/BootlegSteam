#include "pch.h"
#include "csv.h"
#include <fstream>
#include <exception>
#include <core.h>

int csv::check_row_count(const std::string& filename)
{
	std::ifstream in((filename + ".csv").c_str());
	std::string buffer;
	std::getline(in, buffer);
	using core::string::split_str;
	print(split_str(buffer, ",")->size());
	in.close();
	return split_str(buffer, ",")->size();
}

csv::csv(const std::string& filename)
{
	this->filename = filename;
	this->open();
	this->head = read_row();
}

csv::csv(const std::string& filename, const file_op::op& operation, const int& field_count)
{
	this->filename = filename;
	this->open(operation);
	this->row_count = field_count;
}

csv::csv(const csv& other)
{

}

csv::csv(const std::string& filename, const file_op::op& operation, const std::vector<std::string>& fields)
{
	this->filename = filename;
	this->open(operation);
	this->row_count = fields.size();
	write_row(fields);
}

void csv::write_row(const std::vector<std::string>& row)
{
	//print("Writing to file...\n");
	if (this->operation == file_op::read)
	{
		throw access_denied();
	}
	if (!this->_open)
	{
		throw csv_closed();
	}
	if (row.size() != this->row_count)
	{
		throw bad_row_count();
	}
	for (int i = 0; i < row.size() - 1; i++)
	{
		this->file << row[i] << ',';
	}
	this->file << row.back() << '\n';
}

void csv::open(file_op::op operation)
{
	if (this->_open)
	{
		close();
	}
	switch (operation)
	{
	case file_op::read:
	{
		this->operation = file_op::read;
		file.open((filename + ".csv").c_str(), 
			std::fstream::in);
		break;
	}
	case file_op::append:
	{
		try
		{
			file.open((filename + ".csv").c_str(), 
				std::fstream::app);
			this->operation = file_op::append;
		}
		catch (std::exception& e)
		{
			print("Error: ", e.what());
			throw access_denied();
		}
		break;
	}
	case file_op::write:
	{
		this->operation = file_op::write;
		file.open((filename + ".csv").c_str(), 
			std::fstream::out);
		break;
	}
	}
	this->_open = true;
}

void csv::close()
{
	
	if (_open)
	{
		file.close();
	}
	this->_open = false;
}

std::vector<std::string> csv::read_row()
{
	if (this->operation != file_op::read)
	{
		throw access_denied();
	}
	if (!this->_open)
	{
		throw access_denied();
	}
	std::string buffer;
	std::getline(this->file, buffer);
	using core::string::split_str;
	return *split_str(buffer, ",");
}

std::shared_ptr<std::vector<std::vector<std::string>>> csv::read_rows()
{
	std::vector<std::string> row = read_row();
	std::shared_ptr<std::vector<std::vector<std::string>>> res
	(
		new std::vector<std::vector<std::string>>
	);
	while (row.size())
	{
		res->push_back(row);
		row = read_row();
	}
	/*for (auto row : *res)
	{
		for (auto el : row)
		{
			print(el, ' ');
		}
		print();
	}*/
	return res;
}

csv::~csv()
{
	close();
}

const char* csv_error::what() const noexcept
{
	return	"Csv error";
}

const char* access_denied::what() const noexcept
{
	return "Access denied to file";
}

const char* bad_row_count::what() const noexcept
{
	return "Given row count doesn't match the head row count";
}

const char* csv_closed::what() const noexcept
{
	return "File is closed";
}
