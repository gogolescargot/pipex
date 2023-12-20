/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:24:28 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/17 21:24:28 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exec_child(char **argv, char **envp)
{
	char	**args;
	char	*command;

	args = ft_split(argv[2], ' ');
	if (!args)
		exit(127);
	execve(args[0], args, envp);
	if (check_path_cmd(args[0], envp) == 1)
		(handle_error(args[0], -1), free_array(args), exit(127));
	else if (check_path_cmd(args[0], envp) == 2)
		(handle_error(args[0], 13),
			free_array(args), exit(127));
	command = get_path_cmd(args[0], envp);
	execve(command, args, envp);
	handle_error("Exec", errno);
	free_array(args);
	free(command);
	exit(127);
}

void	exec_parent(char **argv, char **envp)
{
	char	*command;
	char	**args;

	args = ft_split(argv[3], ' ');
	if (!args)
		exit(127);
	execve(args[0], args, envp);
	if (check_path_cmd(args[0], envp) == 1)
		(handle_error(args[0], -1), free_array(args), exit(127));
	else if (check_path_cmd(args[0], envp) == 2)
		(handle_error(args[0], 13),
			free_array(args), exit(127));
	command = get_path_cmd(args[0], envp);
	execve(command, args, envp);
	handle_error("Exec", errno);
	free_array(args);
	free(command);
	exit(127);
}
