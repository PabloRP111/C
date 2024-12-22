/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:16:35 by prosas-p          #+#    #+#             */
/*   Updated: 2024/02/07 20:00:50 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

unsigned int	ft_strlen_bonus(const char *s, int boolxd);
char			*get_next_line(int fd);
char			*ft_strjoin_bonus(char **s1, char **s2);
char			*ft_strdup_bonus(char **s1);
char			*free_fail_bonus(char **s1, char **s2);
char			*ft_substr_bonus(char *s, unsigned int start, unsigned int len);

#endif