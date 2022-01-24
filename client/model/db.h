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
}

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
}

struct recapito {
	char contatto[STR_LEN];
	bool preferito;
}

struct indirizzo {
	char citta[STR_LEN];
	char via[STR_LEN];
	char num_civico[STR_LEN];
	bool fatturazione;
}

struct fornitore {
	char nome[STR_LEN];
	unsigned num_recapiti;
	struct recapito recapiti[];
	unsigned num_indirizzi;
	struct indirizzo indirizzi[];
}

struct prodotto_richiesto {
	char nome_prodotto[STR_LEN];
	char nome_fornitore[STR_LEN];
	int quantita;
}

struct lettera_acquisto {
	int codice;
	char giorno[DATE_LEN];
	unsigned num_richieste;
	struct prodotto_richiesto richieste[];
}

struct interazioni {
	char nome_categoria[STR_LEN];
	unsigned num_interazioni;
	char cat_interagenti[][STR_LEN];
}

struct scatola {
	int codice;
	char scadenza[DATE_LEN];
	int cassetto;
	struct scaffale scaff;
}

struct scatole_prodotto {
	char nome_prodotto[STR_LEN];
	char nome_fornitore[STR_LEN];
	unsigned num_scatole;
	struct scatola scatole[];
}

struct scaffale {
	int codice;
	char categoria[STR_LEN];
}

struct magazzino {
	unsigned num_scaffali;
	struct scaffale scaffali[];
}

struct prodotto_venduto {
	char nome_prodotto[STR_LEN];
	char nome_fornitore[STR_LEN];
	char tipo;
	int quantita;
	char medico[STR_LEN];
	char cf[STR_LEN];
}

struct vendita {
	int scontrino;
	char giorno[DATE_LEN];
	unsigned num_prodotti;
	struct prodotto_venduto prod_venduti[];
}


extern bool init_db(void);
extern void fini_db(void);

extern void db_switch_to_login(void);
extern void db_switch_to_administrator(void);
extern void db_switch_to_medical(void);

extern role_t attempt_login(struct credentials *cred);

extern void do_add_product_description(struct prodotto *prodotto, struct descrizione *descrizione);
extern struct scaffale * do_get_shelves(void);
extern void magazzino_dispose(struct magazzino *magazzino);
extern void do_remove_box(struct scatola *box);
extern void do_update_stock(struct prodotto *prodotto) 

extern struct prodotto *do_get_product_info(struct prodotto *prod);

