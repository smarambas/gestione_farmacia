#include <stdio.h>

#include "amministrativo.h"
#include "../utils/io.h"
#include "../utils/validation.h"

int get_administrative_action(void)
{
	int options[24] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       11, 12, 13, 14, 15, 16, 17, 18,
                       19, 20, 21, 22, 23, 24};
	int op;

	clear_screen();
	puts("****************************************");
	puts("*    ADMINISTRATIVE STAFF DASHBOARD    *");
	puts("****************************************\n");
	puts("****** What should I do for you? ******\n");
	puts("1) Add description to product");
	puts("2) Print shelves list");
	puts("3) Add cosmetic");
    puts("4) Add medicine");
    puts("5) Get stock report");
    puts("6) Remove product");
    puts("7) Add supplier");
    puts("8) Remove supplier");
    puts("9) Print supplier info");
    puts("10) Print supplier products");
    puts("11) Add address to supplier");
    puts("12) Remove address");
    puts("13) Add contact to supplier");
    puts("14) Remove contact");
    puts("15) Add box");
    puts("16) Get expiry report");
    puts("17) Add shelf");
    puts("18) Update shelf category");
    puts("19) Send purchase letter to supplier");
    puts("20) Print letters sent to supplier");
    puts("21) Print sales made on a given date");
    puts("22) Print sales including a product");
    puts("23) Print most sold products list");
	puts("24) Quit");

	op = alt_multi_choice("Select an option: ", options, 24);
	return op - 1;
}