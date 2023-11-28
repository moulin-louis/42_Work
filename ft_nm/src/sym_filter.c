//
// Created by louis on 11/2/23.
//

#include "ft_nm.h"

int base_filter(const void* ptr) {
    const t_sym* node = (t_sym *)ptr;
    if (node->dyn_located)
        return 1;
    if (!node->name)
        return 1;
    if (node->name[0] == '\0')
        return 1;
    if (node->type == 'a')
        return 1;
    if (node->len_name <= 3)
        return 0;
    if (node->name[node->len_name - 2] == '.' && (
            node->name[node->len_name - 1] == 'c' || node->name[node->len_name - 1] == 'o'))
        return 1;
    return 0;
}

int no_filter(const void* ptr __attribute__((unused))) {
    const t_sym* node = (t_sym *)ptr;
    if (node->dyn_located)
        return 1;
    if (node->name[0] == '\0' && node->type == 'U')
        return 1;
    return 0;
}

int local_filter(const void* ptr) {
    const t_sym* node = (t_sym *)ptr;
    if (base_filter(node))
        return 1;
    if (ELF64_ST_BIND(node->sym->st_info) == STB_LOCAL)
        return 1;
    return 0;
}

int defined_filter(const void* ptr) {
    const t_sym* node = (t_sym *)ptr;
    if (base_filter(node))
        return 1;
    if (node->sym->st_shndx != SHN_UNDEF)
        return 1;
    return 0;
}

