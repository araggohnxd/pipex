/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:23:07 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/16 18:34:09 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	ft_putstr_fd("pipex: ", STDERR);
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
	ft_memfree((void *) &data->cmds[0]);
	ft_memfree((void *) &data->cmds[1]);
	ft_memfree((void *) &data->cmds);
	ft_free_split((void *) &data->args[0]);
	ft_free_split((void *) &data->args[1]);
	ft_memfree((void *) &data->args);
	if (data->infile_fd >= 0)
		close(data->infile_fd);
	if (data->outfile_fd >= 0)
		close(data->outfile_fd);
}
