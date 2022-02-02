#include <stdio.h>
#include <string.h>

#include "amministrativo.h"
#include "../utils/io.h"
#include "../utils/validation.h"

int get_administrative_action(void)
{
	int options[26] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       11, 12, 13, 14, 15, 16, 17, 18,
                       19, 20, 21, 22, 23, 24, 25, 26};
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
    puts("24) Print products list");
    puts("25) Increase product stock quantity");
	puts("26) Quit\n");

	op = alt_multi_choice("Select an option: ", options, 26);
	return op - 1;
}

void get_product_name_administrative(struct prodotto *prod)
{
    clear_screen();
    puts("** Select a product **\n");

	get_input("Insert product name: ", STR_LEN, prod->nome, false);
    get_input("Insert product supplier name: ", STR_LEN, prod->nome_fornitore, false);
}

void get_product_description_administrative(struct descrizione *descr)
{
    clear_screen();
    puts("** Insert product description **\n");

	get_input("Insert description:\n", TXT_LEN, descr->text, false);
}

void print_lista_scaffali_administrative(struct magazzino *magazzino)
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
    do{
        get_input("Insert product category: ", STR_LEN, prod->categoria, false);

        if(strlen(prod->categoria) < 1)
            puts("\nCategory can't be empty!");
    }while(strlen(prod->categoria) < 1);
    prod->ricetta = yes_or_no("Does the product require a prescription? ", 'y', 'n', false, true);
    prod->mutuabile = yes_or_no("Can the product be prescribed on the National Health Service? ", 'y', 'n', false, true);
}

