#include "PmergeMe.hpp"
#include <iostream>
#include <sys/time.h>
#include <ctime>

void	check_input( char ** input ) {
	unsigned int i = 0;
	while (input[++i]) {
		unsigned j = -1;
		while (input[i][++j]) {
			if (input[i][j] >= '0' && input[i][j] <= '9') {
				continue;
			}
			else {
				std::cout << input[i][j] << std::endl;
				throw std::invalid_argument("Invalid char");
			}
		}
	}
}

int main( int ac, char **av ) {
	if (ac < 2 ) { std::cout << "Wrong nbr of args " << ac << std::endl; return (1); }
	try { check_input(av); }
	catch (std::invalid_argument& x) { std::cout << "Error: " << x.what() << std::endl; return (1);	}

	PmergeMe foo;

	try { foo.fill_vec(av); }
	catch (std::invalid_argument& x) { std::cout << "Error: " << x.what() << std::endl; return (1);	}

	foo.fill_deque(av);
	// foo.display_dequeu();
	if (foo.getsize() < 30)
		foo.display_vec();

	struct timespec temp;
	clock_gettime(CLOCK_REALTIME, &temp);
	long old_ns = temp.tv_nsec;
	foo.sort_vec();
	if (foo.getsize() < 30)
		foo.display_vec();
	clock_gettime(CLOCK_REALTIME, &temp);
	long new_ns = temp.tv_nsec;
	std::cout << "Vector took\t" << new_ns - old_ns << "ns for " << foo.getsize() << " element" << std::endl;
	clock_gettime(CLOCK_REALTIME, &temp);
	old_ns = temp.tv_nsec;
	foo.sort_deque();
	clock_gettime(CLOCK_REALTIME, &temp);
	new_ns = temp.tv_nsec;
	std::cout << "Deque took\t" << new_ns - old_ns << "ns for " << foo.getsize() << " element" << std::endl;
}