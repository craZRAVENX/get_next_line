/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_outils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealbayra <ealbayra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:27:47 by ealbayra          #+#    #+#             */
/*   Updated: 2022/12/28 01:48:51 by ealbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *c)//biliyorsun
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)//biliyorsun
{
	char	*ptr;
	size_t	i;

	ptr = (char *)malloc(sizeof(*str) * (ft_strlen(str) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)//biliyorsun
{
	int	s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	while (s_len >= 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
		s_len--;
	}
	return (NULL);
}

char	*ft_strjoin(const char *s1, char const *s2)//biliyorsun.
{
	char	*s3;
	char	*tmp_s3;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	while (s1[i])
		i += 1;
	while (s2[j])
		j += 1;
	if (!s1 || !s2 || !(s3 = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	tmp_s3 = s3;
	while (*s1 != '\0')
		*tmp_s3++ = *s1++;
	while (*s2 != '\0')
		*tmp_s3++ = *s2++;
	*tmp_s3 = '\0';
	return (s3);
}
