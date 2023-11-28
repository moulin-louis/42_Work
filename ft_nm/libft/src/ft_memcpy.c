// CODE BY MOTERO

#include "libft.h"

// #if defined(__x86_64__) && defined(__SSE2__) && defined(__AVX__)

// void	*ft_memcpy(void *dst,
// 	const void *src,
// 	const size_t size)
// {
// 	const size_t	src_alignment_offset = ((uintptr_t)src & 0x1F);
// 	const size_t	dst_alignment_offset = ((uintptr_t)dst & 0x1F);

// 	if (!src || !dst)
// 		return (NULL);
// 	if (size > 32 && src_alignment_offset < 1 && dst_alignment_offset < 1)
// 		return (memcpy_avx(dst, src, size));
// 	return (memcpy_avx(dst, src, size));
// }

// #else 

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while (n && (((long)d % sizeof(long) != 0)
			|| ((long)s % sizeof(long) != 0)))
	{
		*d++ = *s++;
		n--;
	}
	while (n >= sizeof(long))
	{
		*(long *)d = *(const long *)s;
		d += sizeof(long);
		s += sizeof(long);
		n -= sizeof(long);
	}
	while (n)
	{
		*d++ = *s++;
		n--;
	}
	return (dest);
}
// #endif