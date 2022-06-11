/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 02:17:00 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/10 22:24:03 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_init_exec(t_data *data)
{
	int	index;

	index = -1;
	while (++index < 2)
	{
		data->pid[index] = fork();
		if (data->pid[index] < 0)
			perror("pipex: error creating fork");
		else if (data->pid[index] == 0)
		{
			if (index == 0)
				ft_exec_first_cmd(data);
			else
				ft_exec_last_cmd(data);
		}
	}
	close(data->pipe_fd[READ]);
	close(data->pipe_fd[WRITE]);
	index = -1;
	while (++index < 2)
	{
		waitpid(data->pid[index], &data->child_exit_status, 0);
		data->exit_value = WEXITSTATUS(data->child_exit_status);
	}
}

static void	ft_init_pipe(t_data *data)
{
	if (pipe(data->pipe_fd) < 0)
	{
		perror("pipex: error creating pipe");
		ft_free_pipex(data);
		exit(EXIT_FAILURE);
	}
}

static void	ft_init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->infile = argv[1];
	data->outfile = argv[4];
	data->cmds = NULL;
	data->args = NULL;
	data->exit_value = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
	{
		if (argc > 5)
			ft_putendl_fd("pipex: Too many arguments", STDERR);
		else if (argc < 5)
			ft_putendl_fd("pipex: Too few arguments", STDERR);
		ft_putendl_fd(
			"Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>", STDERR);
		exit(EXIT_FAILURE);
	}
	ft_init_data(&data, argc, argv, envp);
	ft_argument_parser(&data);
	ft_init_pipe(&data);
	ft_init_exec(&data);
	ft_free_pipex(&data);
	return (data.exit_value);
}
