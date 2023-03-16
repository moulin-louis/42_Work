#include <iostream>

#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "ICharacter.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
int main()
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	delete bob;
	delete me;
	delete src;
	return 0;
}

// int main( void ) {
// 	Character test("loulou");
// 	std::cout << "char name is " << test.getName() << std::endl;


// 	AMateria* material_temp = new Ice();
// 	test.equip(material_temp);
// 	delete material_temp;
// 	// test.display_inventory();
// 	material_temp = new Cure();
// 	test.equip(material_temp);
// 	delete material_temp;
// 	material_temp = new Ice();
// 	test.equip(material_temp);
// 	delete material_temp;
// 	material_temp = new Cure();
// 	test.equip(material_temp);
// 	delete material_temp;

// 	Character test2;

// 	test2 = test;
// 	test.unequip(0);
// 	test2.unequip(0);
// }