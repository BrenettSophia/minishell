#include "minishell.h"

char        *replace_dollar_que_into_code(char *str, t_untils *untils)
{
    t_rdqic r;

    if (str == 0)
        return (str);
    if (str[0] == '~' && str[1] == 0)
    {
        ft_free(str);
        return(my_get_env("HOME", untils->env));
    }
    while (1)
    {
        if ((r.start = ft_strnstr(str, "$?+?", ft_strlen(str))) == 0)
            return (str);
        r.first_part = ft_substr(str, 0, ft_strlen(str) - ft_strlen(r.start));
        r.second_part = ft_substr(str, ft_strlen(str) - ft_strlen(r.start) + 4, ft_strlen(str));
        r.tmp = ft_itoa(untils->status);
        r.temporary = ft_strjoin(r.first_part, r.tmp);
        ft_free(r.tmp);
        ft_free(r.first_part);
        ft_free(str);
        str = ft_strjoin(r.temporary, r.second_part);
        ft_free(r.temporary);
        ft_free(r.second_part);
    }
    return (str);
}
