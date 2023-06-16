#include "libasm.h"

void testing(int fd, const char *str, int size, int expected_errno, int expected_retval) {
    static int x;
    bool result;
    errno = 0;
    char buff[100] = {0};
    int retval = ft_read(fd, buff, size);
    //first test
    result = (errno == expected_errno) ? true : false;
    handle_result(result, &x);
    char c = -1;
    read(fd, &c, 1);
    if (errno == 0) {
        //second test
        result = !memcmp(str, buff, size) ? true : false;
        cout << (result ? GREEN : RED);
        cout << "Test " << x++ << ": " << (result ? "OK!" : "KO!") << " ";
        //third test
        result = (c == -1 || c == str[size]) ? true : false;
        handle_result(result, &x);
    }
        //4r test
    result = (retval == expected_retval) ? true : false;
    handle_result(result, &x);
    cout.flush();
}


void test_read(void) {
    cout << YELLOW << "Testing ft_read:" << RESET << endl;
    signal(SIGPIPE, SIG_IGN);
    int fd = open("./test_file", O_RDONLY);
    testing(fd, "loumouli", 0, 0, 0); // test 0-1-2
    close(fd);
    fd = open("./test_file", O_RDONLY);
    testing(fd, "loumouli", 3, 0, 3); // test 3-4-5
    close(fd);
    fd = open("./test_file", O_RDONLY);
    testing(fd, "loumouli", 8, 0, 8); // test 6-7-8
    close(fd);
    testing(-1, "", 1, EBADF, -1); // test 9-10
    fd = open("./libft", O_RDONLY);
    testing(fd, "", 1, EISDIR, -1); //test11-12
    close(fd);
    cout << endl;
}