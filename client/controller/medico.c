#include <stdio.h>
#include <string.h>
#include "medico.h"

#include "../model/db.h"
#include "../view/medico.h"
#include "../utils/io.h"

static bool prod_info(void)
{
    struct prodotto prod;
    memset(&prod, 0, sizeof(prod));
    get_product_name_medical(&prod);

    struct prodotto *info_prodotto = do_get_product_info(&prod);
    if(info_prodotto != NULL) {
        show_product_info(info_prodotto);
        free(info_prodotto);
    }
    return false;
}

static bool prod_description(void)
{
    struct prodotto prod;
    memset(&prod, 0, sizeof(prod));
    get_product_name_medical(&prod);

    struct descrizione descr;
    memset(&descr, 0, sizeof(descr));
    get_product_description_medical(&descr);

    do_add_product_description(&prod, &descr);

    return false;
}

static bool add_cat(void)
{
    char categoria[STR_LEN];
    get_new_category(categoria);

    do_add_category(categoria);

    return false;
}

static bool add_interaction(void)
{
    struct interazione inter;
    memset(&inter, 0, sizeof(inter));
    get_new_interaction(&inter);

    do_add_interaction(&inter);

    return false;
}

static bool print_cats(void)
{
    struct prodotto prod;
    memset(&prod, 0, sizeof(prod));
    get_product_name_medical(&prod);

    struct interazioni *interazioni = do_get_interacting_categories(&prod);
    if(interazioni != NULL) {
        print_interacting_categories(interazioni);
        dispose_interactions(interazioni);
    }

    return false;
}

static bool print_shelves(void)
{
    struct magazzino *magazzino = do_get_shelves();
    if(magazzino != NULL) {
        print_lista_scaffali_medical(magazzino);
        magazzino_dispose(magazzino);
    }

    return false;
}

static bool record_sale(void)
{
    bool res = true;

    struct scatole_prodotto *scatoleProdotto = NULL;
    struct scatola box;

    struct vendita *vendita = do_record_sale();
    if(vendita != NULL) {
        struct prodotto_venduto prodottoVenduto;
        struct prodotto prod;
        struct prodotto *info_prodotto = NULL;

        do {
            memset(&prod, 0, sizeof(prod));
            get_product_name_medical(&prod);

            info_prodotto = do_get_product_info(&prod);
            if(info_prodotto != NULL) {
                memset(&prodottoVenduto, 0, sizeof(prodottoVenduto));
                strcpy(prodottoVenduto.nome_prodotto, info_prodotto->nome);
                strcpy(prodottoVenduto.nome_fornitore, info_prodotto->nome_fornitore);
                strcpy(&(prodottoVenduto.tipo), &(info_prodotto->tipo));

                get_sold_product_info(&prodottoVenduto);
                do_add_product_to_sale(vendita, &prodottoVenduto);

                if(info_prodotto->tipo == 'M') {
                    scatoleProdotto = do_get_product_boxes(&prodottoVenduto);
                    if (scatoleProdotto != NULL) {
                        print_boxes_codes(scatoleProdotto);

                        do {
                            select_box_to_remove(&box);
                            do_remove_box(&box);    //I'm not interested in the result set here
                        } while(yes_or_no("\nDo you want to remove another box?", 'y', 'n', false, true));
                    }
                }

                free(info_prodotto);
                info_prodotto = NULL;
            }

            res = yes_or_no("\nDo you want to insert another product?", 'y', 'n', false, true);
        } while(res);

        free(vendita);
    }

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
	{.action = PROD_INFO, .control = prod_info},
	{.action = PROD_DESCRIPTION, .control = prod_description},
	{.action = ADD_CAT, .control = add_cat},
    {.action = ADD_INTERACTION, .control = add_interaction},
    {.action = PRINT_CATS, .control = print_cats},
    {.action = PRINT_SHELVES, .control = print_shelves},
    {.action = RECORD_SALE, .control = record_sale},
	{.action = QUIT, .control = quit}
};

void medical_controller(void)
{
	db_switch_to_medical();

	while(true) {
		int action = get_medical_action();
		if(action >= END_OF_ACTIONS) {
			fprintf(stderr, "Error: unknown action\n");
			continue;
		}
		if (controls[action].control())
			break;

		press_anykey();
	}
}