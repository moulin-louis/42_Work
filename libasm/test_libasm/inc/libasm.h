#ifndef         LIBASM_H
#define         LIBASM_H
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <cerrno>
#include <ctime>
#include <chrono>
#include <iostream>
#include <csignal>
using namespace std;
using namespace std::chrono;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//Libasm functions
extern "C" {
	long			ft_read(int fd, char *buff, unsigned int size_buff);
    int             ft_strcmp(const char *s1, const char *s2);
    char            *ft_strcpy(char *dest, const char *src);
    char            *ft_strdup(const char *s);
    unsigned long   ft_strlen(const char *ptr);
	long			ft_write(int fd, char *buff, unsigned int size_buff);
    unsigned int    ft_list_size(t_list *head);
    void            ft_list_push_front(t_list **head, void *data);
	void			ft_remove_if(t_list **head, void *data_ref, int (*cmp)(void *, void *), void (*free_fct)(void *));
	void			ft_list_sort(t_list **begin_list, int (*cmp)(void *, void *));
	int 			ft_atoi_base(char *str, char *base);
}

// Test functions
void            test_read(void);
void            test_strlen(void);
void			perf_strlen(void);
void            test_strcmp(void);
void            test_strcpy(void);
void            test_strdup(void);
void            test_write(void);
void            test_list_size(void);
void			test_push_front(void);
void			test_remove_if(void);
void			test_list_sort(void);
void			test_atoi_base(void);
void            handle_result(bool result, int *);
void			ft_push_back(t_list **head, void *data);

#define        	get_time() duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()
#define         RED "\033[0;31m"
#define         GREEN "\033[0;32m"
#define         YELLOW "\033[0;33m"
#define         RESET "\033[0m"
#define			ITER_TEST 100000000

#endif
