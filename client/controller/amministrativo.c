#include <stdio.h>
#include <string.h>
#include "amministrativo.h"

#include "../model/db.h"
#include "../view/amministrativo.h"
#include "../utils/io.h"

static bool prod_description(void)
{
    struct prodotto prod;
    memset(&prod, 0, sizeof(prod));
    get_product_name_administrative(&prod);

    struct descrizione descr;
    memset(&descr, 0, sizeof(descr));
    get_product_description_administrative(&descr);

    do_add_product_description(&prod, &descr);

    return false;
}

static bool print_shelves(void)
{
    struct magazzino *magazzino = do_get_shelves();
    if(magazzino != NULL) {
        print_lista_scaffali_administrative(magazzino);
        magazzino_dispose(magazzino);
    }
    else
        print_message_administrative("No shelf found!");

    return false;
}

static bool add_cosmetic(void)
{
    struct prodotto prod;
    memset(&prod, 0, sizeof(prod));
    get_cosmetic(&prod);

    do_add_cosmetic(&prod);

    return false;
}

static bool add_medicine(void)
{
    struct prodotto prod;
    memset(&prod, 0, sizeof(prod));
    get_medicine(&prod);

    do_add_medicine(&prod);

    return false;
}

static bool get_stock_report(void)
{
    struct prodotti_magazzino *prodottiMagazzino;
    prodottiMagazzino = do_get_stock_report();

    if(prodottiMagazzino != NULL) {
        print_stock_report(prodottiMagazzino);
        dispose_stock_report(prodottiMagazzino);
    }
    else
        print_message_administrative("No product found!");

    return false;
}

static bool remove_product(void)
{
    struct prodotto prod;
    memset(&prod, 0, sizeof(prod));
    get_product_name_administrative(&prod);

    do_remove_product(&prod);

    return false;
}

static bool add_supplier(void)
{
    struct fornitore fornitore;
    memset(&fornitore, 0, sizeof(fornitore));
    get_supplier_name(&fornitore);

    do_add_supplier(&fornitore);

    return false;
}

static bool remove_supplier(void)
{
    struct fornitore fornitore;
    memset(&fornitore, 0, sizeof(fornitore));
    get_supplier_name(&fornitore);

    do_remove_supplier(&fornitore);

    return false;
}

static bool get_supplier_info(void)
{
    struct fornitore fornitore;
    memset(&fornitore, 0, sizeof(fornitore));
    get_supplier_name(&fornitore);

    struct fornitore *infoFornitore;

    infoFornitore = do_get_info_supplier(&fornitore);
    if(infoFornitore != NULL) {
        print_supplier_info(infoFornitore);
        dispose_supplier(infoFornitore);
    }
    else
        print_message_administrative("Can't find selected supplier!");

    return false;
}

static bool get_supplier_prod(void)
{
    struct fornitore fornitore;
    memset(&fornitore, 0, sizeof(fornitore));
    get_supplier_name(&fornitore);

    struct prodotti_magazzino *prodottiMagazzino;
    prodottiMagazzino = do_get_supplier_products(&fornitore);
    if(prodottiMagazzino != NULL) {
        print_supplier_prod(prodottiMagazzino);
        dispose_stock_report(prodottiMagazzino);
    }
    else
        print_message_administrative("Can't find selected supplier products!");

    return false;
}

static bool add_address(void)
{
    struct fornitore fornitore;
    memset(&fornitore, 0, sizeof(fornitore));
    get_supplier_name(&fornitore);

    struct indirizzo indirizzo;
    memset(&indirizzo, 0, sizeof(indirizzo));
    get_supplier_address(&indirizzo, true);

    do_add_address(&indirizzo, &fornitore);

    return false;
}

static bool remove_address(void)
{
    get_supplier_info();

    struct indirizzo indirizzo;
    memset(&indirizzo, 0, sizeof(indirizzo));
    get_supplier_address(&indirizzo, false);

    do_remove_address(&indirizzo);

    return false;
}

