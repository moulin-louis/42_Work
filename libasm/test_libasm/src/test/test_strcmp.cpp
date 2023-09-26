#include "libasm.h"

static void testing(const string& str1, const string& str2) {
    static int x;
	bool result = false;
	int of_result = strcmp(str1.c_str(), str2.c_str());
	int my_result = ft_strcmp(str1.c_str(), str2.c_str());
	if (of_result < 0 && my_result < 0)
		result = true;
	if (of_result > 0 && my_result > 0)
		result = true;
	if (of_result == 0 && my_result == 0)
		result = true;
    handle_result(result, &x);
    cout.flush();
}

void test_strcmp() {
    cout << YELLOW << "\tTesting ft_strcmp:" << RESET << endl;
    // I just stole Tripouille test tbh
    testing("", ""); //test 0
    testing("loumouli", "loumouli"); // test 1
    testing("loumouli", "louMouli"); // test 2
    testing("loumouli", "loumoulI"); // test 3
    testing("loumouli", "loumoulix"); // test 4
    testing("loumouli", "loumoul"); // test 5
    testing("long_string", "long_string"); // test 6
    cout << endl;
}
