/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:05:55 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/23 13:34:38 by loumouli         ###   ########.fr       */
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
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();
	delete meta;
	delete j;
	delete i;
	}
	std::cout << std::endl << "New test with Wrong Class" << std::endl << std::endl;
	{
		const WrongAnimal* animal_ptr = new WrongAnimal();
		const WrongAnimal* cat_ptr = new WrongCat();
		std::cout << animal_ptr->getType() << std::endl;
		std::cout << cat_ptr->getType() << std::endl;
		animal_ptr->makeSound();
		cat_ptr->makeSound();
		delete animal_ptr;
		delete cat_ptr;
	}
	return 0;
}