void print_stock_report(struct prodotti_magazzino *prodottiMagazzino)
{
    clear_screen();
    puts("** Stock report **\n");

    for(int i = 0; i < prodottiMagazzino->num_prodotti; i++) {
        printf("* %s (%s) \n---> In stock: %d\n\n",
                prodottiMagazzino->prodotti[i].nome,
                prodottiMagazzino->prodotti[i].nome_fornitore,
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

    if(fornitore->indirizzi != NULL) {
        num_indirizzi = fornitore->indirizzi->num_indirizzi;
        printf("Supplier: %s\n", fornitore->nome);
        printf("Addresses: \n");
        for (i = 0; i < num_indirizzi; i++) {
            printf("\t%d) %s, %s %s %s\n", i + 1,
                   fornitore->indirizzi->lista_indirizzi[i].citta,
                   fornitore->indirizzi->lista_indirizzi[i].via,
                   fornitore->indirizzi->lista_indirizzi[i].num_civico,
                   fornitore->indirizzi->lista_indirizzi[i].fatturazione ? "(billing address)" : "");
        }
    }

    if(fornitore->recapiti != NULL) {
        num_recapiti = fornitore->recapiti->num_recapiti;
        printf("Contacts: \n");
        for (i = 0; i < num_recapiti; i++) {
            printf("\t%d) %s %s\n", i + 1,
                   fornitore->recapiti->lista_recapiti[i].contatto,
                   fornitore->recapiti->lista_recapiti[i].preferito ? "(preferred)" : "");
        }
    }
}

void print_supplier_prod(struct prodotti_magazzino *prodottiMagazzino)
{
    clear_screen();
    puts("** Supplier products **\n");

    printf("Supplier: %s\n\n", prodottiMagazzino->prodotti[0].nome_fornitore);

    for(int i = 0; i < prodottiMagazzino->num_prodotti; i++) {
        printf("* Product name: %s\nType: %s\nCategory: %s\nNeeds prescription: %s\nMutuabile: %s\nIn stock: %d\n\n",
               prodottiMagazzino->prodotti[i].nome,
               prodottiMagazzino->prodotti[i].tipo == 'M' ? "Medicinale" : "Cosmetico",
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

void get_box_info(struct scatola *scatola)
{
    clear_screen();
    puts("** Register a box **\n");

    while(true) {
		get_input("Insert expiration date [YYYY-MM-DD]: ", DATE_LEN, scatola->scadenza, false);
		if(validate_date(scatola->scadenza))
			break;
		fprintf(stderr, "Invalid date!\n");
	}
    scatola->scaff.codice = get_int_input("Insert shelf number: ");
    scatola->cassetto = get_int_input("Insert drawer number: ");
}

void get_box_code(struct scatola *scatola, bool clear)
{
    if(clear)
        clear_screen();

    puts("** Select a box **\n");

    scatola->codice = get_int_input("Insert box code: ");
}

void print_expiry_report(struct scatole_in_scadenza *scatoleInScadenza)
{
    clear_screen();
    puts("** Expiry report **\n");

    for(int i = 0; i < scatoleInScadenza->num_in_scadenza; i++) {
        printf("* Box #%d\nProduct: %s\nSupplier: %s\nShelf: %d\nDrawer: %d\nExpiration date: %s\n\n",
               scatoleInScadenza->scatole[i].scatole->codice,
               scatoleInScadenza->scatole[i].nome_prodotto,
               scatoleInScadenza->scatole[i].nome_fornitore,
               scatoleInScadenza->scatole[i].scatole->scaff.codice,
               scatoleInScadenza->scatole[i].scatole->cassetto,
               scatoleInScadenza->scatole[i].scatole->scadenza);
    }
    puts("\n");
}

void get_shelf_category(struct scaffale *scaffale)
{
    clear_screen();
    puts("** Add new shelf **\n");

    get_input("Insert shelf category: ", STR_LEN, scaffale->categoria, false);
}

void modify_shelf_category(struct scaffale *scaffale)
{
    clear_screen();
    puts("** Modify shelf category **\n");

    scaffale->codice = get_int_input("Select shelf: ");
    get_input("Insert shelf new category: ", STR_LEN, scaffale->categoria, false);
}

void get_product_for_letter(struct prodotto_richiesto *prodottoRichiesto)
{
    clear_screen();
    puts("** Add product to purchase letter **\n");

    get_input("Insert product name: ", STR_LEN, prodottoRichiesto->nome_prodotto, false);
    get_input("Insert supplier name: ", STR_LEN, prodottoRichiesto->nome_fornitore, false);
    prodottoRichiesto->quantita = get_int_input("Insert requested quantity: ");
}

void print_supplier_letters(struct lettere_inviate *lettereInviate, struct fornitore *fornitore)
{
    clear_screen();
    puts("** Letters sent to supplier **\n");

    printf("Supplier: %s\n\n", fornitore->nome);
    for(int i = 0; i < lettereInviate->num_lettere; i++) {
        printf("* Letter #%d (%s)\n",
               lettereInviate->lettere[i].codice,
               lettereInviate->lettere[i].giorno);

        for(int j = 0; j < lettereInviate->lettere[i].num_richieste; j++) {
            printf("\t- %s x %d\n",
                   lettereInviate->lettere[i].richieste[j].nome_prodotto,
                   lettereInviate->lettere[i].richieste[j].quantita);
        }
        printf("\n");
    }
    puts("\n");
}

void get_date(char *date)
{
    clear_screen();
    puts("** Select a date **\n");

    while(true) {
        get_input("Insert a valid date (YYYY-MM-DD): ", DATE_LEN, date, false);
        if(validate_date(date))
            break;
        fprintf(stderr, "Invalid date!\n");
    }
}

void print_sales_on_date(struct vendite *vendite, char *giorno)
{
    clear_screen();
    puts("** Sales made on a particular date **\n");

    printf("Date: %s\n\n", giorno);
    for(int i = 0; i < vendite->num_vendite; i++) {
        printf("* Sale #%d\n", vendite->listaVendite[i].scontrino);

        for(int j = 0; j < vendite->listaVendite[i].num_prodotti; j++) {
            printf("\t- Product: %s\n\t  Supplier: %s\n\t  Type: %s\n\t  CF: %s\n\t  Doctor: %s\n\t  Quantity: %d\n\n",
                   vendite->listaVendite[i].prod_venduti[j].nome_prodotto,
                   vendite->listaVendite[i].prod_venduti[j].nome_fornitore,
                   vendite->listaVendite[i].prod_venduti[j].tipo == 'M' ? "Medicinale" : "Cosmetico",
                   strlen(vendite->listaVendite[i].prod_venduti[j].cf) > 1 ? vendite->listaVendite[i].prod_venduti[j].cf : "-",
                   strlen(vendite->listaVendite[i].prod_venduti[j].medico) > 1 ? vendite->listaVendite[i].prod_venduti[j].medico : "-",
                   vendite->listaVendite[i].prod_venduti[j].quantita);
        }
    }
    puts("\n");
}

void print_sales_product(struct vendite *vendite, struct prodotto *prodotto)
{
    clear_screen();
    puts("** Sales including a particular product **\n");

    printf("Product name: %s\nProduct supplier: %s\n\n", prodotto->nome, prodotto->nome_fornitore);
    for(int i = 0; i < vendite->num_vendite; i++) {
        if(vendite->listaVendite[i].prod_venduti[0].tipo == 'M') {
            if(vendite->listaVendite[i].prod_venduti[0].ricetta) {
                printf("* Sale #%d (%s)\n  CF: %s\n  Doctor: %s\n  Quantity: %d\n\n",
                       vendite->listaVendite[i].scontrino,
                       vendite->listaVendite[i].giorno,
                       vendite->listaVendite[i].prod_venduti[0].cf,
                       vendite->listaVendite[i].prod_venduti[0].medico,
                       vendite->listaVendite[i].prod_venduti[0].quantita);
            }
            else {
                printf("* Sale #%d (%s)\n  CF: %s\n  Quantity: %d\n\n",
                       vendite->listaVendite[i].scontrino,
                       vendite->listaVendite[i].giorno,
                       vendite->listaVendite[i].prod_venduti[0].cf,
                       vendite->listaVendite[i].prod_venduti[0].quantita);
            }
        }
        else {
            printf("* Sale #%d (%s)\n  Quantity: %d\n\n",
                       vendite->listaVendite[i].scontrino,
                       vendite->listaVendite[i].giorno,
                       vendite->listaVendite[i].prod_venduti[0].quantita);
        }
    }
    puts("\n");
}

void print_most_sold(struct prodotti_venduti *prodottiVenduti)
{
    clear_screen();
    puts("** Most sold products **\n");

    for(int i = 0; i < prodottiVenduti->num_prodotti; i++) {
        printf("*\nProduct: %s\nSupplier: %s\nType: %s\nSold quantity: %d\n\n",
               prodottiVenduti->prod_venduti[i].nome_prodotto,
               prodottiVenduti->prod_venduti[i].nome_fornitore,
               prodottiVenduti->prod_venduti[i].tipo == 'M' ? "Medicinale" : "Cosmetico",
               prodottiVenduti->prod_venduti[i].quantita);
    }
    puts("\n");
}

void print_products_list_administrative(struct prodotti *prodotti)
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

void get_new_quantity(struct prodotto *prodotto)
{
    clear_screen();
    puts("** Update product stock quantity **\n");

    int quantity;

    get_input("Insert product name: ", STR_LEN, prodotto->nome, false);
    get_input("Insert product supplier: ", STR_LEN, prodotto->nome_fornitore, false);
    while(true) {
        quantity = get_int_input("Insert stock quantity to add: ");

        if(quantity > 0) {
            prodotto->quantita = quantity;
            break;
        }
        else
            puts("Stock quantity can't be zero or negative!\n");
    }
}

void print_message_administrative(char *message)
{
    printf("\n%s\n", message);
}