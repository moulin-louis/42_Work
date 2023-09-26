#include "libasm.h"

t_list *init(int mode) {
    t_list *result = nullptr;
    switch (mode) {
        case 1:
            ft_list_push_front(&result, 42);
            ft_list_push_front(&result, 44);
            break;
        case 2:
            ft_list_push_front(&result, (uint64_t)strdup("A"));
            ft_list_push_front(&result, (uint64_t)strdup("B"));
            ft_list_push_front(&result, (uint64_t)strdup("C"));
            ft_list_push_front(&result, (uint64_t)strdup("D"));
            ft_list_push_front(&result, (uint64_t)strdup("E"));
            break;
        case 3:
            ft_list_push_front(&result, 0);
            ft_list_push_front(&result, 1);
            ft_list_push_front(&result, 2);
            ft_list_push_front(&result, 3);
            ft_list_push_front(&result, 4);
            break ;
    }
    return (result);
}

void clean(int mode, t_list *head) {
    switch (mode) {
        case 1:
            while(head) {
                t_list *tmp = head->next;
                free(head);
                head = tmp;
            }
            break;
        case 2:
            while(head) {
                t_list *tmp = head->next;
                free((void *)head->content);
                free(head);
                head = tmp;
            }
    }
}

void testing(t_list *head, int(*cmp)(uint64_t, uint64_t), uint expected_size) {
	static int x;
	bool result = ft_list_size(head) == expected_size;
	handle_result(result, &x);
	result = true;
	while (head) {
		if (head->next) {
			if (cmp(head->content, head->next->content) > 0) {
				result = false;
				handle_result(result, &x);
				break ;
			}
		}
		head = head->next;
	}
	handle_result(result, &x);
	cout.flush();
}

void print(int mode, t_list *head) {
  printf("\n");
  switch (mode) {
    case 1:
      while (head) {
        printf("- %lu\n", head->content);
        head = head->next;
      }
      break;
    case 2:
      while (head) {
        printf("- %s\n", (char*)head->content);
        head = head->next;
      }
      break;
  }
}

int wrap_strcmp(uint64_t s1, uint64_t s2) {
  const char *str1 = (const char *)s1;
  const char *str2 = (const char *)s2;
  int result = strcmp(str1, str2);
	return (result);
}

int cmp_nbr(uint64_t n1, uint64_t n2) {
    return (n1 - n2);
}

void test_list_sort() {
	cout << YELLOW << "\tTesting test_list_sort:" << RESET << endl;
    {
        t_list *head = init(1);
        ft_list_sort(&head, cmp_nbr);
        testing(head, cmp_nbr, 2);
        clean(1, head);
    }
    {
        t_list *head = init(2);
        ft_list_sort(&head, wrap_strcmp);
        testing(head, wrap_strcmp, 5); //test 0-1
        clean(2, head);
    }
    {
        t_list *head = init(3);
        ft_list_sort(&head, cmp_nbr);
        testing(head, cmp_nbr, 5); //test 2-3
        clean(1, head);
    }
	cout << endl;
}

