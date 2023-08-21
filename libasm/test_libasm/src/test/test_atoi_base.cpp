#include "libasm.h"

//static void testing(t_list *head, unsigned int expected_size) {
//	static int x;
//	bool result = ft_list_size(head) == expected_size;
//	handle_result(result, &x);
//	cout.flush();
//}

void test_atoi_base(void) {
	cout << YELLOW << "\tTesting ft_atoi_base:" << RESET << endl;
	char tmp[] = "2a";
  char base[] = "0123456789abcdef";
  int test = ft_atoi_base(tmp, base);
	cout << "test = " << test << endl;
	cout << endl;
	return ;
}