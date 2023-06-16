#include "libasm.h"

static void testing(string str) {
    static int x;
    bool result = (strlen(str.c_str()) == ft_strlen(str.c_str()) ? true : false);
    handle_result(result, &x);
    cout.flush();
}

void test_strlen(void) {
    cout << YELLOW << "Testing ft_strlen:" << RESET << endl;
    testing(""); //Test 1
    testing("Salut tout le monde"); // Test 2
    testing("0987654321"); // Test 3
    testing(long_string); // Test 4
    cout << endl;
}