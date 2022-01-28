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
    get_medical_prod_name(&prod);

    struct prodotto *info_prodotto = do_get_product_info(&prod);
    if(info_prodotto != NULL) {
        show_product_info(info_prodotto);
    }
    return false;
}

static bool prod_description(void)
{

}

static bool add_cat(void)
{

}

static bool add_interaction(void)
{

}

static bool print_cats(void)
{

}

static bool print_shelves(void)
{

}

static bool record_sale(void)
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
	{.action = PROD_INFO, .control = prod_info},
	{.action = PROD_DESCRIPTION, .control = prod_description},
	{.action = ADD_CAT, .control = add_cat},
    {.action = ADD_INTERACTION, .control = add_interaction},
    {.action = PRINT_CATS, .control = print_cats},
    {.action = PRINT_SHELVES, .control = print_shelves},
    {.action = RECORD_SALE, .control = record_sale},
	{.action = QUIT, .control = quit}
};

void controller_medico(void)
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