/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:16:19 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/19 20:16:19 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	handle_error(char *str, int error_code)
{
	if (error_code == -1)
	{
		str = ft_strjoin(str, ": Command not found\n");
		ft_putstr_fd(str, 2);
		free(str);
	}
	else
	{
		errno = error_code;
		perror(str);
	}
}

int	wait_process(int pid)
{
	int	status;
	int	ret_value;
	int	cur_pid;

	while (true)
	{
		cur_pid = wait(&status);
		if (cur_pid == -1)
			break ;
		if (cur_pid != pid)
			continue ;
		if (WIFEXITED(status))
			ret_value = WEXITSTATUS(status);
		else
			ret_value = (128 + WTERMSIG(status));
	}
	return (ret_value);
}

void	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
