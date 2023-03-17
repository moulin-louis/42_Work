/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:05:55 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:15:22 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{
	{
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		std::cout << std::endl << "First Test..." << std::endl<< std::endl;
		std::cout << "J type is " << j->getType() << ", should be Dog" << std::endl;
		std::cout << "I type is " <<  i->getType() <<", should be Cat" << std::endl;
		std::cout << std::endl;
		std::cout << "Dog will make his sound :" << std::endl;
		j->makeSound();
		std::cout << std::endl;
		std::cout << "Cat will make his sound :" << std::endl;
		i->makeSound();
		std::cout << std::endl;
		std::cout << "Animal will make his sound :" << std::endl;
		meta->makeSound();
		std::cout << std::endl;
		delete meta;
		delete j;
		delete i;
	}
	std::cout << std::endl << "New test with Wrong Class" << std::endl << std::endl;
	{
		const WrongAnimal* wrg_animal_ptr = new WrongAnimal();
		const WrongAnimal* wrg_cat_ptr = new WrongCat();
		std::cout << std::endl;
		std::cout << "wrg_animal type is " << wrg_animal_ptr->getType() << ", should be WrongAnimal" << std::endl;
		std::cout << "wrg_cat type is " << wrg_cat_ptr->getType() << ", should be WrongCat" << std::endl;
		std::cout << std::endl;
		std::cout << "WrongAnimal will make his sound :" << std::endl;
		wrg_animal_ptr->makeSound();
		std::cout << std::endl;
		std::cout << "WrongCat will make his sound :" << std::endl;
		wrg_cat_ptr->makeSound();
		std::cout << std::endl;
		delete wrg_animal_ptr;
		delete wrg_cat_ptr;
	}
	return 0;
}