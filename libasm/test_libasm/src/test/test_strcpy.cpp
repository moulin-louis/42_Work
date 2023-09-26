#include "libasm.h"

static void testing(const string& src) {
    static int x;
    bool result = true;
    char *dest = static_cast<char *>(malloc(ft_strlen(src.c_str()) + 10));
    char *save = ft_strcpy(dest, src.c_str());
    if (dest != save || dest != src)
        result = false;
    handle_result(result, &x);
	free(dest);
	cout.flush();
}

void test_strcpy() {
	cout << YELLOW << "\tTesting ft_strcpy:" << RESET << endl;
    testing("Bonjour"); // Test 0
    testing("123"); // Test 1
    testing("long_string"); // Test 2
    testing(""); // Test 3
	cout << endl;
}
