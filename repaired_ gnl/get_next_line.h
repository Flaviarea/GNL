#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>

/* API */
char	*get_next_line(int fd);

/* util prototypes (used across translation units) */
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
int	str_append_mem(char **s1, char *s2, size_t size2);
int	str_append_str(char **s1, char *s2);

#endif

