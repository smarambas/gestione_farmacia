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

void get_medical_prod_name(struct prodotto *prod)
{
    clear_screen();
    puts("** Select a product **\n");

	get_input("Insert product name: ", STR_LEN, prod->nome, false);
    get_input("Insert product supplier name: ", STR_LEN, prod->nome_fornitore, false);
}

void show_product_info(struct prodotto *prod)
{
    clear_screen();
    puts("** Product info **\n");

    char type[STR_LEN];
    char ricetta[STR_LEN];
    char mutuabile[STR_LEN];

    if(prod->tipo == 'M') {
        type = "Medicine";
        if (prod->ricetta)
            ricetta = "Yes";
        else
            ricetta = "No";
        if (prod->mutuabile)
            mutuabile = "Yes";
        else
            mutuabile = "No";

        printf("\nProduct name: %s\nProduct supplier: %s\nType of product: %s\n /"
               "Stock quantities: %d\nCategory: %s\nPrescription required: %s\n /"
               "Mutuabile: %s\n", prod->nome, prod->nome_fornitore, type, prod->quantita, prod->categoria, ricetta, mutuabile);
        printf("Usage: \n\n");
        for(int i = 0; i < prod->num_usi; i++) {
            printf("%s\n", prod->usi[i].text);
        }
    }
    else {
        type = "Cosmetic";
        printf("\nProduct name: %s\nProduct supplier: %s\nType of product: %s\n /"
               "Stock quantities: %d\n", prod->nome, prod->nome_fornitore, type, prod->quantita);
    }
}

