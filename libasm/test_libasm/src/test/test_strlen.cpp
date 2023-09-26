#include "libasm.h"

static void testing(const string& str) {
	static int x;
	bool result = strlen(str.c_str()) == ft_strlen(str.c_str());
	handle_result(result, &x);
	cout.flush();
}

static long libft_ft_strlen(const char *ptr) {
	const char* start = ptr;
	while (*ptr)
		ptr++;
	return (ptr - start);
}

void perf_strlen() {
	char str[] = "Hello World!";
	int i = 0;
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	while (i++ < ITER_TEST)
		(void)strlen(str);
	end = clock();
	cpu_time_used = (static_cast<double>(end - start)) / CLOCKS_PER_SEC;
	cout << "\t\tstrlen took " << cpu_time_used << " seconds to execute \n";
	i = 0;
	start = clock();
	while (i++ < ITER_TEST)
		(void)ft_strlen(str);
	end = clock();
	cpu_time_used = (static_cast<double>(end - start)) / CLOCKS_PER_SEC;
	cout << "\t\tft_strlen took " << cpu_time_used << " seconds to execute \n";
	i = 0;
	start = clock();
	while (i++ < ITER_TEST)
		(void)libft_ft_strlen(str);
	end = clock();
	cpu_time_used = (static_cast<double>(end - start)) / CLOCKS_PER_SEC;
	cout << "\t\tlibft_strlen took " << cpu_time_used << " seconds to execute \n";
}

void test_strlen() {
	cout << YELLOW << "\tTesting ft_strlen:" << RESET << endl;
	testing(""); //Test 0
	testing("Salut tout le monde"); // Test 1
	testing("0987654321"); // Test 2
	testing("long_string"); // Test 3
	cout << endl;
}
