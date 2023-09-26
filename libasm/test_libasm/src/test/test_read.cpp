#include "libasm.h"

static void testing(int fd, const char *str, uint size, int expected_errno, long expected_retval) {
    static int x;
    bool result;
    errno = 0;
    char buff[100] = {0};
    long retval = ft_read(fd, buff, size);
    result = errno == expected_errno;
    handle_result(result, &x);
    char c = -1;
    read(fd, &c, 1);
    if (errno == 0) {
        result = !memcmp(str, buff, size);
        cout << (result ? GREEN : RED);
		cout << "\tTest " << x++ << ": " << (result ? "OK!" : "KO!") << " ";
        result = c == -1 || c == str[size];
        handle_result(result, &x);
    }
    result = retval == expected_retval;
    handle_result(result, &x);
	cout.flush();
}


void test_read() {
	char path_file[] = "./test_file";
	char path_folder[] = "./src";
	cout << YELLOW << "\tTesting ft_read:" << RESET << endl;
    signal(SIGPIPE, SIG_IGN);
    int fd = open(path_file, O_RDONLY);
    testing(fd, "loumouli", 0, 0, 0); //test 0,1,2,3
    close(fd);
    fd = open(path_file, O_RDONLY);
    testing(fd, "loumouli", 3, 0, 3); //test 4,5,6,7
    close(fd);
    fd = open(path_file, O_RDONLY);
    testing(fd, "loumouli", 8, 0, 8); //test 8,9,10,11
    close(fd);
    testing(-1, "", 1, EBADF, -1); // test 12,13
	fd = open(path_folder, O_RDONLY);
    testing(fd, "", 1, EISDIR, -1); // test 14,15
    close(fd);
	cout << endl;
}
