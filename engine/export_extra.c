#include "../headers/minishell.h"

static bool valid_key(char *key)
{
	if (!key)
		return (true);
	while (key)
	{
		if (*key == 38 || !ft_isascii(*value))
			return (false);
	}
}

static bool valid_value(char *value)
{
	bool	valid;
	if (!value)
		return (true);
	value++;
	while (value)
	{
		if (*value == 38 || !ft_isascii(*value))
			return (false);
		value++;
	}
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
	*pos = '\0';
	pos_plus = ft_strchr(tmp, '+');
	if (pos_plus)
		if (*(++pos_plus) == '+' || !valid_key(tmp) || !valid_value(pos))
			valid = false;
	error_sh_cmd_msg(1, "export", tmp,\
	"not a valid identifier");

	return (valid);
}
