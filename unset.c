#include "minishell.h"

static int	compare_to_equal(char *s1, char *s2)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '=' && s2[i] == '\0')
			return (1);
		if (s1[i] != s2[i])
			return (0); //подали уникальный ключ
		if (s1[i] == '=' && s2[i] == '\0')
			return (1); //ключи одинаковые
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

static int	check_name1(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[0])) && str[0] != '_')
		return (1);
	while (str[i] != '\0')
	{
		if (!(ft_isalpha(str[i])) && (!(ft_isdigit(str[i])))
			&& str[i] != '_' && str[i] != '=')
			return (1);
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static char	**f_unset_line_2(char **cp_env, char *str, int i)
{
	char	**new_env;
	int		k;

	new_env = (char **)malloc(i * sizeof(char *));
	k = 0;
	i = 0;
	while (cp_env[i] != NULL)
	{
		if (strcmp(cp_env[i], "55")) //если это не 55 то копируем наши данные в новый массив
		{
			new_env[k] = ft_strdup(cp_env[i]);
			i++;
			k++;
		}
		else
			i++;
	}
	new_env[k] = NULL;
	i = 0;
	while (cp_env[i] != NULL)
		ft_free(cp_env[i++]);
	ft_free(cp_env);
	return (new_env);
}

static void	love_norma(char *str, t_untils *untils)
{
	printf("unset: %s not a valid identifier\n", str);
	untils->status = 1;
}

char	**f_unset_line(char **cp_env, char *str, t_untils *untils)
{
	char	**new_env;
	int		i;
	int		flag;

	i = -1;
	flag = 2;
	if (!str)
		return (cp_env); //если пустой unset подают то возвращаем сразу наш входящий массив
	if (check_name1(str))
	{
		love_norma(str, untils);
		return (cp_env);
	}
	while (cp_env[++i] != NULL)
	{
		if (compare_to_equal(cp_env[i], str)) //если нашли ключ кладем туда значение 55, так как в переменных окружения нельзя что бы 1 символ был цифрой то наше значение будет уникальным и не будет пересекаться
		{
			ft_free(cp_env[i]);
			cp_env[i] = ft_strdup("55");
			flag = 1;
		}
	}
	if (flag == 2) //если в нашем массиве не нашелся нужный ключ то удалять ничего не нужно, возвращаем текущий массив
		return (cp_env);
	return (f_unset_line_2(cp_env, str, i));
}
