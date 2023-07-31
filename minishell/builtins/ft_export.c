
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:22:32 by villemuston       #+#    #+#             */
/*   Updated: 2023/07/24 15:21:02 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int len_of_env(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
        i++;
    return (i);
}

void    sort(char **argv, int len)
{
    int     i;
    int     j;
    char    *temp;

    j = 0;
    while (argv && j == 0)
    {
        j = 1;
        i = 0;
        while (i < len - 1)
        {
            if (ft_strcmp(argv[i], argv[i + 1]) > 0)
            {
                temp = argv[i];
                argv[i] = argv[i + 1];
                argv[i + 1] = temp;
                j = 0; 
            }
            i++;
        }
        len--;
    }
}

void    print_env(t_env *env)
{
    int     i;
    char    **list;
    char    *str;

    i = 0;
    str = str_env(env);
    list = ft_split(str, '\n');
    sort(list, len_of_env(list));
    while (list[i])
    {
        printf("declare -x ");
        printf("%s\n", list[i]);
        i++;
    }
    free(str);
    free(list);
}

int valid_env(char *src)
{
    int i;

    i = 0;
    if (ft_isdigit(src[i]) == 0)
        return (1);
    while (src[i] && src[i] != '=')
    {
        if (ft_isalnum(src[i]) == 1)
            return (-1);
        i++;
    }
    if (src[i] != '=')
        return (2);
    return (0);
}

int ft_export(char **argv, t_env *env)
{
    int new;
    int error;

    new = 0;
    if (!argv[1])
    {
        print_env(env);
        return (0);
    }
    else
    {
        error = valid_env(argv[1]);
        if (error == 2)
            new = 1;
        else
            new = in_env(env, argv[1]);
        if (new == 0)
        {
            if (error == 0)
                add_env(argv[1], env);
        }
    }
    return (0);
}