/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 07:47:11 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/22 07:47:11 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	pipex_bonus(char *cmd, char **envp, char *file, int state)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		(handle_error("Pipe", errno), exit(1));
	pid = fork();
	if (pid < 0)
		(handle_error("Fork", errno), exit(1));
	if (pid == 0)
	{
		if (state <= 0)
		{
			if (state == -1)
				file_bonus(file, true, fd, false);
			dup2(fd[1], STDOUT_FILENO);
			close_fds(fd);
		}
		else
			file_bonus(file, false, fd, (state == 2));
		close_fds(fd);
		exec(cmd, envp);
	}
	dup2(fd[0], STDIN_FILENO);
	close_fds(fd);
	return (pid);
}

void	file_bonus(char *file, bool mode, int *fd, bool here_doc)
{
	int	file_fd;

	if (mode)
		file_fd = open(file, O_RDONLY);
	else if (!mode && !here_doc)
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file_fd < 0 && mode)
		(handle_error(file, errno), close_fds(fd), exit(1));
	else if (file_fd < 0 && !mode)
		(handle_error(file, errno), close_fds(fd), exit(1));
	if (mode)
	{
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
	}
	else
	{
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
	}
}

void	put_here_doc(char *limiter, int *fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, ft_strlen(limiter))
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			get_next_line(-1);
			close_fds(fd);
			exit(0);
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	get_next_line(-1);
	close_fds(fd);
}

void	here_doc(char **argv)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		(handle_error("Pipe", errno), exit(1));
	pid = fork();
	if (pid < 0)
		(handle_error("Fork", errno), exit(1));
	if (pid == 0)
		put_here_doc(argv[2], fd);
	else
	{
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
		close_fds(fd);
	}
}
