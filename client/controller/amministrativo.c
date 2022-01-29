#include <stdio.h>
#include <string.h>
#include "amministrativo.h"

#include "../model/db.h"
#include "../view/amministrativo.h"
#include "../utils/io.h"



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
    {.action = PRINT_SUPPLIER_INFO, .control = print_supplier_info},
    {.action = PRINT_SUPPLIER_PROD, .control = print_supplier_prod},
    {.action = ADD_ADDRESS, .control = add_address},
    {.action = REMOVE_ADDRESS, .control = remove_address},
    {.action = ADD_CONTACT, .control = add_contact},
    {.action = REMOVE_CONTACT, .control = remove_contact},
    {.action = ADD_BOX, .control = add_box},
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