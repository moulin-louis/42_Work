//
// Created by louis on 11/1/23.
//

#ifndef WOODY_WOODPACKER_WOODY_H
#define WOODY_WOODPACKER_WOODY_H

#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include <signal.h>

#include "libft.h"

typedef struct shdr_64_s {
  Elf64_Shdr* section_header;
  struct shdr_64_s* next;
} shdr_list_64_t;

typedef struct {
  uint8_t *path;
  uint8_t* raw_data;
  size_t data_len;
  //64 bits
  Elf64_Ehdr* elf64_header;
  shdr_list_64_t *sections_list;
  //32 bits
  Elf32_Ehdr* elf32_header;
} t_nm;

typedef struct {
  char *name;
  size_t len_name;
  size_t idx_start;
  char type;
  uint64_t value;
  Elf64_Sym* sym;
  bool dyn_located;
} t_sym;

typedef int (*CmpFn)(const void* node1, const void* node2);
typedef int (*FilterFn)(const void* ptr);

typedef struct {
  CmpFn cmp_fn;
  FilterFn filter_fn;
} t_flags;

typedef struct {
  uint8_t* data;
  size_t len;
  size_t capacity;
} t_set;


#define ALIGN_DOWN(x, align) ((x) & ~(align - 1))
#define ALIGN_UP(x, align) ALIGN_DOWN((x) + (align) - 1, (align)) ? ALIGN_DOWN((x) + (align) - 1, (align)) : (align)

//define red/green/yellow and reset ansi color
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_RESET   "\x1b[0m"
//define emoji
#define ANSI_CHECK "\xE2\x9C\x94"
#define ANSI_CROSS "\xE2\x9D\x8C"

//prototype of all functions
#include "functions.h"

#endif //WOODY_WOODPACKER_WOODY_H
