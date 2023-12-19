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
# include "../libft/inc/libft.h"

char	*get_command(char *s, char **envp);
void	free_array(char **array);
void	input_fd(int *fd, char **argv);
void	output_fd(int *fd, char **argv);
void	exec_child(char **argv, char **envp);
void	exec_parent(char **argv, char **envp);
void	print_output(int fd);

#endif