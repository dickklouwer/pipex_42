/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dickklouwer <tklouwer@student.codam.nl>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 08:16:50 by dickklouwer   #+#    #+#                 */
/*   Updated: 2022/12/14 08:17:10 by dickklouwer   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(2);
}
