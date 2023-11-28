//
// Created by loumouli on 11/10/23.
//

#include "ft_nm.h"

uint32_t append_data_set(t_set* set, const void* data, const size_t len) {
  if (set->capacity < set->len + len) {
    const size_t new_capacity = (set->capacity + len) * 2;
    const void* new_data = realloc(set->data, new_capacity);
    if (new_data == NULL) {
      return 1;
    }
    set->capacity = new_capacity;
    set->data = (uint8_t *)new_data;
  }
  ft_memcpy(set->data + set->len, data, len);
  set->len += len;
  return 0;
}

//Read the entire file into memory
int32_t read_file(const char* path, uint8_t** result, size_t* len) {
  t_set set = {};
  const int file = open(path, O_RDONLY);
  if (file == -1) {
    return 1;
  }
  set.data = malloc(1024);
  if (set.data == NULL) {
    close(file);
    return 2;
  }
  set.capacity = 1024;
  while (1) {
    char buff[4096];
    const ssize_t retval = read(file, buff, sizeof(buff));
    if (retval == -1) {
      free(set.data);
      close(file);
      return 3;
    }
    if (retval == 0)
      break;
    if (append_data_set(&set, buff, retval)) {
      close(file);
      free(set.data);
      return 4;
    }
  }
  close(file);
  *result = set.data;
  *len = set.len;
  return 0;
}

int32_t print_error(const char* filename, const char* error) {
  ft_putstr_fd("ft_nm: ", 2);
  ft_putstr_fd(filename, 2);
  ft_putstr_fd(" ", 2);
  ft_putstr_fd(error, 2);
  ft_putstr_fd("\n", 2);
  return 1;
}

inline char hex_char(int value) {
  if (value >= 0 && value < 10) {
    return '0' + value;
  }
  else {
    return 'a' + (value - 10);
  }
}

// Function to convert an unsigned long to a hexadecimal string with leading zeros
inline void ulong_to_hex_str(unsigned long value, char* str, int len) {
  for (int i = len - 1; i >= 0; i--) {
    str[i] = hex_char(value % 16);
    value /= 16;
  }
  str[len] = '\0'; // Null-terminate the string
}

// Function to print an unsigned long in hexadecimal format
void print_hex(unsigned long value, int fd) {
  char hex_string[17]; // 16 characters for the hexadecimal representation + 1 for null terminator
  ft_memset(hex_string, '0', 17);
  ulong_to_hex_str(value, hex_string, 16);
  ft_putstr_fd(hex_string, fd);
}

// __attribute__((unused)) void hexdump(void* data, size_t len, int32_t row) {
//   if (row == 0) {
//     for (size_t i = 0; i < len; i++) {
//       printf("%02x ", ((uint8_t *)data)[i]);
//     }
//     printf("\n");
//     return;
//   }
//   for (size_t i = 0; i < len; i += row) {
//     for (size_t j = i; j < i + row; j++) {
//       if (j == len) {
//         break;
//       }
//       printf("%02x ", ((uint8_t *)data)[j]);
//     }
//     printf("\n");
//   }
//   printf("\n");
// }

// __attribute__((unused)) void asciidump(void* data, size_t len, uint32_t row) {
//   if (row == 0) {
//     for (size_t i = 0; i < len; i++) {
//       if (((uint8_t *)data)[i] >= 0x20 && ((uint8_t *)data)[i] <= 0x7e) {
//         fprintf(stdout, "%c", ((uint8_t *)data)[i]);
//       }
//       else {
//         fprintf(stdout, ".");
//       }
//     }
//     fprintf(stdout, "\n");
//     return;
//   }
//   for (size_t i = 0; i < len; i += row) {
//     for (size_t j = i; j < i + row; j++) {
//       if (j == len) {
//         break;
//       }
//       if (((uint8_t *)data)[j] >= 0x20 && ((uint8_t *)data)[j] <= 0x7e) {
//         fprintf(stdout, "%c", ((uint8_t *)data)[j]);
//       }
//       else {
//         fprintf(stdout, ".");
//       }
//     }
//     fprintf(stdout, "\n");
//   }
//   fprintf(stdout, "\n");
// }
