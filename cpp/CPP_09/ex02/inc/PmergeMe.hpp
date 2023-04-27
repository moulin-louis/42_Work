/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:05:30 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/14 18:17:55 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string.h>
#include <ctime>

class PmergeMe {
	private:
		std::vector<int> vec;
		std::deque<int> deque;
	public:
		PmergeMe( void );
		PmergeMe( const PmergeMe& );
		~PmergeMe( void );
		PmergeMe& operator=( const PmergeMe& );
		void fill_vec( char **input );
		void fill_deque( char **input );
		// void fill_set( const std::string& );
		void display_vec( void );
		void display_dequeu( void );
		void sort_vec( void );
		void sort_deque( void );
		unsigned long getsize( void );
};

void	atoi_int( unsigned int * val, const std::string& str );

template<typename T>
void merge( T& container, int start, int temp, int end) {
	int n1 = temp - start + 1;
    int n2 = end - temp;
    T LA;
	LA.assign(container.begin() + start,container.begin() + temp + 1 );
    T RA;
	RA.assign(container.begin() + (temp + 1), container.begin() + end + 1);
    int RIDX = 0;
    int LIDX = 0;
    for (int i = start; i < end - start + 1; i++) {
        if (RIDX == n2) {
            container[i] = LA[LIDX];
            LIDX++;
        } else if (LIDX == n1) {
            container[i] = RA[RIDX];
            RIDX++;
        } else if (RA[RIDX] > LA[LIDX]) {
            container[i] = LA[LIDX];
            LIDX++;
        } else {
            container[i] = RA[RIDX];
            RIDX++;
        }
    }
}

template<typename T>
void insertion( T& container, int start, int end ) {
	for (int i = start; i < end; i ++) {
		int temp = container[i + 1];
		int j = i + 1;
		while (j > start && container.at(j - 1) > temp) {
			container[j] = container[j - 1];
			j--;
		}
		container[j] = temp;
	}
}

template<typename T>
void sort( T & container, int start, int end) {
	if (end - start > 5) {
		int temp = (start + end ) / 2;
		sort(container, start, temp);
		sort(container, temp + 1, end);
		merge(container, start, temp, end);
	}
	else {
		insertion( container, start, end);
	}
}


#endif