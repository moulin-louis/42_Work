/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:52:36 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 12:53:54 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

int	trigger_insert(std::string* buffer, int pos, const std::string& s1, const std::string& s2)
{
	std::string og = s1;
	std::string pld = s2;
	if (pos + pld.length() > buffer->length())
	{
		buffer->erase(buffer->begin() + pos , buffer->begin() + (pos + og.length()));
		buffer->insert(pos, pld);
		buffer->append("\n");
		return (s2.length());
	}
	buffer->erase(buffer->begin() + pos , buffer->begin() + (pos + og.length()));
	std::string temp = *buffer;
	(void)temp;
	buffer->insert(pos, pld);
	return (s2.length());
}

int	main( int ac, char ** av )
{
	(void)av;
	if (ac != 4)
	{
		std::cout << "Wrong nbr of args" << std::endl;
		return (1);
	}
	std::ifstream	infile;
	infile.open(av[1], std::ios::in);
	if (!infile.is_open())
	{
		std::cout << "failed to open file, check your infile" << std::endl;
		return (1);
	}
	std::string		buffer;
	std::string		line;
	while (std::getline(infile, line))
		buffer += line += '\n';
	size_t pos = 0;
	while (1)
	{
		pos = buffer.find(av[2], pos);
		if (pos != std::string::npos)
		{
			pos += trigger_insert(&buffer, pos, av[2], av[3]);
		}
		else
			break ;
	}
	std::ofstream	outfile;
	std::string		temp = av[1];
	temp += ".replace";
	outfile.open(temp.c_str(), std::ios::out | std::ios::trunc);
	if (!outfile.is_open())
	{
		std::cout << "failed to open outfile, try again" << std::endl;
		return (1);
	}
	outfile << buffer;
	infile.close();
	return (0);
}