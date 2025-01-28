/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:32:27 by doji              #+#    #+#             */
/*   Updated: 2024/04/13 18:19:53 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	_len(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	_chr(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*_dup(char *str)
{
	char	*new_str;
	int		len;

	if (!str)
		return (NULL);
	len = _len(str);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	_lcpy(new_str, str, len + 1);
	return (new_str);
}

int	_lcpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

char	*_join_free(char **s1, char *s2)
{
	char	*new_str;

	new_str = malloc(_len(*s1) + _len(s2) + 1);
	if (!new_str)
		return (NULL);
	if (*s1)
		_lcpy(new_str, *s1, _len(*s1) + 1);
	_lcpy(new_str + _len(*s1), s2, _len(s2) + 1);
	if (*s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	return (new_str);
}
