#include "libasm.h"

static void testing(const string& src) {
    static int x;
    char *dest = ft_strdup(src.c_str());
    if (!dest) {
		cout << RED << "\tTest " << x << ": " << "Malloc error"<< " " << RESET;
        return ;
    }
    bool result = string(dest) == src;
    handle_result(result, &x);
	cout.flush();
    free(dest);
}

void test_strdup() {
	cout << YELLOW << "\tTesting ft_strdup:" << RESET << endl;
    testing("Bonjour"); // Test 0
    testing("123"); // Test 1
    testing("long_string"); // Test 2
    testing(""); // Test 3
	cout << endl;
}
