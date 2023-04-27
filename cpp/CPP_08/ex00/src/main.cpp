/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:01:30 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/28 11:51:33 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int	main(void)
{
	std::vector<int> vect;
	vect.push_back(0);
	vect.push_back(1);
	vect.push_back(2);
	int *x = new int;
	try {
		*x = easyfind<std::vector<int> >(vect, 1);
	}
	catch (std::invalid_argument& mce)
	{
		std::cout << mce.what() << std::endl;
		delete x;
		return (1);
	}
	std::cout << "We find " << *x << " in the container" << std::endl;
	delete x;


	// std::vector<int> vect;
	// int *x = new int;
	// try {
	// 	*x = easyfind<std::vector<int> >(vect, 1);
	// }
	// catch (std::invalid_argument& mce)
	// {
	// 	std::cout << mce.what() << std::endl;
	// 	delete x;
	// 	return (1);
	// }
	// std::cout << "We find " << *x << " in the container" << std::endl;
	// delete x;


	// std::vector<int> vect;
	// vect.push_back(0);
	// vect.push_back(1);
	// vect.push_back(2);
	// int *x = new int;
	// try {
	// 	*x = easyfind<std::vector<int> >(vect, -657)
	// }
	// catch (std::invalid_argument& mce)
	// {
	// 	std::cout << mce.what() << std::endl;
	// 	delete x;
	// 	return (1);
	// }
	// std::cout << "We find " << *x << " in the container" << std::endl;
	// delete x;


	// int myints[] = {16,2,77,29};
	// std::list<int> my_list (myints, myints + sizeof(myints) / sizeof(int) );
	// int *x = new int;
	// try {
	// 	*x = easyfind<std::list<int> >(my_list, 29);
	// }
	// catch (std::invalid_argument& mce)
	// {
	// 	std::cout << mce.what() << std::endl;
	// 	delete x;
	// 	return (1);
	// }
	// std::cout << "We find " << *x << " in the container" << std::endl;
	// delete x;

	// std::deque<int> deque_test;
	// deque_test.push_back(1);
	// deque_test.push_back(2);
	// deque_test.push_back(3);
	// int *x = new int;
	// try {
	// 	*x = easyfind<std::deque<int> >(deque_test, -1);
	// }
	// catch (std::invalid_argument& mce)
	// {
	// 	std::cout << mce.what() << std::endl;
	// 	delete x;
	// 	return (1);
	// }
	// std::cout << "We find " << *x << " in the container" << std::endl;
	// delete x;
}