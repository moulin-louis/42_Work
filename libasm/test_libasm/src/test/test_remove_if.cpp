#include "libasm.h"

void ft_push_back(t_list **head, uint64_t data) {
	t_list *tmp = *head;
	auto node = (t_list *)calloc(1, sizeof(t_list));
	node->content = data;
	if (!tmp) {
		*head = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int cmp(uint64_t a, uint64_t b) {
    return  (a == b ? 0 : a - b);
}

void free_data(uint64_t ptr) {
  (void)ptr;
}

void testing(t_list *head, unsigned int expected_size) {
    static int x;
    bool result = ft_list_size(head) == expected_size;
    handle_result(result, &x);
    cout.flush();
}

void init_trip(int arr[]) {
  for (int i = 0; i < 42; i++) {
    arr[i] = 2;
  }
}

void wrap_list_remove_if(t_list **begin_list, uint64_t data_ref, int (*cmp)(uint64_t, uint64_t),
                         void (*free_fct)(uint64_t))
{
  int tripouille[42] = {0};
  init_trip(tripouille);
  ft_list_remove_if(begin_list, data_ref, cmp, free_fct);
  tripouille[41] = 42;
}

void test_remove_if() {
  t_list *head = nullptr;
  char c = 0;
  wrap_list_remove_if(&head, (uint64_t)&c, cmp, free_data);
  ft_push_back(&head, 0);
  ft_push_back(&head, 1);
  ft_push_back(&head, 2);
  ft_list_remove_if(&head, 0, cmp, free_data);
  testing(head, 2); // Test 0

  ft_list_remove_if(&head, 2, cmp, free_data);
  testing(head, 1); // Test 1

  ft_list_remove_if(&head, 1, cmp, free_data);
  testing(head, 0); // Test 2

  ft_list_remove_if(&head, 0, cmp, free_data);
  testing(head, 0); // Test 3

  ft_push_back(&head, 0);
  ft_push_back(&head, 1);
  ft_push_back(&head, 2);
  ft_list_remove_if(&head, 2, cmp, free_data);
  testing(head, 2); // Test 4

  ft_list_remove_if(&head, 1, cmp, free_data);
  testing(head, 1); // Test 5

  ft_list_remove_if(&head, 0, cmp, free_data);
  testing(head, 0); // Test 6

  while (head) {
    t_list *tmp = head->next;
    free(head);
    head = tmp;
  }
  cout << endl;
}
