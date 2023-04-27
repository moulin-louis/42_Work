/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:22:03 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/16 12:00:21 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( void ) {
	return ;
}

BitcoinExchange::~BitcoinExchange( void ) {
	return ;
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange& var ) { 
	*this = var;
	return ;
}

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& var ) {
	this->database = var.database;
	this->input = var.input;
	return *this;
}

void BitcoinExchange::setDatabase( std::string input ) {
	this->database = input;
}

void BitcoinExchange::setInput( std::string input ) {
	this->input = input;
}

float to_float( const std::string& str ) {
	return (std::atof(str.c_str()));
}

int	search_nl( std::string str, int pos ) {
	while (str[pos] && str[pos] != '\n')
		pos ++;
	if (!str[pos])
		return 0;
	return pos;
}

void BitcoinExchange::BuildMapData( void ) {
	unsigned long old_pos;

	old_pos = this->database.find("\n") + 1;
	while (1) {
		if (old_pos == this->database.size() - 1)
			break ;
		std::string line = this->database.substr(old_pos, search_nl(this->database, old_pos) - old_pos);
		this->mapData.insert(std::pair<std::string, float>(line.substr(0, line.find(",")), to_float(line.substr(line.find(",") + 1, line.size()))));
		(old_pos += line.size()) += 1;
	}
	return ;
}

void BitcoinExchange::printPrice( void ) {
	unsigned long old_pos;

	old_pos = this->input.find("\n") + 1;
	while (1) {
		if (old_pos == this->input.size() - 1 ) { break ; }
		std::string line = this->input.substr(old_pos, search_nl(this->input, old_pos) - old_pos);
		if (line.size() <= 2) { break ;	}

		if (line.find(" | ") == 0 ) {
			std::cout << "Error: bad input => " << line << std::endl;
			return ;
		}
		std::string float_str = line.substr(line.find(" | ") + 3, line.size());
		std::string date_str = line.substr(0, line.find(" | "));
		float nbr = to_float(float_str);
		if (nbr > 1000) {
			std::cout << "Error: too large number => " << float_str << std::endl;
			(old_pos += line.size()) += 1;
			continue ;
		}
		else if ( nbr < 0) {
			std::cout << "Error: too low number => " << float_str << std::endl;
			(old_pos += line.size()) += 1;
			continue ;
		}
		else {
			std::map<std::string, float>::iterator it =  this->mapData.find(date_str);
			if (it == this->mapData.end()) {
				std::cout << "Error cant find the date in the database " << date_str << std::endl;
				(old_pos += line.size()) += 1;
				continue ;
			}
			std::cout << date_str << " => " << nbr << " = " << nbr * it->second << std::endl;
		}
		(old_pos += line.size()) += 1;
	}
}