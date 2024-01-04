/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:22:58 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/14 15:22:58 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/inc/libft.h"

void	pipex(char **argv, char **envp);
void	file(int *fd, char *file, bool mode);
void	exec(char *cmd, char **envp);

char	*get_path_cmd(char *cmd, char **envp);
int		check_path_cmd(char *cmd, char **envp);

int		wait_process(int pid);
bool	check_folder(char *path);
void	close_fds(int *fd, int file);
void	handle_error(char *str, int error_code);

int		pipex_bonus(char *cmd, char **envp, char *file, int state);
void	file_bonus(char *file, bool mode, int *fd, bool here_doc);
void	here_doc(char *limiter);
void	put_here_doc(char *limiter, int *fd);

#endif