#include "text_correction.h"


static size_t str_length(char* str_ptr) {
	size_t length = 0;
	while (str_ptr[length] != '\0') {
		length++;
	}
	return length++;
}








static void replace_symb(char *string_ptr, size_t position, char simbol) {
	string_ptr[position] = simbol;

	return;
}








static void delete_symb(char *string_ptr, size_t position) {
	do {
		string_ptr[position] = string_ptr[position + 1];
		position++;
	} while (string_ptr[position - 1] != '\0');

	return;
}








static void insert_symb(char *string_ptr, size_t position, char symbol) {
	char tmp_symb;

	do {
		tmp_symb = string_ptr[position];
		string_ptr[position] = symbol;
		symbol = tmp_symb;
		position++;
	} while (symbol != '\0');

	string_ptr[position] = symbol;

	return;
}








static int symb_analysis(char symb) {
	if (symb == '.' || symb == '!' || symb == '?') {
		return 1;
	}

	if (symb == ',' || symb == ';' || symb == ':' || symb == '[' || symb == ']' ||
		symb == '{' || symb == '}' || symb == '(' || symb == ')') {

		return 2;
	}

	if (symb == ' ' || symb == '\t' || symb == '\n') {
		return 3;
	}
	return 0;
}








static int english_letter_analysis(char letter) {
	if (letter >= (char)65 && letter <= (char)90) {
		return 1;
	}
	else {
		if (letter >= (char)97 && letter <= (char)122) {
			return 2;
		}
		else {
			return 0;
		}
	}
}








static void near_comma_like_symb_pros(char *str_ptr, size_t *comma_pos) {
	if (str_ptr[*comma_pos - 1] == ' ') {
		delete_symb(str_ptr, *comma_pos - 1);
		(*comma_pos)--;
	}

	if (str_ptr[*comma_pos + 1] != ' ') {
		insert_symb(str_ptr, *comma_pos + 1, ' ');
	}
	
	while (str_ptr[*comma_pos + 2] == ' ') {
		delete_symb(str_ptr, *comma_pos + 2);
	}
	
	return;
}







static void near_dot_like_symb_pros(char *str_ptr, size_t *dot_pos) {
	near_comma_like_symb_pros(str_ptr, dot_pos);

	if (english_letter_analysis(str_ptr[*dot_pos + 2]) == 2) {
		str_ptr[*dot_pos + 2] -= (char)32;
	}

	return;
}







static void after_space_pros(char* str_ptr, size_t space_pos) {
	while (str_ptr[space_pos + 1] == ' ' || str_ptr[space_pos + 1] == '\t') {
		delete_symb(str_ptr, space_pos + 1);
	}

	return;
}








void text_analysis(char **string_ptr_ptr) {
	char *tmp_str_ptr = (char *)malloc(2 * str_length(*string_ptr_ptr) * sizeof(char));

	*tmp_str_ptr = **string_ptr_ptr;

	for (size_t i = 0; (*string_ptr_ptr)[i] != '\0'; i++) {
		tmp_str_ptr[i + 1] = (*string_ptr_ptr)[i + 1];
	}

	free(*string_ptr_ptr);

	if (*tmp_str_ptr < (char)65 || *tmp_str_ptr > (char)90) {
		*tmp_str_ptr -= (char)32;
	}

	for (size_t i = 1; tmp_str_ptr[i] != '\0'; i++) {
		switch (symb_analysis(tmp_str_ptr[i])) {
		case 2:
			near_comma_like_symb_pros(tmp_str_ptr, &i);
			break;
		case 1:
			near_dot_like_symb_pros(tmp_str_ptr, &i);
			break;
		case 3:
			after_space_pros(tmp_str_ptr, i);
			break;
		}
	}

	char *res_str_ptr = (char *)malloc(str_length(tmp_str_ptr) * sizeof(char));
	
	*res_str_ptr = *tmp_str_ptr;

	for (size_t i = 0; tmp_str_ptr[i] != '\0'; i++) {
		res_str_ptr[i + 1] = tmp_str_ptr[i + 1];
	}

	free(tmp_str_ptr);
	*string_ptr_ptr = res_str_ptr;
	return;
}