static bool add_contact(void)
{
    struct fornitore fornitore;
    memset(&fornitore, 0, sizeof(fornitore));
    get_supplier_name(&fornitore);

    struct recapito recapito;
    memset(&recapito, 0, sizeof(recapito));
    get_supplier_contact(&recapito, true);

    do_add_contact(&recapito, &fornitore);

    return false;
}

static bool remove_contact(void)
{
    get_supplier_info();

    struct recapito recapito;
    memset(&recapito, 0, sizeof(recapito));
    get_supplier_contact(&recapito, false);

    do_remove_contact(&recapito);

    return false;
}

static bool add_box(void)
{
    struct prodotto prod;
    memset(&prod, 0, sizeof(prod));
    get_product_name_administrative(&prod);

    struct scatola scatola;
    memset(&scatola, 0, sizeof(scatola));
    get_box_info(&scatola);

    do_add_box(&prod, &scatola);

    return false;
}

static void remove_box_expiry(struct scatole_in_scadenza *scatoleInScadenza)
{
    struct scatola scatola;
    memset(&scatola, 0, sizeof(scatola));

    bool is_end = false;

    while(!is_end) {
        get_box_code(&scatola, false);

        for(int i = 0; i < scatoleInScadenza->num_in_scadenza; i++) {
            if(scatola.codice == scatoleInScadenza->scatole[i].scatole[0].codice) {
                is_end = true;
                break;
            }
        }

        if(!is_end)
            puts("\nThe selected box is not expiring!\n");
    }

    struct prodotto *prodotto = do_remove_box(&scatola);
    if(prodotto != NULL) {
        prodotto->quantita = 1; //one box removed
        do_decrease_stock(prodotto);
        free(prodotto);
    }

    return;
}

static bool get_expiry_report(void)
{
    struct scatole_in_scadenza *scatoleInScadenza;
    scatoleInScadenza = do_get_expiry_report();
    if(scatoleInScadenza != NULL) {
        print_expiry_report(scatoleInScadenza);

        while(yes_or_no("Do you want to remove a box?", 'y', 'n', false, true)) {
            remove_box_expiry(scatoleInScadenza);

            printf("\n");
        }

        dispose_in_scadenza(scatoleInScadenza);
    }
    else
        print_message_administrative("There are no expiring boxes!");

    return false;
}

static bool add_shelf(void)
{
    struct scaffale scaffale;
    memset(&scaffale, 0, sizeof(scaffale));
    get_shelf_category(&scaffale);

    do_add_shelf(&scaffale);

    return false;
}

static bool update_shelf(void)
{
    struct scaffale scaffale;
    memset(&scaffale, 0, sizeof(scaffale));
    modify_shelf_category(&scaffale);

    do_update_shelf_category(&scaffale);

    return false;
}

static bool send_letter(void)
{
    struct lettera_acquisto *letteraAcquisto;
    letteraAcquisto = do_get_purchase_letter();
    if(letteraAcquisto != NULL) {
        struct prodotto_richiesto prodottoRichiesto;

        do{
            memset(&prodottoRichiesto, 0, sizeof(prodottoRichiesto));
            get_product_for_letter(&prodottoRichiesto);

            do_add_product_to_letter(letteraAcquisto, &prodottoRichiesto);
        }while(yes_or_no("\nDo you want to add another product to the letter?", 'y', 'n', false, true));
    }

    free(letteraAcquisto);

    return false;
}

static bool get_supplier_letters(void)
{
    struct fornitore fornitore;
    memset(&fornitore, 0, sizeof(fornitore));
    get_supplier_name(&fornitore);

    struct lettere_inviate *lettereInviate;
    lettereInviate = do_get_letters_to_supplier(&fornitore);
    if(lettereInviate != NULL) {
        print_supplier_letters(lettereInviate, &fornitore);
        dispose_letters(lettereInviate);
    }
    else
        print_message_administrative("No letter found for the selected supplier!");

    return false;
}

