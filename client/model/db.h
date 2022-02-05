#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define DATE_LEN 11
#define TIME_LEN 6
#define DATETIME_LEN (DATE_LEN + TIME_LEN)

#define USERNAME_LEN 45
#define PASSWORD_LEN 45

#define STR_LEN 45
#define TXT_LEN 256

typedef enum {
	LOGIN_ROLE,
	MEDICO,
	AMMIN,
	FAILED_LOGIN
} role_t;

struct credentials {
	char username[USERNAME_LEN];
	char password[PASSWORD_LEN];
};

struct descrizione {
	int codice;
	char text[TXT_LEN];
};

struct prodotto {
	char nome[STR_LEN];
	char nome_fornitore[STR_LEN];
	char tipo;
	int quantita;
	char categoria[STR_LEN];
	unsigned num_usi;
	struct descrizione *usi;
	bool ricetta;
	bool mutuabile;
};

struct prodotti {
    unsigned num_prodotti;
    struct prodotto *lista_prodotti;
};

struct prodotti_magazzino {
    unsigned num_prodotti;
    struct prodotto *prodotti;
};

struct recapito {
	char contatto[STR_LEN];
	bool preferito;
};

struct recapiti {
    unsigned num_recapiti;
    struct recapito *lista_recapiti;
};

struct indirizzo {
	char citta[STR_LEN];
	char via[STR_LEN];
	char num_civico[STR_LEN];
	bool fatturazione;
};

struct indirizzi {
    unsigned num_indirizzi;
    struct indirizzo *lista_indirizzi;
};

struct fornitore {
	char nome[STR_LEN];
	struct indirizzi *indirizzi;
    struct recapiti *recapiti;
};

struct prodotto_richiesto {
	char nome_prodotto[STR_LEN];
	char nome_fornitore[STR_LEN];
	int quantita;
};

struct lettera_acquisto {
	int codice;
	char giorno[DATE_LEN];
	unsigned num_richieste;
	struct prodotto_richiesto *richieste;
};

struct lettere_inviate {
    unsigned num_lettere;
    struct lettera_acquisto *lettere;
};

struct interazione {
	char cat1[STR_LEN];
	char cat2[STR_LEN];
};

struct interazioni {
	unsigned num_interazioni;
	struct interazione *cat_interagenti;
};

struct scaffale {
    int codice;
    char categoria[STR_LEN];
};

struct scatola {
	int codice;
	char scadenza[DATE_LEN];
	int cassetto;
	struct scaffale scaff;
};

struct scatole_prodotto {
	char nome_prodotto[STR_LEN];
	char nome_fornitore[STR_LEN];
	unsigned num_scatole;
	struct scatola *scatole;
};

struct scatole_in_scadenza {
    unsigned num_in_scadenza;
    struct scatole_prodotto * scatole;
};

struct magazzino {
	unsigned num_scaffali;
	struct scaffale *scaffali;
};

struct prodotto_venduto {
	char nome_prodotto[STR_LEN];
	char nome_fornitore[STR_LEN];
	char tipo;
	int quantita;
	char medico[STR_LEN];
	char cf[STR_LEN];
    bool ricetta;
};

struct vendita {
	int scontrino;
	char giorno[DATE_LEN];
	unsigned num_prodotti;
	struct prodotto_venduto *prod_venduti;
};

struct vendite {
    unsigned num_vendite;
    struct vendita *listaVendite;
};

struct prodotti_venduti {
    unsigned num_prodotti;
    struct prodotto_venduto *prod_venduti;
};

extern bool init_db(void);
extern void fini_db(void);

extern void db_switch_to_login(void);
extern void db_switch_to_administration(void);
extern void db_switch_to_medical(void);

extern role_t attempt_login(struct credentials *cred);

extern void do_add_product_description(struct prodotto *prodotto, struct descrizione *descrizione);
extern struct magazzino * do_get_shelves(void);
extern void magazzino_dispose(struct magazzino *magazzino);
extern struct prodotto *do_remove_box(struct scatola *box);
extern void do_decrease_stock(struct prodotto *prod);
extern struct prodotti *do_get_products_list(void);
extern void dispose_products_list(struct prodotti *prodotti);

extern struct prodotto *do_get_product_info(struct prodotto *prod);
extern void do_add_category(char *categoria);
extern void do_add_interaction(struct interazione *inter);
extern struct interazioni *do_get_interacting_categories(struct prodotto *prod);
extern void dispose_interactions(struct interazioni *interazioni);
extern struct vendita *do_record_sale(void);
extern bool do_add_product_to_sale(struct vendita *vendita, struct prodotto_venduto *prodottoVenduto);
extern struct scatole_prodotto *do_get_product_boxes(struct prodotto_venduto *prod);
extern void dispose_scatole_prodotto(struct scatole_prodotto *scatoleProdotto);
extern void do_remove_sale(struct vendita *vendita);

extern void do_add_cosmetic(struct prodotto *prodotto);
extern void do_add_medicine(struct prodotto *prodotto);
extern struct prodotti_magazzino *do_get_stock_report(void);
extern void dispose_stock_report(struct prodotti_magazzino *prodottiMagazzino);
extern void do_remove_product(struct prodotto *prodotto);
extern void do_add_supplier(struct fornitore *fornitore);
extern void do_remove_supplier(struct fornitore *fornitore);
extern struct fornitore *do_get_info_supplier(struct fornitore *fornitore);
extern void dispose_supplier(struct fornitore *fornitore);
extern struct prodotti_magazzino *do_get_supplier_products(struct fornitore *fornitore);
extern void do_add_address(struct indirizzo *indirizzo, struct fornitore *fornitore);
extern void do_remove_address(struct indirizzo *indirizzo);
extern void do_add_contact(struct recapito *recapito, struct fornitore *fornitore);
extern void do_remove_contact(struct recapito *recapito);
extern void do_add_box(struct prodotto *prodotto, struct scatola *scatola);
extern void dispose_in_scadenza(struct scatole_in_scadenza * scatoleInScadenza);
extern struct scatole_in_scadenza *do_get_expiry_report(void);
extern void do_add_shelf(struct scaffale *scaffale);
extern void do_update_shelf_category(struct scaffale *scaffale);
extern struct lettera_acquisto *do_get_purchase_letter(void);
extern void do_add_product_to_letter(struct lettera_acquisto *letteraAcquisto, struct prodotto_richiesto *prodottoRichiesto);
extern struct lettere_inviate *do_get_letters_to_supplier(struct fornitore *fornitore);
extern void dispose_letters(struct lettere_inviate *lettereInviate);
extern struct vendite *do_get_sales_on_date(char giorno[DATE_LEN]);
extern struct vendite *do_get_product_sales(struct prodotto *prodotto);
extern void dispose_sales(struct vendite *vendite);
extern struct prodotti_venduti *do_get_most_sold(void);
extern void dispose_most_sold(struct prodotti_venduti *prodottiVenduti);
extern void do_increase_stock(struct prodotto *prodotto);