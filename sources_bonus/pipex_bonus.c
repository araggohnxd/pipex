/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 02:17:00 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/12 15:11:58 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
	{
		ft_putendl_fd("pipex: Too few arguments", STDERR);
		ft_putendl_fd(
			"Usage: ./pipex <infile> <cmd1> <cmd2>...<cmdn> <outfile>",
			STDERR);
		ft_putendl_fd(
			"      ./pipex here_doc <LIMITER> <cmd1> <cmd2>...<cmdn> <outfile>",
			STDERR);
		exit(EXIT_FAILURE);
	}
	else if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
		ft_init_here_doc(&data, argc, argv, envp);
	else
		ft_init_data(&data, argc, argv, envp);
	ft_argument_parser(&data);
	ft_init_pipe(&data);
	ft_init_pid(&data);
	ft_init_exec(&data);
	ft_free_pipex(&data);
	return (data.exit_value);
}
