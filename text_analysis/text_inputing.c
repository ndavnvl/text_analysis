#include "text_inputing.h"


static void realloc_buffer(char **buffer, size_t num_of_el) {
	g___num_of_bf++;

	char *tmp_buffer = (char *)malloc(g___num_of_bf * SIZE_OF_ELEMENTARY_BUFFER * sizeof(char));

	for (size_t j = 0; j < num_of_el; j++) {
		tmp_buffer[j] = (*buffer)[j];
	}

	free(*buffer);
	*buffer = tmp_buffer;
	return;
}








static void trim_buffer(char **buffer, size_t num_of_el) {
	char *input_text = (char *)malloc(num_of_el * sizeof(char *));

	for (size_t j = 0; j < num_of_el; j++) {
		input_text[j] = (*buffer)[j];
	}

	free(*buffer);
	*buffer = input_text;
	return;
}








char *get_text_from_current(FILE *stream) {
	char *buffer = (char *)malloc(SIZE_OF_ELEMENTARY_BUFFER * sizeof(char));
	size_t max_index_of_el = 0;

	for (g___num_of_bf = 1; !feof(stream) && (buffer[max_index_of_el] = fgetc(stream)) != '#'; max_index_of_el++) {
		if (max_index_of_el == g___num_of_bf * SIZE_OF_ELEMENTARY_BUFFER - 1) {
			realloc_buffer(&buffer, max_index_of_el + 1);
		}
	}

	clean_stdin();
	trim_buffer(&buffer, max_index_of_el + 1);
	
	if (buffer[max_index_of_el] != '#') {
		max_index_of_el++;
	}

	buffer[max_index_of_el] = '\0';
	return buffer;
}