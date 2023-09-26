#include "libasm.h"

static void testing(t_list *head, unsigned int expected_size) {
    static int x;
    bool result = ft_list_size(head) == expected_size;
    handle_result(result, &x);
	cout.flush();
}

void test_list_size() {
	cout << YELLOW << "\tTesting ft_list_size:" << RESET << endl;
    auto head = static_cast<t_list *>(calloc(sizeof(t_list), 1));
    testing(nullptr, 0); //Test 1
    testing(head, 1); // Test 2
    head->next = static_cast<t_list *>(calloc(sizeof(t_list), 1));
    testing(head, 2); // Test 3
    head->next->next = static_cast<t_list *>(calloc(sizeof(t_list), 1));
    testing(head, 3); // Test 4
    free(head->next->next);
    head->next->next = nullptr;
    testing(head, 2); // Test 5
    free(head->next);
    free(head);
	cout << endl;
}
