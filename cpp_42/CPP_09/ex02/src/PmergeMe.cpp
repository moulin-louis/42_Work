/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:10:35 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/14 18:14:49 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe( void ) { return ; }

PmergeMe::PmergeMe( const PmergeMe& var ) { *this = var; return ; }

PmergeMe::~PmergeMe( void ) { return ; }

PmergeMe& PmergeMe::operator=( const PmergeMe& var ) { this->vec = var.vec; return (*this); }

void PmergeMe::fill_vec( char **input ) {

	unsigned int i = 0;
	while (input[++i]) {
		unsigned int temp = 0;
		atoi_int(&temp, input[i]);
		this->vec.push_back(temp);
	}
	for (std::vector<int>::iterator it = this->vec.begin(); it != this->vec.end(); it++) {
		for (std::vector<int>::iterator temp = it + 1; temp != this->vec.end(); temp ++) {
			if (*temp == *it) {
				throw std::invalid_argument("Duplicate");
			}
		}
	}
}

void PmergeMe::fill_deque( char **input ) {
	unsigned int i = 0;
	while (input[++i]) {
		unsigned int temp = 0;
		atoi_int(&temp, input[i]);
		this->deque.push_back(temp);
	}
}

void PmergeMe::display_vec( void ) {
	std::cout << "Before: ";
	for (std::vector<int>::iterator it = this->vec.begin(); it != this->vec.end(); it ++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::display_dequeu( void ) {
	std::cout << "Before: ";
	for (std::deque<int>::iterator it = this->deque.begin(); it != this->deque.end(); it ++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::sort_vec( void ) {
	sort(this->vec, 0, this->vec.size() -1 );
}

void PmergeMe::sort_deque( void ) {
	sort(this->deque, 0, this->vec.size() - 1);
}

unsigned long PmergeMe::getsize( void ) {
	return this->vec.size();
}