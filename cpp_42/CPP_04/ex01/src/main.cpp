/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:05:55 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/23 15:28:53 by loumouli         ###   ########.fr       */
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
			std::cout << std::endl << "One cat created" << std::endl << std::endl;
		}
		else
		{
			ptr[i] = new Dog();
			std::cout << std::endl << "One dog created" << std::endl << std::endl;
		}
	}
	std::cout << std::endl << "Constructor done..." << std::endl << std::endl;
	for (int i = 0; i < NBR_ANIMALS; i++)
	{
		delete ptr[i];
		std::cout << std::endl << "One animal delete" << std::endl << std::endl;
	}

	std::cout << std::endl << "Second Test" << std::endl << std::endl;
	Dog	temp1;
	std::cout << std::endl << std::endl;
	Dog temp2;
	std::cout << std::endl << std::endl;

	Brain* ptr_brain1 = temp1.get_brain();
	ptr_brain1->ideas[0] = "FOOD";
	temp2 = temp1;
	Brain* ptr_brain2 = temp2.get_brain();
	std::cout << ptr_brain1->ideas[0] << " is the idead 0 of Dog1" << std::endl;
	std::cout << ptr_brain2->ideas[0] << " is the idead 0 of Dog2" << std::endl;
	ptr_brain1->ideas[0] = "SLEEP";
	std::cout << ptr_brain1->ideas[0] << " is the idead 0 of Dog1" << std::endl;
	std::cout << ptr_brain2->ideas[0] << " is the idead 0 of Dog2" << std::endl;
	return 0;
}