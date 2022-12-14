/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 14:57:41 by tklouwer      #+#    #+#                 */
/*   Updated: 2022/12/14 09:34:20 by dickklouwer   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int arraylen(char **arr)
{
    int i;
    
    i = 0;
    while (arr[i])
    {
        i++;
    }
    return (i);
}

void    command_args(t_data *data, char **argv)
{
    int i = 0;
    char **tmp1;

    tmp1 = ft_split(argv[2], ' ');
    data->cmd1 = ft_calloc((arraylen(tmp1) + 1), sizeof(char *));
    if (!data->cmd1)
        error("Memory allocation error");
    while (tmp1[i])
    {
        data->cmd1[i] = tmp1[i];
        free(tmp1[i]);
        i++;
    }
    data->cmd2 = ft_strdup(argv[3]);
    free(tmp1);
}

int   path_search(t_data *data, char **envp)
{
    data->path = NULL;
    while(!data->path)
    {
        if (ft_strnstr(*envp, "PATH=", ft_strlen(*envp)))
        {
            data->path = ft_substr(*envp, 5, ft_strlen(*envp));
            return (EXIT_SUCCESS);
        }
        envp++;
    }
    return (EXIT_FAILURE);
}

void    path_vars(t_data *data)
{
    char    **tmp;
    int     i;

    i = 0;
    tmp = ft_split(data->path, ':');
    data->path_vars = ft_calloc((arraylen(tmp) + 1), sizeof(char *));
    if (!data->path_vars)
        error("Memory allocation error");
    while (tmp[i])
    {
        data->path_vars[i] = ft_strjoin(tmp[i], "/");
        if (access(data->path_vars[i], X_OK))
            error("Command not found");
        free(tmp[i]);
        i++;
    }
    free(tmp);
}

int parse_path(t_data *data, char **argv, char **envp)
{
    if (path_search(data, envp))
        exit(EXIT_FAILURE);
    command_args(data, argv);
    path_vars(data);
    return(EXIT_SUCCESS);
}
