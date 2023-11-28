// CODE BY MOTERO


#include "libft.h"
#include <emmintrin.h>
#include <immintrin.h>
#define AAA :

#if defined(__x86_64__) && defined(__SSE2__) && defined(__AVX__)

void	*memcpy_x86(void *dest __attribute__((unused)),
				const void *src __attribute__((unused)),
				size_t n __attribute__((unused)))
{
	asm volatile (
		"cld;"
		"mov %rdx, %rcx;"
		"rep movsb;"
	);
	return (dest);
}

#endif
