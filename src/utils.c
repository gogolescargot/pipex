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

void	handle_error(char *str, int exit_code)
{
	if (exit_code == -1)
	{
		str = ft_strjoin(str, ": Command not found\n");
		ft_putstr_fd(str, 2);
		free(str);
	}
	else
	{
		errno = exit_code;
		perror(str);
	}
}

void	exec(char *cmd, char **envp)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		exit(127);
	execve(args[0], args, envp);
	if (check_path_cmd(args[0], envp) == 1)
		(handle_error(args[0], -1), ft_arrayclear(args), exit(127));
	else if (check_path_cmd(args[0], envp) == 2)
		(handle_error(args[0], 13),
			ft_arrayclear(args), exit(127));
	cmd = get_path_cmd(args[0], envp);
	execve(cmd, args, envp);
	handle_error("Exec", errno);
	ft_arrayclear(args);
	free(cmd);
	exit(127);
}

void	file(int *fd, char *file, bool mode)
{
	int	file_fd;

	if (mode)
		file_fd = open(file, O_RDONLY);
	else
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd < 0)
		(handle_error(file, errno), exit(1));
	if (mode)
	{
		dup2(file_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(file_fd, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
	}
	close(file_fd);
	close(fd[0]);
	close(fd[1]);
}
