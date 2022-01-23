#include <stdio.h>

#include "medico.h"
#include "../utils/io.h"
#include "../utils/validation.h"

int get_medical_action(void) {
	
	char options[8] = {'1','2', '3', '4', '5', '6', '7', '8'};
	char op;

	clear_screen();
	puts("*********************************");
	puts("*    MEDICAL STAFF DASHBOARD    *");
	puts("*********************************\n");
	puts("*** What should I do for you? ***\n");
	puts("1) Print product info");
	puts("2) Add use description to product");
	puts("3) Add pharmacotherapeutic category");
	puts("4) Add interaction between categories");
	puts("5) Print product-interacting categories");
	puts("6) Print shelves list");
	puts("7) Record sale");
	puts("8) Quit");

	op = multi_choice("Select an option", options, 8);
	return op - '1';
}
