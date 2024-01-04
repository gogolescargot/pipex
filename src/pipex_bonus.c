/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:38:40 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/22 03:38:40 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	state;

	state = 1;
	if (argc < 5)
		(handle_error("Bad number of parameters", 1), exit(1));
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		i = 3;
		if (argc < 6)
			(handle_error("Bad number of parameters", 1), exit(1));
		state = 2;
		here_doc(argv[2]);
	}
	else
		i = 2;
	pipex_bonus(argv[i], envp, argv[1], state * -1);
	while (++i < argc - 2)
		pipex_bonus(argv[i], envp, argv[1], 0);
	return (wait_process(pipex_bonus(argv[argc - 2], envp
				, argv[argc - 1], state)));
}
