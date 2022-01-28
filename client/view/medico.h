#pragma once
#include "../model/db.h"

enum actions {
	PROD_INFO,
	PROD_DESCRIPTION,
	ADD_CAT,
	ADD_INTERACTION,
	PRINT_CATS,
	PRINT_SHELVES,
	RECORD_SALE,
	QUIT,
	END_OF_ACTIONS
};

extern int get_medical_action(void);
extern void get_medical_prod_name(struct prodotto *prod);
extern void show_product_info(struct prodotto *prod);