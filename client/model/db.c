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
static MYSQL_STMT *print_shelves;
static MYSQL_STMT *remove_box;
static MYSQL_STMT *update_stock;

//medical procedures
static MYSQL_STMT *print_product_info;
static MYSQL_STMT *add_category;
static MYSQL_STMT *add_interaction;
static MYSQL_STMT *print_interacting_categories;
static MYSQL_STMT *record_sale;
static MYSQL_STMT *add_product_to_sale;

//ammin procedures
static MYSQL_STMT *add_cosmetic;
static MYSQL_STMT *add_medicine;
static MYSQL_STMT *do_stock_report;
static MYSQL_STMT *remove_product;
static MYSQL_STMT *add_supplier;
static MYSQL_STMT *remove_supplier;
static MYSQL_STMT *print_info_supplier;
static MYSQL_STMT *print_supplier_products;
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
static MYSQL_STMT *print_letters_to_supplier;
static MYSQL_STMT *print_sales_on_date;
static MYSQL_STMT *print_product_sales;
static MYSQL_STMT *print_most_sold;


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
	if(print_shelves) {
		mysql_stmt_close(print_shelves);
		print_shelves = NULL;
	}
	if(remove_box) {
		mysql_stmt_close(remove_box);
		remove_box = NULL;
	}
	if(update_stock) {
		mysql_stmt_close(update_stock);
		update_stock = NULL;
	}
	if(print_product_info) {
		mysql_stmt_close(print_product_info);
		print_product_info = NULL;
	}
	if(add_category) {
		mysql_stmt_close(add_category);
		add_category = NULL;
	}
	if(add_interaction) {
		mysql_stmt_close(add_interaction);
		add_interaction = NULL;
	}
	if(print_interacting_categories) {
		mysql_stmt_close(print_interacting_categories);
		print_interacting_categories = NULL;
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
	if(print_info_supplier) {
		mysql_stmt_close(print_info_supplier);
		print_info_supplier = NULL;
	}
	if(print_supplier_products) {
		mysql_stmt_close(print_supplier_products);
		print_supplier_products = NULL;
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
	if(print_letters_to_supplier) {
		mysql_stmt_close(print_letters_to_supplier);
		print_letters_to_supplier = NULL;
	}
	if(print_sales_on_date) {
		mysql_stmt_close(print_sales_on_date);
		print_sales_on_date = NULL;
	}
	if(print_product_sales) {
		mysql_stmt_close(print_product_sales);
		print_product_sales = NULL;
	}
	if(print_most_sold) {
		mysql_stmt_close(print_most_sold);
		print_most_sold = NULL;
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
			if(!setup_prepared_stmt(&print_info_supplier, "call info_fornitore(?)", conn)) {
				print_stmt_error(print_info_supplier, "Unable to initialize print info supplier statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&print_supplier_products, "call lista_prodotti_fornitore(?)", conn)) {
				print_stmt_error(print_supplier_products, "Unable to initialize print supplier products statement\n");
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
			if(!setup_prepared_stmt(&print_letters_to_supplier, "call lista_lettere_inviate(?)", conn)) {
				print_stmt_error(print_letters_to_supplier, "Unable to initialize print letters to supplier statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&print_sales_on_date, "call lista_vendite_data(?)", conn)) {
				print_stmt_error(print_sales_on_date, "Unable to initialize print sales on date statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&print_product_sales, "call vendite_prodotto(?, ?)", conn)) {
				print_stmt_error(print_product_sales, "Unable to initialize print product sales statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&print_most_sold, "call lista_prodotti_top()", conn)) {
				print_stmt_error(print_most_sold, "Unable to initialize print most sold statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&add_product_description, "call aggiungi_uso(?, ?, ?)", conn)) {
				print_stmt_error(add_product_description, "Unable to initialize add product description statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&print_shelves, "call lista_scaffali()", conn)) {
				print_stmt_error(print_shelves, "Unable to initialize print shelves statement\n");
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
			if(!setup_prepared_stmt(&print_product_info, "call info_prodotto(?, ?)", conn)) {
				print_stmt_error(print_product_info, "Unable to initialize print product info statement\n");
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
			if(!setup_prepared_stmt(&print_interacting_categories, "call lista_cat_interagenti(?, ?)", conn)) {
				print_stmt_error(print_interacting_categories, "Unable to initialize print interacting categories statement\n");
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
			if(!setup_prepared_stmt(&print_shelves, "call lista_scaffali()", conn)) {
				print_stmt_error(print_shelves, "Unable to initialize print shelves statement\n");
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

