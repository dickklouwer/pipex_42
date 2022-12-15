/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dickklouwer <tklouwer@student.codam.nl>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 08:16:50 by dickklouwer   #+#    #+#                 */
/*   Updated: 2022/12/15 11:10:03 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	error(char *str, int fd)
{
	ft_putendl_fd(str, fd);
	exit(2);
}
