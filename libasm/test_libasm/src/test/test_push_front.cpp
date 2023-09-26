#include "libasm.h"

static void testing(t_list **head, uint64_t data, unsigned int expected_size) {
	static int x;
	bool result = true;
	ft_list_push_front(head, data);
	if (ft_list_size(*head) != expected_size)
		result = false;
	handle_result(result, &x);
	result = true;
	if ((*head)->content != data)
		result = false;
	handle_result(result, &x);
	cout.flush();
}

void test_push_front() {
	cout << YELLOW << "\tTesting ft_list_push_front:" << RESET << endl;
	auto head = static_cast<t_list *>(calloc(1, 16));
	char str[] = "Bonjour";
	testing(&head, 0, 2); //Test 0,1
	testing(&head, 1, 3); //Test 2,3
	free(head->next->next);
	head->next->next = nullptr;
	testing(&head, 2, 3); //Test 4,5
	testing(&head, (uint64_t)str, 4); //Test 6,7
	testing(&head, 0, 5); //Test 8,9
	t_list *tmp;
	while(head) {
		tmp = head->next;
		free(head);
		head = tmp;
	}
	cout << endl;
}
