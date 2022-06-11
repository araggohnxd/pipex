/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 02:17:00 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/11 05:39:21 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_close_parent_pipe(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->pipe_count)
	{
		close(data->pipe_fd[index][READ]);
		close(data->pipe_fd[index][WRITE]);
	}
}

static void	ft_init_exec(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->cmd_count)
	{
		data->pid[index] = fork();
		if (data->pid[index] < 0)
			ft_set_perror(data, EXIT_FAILURE, "error creating fork");
		else if (data->pid[index] == 0)
		{
			if (index == 0)
				ft_exec_first_cmd(data);
			else if (index < (data->cmd_count - 1))
				ft_exec_nth_cmd(data, index);
			else
				ft_exec_last_cmd(data);
		}
	}
	ft_close_parent_pipe(data);
	index = -1;
	while (++index < data->cmd_count)
	{
		waitpid(data->pid[index], &data->child_exit_status, 0);
		data->exit_value = WEXITSTATUS(data->child_exit_status);
	}
}

static void	ft_init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->cmds = NULL;
	data->args = NULL;
	data->pipe_fd = NULL;
	data->pid = NULL;
	data->cmd_count = argc - 3;
	data->pipe_count = data->cmd_count - 1;
	data->exit_value = 0;
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
	{
		ft_putendl_fd("pipex: Too few arguments", STDERR);
		ft_putendl_fd(
			"Usage: ./pipex <infile> <cmd1> <cmd2> ... <cmdn> <outfile>",
			STDERR);
		exit(EXIT_FAILURE);
	}
	ft_init_data(&data, argc, argv, envp);
	ft_argument_parser(&data);
	ft_init_pipe(&data);
	ft_init_pid(&data);
	ft_init_exec(&data);
	ft_free_pipex(&data);
	return (data.exit_value);
}
