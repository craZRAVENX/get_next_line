/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealbayra <ealbayra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:27:35 by ealbayra          #+#    #+#             */
/*   Updated: 2022/12/28 02:45:33 by ealbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//sadece ilk satiri aliyor.
static char	*ft_get_line(char *remainder)
{
	int		i;
	char	*string;

	i = 0;
	if (!remainder[i])
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')// newline veya null olana kadar i'yi artirdik.
		i++;
	string = (char *)malloc(sizeof(char) * (i + 2)); // i + 2 null ve \n. (+2 vermemizin sebebi eger i '\n' gordugu icin durduysa onuda ekleyip null koymak gerekiyor)
	if (!string)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')// newline veya null olana kadar i'yi artirdik.
	{
		string[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')// eger newline var ise sona '\n' koyup i++ yapip oyle null koyuyoruz.
	{
		string[i] = remainder[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

//sıradaki satirda karakter kalmissa kalan karakterleri yolluyor.
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


//ilk satiri \n bulana kadar okur. buffer size in boyutuna
//gore siradaki satirdan karakter alabilir.
#include "stdio.h"
static char	*ft_read_to_left_str(int fd, char *remainder)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFF_SIZE + 1) * sizeof(char));//BUFF_SIZE islem yapmak icin bize ayrilmis alan. Verilen islem yapma boyutu kadar yer aciliyor.
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(remainder, '\n') && rd_bytes != 0)//new line veya okuyacak bir yer kalmadigi surece devam eder.
	{
		rd_bytes = read(fd, buff, BUFF_SIZE);// read her calistiginda okudugu dosyada SON KALDIGI yerden okuyor. BUFF_SIZE kadar okuyup buff'in icine yaziyor ve okudugu kismin uzunlugunu donduruyor. BAK (ornek exercise1.c)
		if (rd_bytes == -1)// hata durumu.
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';// read okudugunun uzunlugunu dondurdugu icin rd_bytes'i null koymak istedigimiz stringi bitirmek icin kullaniyoruz.
		remainder = ft_strjoin(remainder, buff);// remainder be buff'i birlestiriyoruz.
	}
	free(buff);// Buff'i artik kullanmadigimiz icin free'liyoruz.
	return (remainder);//BUFF_SIZE'in katinda dosyada okudugumuzu gonderiyoruz. (Bu kismi yaninda daha iyi aciklayacagim).
}


//read okudugu kadarini dondurur.
//read fonksiyonu fdnin icinde buffersize kadar okuyup buffa atıyor
//buffun uzunlugunu donduruyor.
char	*get_next_line(int fd)
{
	char		*string;
	static char	*remainder;

	if (fd < 0 || BUFF_SIZE <= 0)
		return (0);
	remainder = ft_read_to_left_str(fd, remainder);
	if (!remainder)
		return (NULL);
	string = ft_get_line(remainder);
	remainder = ft_new_left_str(remainder);
	return (string);
}

int main ()
{
	int fd = open("test.txt", O_RDONLY);
	// int resfd = open("result", O_RDWR);
	char string[5];
	char str[5];
	int a = read(fd, string, BUFF_SIZE);
	int b = read(fd, str, BUFF_SIZE);
	string[a] = '\0';
	str[b] = '\0';
	close(fd);
	printf("%s %s",string, str);
}