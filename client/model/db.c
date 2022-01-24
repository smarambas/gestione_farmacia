#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include <assert.h>

#include "db.h"
#include "../utils/db.h"

static MYSQL *conn;

static MYSQL_STMT *login_procedure;

//ammin/medical procedures
static MYSQL_STMT *add_product_description;
static MYSQL_STMT *get_shelves;
static MYSQL_STMT *remove_box;
static MYSQL_STMT *update_stock;

//medical procedures
static MYSQL_STMT *get_product_info;
static MYSQL_STMT *add_category;
static MYSQL_STMT *add_interaction;
static MYSQL_STMT *get_interacting_categories;
static MYSQL_STMT *record_sale;
static MYSQL_STMT *add_product_to_sale;

//ammin procedures
static MYSQL_STMT *add_cosmetic;
static MYSQL_STMT *add_medicine;
static MYSQL_STMT *do_stock_report;
static MYSQL_STMT *remove_product;
static MYSQL_STMT *add_supplier;
static MYSQL_STMT *remove_supplier;
static MYSQL_STMT *get_info_supplier;
static MYSQL_STMT *get_supplier_products;
static MYSQL_STMT *add_address;
static MYSQL_STMT *remove_address;
static MYSQL_STMT *add_contact;
static MYSQL_STMT *remove_contact;
static MYSQL_STMT *add_box;
static MYSQL_STMT *do_expiry_report;
static MYSQL_STMT *add_shelf;
static MYSQL_STMT *update_shelf_category;
static MYSQL_STMT *do_purchase_letter;
static MYSQL_STMT *add_product_to_letter;
static MYSQL_STMT *get_letters_to_supplier;
static MYSQL_STMT *get_sales_on_date;
static MYSQL_STMT *get_product_sales;
static MYSQL_STMT *get_most_sold;


static void close_prepared_stmts(void)
{
	if(login_procedure) {
		mysql_stmt_close(login_procedure);
		login_procedure = NULL;
	}
	if(add_product_description) {
		mysql_stmt_close(add_product_description);
		add_product_description = NULL;
	}
	if(get_shelves) {
		mysql_stmt_close(get_shelves);
		get_shelves = NULL;
	}
	if(remove_box) {
		mysql_stmt_close(remove_box);
		remove_box = NULL;
	}
	if(update_stock) {
		mysql_stmt_close(update_stock);
		update_stock = NULL;
	}
	if(get_product_info) {
		mysql_stmt_close(get_product_info);
		get_product_info = NULL;
	}
	if(add_category) {
		mysql_stmt_close(add_category);
		add_category = NULL;
	}
	if(add_interaction) {
		mysql_stmt_close(add_interaction);
		add_interaction = NULL;
	}
	if(get_interacting_categories) {
		mysql_stmt_close(get_interacting_categories);
		get_interacting_categories = NULL;
	}
	if(record_sale) {
		mysql_stmt_close(record_sale);
		record_sale = NULL;
	}
	if(add_product_to_sale) {
		mysql_stmt_close(add_product_to_sale);
		add_product_to_sale = NULL;
	}
	if(add_cosmetic) {
		mysql_stmt_close(add_cosmetic);
		add_cosmetic = NULL;
	}
	if(add_medicine) {
		mysql_stmt_close(add_medicine);
		add_medicine = NULL;
	}
	if(do_stock_report) {
		mysql_stmt_close(do_stock_report);
		do_stock_report = NULL;
	}
	if(remove_product) {
		mysql_stmt_close(remove_product);
		remove_product = NULL;
	}
	if(add_supplier) {
		mysql_stmt_close(add_supplier);
		add_supplier = NULL;
	}
	if(remove_supplier) {
		mysql_stmt_close(remove_supplier);
		remove_supplier = NULL;
	}
	if(get_info_supplier) {
		mysql_stmt_close(get_info_supplier);
		get_info_supplier = NULL;
	}
	if(get_supplier_products) {
		mysql_stmt_close(get_supplier_products);
		get_supplier_products = NULL;
	}
	if(add_address) {
		mysql_stmt_close(add_address);
		add_address = NULL;
	}
	if(remove_address) {
		mysql_stmt_close(remove_address);
		remove_address = NULL;
	}
	if(add_contact) {
		mysql_stmt_close(add_contact);
		add_contact = NULL;
	}
	if(remove_contact) {
		mysql_stmt_close(remove_contact);
		remove_contact = NULL;
	}
	if(add_box) {
		mysql_stmt_close(add_box);
		add_box = NULL;
	}
	if(do_expiry_report) {
		mysql_stmt_close(do_expiry_report);
		do_expiry_report = NULL;
	}
	if(add_shelf) {
		mysql_stmt_close(add_shelf);
		add_shelf = NULL;
	}
	if(update_shelf_category) {
		mysql_stmt_close(update_shelf_category);
		update_shelf_category = NULL;
	}
	if(do_purchase_letter) {
		mysql_stmt_close(do_purchase_letter);
		do_purchase_letter = NULL;
	}
	if(add_product_to_letter) {
		mysql_stmt_close(add_product_to_letter);
		add_product_to_letter = NULL;
	}
	if(get_letters_to_supplier) {
		mysql_stmt_close(get_letters_to_supplier);
		get_letters_to_supplier = NULL;
	}
	if(get_sales_on_date) {
		mysql_stmt_close(get_sales_on_date);
		get_sales_on_date = NULL;
	}
	if(get_product_sales) {
		mysql_stmt_close(get_product_sales);
		get_product_sales = NULL;
	}
	if(get_most_sold) {
		mysql_stmt_close(get_most_sold);
		get_most_sold = NULL;
	}
}


