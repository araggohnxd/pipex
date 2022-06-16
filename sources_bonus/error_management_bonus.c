/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:23:07 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/16 18:37:10 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_error_file(char *str)
{
	perror(str);
	return (0);
}

static int	ft_error_command(char *str)
{
	ft_putstr_fd(str, STDERR);
	ft_putendl_fd(": Command not found", STDERR);
	return (0);
}

int	ft_set_perror(t_data *data, int error_id, char *str)
{
	ft_putstr_fd("pipex_bonus: ", STDERR);
	if (error_id == ERR_CMD_NOT_FOUND)
		return (ft_error_command(str));
	else if (error_id == ERR_IO_FILE)
		return (ft_error_file(str));
	else
		perror(str);
	ft_free_pipex(data);
	exit(error_id);
	return (error_id);
}

void	ft_free_pipex(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->cmd_count)
	{
		ft_memfree((void *) &data->cmds[index]);
		ft_free_split((void *) &data->args[index]);
	}
	ft_memfree((void *) &data->cmds);
	ft_memfree((void *) &data->args);
	ft_memfree((void *) &data->pid);
	ft_free_split((void *) &data->pipe_fd);
	if (data->infile_fd >= 0)
		close(data->infile_fd);
	if (data->outfile_fd >= 0)
		close(data->outfile_fd);
}
