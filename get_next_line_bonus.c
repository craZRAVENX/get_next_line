/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealbayra <ealbayra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:28:51 by ealbayra          #+#    #+#             */
/*   Updated: 2022/12/28 03:02:19 by ealbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_new_left_str(char *remainder)
{
	int		i;
	int		i2;
	char	*string;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')// New line veya null olana kadar i'yi arttiriyoruz.
		i++;
	if (!remainder[i])// remainder null ise okuyacak bisey kalmadi anlamina geliyor ve null return ediyoruz.
	{
		free(remainder);
		return (NULL);
	}
	string = (char *)malloc(sizeof(char) * (ft_strlen(remainder) - i + 1));// Newline'dan sonrasi icin bir alan aciyoruz.
	if (!string)
		return (NULL);
	i++;
	i2 = 0;
	while (remainder[i])// newline'dan sonrasini string'in icine kayit ediyoruz.
		string[i2++] = remainder[i++];
	string[i2] = '\0';
	free(remainder);// remainder'in icindekini newline'a kadar kullandik, newline'dan sonrasini string'in icine kayit ettik. remainder ile isimiz kalmadi.
	return (string);// newline'dan sonrasini return ettik.
}

static char	*ft_get_line(char *remainder)
{
	int		i;
	char	*string;

	i = 0;
	if (!remainder[i])
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	string = (char *)malloc(sizeof(char) * (i + 2));
	if (!string)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		string[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
	{
		string[i] = remainder[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

static char	*ft_read_to_left_str(int fd, char *remainder)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFF_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(remainder, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFF_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		remainder = ft_strjoin(remainder, buff);
	}
	free(buff);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*string;
	static char	*remainder[4096]; // bir metnin max 4095 olabilir (+1 null icin) 
	//buna maping deniyor. her fd birbirinden farkli oldugu icin bir string array'i olusturuyoruz ve index olarak fd'lerini veriyoruz. Bonusun tek farki bu. her bireysel fd icin farkli bir yerimiz oluyor.
	if (fd < 0 || BUFF_SIZE <= 0)
		return (0);
	remainder[fd] = ft_read_to_left_str(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	string = ft_get_line(remainder[fd]);
	remainder[fd] = ft_new_left_str(remainder[fd]);
	return (string);
}

#include <stdio.h>
int main()
{
	int fd[3];
	fd[0] = open("a.txt",O_RDONLY);
	printf("%s", get_next_line(fd[0]));
	fd[1] = open("b.txt",O_RDONLY);
	printf("%s", get_next_line(fd[1]));
	fd[2] = open("c.txt",O_RDONLY);
	printf("%s", get_next_line(fd[2]));
	printf("%s", get_next_line(3));
} 