/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:22:49 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/14 15:22:49 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int main(int argc, char **argv)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	char **args;
	int	input_file;
	int	output_file;
	char	*line;

	if (argc != 5)
		exit(1);

	if (pipe(fd) < 0)
	{
		perror("Pipe");
		exit(1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Fork");
		exit(1);
	}
		
	if (pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		input_file = open(argv[1], O_RDONLY);
		if (input_file < 0)
		{
			perror("Input file");
			exit(1);
		}
		dup2(input_file, 0);
		close(input_file);
		if (argv[2][0])
		{
			args = ft_split(argv[2], ' ');
			if (!args)
				return (1);
			if (!get_command(args[0]))
			{
				perror("Command");
				free_array(args);
				exit(1);
			}
			execve(get_command(args[0]), args, NULL);
			perror("Exec");
			exit(1);
		}
		else
		{
			while (1)
			{
				line = get_next_line(1);
				if (!line)
					break;
				ft_printf("%s", line);
				free(line);
			}
		}
	}
	
	close(fd[1]);
	pid2 = fork();

	if (pid2 < 0)
	{
		perror("Fork");
		return (1);
	}
	if (pid2 == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
		if (output_file < 0)
		{
			perror("Output file");
			exit(1);
		}
		dup2(output_file, 1);
		close(output_file);
		if (argv[3][0])
		{
			args = ft_split(argv[3], ' ');
			if (!get_command(args[0]))
			{
				free_array(args);
				perror("Command not found");
				exit(1);
			}
			execve(get_command(args[0]), args, NULL);
			perror("Exec");
			exit(0);
		}
		else
		{
			while (1)
			{
				line = get_next_line(0);
				if (!line)
					break;
				ft_printf("%s", line);
				free(line);
			}
		}
	}

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	close(fd[0]);

	return (0);
}
