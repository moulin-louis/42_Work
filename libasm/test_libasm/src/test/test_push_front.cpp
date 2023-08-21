#include "libasm.h"

static void testing(t_list **head, void *data, unsigned int expected_size) {
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

void test_push_front(void) {
	cout << YELLOW << "\tTesting ft_list_push_front:" << RESET << endl;
	t_list *head = static_cast<t_list *>(calloc(1, 16));
	char str[] = "Bonjour";
	testing(&head, nullptr, 2); //Test 0,1
	testing(&head, reinterpret_cast<void *>(1), 3); //Test 2,3
	free(head->next->next);
	head->next->next = nullptr;
	testing(&head, reinterpret_cast<void *>(2), 3); //Test 4,5
	testing(&head, static_cast<void *>(str), 4); //Test 6,7
	testing(&head, nullptr, 5); //Test 8,9
	t_list *tmp;
	while(head) {
		tmp = head->next;
		free(head);
		head = tmp;
	}
	cout << endl;
}