static bool initialize_prepared_stmts(role_t for_role)
{
	switch(for_role) {

		case LOGIN_ROLE:
			if(!setup_prepared_stmt(&login_procedure, "call login(?, ?, ?)", conn)) {
				print_stmt_error(login_procedure, "Unable to initialize login statement\n");
				return false;
			}
			break;
		case AMMIN:
			if(!setup_prepared_stmt(&add_cosmetic, "call aggiungi_cosmetico(?, ?)", conn)) {
				print_stmt_error(add_cosmetic, "Unable to initialize add cosmetic statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_medicine, "call aggiungi_medicinale(?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(add_medicine, "Unable to initialize add medicine statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&do_stock_report, "call genera_report_magazzino()", conn)) {
				print_stmt_error(do_stock_report, "Unable to initialize do stock report statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&remove_product, "call rimuovi_prodotto(?, ?)", conn)) {
				print_stmt_error(remove_product, "Unable to initialize remove product statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_supplier, "call aggiungi_fornitore(?)", conn)) {
				print_stmt_error(add_supplier, "Unable to initialize add supplier statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&remove_supplier, "call rimuovi_fornitore(?)", conn)) {
				print_stmt_error(remove_supplier, "Unable to initialize remove supplier statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&get_info_supplier, "call info_fornitore(?)", conn)) {
				print_stmt_error(get_info_supplier, "Unable to initialize get info supplier statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&get_supplier_products, "call lista_prodotti_fornitore(?)", conn)) {
				print_stmt_error(get_supplier_products, "Unable to initialize get supplier products statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_address, "call aggiungi_indirizzo(?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(add_address, "Unable to initialize add address statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&remove_address, "call rimuovi_indirizzo(?, ?, ?)", conn)) {
				print_stmt_error(remove_address, "Unable to initialize remove address statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_contact, "call aggiungi_recapito(?, ?, ?)", conn)) {
				print_stmt_error(add_contact, "Unable to initialize add contact statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&remove_contact, "call rimuovi_recapito(?)", conn)) {
				print_stmt_error(remove_contact, "Unable to initialize remove contact statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_box, "call aggiungi_scatola(?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(add_box, "Unable to initialize add box statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&do_expiry_report, "call genera_report_scandenze()", conn)) {
				print_stmt_error(do_expiry_report, "Unable to initialize do expiry report statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_shelf, "call aggiungi_scaffale(?)", conn)) {
				print_stmt_error(add_shelf, "Unable to initialize add shelf statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&update_shelf_category, "call modifica_cat_scaffale(?, ?)", conn)) {
				print_stmt_error(update_shelf_category, "Unable to initialize update shelf category statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&do_purchase_letter, "call genera_lettera_acquisto()", conn)) {
				print_stmt_error(do_purchase_letter, "Unable to initialize do purchase letter statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_product_to_letter, "call aggiungi_richiesta_prodotto(?, ?, ?, ?)", conn)) {
				print_stmt_error(add_product_to_letter, "Unable to initialize add product to letter statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&get_letters_to_supplier, "call lista_lettere_inviate(?)", conn)) {
				print_stmt_error(get_letters_to_supplier, "Unable to initialize get letters to supplier statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&get_sales_on_date, "call lista_vendite_data(?)", conn)) {
				print_stmt_error(get_sales_on_date, "Unable to initialize get sales on date statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&get_product_sales, "call vendite_prodotto(?, ?)", conn)) {
				print_stmt_error(get_product_sales, "Unable to initialize get product sales statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&get_most_sold, "call lista_prodotti_top()", conn)) {
				print_stmt_error(get_most_sold, "Unable to initialize get most sold statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_product_description, "call aggiungi_uso(?, ?, ?)", conn)) {
				print_stmt_error(add_product_description, "Unable to initialize add product description statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&get_shelves, "call lista_scaffali()", conn)) {
				print_stmt_error(get_shelves, "Unable to initialize get shelves statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&remove_box, "call rimuovi_scatola(?)", conn)) {
				print_stmt_error(remove_box, "Unable to initialize remove box statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&update_stock, "call aggiorna_giacenza(?, ?, ?)", conn)) {
				print_stmt_error(update_stock, "Unable to initialize update stock statement\n");
				return false;
			}
			break;
		case MEDICO:
			if(!setup_prepared_stmt(&get_product_info, "call info_prodotto(?, ?)", conn)) {
				print_stmt_error(get_product_info, "Unable to initialize get product info statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_category, "call aggiungi_categoria(?)", conn)) {
				print_stmt_error(add_category, "Unable to initialize add category statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_interaction, "call aggiungi_interazione(?, ?)", conn)) {
				print_stmt_error(add_interaction, "Unable to initialize add interaction statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&get_interacting_categories, "call lista_cat_interagenti(?, ?)", conn)) {
				print_stmt_error(get_interacting_categories, "Unable to initialize get interacting categories statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&record_sale, "call registra_vendita()", conn)) {
				print_stmt_error(record_sale, "Unable to initialize record sale statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_product_to_sale, "call aggiungi_prodotto_venduto(?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(add_product_to_sale, "Unable to initialize add product to sale statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_product_description, "call aggiungi_uso(?, ?, ?)", conn)) {
				print_stmt_error(add_product_description, "Unable to initialize add product description statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&get_shelves, "call lista_scaffali()", conn)) {
				print_stmt_error(get_shelves, "Unable to initialize get shelves statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&remove_box, "call rimuovi_scatola(?)", conn)) {
				print_stmt_error(remove_box, "Unable to initialize remove box statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&update_stock, "call aggiorna_giacenza(?, ?, ?)", conn)) {
				print_stmt_error(update_stock, "Unable to initialize update stock statement\n");
				return false;
			}
			break;
		default:
			fprintf(stderr, "[FATAL] Unexpected role to prepare statements.\n");
			exit(EXIT_FAILURE);
	}

	return true;
}


bool init_db(void)
{
	unsigned int timeout = 300;
	bool reconnect = true;

	conn = mysql_init(NULL);
	if(conn == NULL) {
		finish_with_error(conn, "mysql_init() failed (probably out of memory)\n");
	}

	if(mysql_real_connect(conn, getenv("HOST"), getenv("LOGIN_USER"), getenv("LOGIN_PASS"), getenv("DB"),
			      atoi(getenv("PORT")), NULL,
			      CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS | CLIENT_COMPRESS | CLIENT_INTERACTIVE | CLIENT_REMEMBER_OPTIONS) == NULL) {
		finish_with_error(conn, "mysql_real_connect() failed\n");
	}

	if (mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout)) {
		print_error(conn, "[mysql_options] failed.");
	}
	if(mysql_options(conn, MYSQL_OPT_RECONNECT, &reconnect)) {
		print_error(conn, "[mysql_options] failed.");
	}
#ifndef NDEBUG
	mysql_debug("d:t:O,/tmp/client.trace");
	if(mysql_dump_debug_info(conn)) {
		print_error(conn, "[debug_info] failed.");
	}
#endif

	return initialize_prepared_stmts(LOGIN_ROLE);
}


void fini_db(void)
{
	close_prepared_stmts();

	mysql_close(conn);
}


void db_switch_to_login(void)
{
	close_prepared_stmts();
	if(mysql_change_user(conn, getenv("LOGIN_USER"), getenv("LOGIN_PASS"), getenv("DB"))) {
		fprintf(stderr, "mysql_change_user() failed: %s\n", mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	if(!initialize_prepared_stmts(LOGIN_ROLE)) {
		fprintf(stderr, "[FATAL] Cannot initialize prepared statements.\n");
		exit(EXIT_FAILURE);
	}
}


void db_switch_to_administrator(void)
{
	close_prepared_stmts();
	if(mysql_change_user(conn, getenv("ADMIN_USER"), getenv("ADMIN_PASS"), getenv("DB"))) {
		fprintf(stderr, "mysql_change_user() failed: %s\n", mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	if(!initialize_prepared_stmts(AMMIN)) {
		fprintf(stderr, "[FATAL] Cannot initialize prepared statements.\n");
		exit(EXIT_FAILURE);
	}
}


void db_switch_to_medical(void)
{
	close_prepared_stmts();
	if(mysql_change_user(conn, getenv("MEDICAL_USER"), getenv("MEDICAL_PASS"), getenv("DB"))) {
		fprintf(stderr, "mysql_change_user() failed: %s\n", mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	if(!initialize_prepared_stmts(MEDICO)) {
		fprintf(stderr, "[FATAL] Cannot initialize prepared statements.\n");
		exit(EXIT_FAILURE);
	}
}


role_t attempt_login(struct credentials *cred)
{
	MYSQL_BIND param[3]; // Used both for input and output
	int role = 0;

	// Prepare parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cred->username, strlen(cred->username));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cred->password, strlen(cred->password));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &role, sizeof(role));

	if(mysql_stmt_bind_param(login_procedure, param) != 0) { // Note _param
		print_stmt_error(login_procedure, "Could not bind parameters for login");
		role = FAILED_LOGIN;
		goto out;
	}

	// Run procedure
	if(mysql_stmt_execute(login_procedure) != 0) {
		print_stmt_error(login_procedure, "Could not execute login procedure");
		role = FAILED_LOGIN;
		goto out;
	}

	// Prepare output parameters
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &role, sizeof(role));

	if(mysql_stmt_bind_result(login_procedure, param)) {
		print_stmt_error(login_procedure, "Could not retrieve output parameter");
		role = FAILED_LOGIN;
		goto out;
	}

	// Retrieve output parameter
	if(mysql_stmt_fetch(login_procedure)) {
		print_stmt_error(login_procedure, "Could not buffer results");
		role = FAILED_LOGIN;
		goto out;
	}

    out:
	// Consume the possibly-returned table for the output parameter
	while(mysql_stmt_next_result(login_procedure) != -1) {}

	mysql_stmt_free_result(login_procedure);
	mysql_stmt_reset(login_procedure);
	return role;
}

void do_add_product_description(struct prodotto *prodotto, struct descrizione *descrizione) 
{
	MYSQL_BIND param[3];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prodotto->nome, strlen(prodotto->nome));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prodotto->nome_fornitore, strlen(prodotto->nome_fornitore));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, descrizione->text, strlen(descrizione->text));	

	if(mysql_stmt_bind_param(add_product_description, param) != 0) {
		print_stmt_error(add_product_description, "Could not bind parameters for do_add_product_description");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_product_description) != 0) {
		print_stmt_error(add_product_description, "Could not execute add product description procedure");
		return;
	}

	mysql_stmt_free_result(add_product_description);
	mysql_stmt_reset(add_product_description);
}

struct scaffale *do_get_shelves(void)
{
	int status;
	size_t row = 0;
	MYSQL_BIND param[2];
	int codice;
	char categoria[STR_LEN];
	
	struct magazzino *magazzino = NULL;
	
	// Run procedure
	if(mysql_stmt_execute(get_shelves) != 0) {
		print_stmt_error(get_shelves, "Could not execute get shelves procedure");
		goto out;
	}
	
	mysql_stmt_store_result(get_shelves);
	
	magazzino = malloc(sizeof(*magazzino) + sizeof(struct scaffale) * mysql_stmt_num_rows(get_shelves));
	if(magazzino == NULL)
		goto out;
	memset(magazzino, 0, sizeof(*magazzino) + sizeof(struct scaffale) * mysql_stmt_num_rows(get_shelves));
	magazzino->num_scaffali = mysql_stmt_num_rows(get_shelves);
	
	// Get bound parameters
	mysql_stmt_store_result(get_shelves);
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &codice, sizeof(codice));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, categoria, STR_LEN);
	
	if(mysql_stmt_bind_result(get_shelves, param)) {
		print_stmt_error(get_shelves, "Unable to bind output parameters for get shelves\n");
		free(magazzino);
		magazzino = NULL;
		goto out;
	}
	
	while (true) {
		status = mysql_stmt_fetch(get_shelves);

		if (status == 1 || status == MYSQL_NO_DATA)
			break;

		strcpy(magazzino->magazzino[row].codice, codice);
		strcpy(magazzino->magazzino[row].categoria, categoria);
		
		row++;
	}
	
    out:
	mysql_stmt_free_result(get_shelves);
	mysql_stmt_reset(get_shelves);
	return magazzino;
}

void magazzino_dispose(struct magazzino *magazzino)
{
	free(magazzino);
}

void do_remove_box(struct scatola *box)
{
	MYSQL_BIND param[1];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_LONG, scatola->codice, strlen(scatola->codice));

	if(mysql_stmt_bind_param(remove_box, param) != 0) {
		print_stmt_error(remove_box, "Could not bind parameters for remove_box");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(remove_box) != 0) {
		print_stmt_error(remove_box, "Could not execute remove box procedure");
		return;
	}

	mysql_stmt_free_result(remove_box);
	mysql_stmt_reset(remove_box);
}

void do_update_stock(struct prodotto *prodotto) 
{
	MYSQL_BIND param[3];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prodotto->nome, strlen(prodotto->nome));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prodotto->nome_fornitore, strlen(prodotto->nome_fornitore));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, prodotto->quantita, strlen(prodotto->quantita));

	if(mysql_stmt_bind_param(update_stock, param) != 0) {
		print_stmt_error(update_stock, "Could not bind parameters for update_stock");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(update_stock) != 0) {
		print_stmt_error(update_stock, "Could not execute update stock procedure");
		return;
	}

	mysql_stmt_free_result(update_stock);
	mysql_stmt_reset(update_stock);
}

struct prodotto *do_get_product_info(struct prodotto *prod)
{
	int status, cont = 0;
	size_t row = 0;
	MYSQL_BIND param[8];
	
	char nome[STR_LEN];
	char nome_fornitore[STR_LEN];
	char tipo;
	int quantita;
	char categoria[STR_LEN];
	bool ricetta;
	bool mutuabile;
	char descrizione[TXT_LEN];
	
	struct prodotto *prodotto = NULL;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prod->nome, strlen(prod->nome));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prod->nome_fornitore, strlen(prod->nome_fornitore));
	
	if(mysql_stmt_bind_param(get_product_info, param)) {
		print_stmt_error(get_product_info, "Could not bind input parameters");
		goto out;
	}

	// Run procedure
	if(mysql_stmt_execute(get_product_info) != 0) {
		print_stmt_error(get_product_info, "Could not execute get product info procedure");
		goto out;
	}
	
	mysql_stmt_store_result(get_product_info);
	
	prodotto = malloc(sizeof(*prodotto));
	if(prodotto == NULL)
		goto out;
	memset(prodotto, 0, sizeof(*prodotto));
	prodotto->num_usi = mysql_stmt_num_rows(get_product_info);	
	
	prodotto->usi = malloc(sizeof(struct descrizione) * mysql_stmt_num_rows(get_product_info));
	if(prodotto->usi == NULL)
		goto out;
	memset(prodotto->usi, 0, sizeof(struct descrizione) * mysql_stmt_num_rows(get_product_info));

	// Prepare output parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nome, STR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, nome_fornitore, STR_LEN);
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, &tipo, sizeof(tipo));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &quantita, sizeof(quantita));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, categoria, STR_LEN);
	set_binding_param(&param[5], MYSQL_TYPE_TINY, &ricetta, sizeof(ricetta));
	set_binding_param(&param[6], MYSQL_TYPE_TINY, &mutuabile, sizeof(mutuabile));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, descrizione, TXT_LEN);
	
	if(mysql_stmt_bind_result(get_product_info, param)) {
		print_stmt_error(get_product_info, "Unable to bind output parameters for get product info\n");
		free(prodotto);
		prodotto = NULL;
		goto out;
	}
	
	while (true) {
		status = mysql_stmt_fetch(get_product_info);

		if (status == 1 || status == MYSQL_NO_DATA)
			break;

		if(cont == 0) {
			strcpy(prodotto->prodotto[row].nome, nome);
			strcpy(prodotto->prodotto[row].nome_fornitore, nome_fornitore);
			strcpy(prodotto->prodotto[row].tipo, tipo);
			prodotto->prodotto[row].quantita = quantita;
			strcpy(prodotto->prodotto[row].categoria, categoria);
			prodotto->prodotto[row].ricetta = ricetta;
			prodotto->prodotto[row].mutuabile = mutuabile;
		}
		strcpy(prodotto->prodotto[row].usi[cont], descrizione);
		
		cont++;
		row++;
	}
	
    out:
	mysql_stmt_free_result(get_product_info);
	mysql_stmt_reset(get_product_info);
	return prodotto;
}


































