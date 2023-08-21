#include "libasm.h"

void ft_push_back(t_list **head, void *data) {
	t_list *tmp = *head;
	t_list *node = (t_list *)calloc(1, sizeof(t_list));
	node->content = data;
	if (!tmp) {
		*head = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

static int cmp(void *a, void *b) {
    return ((a == b) ? 0 : 1);
}

static void free_node(void *ptr) {
	free(ptr);
}

static void testing(t_list *head, unsigned int expected_size) {
    static int x;
    bool result = ft_list_size(head) == expected_size;
    handle_result(result, &x);
    cout.flush();
}


void test_remove_if(void) {
    t_list *head = NULL;
    t_list *tmp = NULL;
    cout << YELLOW << "\tTesting ft_remove_if:" << RESET << endl;
    ft_push_back(&head, (void *)0);
    ft_push_back(&head, (void *)1);
    ft_push_back(&head, (void *)2);
    ft_remove_if(&head, (void *)0, cmp, free_node);
    testing(head, 2); // Test 0
    ft_remove_if(&head, (void *)2, cmp, free_node);
    testing(head, 1); // Test 1
    ft_remove_if(&head, (void *)1, cmp, free_node);
    testing(head, 0); // Test 2
    ft_remove_if(&head, (void *)0, cmp, free_node);
    testing(head, 0); // Test 3
    ft_push_back(&head, (void *)0);
    ft_push_back(&head, (void *)1);
    ft_push_back(&head, (void *)2);
    ft_remove_if(&head, (void *)2, cmp, free_node);
    testing(head, 2); // Test 4
    ft_remove_if(&head, (void *)1, cmp, free_node);
    testing(head, 1); // Test 5
    ft_remove_if(&head, (void *)0, cmp, free_node);
    testing(head, 0); // Test 6
    while (head) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
	cout << endl;
}
