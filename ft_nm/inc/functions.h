//
// Created by louis on 11/2/23.
//

#ifndef WOODY_WOODPACKER_FUNCTIONS_H
#define WOODY_WOODPACKER_FUNCTIONS_H

//I/O FUNCTION
int32_t read_file(const char *path, uint8_t** result, uint64_t* len);

int32_t save_new_file(const t_nm* ptr);
void print_hex(unsigned long value, int fd);
//PARSING FUNCTION
int32_t parse_program_headers_64(t_nm* bin);
int32_t parse_program_headers_32(t_nm* bin);

//DEBUG FUNCTIONS
void print_dyn_tag_64(const Elf64_Dyn* tag);
void print_dyn_tag_32(const Elf32_Dyn* tag);

__attribute__((unused)) void hexdump(void* data, uint64_t len, int32_t row);
__attribute__((unused)) void asciidump(void *data, size_t len, uint32_t row);
__attribute__((unused)) void print_elf_header_32(Elf32_Ehdr* header);
__attribute__((unused)) void print_elf_header_64(Elf64_Ehdr* header);

int32_t parse_sections_64(t_nm* file);
int32_t extract_symbols_64(const t_nm* file, const t_flags* flags);
int32_t check_elf_header_64(const Elf64_Ehdr* elf64Ehdr);
int parse_args(int ac, char** av, t_list** head, t_flags* flags);
int32_t print_error(const char *filename, const char *error);
char getSymType(const t_nm* file, const Elf64_Sym* sym);
Elf64_Shdr* get_header_idx_64(const t_nm* file, const uint32_t shndx);
Elf64_Shdr* get_header_type_64(const t_nm* file, const uint64_t type);
char		_64_print_SymType(const t_nm* file, Elf64_Sym* sym);
//COMPARE FN
int sym_strcmp(const void* ptr1, const void* ptr2);
int sym_rev_strcmp(const void* ptr1, const void* ptr2);
int sym_nocmp(const void* ptr1, const void* ptr2);
//FILTER FN
int base_filter(const void* ptr);
int no_filter(const void* ptr);
int local_filter(const void* ptr);
int defined_filter(const void* ptr);


#endif //WOODY_WOODPACKER_FUNCTIONS_H
