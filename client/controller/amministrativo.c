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
    get_product_name(&prod);

    struct descrizione descr;
    memset(&descr, 0, sizeof(descr));
    get_product_description(&descr);

    do_add_product_description(&prod, &descr);

    return false;
}

static bool print_shelves(void)
{
    struct magazzino *magazzino = do_get_shelves();
    if(magazzino != NULL) {
        print_lista_scaffali(magazzino);
        magazzino_dispose(magazzino);
    }

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
    }

    return false;
}

static bool remove_product(void)
{
    struct prodotto prod;
    memset(&prod, 0, sizeof(prod));
    get_product_name(&prod);

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
    struct fornitore *fornitore;
    memset(fornitore, 0, sizeof(*fornitore));
    get_supplier_name(fornitore);

    fornitore = do_get_info_supplier(fornitore);
    if(fornitore != NULL) {
        print_supplier_info(fornitore);
    }

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
    }

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
    get_product_name(&prod);

    struct scatola scatola;
    memset(&scatola, 0, sizeof(scatola));
    get_box_info(&scatola);

    do_add_box(&prod, &scatola);

    return false;
}

static bool remove_box(void)
{
    struct scatola scatola;
    memset(&scatola, 0, sizeof(scatola));
    get_box_code(&scatola, true);

    struct prodotto *prodotto = do_remove_box(&scatola);
    if(prodotto != NULL) {
        do_decrease_stock(prodotto);
        free(prodotto);
    }

    return false;
}

static void remove_box_expiry(void)
{
    struct scatola scatola;
    memset(&scatola, 0, sizeof(scatola));
    get_box_code(&scatola, false);

    struct prodotto *prodotto = do_remove_box(&scatola);
    if(prodotto != NULL) {
        do_decrease_stock(prodotto);
        free(prodotto);
    }

    return false;
}

static bool get_expiry_report(void)
{
    struct scatole_in_scadenza *scatoleInScadenza;
    scatoleInScadenza = do_get_expiry_report();
    if(scatoleInScadenza != NULL) {
        print_expiry_report(scatoleInScadenza);

        while(yes_or_no("Do you want to remove a box?", 'y', 'n', false, true)) {
            remove_box_expiry();

            printf("\n");
        }

        dispose_in_scadenza(scatoleInScadenza);
    }

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
        }while(yes_or_no("Do you want to add another product to the letter?", 'y', 'n', false, true));
    }

    free(letteraAcquisto);

    return false;
}

static bool print_letters(void)
{

}

static bool print_sales_date(void)
{

}

static bool print_sales_prod(void)
{

}

static bool print_most_sold(void)
{

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
    {.action = REMOVE_BOX, .control = remove_box},
    {.action = GET_EXPIRY_REPORT, .control = get_expiry_report},
    {.action = ADD_SHELF, .control = add_shelf},
    {.action = UPDATE_SHELF, .control = update_shelf},
    {.action = SEND_LETTER, .control = send_letter},
    {.action = PRINT_LETTERS, .control = print_letters},
    {.action = PRINT_SALES_DATE, .control = print_sales_date},
    {.action = PRINT_SALES_PROD, .control = print_sales_prod},
    {.action = PRINT_MOST_SOLD, .control = print_most_sold},
	{.action = QUIT, .control = quit}
};

void controller_medico(void)
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