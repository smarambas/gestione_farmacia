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
    REMOVE_BOX,
    GET_EXPIRY_REPORT,
    ADD_SHELF,
    UPDATE_SHELF,
    SEND_LETTER,
    GET_SUPPLIER_LETTERS,
    GET_SALES_DATE,
    GET_SALES_PROD,
    GET_MOST_SOLD,
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
extern void get_box_info(struct scatola *scatola);
extern void get_box_code(struct scatola *scatola, bool clear);
extern void print_expiry_report(struct scatole_in_scadenza *scatoleInScadenza);
extern void get_shelf_category(struct scaffale *scaffale);
extern void modify_shelf_category(struct scaffale *scaffale);
extern void get_product_for_letter(struct prodotto_richiesto *prodottoRichiesto);
extern void print_supplier_letters(struct lettere_inviate *lettereInviate, struct fornitore *fornitore);
extern void get_date(char *date);
extern void print_sales_on_date(struct vendite *vendite, char *giorno);
extern void print_sales_product(struct vendite *vendite, struct prodotto *prodotto);
extern void print_most_sold(struct prodotti_venduti *prodottiVenduti);
