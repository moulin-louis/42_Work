// CODE BY MOTERO

#include "libft.h"
#include <emmintrin.h>
#include <immintrin.h>

#if defined(__x86_64__) && defined(__SSE2__) && defined(__AVX__)

static inline void	align_memory_sse_asm(char **d, const char **s, size_t *n)
{
	asm	volatile
		(
			"movdqu  (%1), %%xmm0\n\t"
			"movdqu  %%xmm0, (%0)\n\t"
			"add     $16, %0\n\t"
			"add     $16, %1\n\t"
			"sub     $16, %2\n\t"
			: "+r"(*d), "+r"(*s), "+r"(*n)
			);
}

static inline void	align_memory_sse(char **d, const char **s, size_t *n)
{
	while ((((uintptr_t) * d & 0x1F) || ((uintptr_t) * s & 0x1F)) && *n >= 16)
		align_memory_sse_asm(d, s, n);
}

static inline void	copy_chunks_avx_asm(char *d,
	const char *s,
	size_t *num_chunks)
{
	asm	volatile (
			"1:                             \n\t"
			"vmovdqa  (%1), %%ymm0          \n\t"
			"vmovntdq  %%ymm0, (%0)         \n\t"
			"add      $32, %0              \n\t"
			"add      $32, %1              \n\t"
			"dec      %2                   \n\t"
			"jnz      1b                   \n\t"
			"sfence						   \n\t"
			: "+r"(d), "+r"(s), "+r"(*num_chunks)
			:
			: "memory", "ymm0");
}

static inline void	copy_chunks_avx(char *d, const char *s, size_t *n)
{
	size_t	num_chunks;

	num_chunks = (*n >> 5);
	copy_chunks_avx_asm(d, s, &num_chunks);
	*n %= 32;
}

void	*memcpy_avx(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s = src;

	d = dest;
	align_memory_sse(&d, &s, &n);
	if (!n)
		return (dest);
	copy_chunks_avx(d, s, &n);
	while (n--)
		*(d)++ = *(s)++;
	return (dest);
}

#endif
