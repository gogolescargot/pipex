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

	if (argv[2][0])
	{
		args = ft_split(argv[2], ' ');
		if (!args)
			exit(1);
		command = get_command(args[0], envp);
		if (!command)
			(perror("Command not found"), free_array(args), exit(127));
		else if (access(command, X_OK) == -1)
			(perror("Permission denied"),
				free_array(args), free(command), exit(127));
		execve(command, args, envp);
		perror("Exec");
		free_array(args);
		free(command);
		exit(127);
	}
	print_output(1);
}

void	exec_parent(char **argv, char **envp)
{
	char	*command;
	char	**args;

	if (argv[3][0])
	{
		args = ft_split(argv[3], ' ');
		command = get_command(args[0], envp);
		if (!command)
			(perror("Command not found"),
				free_array(args), exit(127));
		else if (access(command, X_OK) == -1)
			(perror("Permission denied"),
				free_array(args), free(command), exit(127));
		execve(command, args, envp);
		perror("Exec");
		free_array(args);
		free(command);
		exit(127);
	}
	print_output(0);
}
