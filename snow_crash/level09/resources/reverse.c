#include <unistd.h>

int main(int ac, char **av) {
	if (ac != 2)
		return 1;
	char *begin = av[1];
	while (*av[1]) {
		char c = *av[1] - (av[1] - begin);
		write(1, &c, 1);
		av[1]++;
	}
	write(1, "\n", 1);
	return 0;
}
