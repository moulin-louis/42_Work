#include "Ice.hpp"

Ice::Ice( void ) {
	this->type = "ice";
	return ;
}

Ice* Ice::clone( void ) const {
	Ice* result = new Ice;
	result->type = this->type;
	return result;
}

void Ice::use( ICharacter& charac ) {
	std::cout << "* shoots an ice bolt at " << charac.getName() << " *" << std::endl;
	return ;
}