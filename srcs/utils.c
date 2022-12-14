/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dickklouwer <tklouwer@student.codam.nl>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 09:52:16 by dickklouwer   #+#    #+#                 */
/*   Updated: 2022/12/14 16:02:03 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/pipex.h"

// int open_fd(t_data *data, char **argv)
// {
// 	data->fd[0] = open(argv[1], O_RDONLY);
// 	data->fd[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
// 	if (data->fd[0] < 0 || data->fd[1] < 0)
// 	{
// 		close(data->fd[0]);
// 		close(data->fd[1]);
// 		return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }
