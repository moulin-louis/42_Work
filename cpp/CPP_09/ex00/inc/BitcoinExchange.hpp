/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:58:13 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/14 14:18:44 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 
#ifndef BITCOIN_HPP
#define BITCOIN_HPP

#include <map>
#include <iostream>
#include <ios>
#include <fstream>
#include <string>
#include <cstdlib>

class BitcoinExchange {
	private:
		std::string database;
		std::string input;
		std::map<std::string, float> mapData;
		std::map<std::string, float> mapInput;
	public:
	BitcoinExchange( void );
	~BitcoinExchange( void );
	BitcoinExchange( const BitcoinExchange& );
	BitcoinExchange& operator=( const BitcoinExchange& );
	void setDatabase( std::string );
	void setInput( std::string );
	void BuildMapData( void );
	void printPrice( void );
};

#endif