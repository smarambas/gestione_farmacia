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
extern void get_product_name_medical(struct prodotto *prod);
extern void show_product_info(struct prodotto *prod);
extern void get_product_description_medical(struct descrizione *descr);
extern void get_new_category(char *categoria);
extern void get_new_interaction(struct interazione *inter);
extern void print_interacting_categories(struct interazioni *interazioni);
extern void print_lista_scaffali_medical(struct magazzino *magazzino);
extern void get_sold_product_info(struct prodotto_venduto *prod);
extern void print_boxes_codes(struct scatole_prodotto *scatoleProdotto);
extern void select_box_to_remove(struct scatola *box);
