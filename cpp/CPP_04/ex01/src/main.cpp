/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:05:55 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:33:51 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"

#define NBR_ANIMALS 4

int main()
{
	const Animal* ptr[NBR_ANIMALS];
	for (int i = 0; i < NBR_ANIMALS; i++)
	{
		if (i % 2)
		{
			ptr[i] = new Cat();
			std::cout << "One cat created" << std::endl;
		}
		else
		{
			ptr[i] = new Dog();
			std::cout << "One dog created" << std::endl;
		}
	}
	std::cout << std::endl << "Constructor done..." << std::endl << std::endl;
	for (int i = 0; i < NBR_ANIMALS; i++)
	{
		delete ptr[i];
		std::cout << "One animal delete" << std::endl;
	}

	Dog dog1;
	Dog dog2;
	
	dog1.display_brain();
	dog1.set_idea(0, "food");
	dog1.set_idea(1, "play");
	dog1.set_idea(2, "sleep");
	dog1.display_brain();
	dog2 = dog1;
	dog1.set_idea(3, "other cat");
	std::cout << std::endl<< "Brain of dog1" << std::endl;
	dog1.display_brain();
	std::cout << std::endl << "Brain of dog2" << std::endl;
	dog2.display_brain();

	return 0;
}