//
// Created by loumouli on 11/24/23.
//

#include "ft_nm.h"

Elf64_Shdr* get_header_type_64(const t_nm* file, const uint64_t type) {
  for (const shdr_list_64_t* tmp = file->sections_list; tmp != NULL; tmp = tmp->next) {
    if (tmp->section_header->sh_type == type) {
      return tmp->section_header;
    }
  }
  return NULL;
}

Elf64_Shdr* get_header_idx_64(const t_nm* file, const uint32_t shndx) {
  uint32_t idx = 0;
  for (const shdr_list_64_t* tmp = file->sections_list; tmp != NULL; tmp = tmp->next) {
    if (idx == shndx)
      return tmp->section_header;
    idx += 1;
  }
  return NULL;
}

int32_t add_sym_node(const t_nm* file, t_list** head, Elf64_Sym* data, const char* sym_str_tab,
                     const bool dyn_located) {
  t_list* node = malloc(sizeof(t_list));
  if (node == NULL)
    return 1;
  node->next = NULL;
  node->content = ft_calloc(sizeof(t_sym), 1);
  if (node->content == NULL) {
    free(node);
    return 1;
  }
  ((t_sym *)node->content)->name = ft_strdup(sym_str_tab + data->st_name);
  if (((t_sym *)node->content)->name == NULL) {
    free(node->content);
    free(node);
    return 1;
  }
  ((t_sym *)node->content)->len_name = ft_strlen(sym_str_tab + data->st_name);
  while (((t_sym *)node->content)->name[((t_sym *)node->content)->idx_start] == '_') {
    ((t_sym *)node->content)->idx_start += 1;
  }
  ((t_sym *)node->content)->dyn_located = dyn_located;
  ((t_sym *)node->content)->type = getSymType(file, data);
  ((t_sym *)node->content)->value = data->st_value;
  ((t_sym *)node->content)->sym = data;
  if (*head == NULL) {
    node->last_node = node;
    *head = node;
    return 0;
  }
  (*head)->last_node->next = node;
  (*head)->last_node = node;
  return 0;
}

t_list* craft_linked_list(
  const t_nm* file,
  const Elf64_Shdr* sym_tab_header,
  const Elf64_Shdr* sym_str_tab_header,
  const Elf64_Shdr* dyn_sym_header,
  const Elf64_Shdr* dyn_str_tab_header
) {
  const char* sym_str_tab = (char *)(file->raw_data + sym_str_tab_header->sh_offset);
  t_list* result = NULL;
  for (uint32_t i = 0; i < sym_tab_header->sh_size / sizeof(Elf64_Sym); i++) {
    Elf64_Sym* sym = (Elf64_Sym *)(file->raw_data + sym_tab_header->sh_offset + i * sizeof(Elf64_Sym));
    if (add_sym_node(file, &result, sym, sym_str_tab, false))
      return NULL;
  }
  if (dyn_sym_header == NULL)
    return result;
  const char* dyn_str_tab = (char *)(file->raw_data + dyn_str_tab_header->sh_offset);
  for (uint32_t i = 0; i < dyn_sym_header->sh_size / sizeof(Elf64_Sym); i++) {
    Elf64_Sym* sym = (Elf64_Sym *)(file->raw_data + dyn_sym_header->sh_offset + i * sizeof(Elf64_Sym));
    if (add_sym_node(file, &result, sym, dyn_str_tab, true))
      return NULL;
  }
  return result;
}

void display_symbols(const t_list* head) {
  for (const t_list* tmp = head; tmp != NULL; tmp = tmp->next) {
    if (((t_sym*)tmp->content)->type == 'U'
      || (((t_sym *)tmp->content)->value == 0x0 && ((t_sym *)tmp->content)->type != 'a' && ((t_sym *)tmp->content)->type!= 'T' && ((t_sym *)tmp->content)->type != 'b') )
      ft_putstr_fd("                ", 1);
    else {
      print_hex(((t_sym *)tmp->content)->value, 1);
    }
    ft_putchar_fd(' ', 1);
    ft_putchar_fd(((t_sym *)tmp->content)->type, 1);
    ft_putchar_fd(' ', 1);
    ft_putstr_fd(((t_sym *)tmp->content)->name, 1);
    ft_putchar_fd('\n', 1);
  }
}

void free_sym(void* sym) {
  free(((t_sym *)sym)->name);
  free(sym);
}

int is_empty_name(const void* ptr) {
  const t_sym* sym = (t_sym *)ptr;
  return sym->name[0] == '\0';
}

int32_t extract_symbols_64(const t_nm* file, const t_flags* flags) {
  const Elf64_Shdr* sym_tab_header = get_header_type_64(file, SHT_SYMTAB);
  if (!sym_tab_header)
    return print_error((const char *)file->path, "no symbols");
  const Elf64_Shdr* sym_str_tab_header = get_header_idx_64(file, sym_tab_header->sh_link);
  if (sym_str_tab_header == NULL)
    return print_error((const char *)file->path, "no symbols");
  const Elf64_Shdr* dyn_sym_header = get_header_type_64(file, SHT_DYNSYM);
  const Elf64_Shdr* dyn_str_tab_header = NULL;
  if (dyn_sym_header)
    dyn_str_tab_header = get_header_idx_64(file, dyn_sym_header->sh_link);
  t_list* head = craft_linked_list(file, sym_tab_header, sym_str_tab_header, dyn_sym_header, dyn_str_tab_header);
  filter_lst(&head, flags->filter_fn, free_sym);
  ft_lstsort(head, flags->cmp_fn);
  // ft_lstsort(head, sym_val_strcmp);
  display_symbols(head);
  ft_lstclear(&head, free_sym);
  return 0;
}
