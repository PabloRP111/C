/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_utils_pipex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 08:47:33 by prosas-p          #+#    #+#             */
/*   Updated: 2024/08/01 13:20:29 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_error2(char *error_message, int fd, int fd2)
{
	perror(error_message);
	close(fd);
	close(fd2);
	exit(EXIT_FAILURE);
}

void	dup_error3(char *error_message, int fd, int fd2, int fd3)
{
	perror(error_message);
	close(fd);
	close(fd2);
	close(fd3);
	exit(EXIT_FAILURE);
}

void	close2(int fd, int fd2)
{
	close(fd);
	close(fd2);
}

void	close3(int fd, int fd2, int fd3)
{
	close(fd);
	close(fd2);
	close(fd3);
	exit(EXIT_FAILURE);
}

void	exit_error(char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}
