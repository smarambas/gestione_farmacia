#include <stdio.h>
#include <string.h>

#include "medico.h"
#include "../utils/io.h"
#include "../utils/validation.h"

int get_medical_action(void)
{
	int options[10] = {1, 2, 3, 4, 5,
                       6, 7, 8, 9, 10};
    int op;

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
    puts("8) Print products list");
    puts("9) Print product boxes list");
	puts("10) Quit\n");

    op = alt_multi_choice("Select an option: ", options, 10);
	return op - 1;
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

    if(prod != NULL) {
        if (prod->tipo == 'M') {
            printf("\nProduct name: %s\nSupplier: %s\nType: %s\nCategory: %s\nNeeds prescription: %s\nMutuabile: %s\nIn stock: %d\n",
                   prod->nome,
                   prod->nome_fornitore,
                   "Medicinale",
                   prod->categoria,
                   prod->ricetta ? "yes" : "no",
                   prod->mutuabile ? "yes" : "no",
                   prod->quantita);
            printf("Usage: ");
            for (int i = 0; i < prod->num_usi; i++) {
                if (strlen(prod->usi[i].text) > 1)
                    printf("\n\t%d) %s\n", i + 1, prod->usi[i].text);
                else {
                    printf("-\n");
                    break;
                }
            }
        } else {
            printf("\nProduct name: %s\nSupplier: %s\nType: %s\nIn stock: %d\n",
                   prod->nome,
                   prod->nome_fornitore,
                   "Cosmetico",
                   prod->quantita);
            printf("Usage: ");
            for (int i = 0; i < prod->num_usi; i++) {
                if (strlen(prod->usi[i].text) > 1)
                    printf("\n\t%d) %s\n", i + 1, prod->usi[i].text);
                else {
                    printf("-\n");
                    break;
                }
            }
        }
    }
    else
        puts("The selected product doesn't exist\n");
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

	get_input("Insert category: ", STR_LEN, categoria, false);
}

void get_new_interaction(struct interazione *inter)
{
    clear_screen();
    puts("** Insert new interaction **\n");

	get_input("Insert first category: ", STR_LEN, inter->cat1, false);
    get_input("Insert second category: ", STR_LEN, inter->cat2, false);
}

void print_interacting_categories(struct interazioni *interazioni)
{
    clear_screen();
    puts("** Product-interacting categories **\n");

    if(interazioni != NULL) {
        for (int i = 0; i < interazioni->num_interazioni; i++) {
            printf("%s <----> %s\n", interazioni->cat_interagenti[i].cat1, interazioni->cat_interagenti[i].cat2);
        }
    }
    else
        puts("No interaction exists with the selected medicine.\n");
}

void print_lista_scaffali_medical(struct magazzino *magazzino)
{
    clear_screen();
    puts("** Shelves codes and categories **\n");

    int drawer_min, drawer_max;

    for(int i = 0; i < magazzino->num_scaffali; i++) {
        drawer_min = (magazzino->scaffali[i].codice * 10 - 10) + 1;
        drawer_max = drawer_min + 9;

        printf("Shelf #%d (%d-%d) ---> %s\n",
               magazzino->scaffali[i].codice,
               drawer_min,
               drawer_max,
               magazzino->scaffali[i].categoria);
    }
}

void get_sold_product_info(struct prodotto_venduto *prod)
{
    clear_screen();
    puts("** Add product to sale **\n");

    prod->quantita = get_int_input("Insert sold quantity: ");
    if(prod->tipo == 'M') {
        get_input("Insert codice fiscale: ", STR_LEN, prod->cf, false);
        if(prod->ricetta)
            while(true) {
                get_input("Insert doctor: ", STR_LEN, prod->medico, false);

                if(strlen(prod->medico) < 1)
                    puts("\nDoctor field can't be empty!\n");
                else
                    break;
            }
        else
            strcpy(prod->medico, "");
    }
    else {
        strcpy(prod->cf, "");
        strcpy(prod->medico, "");
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

void select_box_to_remove(struct scatola *box, struct scatole_prodotto *scatoleProdotto)
{
    int code;
    bool is_end = false;

    while(!is_end) {
        code = get_int_input("Select box: ");

        for(int i = 0; i < scatoleProdotto->num_scatole; i++) {
            if(code == scatoleProdotto->scatole[i].codice) {
                box->codice = code;
                is_end = true;
                break;
            }
        }

        if(!is_end)
            puts("The selected box can't be removed, please try again...\n");
    }
}

void print_products_list_medical(struct prodotti *prodotti)
{
    clear_screen();
    puts("** Products list **\n");

    for(int i = 0; i < prodotti->num_prodotti; i++) {
        printf("* %s (%s)\n",
               prodotti->lista_prodotti[i].nome,
               prodotti->lista_prodotti[i].nome_fornitore);
    }
    puts("\n");
}

void print_product_boxes(struct scatole_prodotto *scatoleProdotto)
{
    clear_screen();
    puts("** Product boxes list **\n");

    printf("Product: %s\nSupplier: %s\n\n",
           scatoleProdotto->nome_prodotto, scatoleProdotto->nome_fornitore);

    for(int i = 0; i < scatoleProdotto->num_scatole; i++) {
        printf("* Box #%d (Shelf #%d ---> Drawer #%d)\n",
               scatoleProdotto->scatole[i].codice,
               scatoleProdotto->scatole[i].scaff.codice,
               scatoleProdotto->scatole[i].cassetto);
    }
    puts("\n");
}

void print_message_medical(char *message)
{
    printf("\n%s\n", message);
}