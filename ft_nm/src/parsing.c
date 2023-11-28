//
// Created by loumouli on 11/24/23.
//

#include "ft_nm.h"

int32_t sections_push_back_64(t_nm* file, Elf64_Shdr* segment) {
  shdr_list_64_t* node = ft_calloc(sizeof(shdr_list_64_t), 1);
  if (node == NULL)
    return 1;
  node->section_header = segment;
  if (file->sections_list == NULL) {
    file->sections_list = node;
    return 0;
  }
  shdr_list_64_t* tmp = file->sections_list;
  while (tmp->next) {
    tmp = tmp->next;
  }
  tmp->next = node;
  return 0;
}

int32_t parse_sections_64(t_nm* file) {
  const uint64_t offset_section_table = file->elf64_header->e_shoff;
  uint8_t* sections_table = file->raw_data + offset_section_table;
  for (uint32_t idx = 0; idx < file->elf64_header->e_shnum * file->elf64_header->e_shentsize;
       idx += file->elf64_header->e_shentsize) {
    if (sections_push_back_64(file, (Elf64_Shdr *)(sections_table + idx))) {
      return 1;
    }
  }
  return 0;
}

int32_t check_elf_header_64(const Elf64_Ehdr* elf64Ehdr) {
  //check for the magic number
  if (ft_memcmp(elf64Ehdr, "\x7F" "ELF", 4) != 0) {
    return 1;
  }
  //check for the elf version
  if (elf64Ehdr->e_version != 1) {
    return 1;
  }
  //check for the elf type
  if (elf64Ehdr->e_type != ET_EXEC && elf64Ehdr->e_type != ET_DYN && elf64Ehdr->e_type != ET_REL) {
    return 1;
  }
  return 0;
}

int is_flags(const char* args) {
  const size_t len = ft_strlen(args);
  if (
    ft_strncmp(args, "-a", len) == 0 ||
    ft_strncmp(args, "--debug-syms", len) == 0 ||
    ft_strncmp(args, "-g", len) == 0 ||
    ft_strncmp(args, "--extern-only", len) == 0 ||
    ft_strncmp(args, "-u", len) == 0 ||
    ft_strncmp(args, "--undefined-only", len) == 0 ||
    ft_strncmp(args, "-r", len) == 0 ||
    ft_strncmp(args, "--reverse-sort", len) == 0 ||
    ft_strncmp(args, "-p", len) == 0 ||
    ft_strncmp(args, "--no-sort", len) == 0
  ) {
    return 1;
  }
  return 0;
}

void process_flags(const char* args, t_flags* flags) {
  const size_t len = ft_strlen(args);
  if (ft_strncmp(args, "-r", len) == 0 || ft_strncmp(args, "--reverse-sort", len) == 0) {
    flags->cmp_fn = sym_rev_strcmp;
  }
  if (ft_strncmp(args, "-p", len) == 0 || ft_strncmp(args, "--no-sort", len) == 0) {
    flags->cmp_fn = NULL;
  }
  if (ft_strncmp(args, "-a", len) == 0 || ft_strncmp(args, "--debug-syms", len) == 0) {
    flags->filter_fn = no_filter;
  }
  if (ft_strncmp(args, "-g", len) == 0 || ft_strncmp(args, "--extern-only", len) == 0) {
    flags->filter_fn = local_filter;
  }
  if (ft_strncmp(args, "-u", len) == 0 || ft_strncmp(args, "--undefined-only", len) == 0) {
    flags->filter_fn = defined_filter;
  }
}

int add_to_head(t_list** head, const char* args) {
  t_list* node = ft_calloc(sizeof(t_list), 1);
  if (node == NULL)
    return 1;
  node->content = ft_strdup(args);
  if (node->content == NULL) {
    free(node);
    return 1;
  }
  if (*head == NULL) {
    *head = node;
    return 0;
  }
  t_list* tmp = *head;
  while (tmp->next) {
    tmp = tmp->next;
  }
  tmp->next = node;
  return 0;
}

int parse_args(const int ac, char** av, t_list** head, t_flags* flags) {
  for (int idx = 1; idx < ac; idx++) {
    if (is_flags(av[idx])) {
      process_flags(av[idx], flags);
      continue;
    }
    if (add_to_head(head, av[idx]))
      return 1;
  }
  return 0;
}
