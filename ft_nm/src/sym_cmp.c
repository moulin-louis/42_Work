//
// Created by louis on 11/2/23.
//
#include <mm_malloc.h>
#include <stdnoreturn.h>

#include "ft_nm.h"

inline int sym_nocmp(const void* ptr1 __attribute__((unused)), const void* ptr2 __attribute__((unused))) {
  return 0;
}

char do_nothing(char c) {
  return c;
}

int sym_strcmp(const void* ptr1, const void* ptr2) {
  const t_sym* node1 = (t_sym *)ptr1;
  const t_sym* node2 = (t_sym *)ptr2;
  return ft_strcmp(node1->name, node2->name);
}

int sym_rev_strcmp(const void* ptr1, const void* ptr2) {
  const t_sym* node1 = (t_sym *)ptr1;
  const t_sym* node2 = (t_sym *)ptr2;
  return ft_strcmp(node2->name, node1->name);
}
