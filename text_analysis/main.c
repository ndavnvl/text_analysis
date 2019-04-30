#include <stdlib.h>
#include "inputing.h"
#include "text_correction.h"
#include "text_inputing.h"








int main() {
	printf("This program scans and analyzes string with random length.\n\n");

	while (1) {
		printf("If you want to input text from console input \"0\", from file \"1\"\n");

		int input_mode;

		scaning_int_with_limits(&input_mode, 0, 1);

		char *string = NULL;

		if (input_mode) {
			printf("\nInput a name of a file with a text with a path. It must be shorter than 255.\n");

			char file_name[256];
			FILE *file_ptr;

			scanf_s("%s", file_name, (unsigned int)_countof(file_name));

			if (fopen_s(&file_ptr, file_name, "r")) {
				printf("\nSomting have gone wrong.\n");
				string = NULL;
			}
			else {
				string = get_text_from_current(file_ptr);
			}

		}
		else {
			printf("\nInput a string in english. End of the string must be #.\n\n");

			string = get_text_from_current(stdin);				
		}

		if (string != NULL) {
			printf("\n\nYou have input:\n%s\n", string);
			printf("\nDo you want to correct it? \"1\" means \"yes\", \"0\" - \"no\".\n");

			int analysis_mode;

			scaning_int_with_limits(&analysis_mode, 0, 1);

			if (analysis_mode) {
				text_analysis(&string);
				printf("\nResult:\n\n%s\n", string);
			}
		}
		
		int cont;

		printf("\nIf you want to do it again input 1 else input 0\n");
		scaning_int_with_limits(&cont, 0, 1);

		if (!cont) {
			break;
		}
	}

	return 0;
}