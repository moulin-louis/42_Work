//
// Created by loumouli on 11/26/23.
//

#include "libft.h"

void filter_lst(t_list **head, int (*filter)(const void*), void (*del)(void *)) {
  t_list *current = *head;
  t_list *prev = NULL;

  while (current != NULL) {
    if (filter(current->content)) {
      if (prev == NULL) {
        *head = current->next;
        del(current->content);
        free(current);
        current = *head;
      } else {
        t_list *temp = current;
        prev->next = current->next;
        current = current->next;
        del(temp->content);
        free(temp);
      }
    } else {
      prev = current;
      current = current->next;
    }
  }
}
