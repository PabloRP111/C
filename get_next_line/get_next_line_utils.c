/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:30:35 by prosas-p          #+#    #+#             */
/*   Updated: 2024/02/07 17:34:25 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *s, unsigned int start, unsigned int len)
{
	char			*substr;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s, 0))
		return (NULL);
	if (len > (ft_strlen(s, 0) - start))
		len = (ft_strlen(s, 0) - start);
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (0);
	while (s[i] != '\0' && i < start)
		i++;
	while (s[i] != '\0' && j < len)
		substr[j++] = s[i++];
	substr[j] = '\0';
	return (substr);
}

char	*free_fail(char **s1, char **s2)
{
	if (*s1 != NULL)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 != NULL)
	{
		if (*s2 != NULL)
		{
			free(*s2);
			*s2 = NULL;
		}
	}
	return (NULL);
}

char	*ft_strjoin(char **s1, char **s2)
{
	char	*str;
	int		i;
	int		j;

	if (*s1 == NULL)
		return (ft_strdup(s2));
	i = 0;
	j = 0;
	str = (char *) malloc((ft_strlen(*s1, 0) + ft_strlen(*s2, 0) + 1));
	if (!str)
		return (free_fail(s1, s2));
	while (s1[0][i] != '\0')
	{
		str[i] = s1[0][i];
		i++;
	}
	while (s2[0][j] != '\0')
	{
		str[i + j] = s2[0][j];
		j++;
	}
	str[i + j] = '\0';
	free_fail(s1, NULL);
	return (str);
}

size_t	ft_strlen(const char *s, int boolxd)
{
	size_t	n;

	n = 0;
	if (s == NULL)
		return (0);
	if (boolxd == 0)
	{
		while (s[n] != '\0')
			n++;
	}
	else if (boolxd == 1)
	{
		while (s[n] != '\0')
		{
			if (s[n] == '\n')
				return (1);
			n++;
		}
		return (0);
	}
	return (n);
}

char	*ft_strdup(char **s1)
{
	size_t	len;
	char	*dup;
	int		i;

	len = 0;
	while (s1[0][len] != '\0')
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (free_fail(s1, NULL));
	i = 0;
	while (s1[0][i] != '\0')
	{
		dup[i] = s1[0][i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
