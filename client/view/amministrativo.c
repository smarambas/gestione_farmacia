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

void get_product_name(struct prodotto *prod)
{
    clear_screen();
    puts("** Select a product **\n");

	get_input("Insert product name: ", STR_LEN, prod->nome, false);
    get_input("Insert product supplier name: ", STR_LEN, prod->nome_fornitore, false);
}

void get_product_description(struct descrizione *descr)
{
    clear_screen();
    puts("** Insert product description **\n");

	get_input("Insert description:\n", TXT_LEN, descr->text, false);
}

void print_lista_scaffali(struct magazzino *magazzino)
{
    clear_screen();
    puts("** Shelves codes and categories **\n");

    for(int i = 0; i < magazzino->num_scaffali; i++) {
        printf("Shelf #%d ---> %s\n", magazzino->scaffali[i].codice, magazzino->scaffali[i].categoria);
    }
}

void get_cosmetic(struct prodotto *prod)
{
    clear_screen();
    puts("** Insert a cosmetic **\n");

	get_input("Insert product name: ", STR_LEN, prod->nome, false);
    get_input("Insert product supplier name: ", STR_LEN, prod->nome_fornitore, false);
}

void get_medicine(struct prodotto *prod)
{
    clear_screen();
    puts("** Insert a medicine **\n");

	get_input("Insert product name: ", STR_LEN, prod->nome, false);
    get_input("Insert product supplier name: ", STR_LEN, prod->nome_fornitore, false);
    get_input("Insert product category: ", STR_LEN, prod->categoria, false);
    prod->ricetta = yes_or_no("Does the product require a prescription? ", 'y', 'n', false, true);
    prod->mutuabile = yes_or_no("Can the product be prescribed on the National Health Service? ", 'y', 'n', false, true);
}

void print_stock_report(struct prodotti_magazzino *prodottiMagazzino)
{
    clear_screen();
    puts("** Stock report **\n");

    for(int i = 0; i < prodottiMagazzino->num_prodotti; i++) {
        printf("* %s (%s) Type: %c ---> In stock: %d\n",
                prodottiMagazzino->prodotti[i].nome,
                prodottiMagazzino->prodotti[i].nome_fornitore,
                prodottiMagazzino->prodotti[i].tipo,
                prodottiMagazzino->prodotti[i].quantita);
    }
    puts("\n");
}

void get_supplier_name(struct fornitore *fornitore)
{
    clear_screen();
    puts("** Select a supplier **\n");

    get_input("Insert supplier name: ", STR_LEN, fornitore->nome, false);
}

void print_supplier_info(struct fornitore *fornitore)
{
    clear_screen();
    puts("** Supplier informations **\n");

    int num_indirizzi, num_recapiti, i;

    num_indirizzi = fornitore->indirizzi->num_indirizzi;
    num_recapiti = fornitore->recapiti->num_recapiti;

    printf("Name: %s\n", fornitore->nome);
    printf("Addresses: \n");
    for(i = 0; i < num_indirizzi; i++) {
        printf("\t%d) %s, %s %s %s\n", i+1,
               fornitore->indirizzi->lista_indirizzi[i].citta,
               fornitore->indirizzi->lista_indirizzi[i].via,
               fornitore->indirizzi->lista_indirizzi[i].num_civico,
               fornitore->indirizzi->lista_indirizzi[i].fatturazione ? "(preferred)" : "");
    }
    printf("Contacts: \n");
    for(i = 0; i < num_recapiti; i++) {
        printf("\t%d) %s %s\n", i+1,
               fornitore->recapiti->lista_recapiti[i].contatto,
               fornitore->recapiti->lista_recapiti[i].preferito ? "(preferred)" : "");
    }
}

void print_supplier_prod(struct prodotti_magazzino *prodottiMagazzino)
{
    clear_screen();
    puts("** Supplier products **\n");

    printf("Supplier: %s\n\n", prodottiMagazzino->prodotti[0].nome_fornitore);

    for(int i = 0; i < prodottiMagazzino->num_prodotti; i++) {
        printf("* Product name: %s\nType: %c\nCategory: %s\nNeeds prescription: %s\nMutuabile: %s\nIn stock: %d\n\n",
               prodottiMagazzino->prodotti[i].nome,
               prodottiMagazzino->prodotti[i].tipo,
               prodottiMagazzino->prodotti[i].categoria,
               prodottiMagazzino->prodotti[i].ricetta ? "yes" : "no",
               prodottiMagazzino->prodotti[i].mutuabile ? "yes" : "no",
               prodottiMagazzino->prodotti[i].quantita);
    }
    puts("\n");
}

void get_supplier_address(struct indirizzo *indirizzo, bool is_add)
{
    clear_screen();
    puts("** Select an address **\n");

    get_input("Insert city: ", STR_LEN, indirizzo->citta, false);
    get_input("Insert street: ", STR_LEN, indirizzo->via, false);
    get_input("Insert street number: ", STR_LEN, indirizzo->num_civico, false);

    if(is_add)
        indirizzo->fatturazione = yes_or_no("Is it a billing address? ", 'y', 'n', false, true);
}

void get_supplier_contact(struct recapito *recapito, bool is_add)
{
    clear_screen();
    puts("** Select a contact **\n");

    get_input("Insert contact: ", STR_LEN, recapito->contatto, false);

    if(is_add)
        recapito->preferito = yes_or_no("Is it a preferred contact? ", 'y', 'n', false, true);
}
