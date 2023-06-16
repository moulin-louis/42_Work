#include "libasm.h"

static void testing(string str1, string str2) {
    static int x;
    bool result = strcmp(str1.c_str(), str2.c_str()) == ft_strcmp(str1.c_str(), str2.c_str())  ? true : false;
    handle_result(result, &x);
    cout.flush();
}

void test_strcmp(void) {
    cout << YELLOW << "Testing ft_strcmp:" << RESET << endl;
    // I just stole Tripouille test tbh
    testing("", "");
    testing("loumouli", "loumouli");
    testing("loumouli", "louMouli");
    testing("loumouli", "loumoulI");
    testing("loumouli", "loumoulix");
    testing("loumouli", "loumoul");
    testing(long_string, long_string);
    cout << endl;
}