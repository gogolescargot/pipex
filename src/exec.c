/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 10:04:59 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/30 10:04:59 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exec_fullpath(char **args, char **envp)
{
	int	temp;

	execve(args[0], args, envp);
	temp = errno;
	if (check_folder(args[0]))
		(handle_error(args[0], 21), ft_arrayclear(args), exit(127));
	if (temp == 2)
		(handle_error(args[0], -1), ft_arrayclear(args), exit(127));
	else if (temp != 8)
		handle_error(args[0], temp);
	ft_arrayclear(args);
	exit(126);
}

void	exec(char *cmd, char **envp)
{
	char	**args;

	if (!cmd || !cmd[0])
		(handle_error("''", -1), exit(127));
	args = ft_split(cmd, ' ');
	if (!args)
		exit(127);
	if (ft_strnstr(args[0], "/", ft_strlen(cmd)))
		exec_fullpath(args, envp);
	if (check_path_cmd(args[0], envp) == 1)
		(handle_error(args[0], -1), ft_arrayclear(args), exit(127));
	else if (check_path_cmd(args[0], envp) == 2)
		(handle_error(args[0], 13), ft_arrayclear(args), exit(127));
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
		(handle_error(file, errno), close_fds(fd, -1), exit(1));
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
	close_fds(fd, -1);
}
