#include "minishell.h"

char **freed_up_env(int index, char **env)
{
    while (index >= 0)
        free(env[--index]);
    return (NULL);
}

void freed_up_existing_env(char **existing_env)
{
    int i;

    if (!existing_env)
        return ;
    i = 0;
    while (existing_env[i])
        free(existing_env[i++]);
    existing_env = NULL;
}

char **init_env_variable(char **envp)
{
    int i;
    int j;
    char **env_variable;

    if (!envp)
        return (NULL);
    i = 0;
    while (envp[i])
        i++;
    env_variable = malloc(sizeof(char *) * (i + 1));
    if (!env_variable)
        return (NULL);
    j = 0;
    while (envp[j])
    {
        env_variable[j] = ft_strdup(envp[j]);
        if (!env_variable[j])
            return (freed_up_env(j, env_variable));
        j++;
    }
    env_variable[j] = NULL;
    return (env_variable);
}

char **add_new_variable(char **existing_env, char *new_var)
{
    int i;
    int j;
    char **new_env;

    if (!new_var)
        return (NULL);
    i = 0;
    while (existing_env[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return (NULL);
    j = 0;
    while (existing_env[j])
    {
        new_env[j] = ft_strdup(existing_env[j]);
        if (!new_env[j])
            return (freed_up_env(j, &new_env[j]));
        j++;
    }
    new_env[j] = ft_strdup(new_var);
    if (!new_env[j])
        return (freed_up_env(j, &new_env[j]));
    new_env[++j] = NULL;
    freed_up_existing_env(existing_env);
    return (new_env);
}

// int get_target_variable_index(char **existing_env, char **var)
// {
//     int len;
//     int i;

//     len = ft_strlen(var);
//     if (!*existing_env || !var)
//         return (NULL);
//     i = 0;
//     while (existing_env[i])
//     {
//         if (ft_strncmp(existing_env[i], var, len) == 0
//             && existing_env[i][len] == '=')
//         {
//             return (i);
//         }
//         i++;
//     }
//     return (-1);
// }

// char **remove_variable(char **existing_env, char *var)
// {
//     int len;
//     int i;
//     int remove_at;
//     char **new_env;

//     if (!*existing_env || !var)
//         return (NULL);
//     len = ft_strlen(var);
//     i = 0;
//     remove_at = get_target_variable_index(existing_env, var);
//     if (remove_at == -1)
//         new_env = ft_strdup("");
//     else
//     {
        
//     }
//     /* get the index here */
    
// }

// char **update_variable(char **existing_var, char *var)
// {

// }
