//
// Created by Hugor Chau on 7/27/20.
//
#include "../incs/test.h"

void	error(char *error, int ex) {
	ft_putstr(ERROR);
	ft_putstr(error);
	ft_putendl(EOC);
	exit(ex);
}

void *safe_call(void *res, void *expression, char *error_message) {
	static int error_count = 1;//номер ошибки

	if (expression == NULL && res == 0) {
		error_count++;
		return res;
	}
	if (expression != NULL && res != 0) {
		error_count++;
		return res;
	}
	error(error_message, error_count);
	return res;
}
