#include <stdio.h>

#include "medico.h"
#include "../utils/io.h"
#include "../utils/validation.h"

int get_medical_action(void)
{
	char options[8] = {'1','2', '3', '4', '5', '6', '7', '8'};
	char op;

	clear_screen();
	puts("*********************************");
	puts("*    MEDICAL STAFF DASHBOARD    *");
	puts("*********************************\n");
	puts("*** What should I do for you? ***\n");
	puts("1) Print product info");
	puts("2) Add description to product");
	puts("3) Add pharmacotherapeutic category");
	puts("4) Add interaction between categories");
	puts("5) Print product-interacting categories");
	puts("6) Print shelves list");
	puts("7) Record sale");
	puts("8) Quit");

	op = multi_choice("Select an option", options, 8);
	return op - '1';
}

void get_product_name_medical(struct prodotto *prod)
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

    if(prod->tipo == 'M') {
        printf("\nProduct name: %s\nSupplier: %s\nType: %c\nCategory: %s\nNeeds prescription: %s\nMutuabile: %s\nIn stock: %d\n",
               prod->nome,
               prod->nome_fornitore,
               prod->tipo,
               prod->categoria,
               prod->ricetta ? "yes" : "no",
               prod->mutuabile ? "yes" : "no",
               prod->quantita);
        printf("Usage: \n");
        for(int i = 0; i < prod->num_usi; i++) {
            printf("%d) %s\n", i, prod->usi[i].text);
        }
    }
    else {
        printf("\nProduct name: %s\nSupplier: %s\nType: %c\nIn stock: %d\n",
               prod->nome, prod->nome_fornitore, prod->tipo, prod->quantita);
    }
}

void get_product_description_medical(struct descrizione *descr)
{
    clear_screen();
    puts("** Insert product description **\n");

	get_input("Insert description:\n", TXT_LEN, descr->text, false);
}

void get_new_category(char *categoria)
{
    clear_screen();
    puts("** Insert new category **\n");

	get_input("Insert category:\n", STR_LEN, categoria, false);
}

void get_new_interaction(struct interazione *inter)
{
    clear_screen();
    puts("** Insert new interaction **\n");

	get_input("Insert first category:\n", STR_LEN, inter->cat1, false);
    get_input("Insert second category:\n", STR_LEN, inter->cat2, false);
}

void print_interacting_categories(struct interazioni *interazioni)
{
    clear_screen();
    puts("** Product-interacting categories **\n");

    for(int i = 0; i < interazioni->num_interazioni; i++) {
        printf("%s <----> %s\n", interazioni->cat_interagenti[i].cat1, interazioni->cat_interagenti[i].cat2);
    }
}

void print_lista_scaffali_medical(struct magazzino *magazzino)
{
    clear_screen();
    puts("** Shelves codes and categories **\n");

    for(int i = 0; i < magazzino->num_scaffali; i++) {
        printf("Shelf #%d ---> %s\n", magazzino->scaffali[i].codice, magazzino->scaffali[i].categoria);
    }
}

void get_sold_product_info(struct prodotto_venduto *prod)
{
    clear_screen();
    puts("** Add product to sale **\n");

    prod->quantita = get_int_input("Insert sold quantity: ");
    if(prod->tipo == 'M') {
        get_input("Insert codice fiscale: ", STR_LEN, prod->cf, false);
        get_input("Insert doctor: ", STR_LEN, prod->medico, false);
    }
}

void print_boxes_codes(struct scatole_prodotto *scatoleProdotto)
{
    clear_screen();
    puts("** Remove sold boxes **\n");

    for(int i = 0; i < scatoleProdotto->num_scatole; i++) {
        printf("Box #%d (Shelf #%d ---> Drawer #%d)\n", scatoleProdotto->scatole[i].codice, scatoleProdotto->scatole[i].scaff.codice, scatoleProdotto->scatole[i].cassetto);
    }
    puts("\n");
}

void select_box_to_remove(struct scatola *box)
{
    box->codice = get_int_input("Select box: ");
}