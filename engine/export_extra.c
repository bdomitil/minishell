#include "../headers/minishell.h"

//static bool valid_key_and_value(char *value, char *key)
//{
//	if (value)
//		value++;
//	printf("key = %s\t value= %s\n", key, value);
//	while (*value || *key)
//	{
//		if (*value)
//		{
//			if (*value == 38 || *value == 33 || !ft_isascii(*value))
//				return (false);
//			value++;
//		}
//		if (*key)
//		{
//			if (*key == 38 || *key == 33 || !ft_isascii(*key))
//				return (false);
//			key++;
//		}
//	}
//	return (true);
//}

static bool valid_key(char *key)
{
	if (!key)
		return (false);
	while (*key)
	{
		if (*key == 38 || *key == 33 || !ft_isascii(*key))
			return (false);
		key++;
	}
	return (true);
}

static bool valid_value(char *value)
{
	if (!value)
		return (true);
	value++;
	while (*value)
	{
		if (*value == 38 || *value == 33 || !ft_isascii(*value))
			return (false);
		value++;
	}

	return (true);
}

bool	valid_export_arg(char *tmp)
{
	bool	valid;
	char 	*pos;
	char 	*pos_plus;

	valid = true;
	if (!ft_isalpha(tmp[0]))
		valid = false;
	pos = ft_strchr(tmp, '=');
	if (pos)
		*pos = '\0';
	pos_plus = ft_strchr(tmp, '+');
	if (pos_plus)
	{
		*pos_plus = '\0';
		if (*(++pos_plus) == '+')
			valid = false;
	}
	if (!valid_key(tmp) || !valid_value(pos))
		valid = false;
	if (pos)
		*pos = '=';
	if (pos_plus)
		*(--pos_plus) = '+';
	printf("tmp = %s\n", tmp);
	if (!valid)
		error_sh_cmd_msg(1, "export", tmp,\
	"not a valid identifier");
	return (valid);
}

void	changing_value(t_env *env_lst, char *value, char *key, bool plus)
{

}