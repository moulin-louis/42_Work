#include "libasm.h"

void handle_result(bool result, int *nbr_test) {
	cout << (result ? GREEN : RED);
	cout << "\t\tTest " << (*nbr_test) << ": " << (result ? "OK!" : "KO!") << " ";
    (*nbr_test)++;
}

int main(int ac, char **av) {
	int bonus = 0;
	int mandatory = 0;

	if (ac != 2) {
		cout << "Usage: ./test_libasm mandatory/bonus/all" << endl;
		return 1;
	}
	if (strcmp(av[1], "mandatory") == 0)
		mandatory = 1;
	else if (strcmp(av[1], "bonus") == 0) {
		bonus = 1;
	} else if (strcmp(av[1], "all") == 0) {
		bonus = 1;
		mandatory = 1;
	}
    cout << GREEN;
	if (mandatory) {
		cout << "Mandatory Part: " << endl;
		test_strlen();
		perf_strlen();
		test_strcmp();
		test_strcpy();
		test_strdup();
		test_read();
		test_write();
	}
	if (bonus) {
		cout << endl;
		cout << "Bonus Part: " << endl;
		test_list_size();
		test_push_front();
		test_remove_if();
    test_list_sort();
		test_atoi_base();
	}
    if (!bonus && !mandatory)
        cout << RED << "No test selected" << RESET << endl;
}



