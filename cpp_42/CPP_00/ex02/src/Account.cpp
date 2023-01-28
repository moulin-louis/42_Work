/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:57:17 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/14 19:17:59 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>

int		Account::_nbAccounts = -1;
int		Account::_totalAmount = 0;
int		Account::_totalNbDeposits = 0;
int		Account::_totalNbWithdrawals = 0;

/*Classic constructor*/
Account::Account( void )
{
	return ;
}

/*Constructor*/
Account::Account ( int initial_deposit )
{
	this->_amount = initial_deposit;
	this->_nbAccounts++;
	this->_accountIndex = _nbAccounts; 
	this->_totalAmount += initial_deposit;
	this->_displayTimestamp();
	std::cout << " index:" << Account::getNbAccounts() << ";amount:";
	std::cout << this->_amount << ";created" << std::endl;
	return ;
}

/*Destructor*/
Account::~Account ( void )
{;
	this->_displayTimestamp();
	std::cout << " index:" << Account::_nbAccounts << ";amount:" << this->_amount;
	std::cout << ";closed" << std::endl;
	this->_nbAccounts--;
	return ;
}

/*Return nbr of accounts*/
int		Account::getNbAccounts( void ) { return (Account::_nbAccounts); }
/*Return the total ammount of money*/
int		Account::getTotalAmount( void ) { return (Account::_totalAmount); }
/*Return the nb of deposits*/
int		Account::getNbDeposits( void ) { return (Account::_totalNbDeposits); }
/*Return the nb of withdrawals*/
int		Account::getNbWithdrawals( void ) { return (Account::_totalNbWithdrawals); }
/*Check the amount of money*/
int		Account::checkAmount( void ) const { return (this->_amount); }

void	Account::_displayTimestamp( void )
{
	char temp[20];
	time_t rawtime = time( &rawtime);
 	struct tm * timeinfo = localtime (&rawtime);
	std::cout << "[";
	strftime(temp, 30, "%G%m%e_%H%M%S", timeinfo);
	std::cout << temp << "]";
}

/*Display info about all accounts*/
void	Account::displayAccountsInfos( void )
{
	Account::_displayTimestamp();
	std::cout  << " accounts:" << Account::getNbAccounts() + 1;
	std::cout << ";total:" << Account::getTotalAmount() << ";deposits:" << Account::getNbDeposits();
	std::cout << ";withdrawals:" << Account::getNbWithdrawals() << std::endl;
	return ;
}

/*Make a deposit and print info about it*/
void	Account::makeDeposit( int deposit )
{
	this->_amount += deposit;
	this->_nbDeposits++;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;
	this->_displayTimestamp();
	std::cout << " index:" << this->_accountIndex;
	std::cout << ";p_amount:" << this->_amount - deposit << ";deposit:";
	std::cout << deposit << ";amount:" << this->_amount << ";nb_deposits:";
	std::cout << this->_nbDeposits << std::endl;

}

/*Try to make a withdraw and print info about it*/
bool	Account::makeWithdrawal( int withdrawal )
{
	this->_displayTimestamp();
	std::cout << " index:" << this->_accountIndex;
	std::cout << ";p_amount:" << this->_amount << ";withdrawal:";
	if (this->checkAmount() > withdrawal)
	{
		this->_amount -= withdrawal;
		this->_nbWithdrawals++;
		Account::_totalAmount -= withdrawal;
		Account::_totalNbWithdrawals++;
		std::cout << withdrawal << ";amount:" << this->_amount << ";nb_withdrawals:";
		std::cout << this->_nbDeposits << std::endl;
		return (true);
	}
	else
		std::cout << "refused" << std::endl;
	return (false);
}

/*Display info abount an account*/
void	Account::displayStatus( void ) const
{
	this->_displayTimestamp();
	std::cout << " index:" << this->_accountIndex << ";amount:";
	std::cout << this->_amount << ";deposits:" << this->_nbDeposits << ";withdrawals:" << this->_nbWithdrawals;
	std::cout << std::endl;
}