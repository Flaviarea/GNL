/* get_next_line_utils.c */
#include "get_next_line.h"
#include <stdlib.h>
#include <string.h> /* memcpy used if needed */

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t ret = 0;
	if (!s)
		return 0;
	while (s[ret])
		ret++;
	return (ret);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size1 + size2 + 1);
	if (!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return 1;
}

int	str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}