static bool get_sales_date(void)
{
    char giorno[DATE_LEN];
    get_date(giorno);

    struct vendite *vendite;
    vendite = do_get_sales_on_date(giorno);
    if(vendite != NULL) {
        print_sales_on_date(vendite, giorno);
        dispose_sales(vendite);
    }
    else
        print_message_administrative("No sale found for the selected day!");

    return false;
}

static bool get_sales_prod(void)
{
    struct prodotto prod;
    memset(&prod, 0, sizeof(prod));
    get_product_name_administrative(&prod);

    struct vendite *vendite;
    vendite = do_get_product_sales(&prod);
    if(vendite != NULL) {
        print_sales_product(vendite, &prod);
        dispose_sales(vendite);
    }
    else
        print_message_administrative("No sale found for the selected product!");

    return false;
}

static bool get_most_sold(void)
{
    struct prodotti_venduti *prodottiVenduti;
    prodottiVenduti = do_get_most_sold();
    if(prodottiVenduti != NULL) {
        print_most_sold(prodottiVenduti);
        dispose_most_sold(prodottiVenduti);
    }
    else
        print_message_administrative("No sale found!");

    return false;
}

static bool prod_list(void)
{
    struct prodotti *prodotti;
    prodotti = do_get_products_list();
    if(prodotti != NULL) {
        print_products_list_administrative(prodotti);
        dispose_products_list(prodotti);
    }
    else
        print_message_administrative("No product found!");

    return false;
}

static bool increase_stock(void)
{
    struct prodotto prod;
    memset(&prod, 0, sizeof(prod));
    get_new_quantity(&prod);

    do_increase_stock(&prod);

    return false;
}

static bool quit(void)
{
	return true;
}

static struct {
	enum actions action;
	bool (*control)(void);
} controls[END_OF_ACTIONS] = {
	{.action = PROD_DESCRIPTION, .control = prod_description},
    {.action = PRINT_SHELVES, .control = print_shelves},
    {.action = ADD_COSMETIC, .control = add_cosmetic},
    {.action = ADD_MEDICINE, .control = add_medicine},
    {.action = GET_STOCK_REPORT, .control = get_stock_report},
    {.action = REMOVE_PRODUCT, .control = remove_product},
    {.action = ADD_SUPPLIER, .control = add_supplier},
    {.action = REMOVE_SUPPLIER, .control = remove_supplier},
    {.action = GET_SUPPLIER_INFO, .control = get_supplier_info},
    {.action = GET_SUPPLIER_PROD, .control = get_supplier_prod},
    {.action = ADD_ADDRESS, .control = add_address},
    {.action = REMOVE_ADDRESS, .control = remove_address},
    {.action = ADD_CONTACT, .control = add_contact},
    {.action = REMOVE_CONTACT, .control = remove_contact},
    {.action = ADD_BOX, .control = add_box},
    {.action = GET_EXPIRY_REPORT, .control = get_expiry_report},
    {.action = ADD_SHELF, .control = add_shelf},
    {.action = UPDATE_SHELF, .control = update_shelf},
    {.action = SEND_LETTER, .control = send_letter},
    {.action = GET_SUPPLIER_LETTERS, .control = get_supplier_letters},
    {.action = GET_SALES_DATE, .control = get_sales_date},
    {.action = GET_SALES_PROD, .control = get_sales_prod},
    {.action = GET_MOST_SOLD, .control = get_most_sold},
    {.action = PROD_LIST, .control = prod_list},
    {.action = INCREASE_STOCK, .control = increase_stock},
	{.action = QUIT, .control = quit}
};

void administrative_controller(void)
{
	db_switch_to_administration();

	while(true) {
		int action = get_administrative_action();
		if(action >= END_OF_ACTIONS) {
			fprintf(stderr, "Error: unknown action\n");
			continue;
		}
		if (controls[action].control())
			break;

		press_anykey();
	}
}