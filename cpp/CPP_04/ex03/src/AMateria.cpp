#include "AMateria.hpp"

AMateria::AMateria( void ) {
	return ;
}

AMateria::AMateria( const AMateria& var ) {
	*this = var;
	return ;
}

AMateria::AMateria( std::string const& type_i ) {
	this->type = type_i;
	return ;
}

AMateria::~AMateria( void ) {
	return ;
}

AMateria& AMateria::operator=( const AMateria& var ) {
	this->type = var.getType();
	return *this;
}

std::string const& AMateria::getType( void ) const {
	return this->type;
}

void AMateria::use( ICharacter& charac ) {
	(void)charac;
	return ;
}