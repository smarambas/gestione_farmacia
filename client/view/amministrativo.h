#pragma once
#include "../model/db.h"

enum actions {
    PROD_DESCRIPTION,
    PRINT_SHELVES,
    ADD_COSMETIC,
    ADD_MEDICINE,
    GET_STOCK_REPORT,
    REMOVE_PRODUCT,
    ADD_SUPPLIER,
    REMOVE_SUPPLIER,
    GET_SUPPLIER_INFO,
    GET_SUPPLIER_PROD,
    ADD_ADDRESS,
    REMOVE_ADDRESS,
    ADD_CONTACT,
    REMOVE_CONTACT,
    ADD_BOX,
    GET_EXPIRY_REPORT,
    ADD_SHELF,
    UPDATE_SHELF,
    SEND_LETTER,
    PRINT_LETTERS,
    PRINT_SALES_DATE,
    PRINT_SALES_PROD,
    PRINT_MOST_SOLD,
    QUIT,
    END_OF_ACTIONS
};

extern int get_administrative_action(void);
extern void get_product_name(struct prodotto *prod);
extern void get_product_description(struct descrizione *descr);
extern void print_lista_scaffali(struct magazzino *magazzino);
extern void get_cosmetic(struct prodotto *prod);
extern void get_medicine(struct prodotto *prod);
extern void print_stock_report(struct prodotti_magazzino *prodottiMagazzino);
extern void get_supplier_name(struct fornitore *fornitore);
extern void print_supplier_info(struct fornitore *fornitore);
extern void print_supplier_prod(struct prodotti_magazzino *prodottiMagazzino);
extern void get_supplier_address(struct indirizzo *indirizzo, bool is_add);
extern void get_supplier_contact(struct recapito *recapito, bool is_add);
extern