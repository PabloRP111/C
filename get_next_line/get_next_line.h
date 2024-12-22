/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:32:54 by prosas-p          #+#    #+#             */
/*   Updated: 2024/02/07 17:44:04 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

size_t	ft_strlen(const char *s, int boolxd);
char	*get_next_line(int fd);
char	*ft_strjoin(char **s1, char **s2);
char	*ft_strdup(char **s1);
char	*free_fail(char **s1, char **s2);
char	*ft_substr(char *s, unsigned int start, unsigned int len);

#endif