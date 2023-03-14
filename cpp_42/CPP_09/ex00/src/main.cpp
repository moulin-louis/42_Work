/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:22:07 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/14 19:39:27 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std:: string  open_file( const std::string& path ) 
{
	std::ifstream input_file;
	std::string input_str;

	input_file.open(const_cast<char*>(path.c_str()));
	if (!input_file.is_open()) {
		throw std::ios_base::failure("Cant open database");
	}
	while (1) {
		if (input_file.good()) {
			std::string temp;
			std::getline(input_file, temp);
			(input_str += temp) += '\n';
		}
		else {
			break ;
		}
	}
	return input_str;
}

void try_parsing( char *file_path ) {
	try { std::string database = open_file("./data.csv"); }
	catch (std::ios_base::failure& x) {	std::cout << x.what() << std::endl;	exit(1); }

	try { std::string input = open_file((std::string)file_path); }
	catch (std::ios_base::failure& x) { std::cout << x.what() << std::endl;	exit(1); }
}

int main( int ac, char **av ) {
	if (ac != 2) {
		std::cout << "Wrong number of args" << std::endl;
		return 1;
	}
	try_parsing(av[1]);
	
	BitcoinExchange exchange;
	exchange.setDatabase(open_file("./data.csv"));
	exchange.setInput(open_file(av[1]));
	exchange.BuildMapData();
	exchange.printPrice();
}