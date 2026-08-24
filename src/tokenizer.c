#include "minishell.h"

int get_pipe_index(char *line_read)
{
    if (!line_read)
        return (-1);
    
    return (0);
}
t_token_type classify_token()
{
    return (TOKEN_WORD);
}
t_token *token_new(char *value, t_token_type type)
{
    if (!value)
        return (NULL);
    t_token *node = malloc(sizeof(t_token));
    if (!node)
        return (NULL);
    node->value = value;
    node->type = type;
    node->next = NULL;
    return (node);
}

void token_add_back(t_token **lst, t_token *new)
{
    t_token *current_node;

    current_node = *lst;
    if (!current_node || !new)
        return ;
    while (current_node->next != NULL)
        current_node = current_node->next;
    current_node->next = new;
}

void token_clear(t_token **lst)
{
    t_token *tmp;

    if (!lst)
        return ;
    while (*lst)
    {
        tmp = (*lst)->next;
        // if ((*lst)->value)
        //     free(((*lst)->value));
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}

int is_pipe(char c)
{
    return (c == '|');
}

int is_redir_out(char c)
{
    return (c == '>');
}
int is_redir_in(char c)
{
    return (c == '<');
}

int is_double_quote(char c)
{
    return (c == '"');
}

int is_single_quote(char c)
{
    return (c == '\'');
}

int is_delimiter(char c)
{
    return (c == ' ' || c == '\t');
}


/* function to capture token by token, need to cater for different cases */
char *capture_token(int *index, const char *s)
{
    int starts_at;
    int ends_at; /* ends_at always 1 index ahead (can prolly change the var name to token_len)*/
    int flag;
    char *word;
    
    starts_at = *index;
    flag = 0;
    while (s[*index] && flag == 0)
    {
        
        if (!ft_isalnum(s[*index]))
        {
            flag = 1;
            break ;
        }
        (*index)++;
    }
    ends_at = *index;
    word = ft_substr(s, starts_at, ends_at - starts_at);
    if (!word)
        return (NULL);
    return (word);
}

char *capture_double_quoted_token(int *index, const char *s)
{
    int start;
    int end;
    int count;
    char *word;

    count = 1;
    if (s[*index] == '"')
        (*index)++;
    start = *index;
    while (s[*index] && count == 1)
    {
        if (s[*index] == '"')
        {
            count--;
            break ;
        }
        (*index)++;
    }
    end = *index;
    word = ft_substr(s, start, end - start);
    if (!word)
        return (NULL);
    return (word);
    /* every quotations mark should be enclosed */
}

// t_char_type get_symbol(char c)
// {
//     if (c == '"')
//         return (DOUBLE_QUOTE);
//     else if (c == '\'')
//         return (SINGLE_QUOTE);
//     else if (c == ' ' || c == '\t')
//         return (DELIMITER);
//     else
//         return (NONE);
// }

int quote_is_balanced(int count)
{
    if (count == 2)
        return (1);
    else
        return (0);
}


// char *read_token(char *line, int *i)
// {
//     t_char_type char_type;
//     int found_delimiter = 0;
//     int delimiter_as_stopper = 0;
//     int single_quote = 1;
//     int double_quote = 1;
//     int start;
//     int end;
//     char *word;

//     int count;

//     count = 0;
//     start = *i;

//     while (line[*i] && !found_delimiter)
//     {
//         char_type = get_symbol(line[*i]);
//         if (char_type == SINGLE_QUOTE && single_quote)
//         {
//             count++;
//             double_quote = 0;
//         }
//         else if (char_type == DOUBLE_QUOTE && double_quote)
//         {
//             count++;
//             single_quote = 0;
//         }
//         else if (char_type == CHAR_NORMAL || quote_is_balanced(count))
//         {
//             delimiter_as_stopper = 1;
//             single_quote = 1;
//             double_quote = 1;
//             count = 0;
//         }
//         if (char_type == NONE)
//             delimiter_as_stopper = 1;
//         if (char_type == DELIMITER && delimiter_as_stopper)
//         {
//             found_delimiter = 1;
//             break ;
//         }
//         (*i)++;
//     }
//     end = *i;
//     word = ft_substr(line, start, end - start);
//     if (!word)
//         return NULL;
//     return (word);
// }

char *read_token(char *line, int *i)
{
    t_quote_state quote;
    int           start;
    int           end;
    char          *word;

    quote = QUOTE_NONE;
    start = *i;
    while (line[*i])
    {
        if (quote == QUOTE_NONE)
        {
            if (line[*i] == ' ' || line[*i] == '\t')
                break ;
            else if (line[*i] == '\'')
                quote = QUOTE_SINGLE;
            else if (line[*i] == '"')
                quote = QUOTE_DOUBLE;
        }
        else if (quote == QUOTE_SINGLE)
        {
            if (line[*i] == '\'')
                quote = QUOTE_NONE;
        }
        else if (quote == QUOTE_DOUBLE)
        {
            if (line[*i] == '"')
                quote = QUOTE_NONE;
        }
        (*i)++;
    }
    if (quote != QUOTE_NONE)
        return (NULL);
    end = *i;
    word = ft_substr(line, start, end - start);
    return (word);
}





void process_raw_line(char *line_read)
{
    printf("%s\n", line_read);
    if (!line_read)
        return ;
    /* For testing only, remove this later */
    int i;
    int len;
    char *word;

    len = ft_strlen(line_read);
    i = 0;
    while (line_read[i] && i < len)
    {
        word = read_token(line_read, &i);
        if (!word)
            return ;
        printf("%s\n", word);
        i++;
    }
    return ;
}