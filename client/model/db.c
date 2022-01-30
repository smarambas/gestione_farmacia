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
static MYSQL_STMT *decrease_stock;

//medical procedures
static MYSQL_STMT *get_product_info;
static MYSQL_STMT *add_category;
static MYSQL_STMT *add_interaction;
static MYSQL_STMT *get_interacting_categories;
static MYSQL_STMT *record_sale;
static MYSQL_STMT *add_product_to_sale;
static MYSQL_STMT *get_product_boxes;

//ammin procedures
static MYSQL_STMT *add_cosmetic;
static MYSQL_STMT *add_medicine;
static MYSQL_STMT *get_stock_report;
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
static MYSQL_STMT *get_expiry_report;
static MYSQL_STMT *add_shelf;
static MYSQL_STMT *update_shelf_category;
static MYSQL_STMT *get_purchase_letter;
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
    if(get_product_boxes) {
        mysql_stmt_close(get_product_boxes);
		get_product_boxes = NULL;
    }
	if(remove_box) {
		mysql_stmt_close(remove_box);
		remove_box = NULL;
	}
	if(update_stock) {
		mysql_stmt_close(update_stock);
		update_stock = NULL;
	}
    if(decrease_stock) {
		mysql_stmt_close(decrease_stock);
		decrease_stock = NULL;
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
	if(get_stock_report) {
		mysql_stmt_close(get_stock_report);
		get_stock_report = NULL;
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
	if(get_expiry_report) {
		mysql_stmt_close(get_expiry_report);
		get_expiry_report = NULL;
	}
	if(add_shelf) {
		mysql_stmt_close(add_shelf);
		add_shelf = NULL;
	}
	if(update_shelf_category) {
		mysql_stmt_close(update_shelf_category);
		update_shelf_category = NULL;
	}
	if(get_purchase_letter) {
		mysql_stmt_close(get_purchase_letter);
		get_purchase_letter = NULL;
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
			if(!setup_prepared_stmt(&get_stock_report, "call genera_report_magazzino()", conn)) {
				print_stmt_error(get_stock_report, "Unable to initialize get stock report statement\n");
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
			if(!setup_prepared_stmt(&get_expiry_report, "call genera_report_scandenze()", conn)) {
				print_stmt_error(get_expiry_report, "Unable to initialize get expiry report statement\n");
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
			if(!setup_prepared_stmt(&get_purchase_letter, "call genera_lettera_acquisto()", conn)) {
				print_stmt_error(get_purchase_letter, "Unable to initialize get purchase letter statement\n");
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
            if(!setup_prepared_stmt(&get_product_boxes, "call lista_scatole_prodotto(?, ?)", conn)) {
				print_stmt_error(get_product_boxes, "Unable to initialize get product boxes statement\n");
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
            if(!setup_prepared_stmt(&decrease_stock, "call decrementa_giacenza(?, ?)", conn)) {
				print_stmt_error(decrease_stock, "Unable to initialize decrease stock statement\n");
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
            if(!setup_prepared_stmt(&get_product_boxes, "call lista_scatole_prodotto(?, ?)", conn)) {
                print_stmt_error(get_product_boxes, "Unable to initialize get product boxes statement\n");
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
            if(!setup_prepared_stmt(&decrease_stock, "call decrementa_giacenza(?, ?)", conn)) {
				print_stmt_error(decrease_stock, "Unable to initialize decrease stock statement\n");
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


void db_switch_to_administration(void)
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

struct magazzino *do_get_shelves(void)
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

struct scatole_prodotto *do_get_product_boxes(struct prodotto_venduto *prod)
{
    int status;
	size_t row = 0;
	MYSQL_BIND param[3];

    int codice;
    int cassetto;
    int scaffale;

	struct scatole_prodotto *scatoleProdotto = NULL;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prod->nome_prodotto, strlen(prod->nome));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prod->nome_fornitore, strlen(prod->nome_fornitore));

	if(mysql_stmt_bind_param(get_product_boxes, param)) {
		print_stmt_error(get_product_boxes, "Could not bind input parameters");
		goto out;
	}

	// Run procedure
	if(mysql_stmt_execute(get_product_boxes) != 0) {
        if (conn != NULL) {
            if(strcmp(mysql_sqlstate(conn), "45003") != 0)
                print_stmt_error(get_product_boxes, "Could not execute get product boxes procedure");
        }

		goto out;
	}

	mysql_stmt_store_result(get_product_boxes);

    scatoleProdotto = malloc(sizeof(*scatoleProdotto) + sizeof(struct scatola) * mysql_stmt_num_rows(get_product_boxes));
    if(scatoleProdotto == NULL)
		goto out;
    memset(scatoleProdotto, 0, sizeof(*scatoleProdotto) + sizeof(struct scatola) * mysql_stmt_num_rows(get_product_boxes));
    scatoleProdotto->num_scatole = mysql_stmt_num_rows(get_product_boxes);

	// Prepare output parameters
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &codice, sizeof(codice));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &cassetto, sizeof(cassetto));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &scaffale, sizeof(scaffale));

	if(mysql_stmt_bind_result(get_product_boxes, param)) {
		print_stmt_error(get_product_boxes, "Unable to bind output parameters for get product boxes\n");
		free(scatoleProdotto);
		scatoleProdotto = NULL;
		goto out;
	}

    strcpy(scatoleProdotto->nome_prodotto, prod->nome);
    strcpy(scatoleProdotto->nome_fornitore, prod->nome_fornitore);

	while (true) {
		status = mysql_stmt_fetch(get_product_boxes);

		if (status == 1 || status == MYSQL_NO_DATA)
			break;

		scatoleProdotto->scatole[row].codice = codice;
        scatoleProdotto->scatole[row].cassetto = cassetto;
        scatoleProdotto->scatole[row].scaff.codice = scaffale;

		row++;
	}

    out:
	mysql_stmt_free_result(get_product_boxes);
	mysql_stmt_reset(get_product_boxes);
	return scatoleProdotto;
}

struct prodotto *do_remove_box(struct scatola *box)
{
	MYSQL_BIND param[2];

    char nome_prodotto[STR_LEN];
    char nome_fornitore[STR_LEN];

    struct prodotto *prodotto = NULL;

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &(box->codice), strlen(box->codice));

	if(mysql_stmt_bind_param(remove_box, param) != 0) {
		print_stmt_error(remove_box, "Could not bind parameters for remove_box");
		goto out;
	}

	// Run procedure
	if(mysql_stmt_execute(remove_box) != 0) {
		print_stmt_error(remove_box, "Could not execute remove box procedure");
		goto out;
	}

    mysql_stmt_store_result(remove_box);

    prodotto = malloc(sizeof(*prodotto));
    if(prodotto == NULL) {
        goto out;
    }
    memset(prodotto, 0, sizeof(*prodotto));

    // Prepare output parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nome_prodotto, STR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, nome_fornitore, STR_LEN);

    if(mysql_stmt_bind_result(remove_box, param)) {
		print_stmt_error(remove_box, "Unable to bind output parameters for remove box\n");
		free(prodotto);
		prodotto = NULL;
		goto out;
	}

    while (true) {
		status = mysql_stmt_fetch(get_product_boxes);

		if (status == 1 || status == MYSQL_NO_DATA)
			break;

        strcpy(prodotto->nome, nome_prodotto);
        strcpy(prodotto->nome_fornitore, nome_fornitore);
	}

    out:
	mysql_stmt_free_result(remove_box);
	mysql_stmt_reset(remove_box);
    return prodotto;
}

void do_update_stock(struct prodotto *prodotto) 
{
	MYSQL_BIND param[3];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prodotto->nome, strlen(prodotto->nome));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prodotto->nome_fornitore, strlen(prodotto->nome_fornitore));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &(prodotto->quantita), sizeof(prodotto->quantita));

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

void do_decrease_stock(struct prodotto *prod)
{
    MYSQL_BIND param[2];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prodotto->nome, strlen(prodotto->nome));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prodotto->nome_fornitore, strlen(prodotto->nome_fornitore));

	if(mysql_stmt_bind_param(decrease_stock, param) != 0) {
		print_stmt_error(decrease_stock, "Could not bind parameters for decrease_stock");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(decrease_stock) != 0) {
		print_stmt_error(decrease_stock, "Could not execute decrease stock procedure");
		return;
	}

	mysql_stmt_free_result(decrease_stock);
	mysql_stmt_reset(decrease_stock);
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
            //memcpy(&(prodotto->prodotto[row].quantita), &quantita, sizeof(quantita));
			strcpy(prodotto->prodotto[row].categoria, categoria);
			prodotto->prodotto[row].ricetta = ricetta;
            //memcpy(&(prodotto->prodotto[row].ricetta), &ricetta, sizeof(ricetta));
			prodotto->prodotto[row].mutuabile = mutuabile;
            //memcpy(&(prodotto->prodotto[row].mutuabile), &mutuabile, sizeof(mutuabile));
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

void do_add_category(char *categoria)
{
	MYSQL_BIND param[1];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, categoria, strlen(categoria));

	if(mysql_stmt_bind_param(add_category, param) != 0) {
		print_stmt_error(add_category, "Could not bind parameters for add_category");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_category) != 0) {
		print_stmt_error(add_category, "Could not execute add category procedure");
		return;
	}

	mysql_stmt_free_result(add_category);
	mysql_stmt_reset(add_category);
}

void do_add_interaction(struct interazione *inter)
{
	MYSQL_BIND param[2];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, inter->cat1, strlen(inter->cat1));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, inter->cat2, strlen(inter->cat2));

	if(mysql_stmt_bind_param(add_interaction, param) != 0) {
		print_stmt_error(add_interaction, "Could not bind parameters for add_interaction");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_interaction) != 0) {
		print_stmt_error(add_interaction, "Could not execute add interaction procedure");
		return;
	}

	mysql_stmt_free_result(add_interaction);
	mysql_stmt_reset(add_interaction);
}

struct interazioni *do_get_interacting_categories(struct prodotto *prod)
{
	size_t row = 0;
	MYSQL_BIND param[2];
	
	char cat1[STR_LEN];
	char cat2[STR_LEN];
	
	struct interazioni *interazioni = NULL;
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prod->nome, strlen(prod->nome));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prod->nome_fornitore, strlen(prod->nome_fornitore));

	if(mysql_stmt_bind_param(get_interacting_categories, param)) {
		print_stmt_error(get_interacting_categories, "Could not bind input parameters");
		goto out;
	}

	// Run procedure
	if(mysql_stmt_execute(get_interacting_categories) != 0) {
		print_stmt_error(get_interacting_categories, "Could not execute get interacting categories procedure");
		goto out;
	}

	mysql_stmt_store_result(get_interacting_categories);

    interazioni = malloc(sizeof(*interazioni) + sizeof(struct interazione) * mysql_stmt_num_rows(get_interacting_categories));
    if(interazioni == NULL)
        goto out;
    memset(interazioni, 0, sizeof(*interazioni) + sizeof(struct interazione) * mysql_stmt_num_rows(get_interacting_categories));
	interazioni->num_interazioni = mysql_stmt_num_rows(get_interacting_categories);

    // Prepare output parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cat1, STR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cat2, STR_LEN);

	if(mysql_stmt_bind_result(get_interacting_categories, param)) {
		print_stmt_error(get_interacting_categories, "Unable to bind output parameters for get interacting categories\n");
		free(prodotto);
		prodotto = NULL;
		goto out;
	}

	while (true) {
		status = mysql_stmt_fetch(get_interacting_categories);

		if (status == 1 || status == MYSQL_NO_DATA)
			break;

        strcpy(interazioni->cat_interagenti[row].cat1, cat1);
        strcpy(interazioni->cat_interagenti[row].cat2, cat2);

		row++;
	}

    out:
	mysql_stmt_free_result(get_interacting_categories);
	mysql_stmt_reset(get_interacting_categories);
	return interazioni;
}

void dispose_interactions(struct interazioni *interazioni)
{
    for(int i = 0; i < interazioni->num_interazioni; i++) {
        free(interazioni->cat_interagenti[i]);
    }
    free(interazioni);
}

struct vendita *do_record_sale(void)
{
    int status;
    MYSQL_BIND param[2];

    int scontrino;
    MYSQL_TIME giorno;

    struct vendita *vendita = NULL;

	// Run procedure
	if(mysql_stmt_execute(record_sale) != 0) {
		print_stmt_error(record_sale, "Could not execute record sale procedure");
		return;
	}

    vendita = malloc(sizeof(*vendita));
    if(vendita == NULL)
        goto out;
    memset(vendita, 0, sizeof(*vendita));

    // Get bound parameters
    mysql_stmt_store_result(record_sale);

    set_binding_param(&param[0], MYSQL_TYPE_LONG, &scontrino, sizeof(scontrino));
    set_binding_param(&param[1], MYSQL_TYPE_DATE, &giorno, sizeof(giorno));

    if(mysql_stmt_bind_result(record_sale, param)) {
        print_stmt_error(record_sale, "Unable to bind output parameters for record sale\n");
        free(vendita);
        vendita = NULL;
        goto out;
    }

    if (mysql_stmt_store_result(record_sale)) {
		print_stmt_error(record_sale, "Unable to store record_sale result set.");
		goto out;
	}

    while (true) {
        status = mysql_stmt_fetch(record_sale);

        if (status == 1 || status == MYSQL_NO_DATA)
            break;

        vendita->scontrino = scontrino;
        //memcpy(&(vendita->scontrino), &scontrino, sizeof(scontrino));
        mysql_date_to_string(&giorno, vendita->giorno);
    }

    out:
    mysql_stmt_free_result(record_sale);
    mysql_stmt_reset(record_sale);
    return vendita;
}

void do_add_product_to_sale(struct vendita *vendita, struct prodotto_venduto *prodottoVenduto)
{
    MYSQL_BIND param[6];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &(vendita->scontrino), sizeof(vendita->scontrino));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prodottoVenduto->nome_prodotto, strlen(prodottoVenduto->nome_prodotto));
    set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, prodottoVenduto->nome_fornitore, strlen(prodottoVenduto->nome_fornitore));
    set_binding_param(&param[3], MYSQL_TYPE_LONG, &(prodottoVenduto->quantita), sizeof(prodottoVenduto->quantita));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, prodottoVenduto->cf, strlen(prodottoVenduto->cf));
    set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, prodottoVenduto->medico, strlen(prodottoVenduto->medico));

	if(mysql_stmt_bind_param(add_product_to_sale, param) != 0) {
		print_stmt_error(add_product_to_sale, "Could not bind parameters for add_product_to_sale");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_product_to_sale) != 0) {
		print_stmt_error(add_product_to_sale, "Could not execute add product to sale procedure");
		return;
	}

	mysql_stmt_free_result(add_product_to_sale);
	mysql_stmt_reset(add_product_to_sale);
}

void do_add_cosmetic(struct prodotto *prodotto)
{
    MYSQL_BIND param[2];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prodotto->nome, strlen(prodotto->nome));
    set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prodotto->nome_fornitore, strlen(prodotto->nome_fornitore));

	if(mysql_stmt_bind_param(add_cosmetic, param) != 0) {
		print_stmt_error(add_cosmetic, "Could not bind parameters for add_cosmetic");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_cosmetic) != 0) {
		print_stmt_error(add_cosmetic, "Could not execute add cosmetic procedure");
		return;
	}

	mysql_stmt_free_result(add_cosmetic);
	mysql_stmt_reset(add_cosmetic);
}

void do_add_medicine(struct prodotto *prodotto)
{
    MYSQL_BIND param[2];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prodotto->nome, strlen(prodotto->nome));
    set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prodotto->nome_fornitore, strlen(prodotto->nome_fornitore));

	if(mysql_stmt_bind_param(add_medicine, param) != 0) {
		print_stmt_error(add_medicine, "Could not bind parameters for add_medicine");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_medicine) != 0) {
		print_stmt_error(add_medicine, "Could not execute add medicine procedure");
		return;
	}

	mysql_stmt_free_result(add_medicine);
	mysql_stmt_reset(add_medicine);
}

struct prodotti_magazzino *do_get_stock_report(void)
{
    int status;
	size_t row = 0;
	MYSQL_BIND param[4];

	char nome[STR_LEN];
    char nome_fornitore[STR_LEN];
    char tipo;
	char categoria[STR_LEN];

	struct prodotti_magazzino *prodotti = NULL;

	// Run procedure
	if(mysql_stmt_execute(get_stock_report) != 0) {
		print_stmt_error(get_stock_report, "Could not execute get stock report procedure");
		goto out;
	}

	prodotti = malloc(sizeof(*prodotti) + sizeof(struct prodotto) * mysql_stmt_num_rows(get_stock_report));
	if(prodotti == NULL)
		goto out;
	memset(prodotti, 0, sizeof(*prodotti) + sizeof(struct prodotto) * mysql_stmt_num_rows(get_stock_report));
	prodotti->num_prodotti = mysql_stmt_num_rows(get_stock_report);

	// Get bound parameters
	mysql_stmt_store_result(get_stock_report);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nome, STR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, nome_fornitore, STR_LEN);
    set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, &tipo, sizeof(tipo));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, categoria, STR_LEN);

	if(mysql_stmt_bind_result(get_stock_report, param)) {
		print_stmt_error(get_stock_report, "Unable to bind output parameters for get stock report\n");
		free(prodotti);
		prodotti = NULL;
		goto out;
	}

	while (true) {
		status = mysql_stmt_fetch(get_stock_report);

		if (status == 1 || status == MYSQL_NO_DATA)
			break;

		strcpy(prodotti->prodotti[row].nome, nome);
        strcpy(prodotti->prodotti[row].nome_fornitore, nome_fornitore);
        strcpy(prodotti->prodotti[row].tipo, tipo);
        strcpy(prodotti->prodotti[row].categoria, categoria);

		row++;
	}

    out:
	mysql_stmt_free_result(get_stock_report);
	mysql_stmt_reset(get_stock_report);
	return prodotti;
}

void do_remove_product(struct prodotto *prodotto)
{
    MYSQL_BIND param[2];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prodotto->nome, strlen(prodotto->nome));
    set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prodotto->nome_fornitore, strlen(prodotto->nome_fornitore));

	if(mysql_stmt_bind_param(remove_product, param) != 0) {
		print_stmt_error(remove_product, "Could not bind parameters for remove_product");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(remove_product) != 0) {
		print_stmt_error(remove_product, "Could not execute remove product procedure");
		return;
	}

	mysql_stmt_free_result(remove_product);
	mysql_stmt_reset(remove_product);
}

void do_add_supplier(struct fornitore *fornitore)
{
    MYSQL_BIND param[1];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, fornitore->nome, strlen(fornitore->nome));

	if(mysql_stmt_bind_param(add_supplier, param) != 0) {
		print_stmt_error(add_supplier, "Could not bind parameters for add_supplier");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_supplier) != 0) {
		print_stmt_error(add_supplier, "Could not execute add supplier procedure");
		return;
	}

	mysql_stmt_free_result(add_supplier);
	mysql_stmt_reset(add_supplier);
}

void do_remove_supplier(struct fornitore *fornitore)
{
    MYSQL_BIND param[1];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, fornitore->nome, strlen(fornitore->nome));

	if(mysql_stmt_bind_param(remove_supplier, param) != 0) {
		print_stmt_error(remove_supplier, "Could not bind parameters for remove_supplier");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(remove_supplier) != 0) {
		print_stmt_error(remove_supplier, "Could not execute remove supplier procedure");
		return;
	}

	mysql_stmt_free_result(remove_supplier);
	mysql_stmt_reset(remove_supplier);
}

static struct indirizzi *extract_addresses(void)
{
    int status;
	size_t row = 0;
	MYSQL_BIND param[4];

    char citta[STR_LEN];
	char via[STR_LEN];
	char num_civico[STR_LEN];
	bool fatturazione;

    struct indirizzi *indirizzi = NULL;

    set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, citta, STR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, via, STR_LEN);
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, num_civico, STR_LEN);
	set_binding_param(&param[3], MYSQL_TYPE_TINY, &fatturazione, sizeof(fatturazione));

    if(mysql_stmt_bind_result(get_info_supplier, param)) {
		print_stmt_error(get_info_supplier, "Unable to bind parameters for extract_addresses\n");
		goto out;
	}

    if (mysql_stmt_store_result(get_info_supplier)) {
		print_stmt_error(get_info_supplier, "Unable to store addresses information result set.");
		goto out;
	}

    indirizzi = malloc(sizeof(*indirizzi) + sizeof(struct indirizzo) * mysql_stmt_num_rows(get_info_supplier));
    if(indirizzi == NULL)
        goto out;
    memset(indirizzi, 0, sizeof(*indirizzi) + sizeof(struct indirizzo) * mysql_stmt_num_rows(get_info_supplier));
    indirizzi->num_indirizzi = mysql_stmt_num_rows(get_info_supplier);

    while (true) {
		status = mysql_stmt_fetch(get_info_supplier);

		if (status == 1 || status == MYSQL_NO_DATA)
			break;

		strcpy(indirizzi->lista_indirizzi[row].citta, citta);
		strcpy(indirizzi->lista_indirizzi[row].via, via);
		strcpy(indirizzi->lista_indirizzi[row].num_civico, num_civico);
        indirizzi->lista_indirizzi[row].fatturazione = fatturazione;

		row++;
	}
    
    out:
	return indirizzi;
}

static struct recapiti *extract_contacts(void)
{
    int status;
	size_t row = 0;
	MYSQL_BIND param[2];

    char contatto[STR_LEN];
	bool preferito;

    struct recapiti *recapiti = NULL;

    set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, contatto, STR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_TINY, &preferito, sizeof(preferito));

    if(mysql_stmt_bind_result(get_info_supplier, param)) {
		print_stmt_error(get_info_supplier, "Unable to bind parameters for extract_addresses\n");
		goto out;
	}

    if (mysql_stmt_store_result(get_info_supplier)) {
		print_stmt_error(get_info_supplier, "Unable to store addresses information result set.");
		goto out;
	}

    recapiti = malloc(sizeof(*recapiti) + sizeof(struct recapito) * mysql_stmt_num_rows(get_info_supplier));
    if(recapiti == NULL)
        goto out;
    memset(recapiti, 0, sizeof(*recapiti) + sizeof(struct recapito) * mysql_stmt_num_rows(get_info_supplier));
    recapiti->num_recapiti = mysql_stmt_num_rows(get_info_supplier);

    while (true) {
		status = mysql_stmt_fetch(get_info_supplier);

		if (status == 1 || status == MYSQL_NO_DATA)
			break;

		strcpy(recapiti->lista_recapiti[row].contatto, contatto);
        recapiti->lista_recapiti[row].preferito = preferito;

		row++;
	}

    out:
	return recapiti;
}

struct fornitore *do_get_info_supplier(struct fornitore *fornitore)
{
    struct fornitore *info_fornitore = NULL;
    struct recapiti *recapiti = NULL;
    struct indirizzi *indirizzi = NULL;
    unsigned count = 0;
    int status;

    MYSQL_BIND param[1];

    // Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, fornitore->nome, strlen(fornitore->nome));

	if(mysql_stmt_bind_param(get_info_supplier, param) != 0) {
		print_stmt_error(get_info_supplier, "Could not bind parameters for get_info_supplier");
		goto out;
	}

    // Run procedure
    if(mysql_stmt_execute(get_info_supplier) != 0) {
		print_stmt_error(get_info_supplier, "An error occurred while retrieving supplier informations");
		goto out;
	}

    // We have multiple result sets here!
	do {
		// Skip OUT variables (although they are not present in the procedure...)
		if(conn->server_status & SERVER_PS_OUT_PARAMS) {
			goto next;
		}

		if(count == 0) {
			indirizzi = extract_addresses();
			if(indirizzi == NULL)
				goto next;
		} else {
			recapiti = extract_contacts();
            if(recapiti == NULL)
                goto out;
		}

    next:
		mysql_stmt_free_result(get_info_supplier);
		// more results? -1 = no, >0 = error, 0 = yes (keep looking)
		status = mysql_stmt_next_result(get_info_supplier);
		if (status > 0)
			finish_with_stmt_error(conn, get_info_supplier, "Unexpected condition", false);

		count++;
	} while(status == 0);

    info_fornitore = malloc(sizeof(*info_fornitore));
    if(info_fornitore == NULL)
        goto out;
    strcpy(info_fornitore->nome, fornitore->nome, strlen(fornitore->nome));
    info_fornitore->indirizzi = indirizzi;
    info_fornitore->recapiti = recapiti;

    out:
	mysql_stmt_free_result(get_info_supplier);
	mysql_stmt_reset(get_info_supplier);
	return info_fornitore;
}

struct prodotti_magazzino *do_get_supplier_products(struct fornitore *fornitore)
{
    size_t row = 0;
    MYSQL_BIND param[6];

    char nome[STR_LEN];
    char tipo;
	int quantita;
	char categoria[STR_LEN];
    bool ricetta;
	bool mutuabile;

    struct prodotti_magazzino *prodottiMagazzino = NULL;

    set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, fornitore->nome, strlen(fornitore->nome));

    if(mysql_stmt_bind_param(get_supplier_products, param)) {
        print_stmt_error(get_supplier_products, "Could not bind input parameters");
        goto out;
    }

    // Run procedure
    if(mysql_stmt_execute(get_supplier_products) != 0) {
        print_stmt_error(get_supplier_products, "Could not execute get supplier products procedure");
        goto out;
    }

    mysql_stmt_store_result(get_supplier_products);

    prodottiMagazzino = malloc(sizeof(*prodottiMagazzino) + sizeof(struct prodotto) * mysql_stmt_num_rows(get_supplier_products));
    if(prodottiMagazzino == NULL)
        goto out;
    memset(prodottiMagazzino, 0, sizeof(*prodottiMagazzino) + sizeof(struct prodotto) * mysql_stmt_num_rows(get_supplier_products));
    prodottiMagazzino->num_prodotti = mysql_stmt_num_rows(get_supplier_products);

    // Prepare output parameters
    set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nome, STR_LEN);
    set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, &tipo, sizeof(tipo));
    set_binding_param(&param[2], MYSQL_TYPE_LONG, &quantita, sizeof(quantita));
    set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, categoria, STR_LEN);
    set_binding_param(&param[4], MYSQL_TYPE_TINY, &ricetta, sizeof(ricetta));
    set_binding_param(&param[5], MYSQL_TYPE_TINY, &mutuabile, sizeof(mutuabile));

    if(mysql_stmt_bind_result(get_supplier_products, param)) {
        print_stmt_error(get_supplier_products, "Unable to bind output parameters for get supplier products\n");
        free(prodottiMagazzino);
        prodottiMagazzino = NULL;
        goto out;
    }

    while (true) {
        status = mysql_stmt_fetch(get_supplier_products);

        if (status == 1 || status == MYSQL_NO_DATA)
            break;

        strcpy(prodottiMagazzino->prodotti[row].nome, nome);
        strcpy(prodottiMagazzino->prodotti[row].nome_fornitore, fornitore->nome);
        strcpy(prodottiMagazzino->prodotti[row].tipo, tipo);
        prodottiMagazzino->prodotti[row].quantita = quantita;
        //memcpy(&(prodottiMagazzino->prodotti[row].quantita), &quantita, sizeof(quantita));
        strcpy(prodottiMagazzino->prodotti[row].categoria, categoria);
        prodottiMagazzino->prodotti[row].ricetta = ricetta;
        //memcpy(&(prodottiMagazzino->prodotti[row].ricetta), &ricetta, sizeof(ricetta));
        prodottiMagazzino->prodotti[row].mutuabile = mutuabile;
        //memcpy(&(prodottiMagazzino->prodotti[row].mutuabile), &mutuabile, sizeof(mutuabile));

        row++;
    }

    out:
    mysql_stmt_free_result(get_supplier_products);
    mysql_stmt_reset(get_supplier_products);
    return prodottiMagazzino;
}

void do_add_address(struct indirizzo *indirizzo, struct fornitore *fornitore)
{
    MYSQL_BIND param[5];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, indirizzo->citta, strlen(indirizzo->citta));
    set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, indirizzo->via, strlen(indirizzo->via));
    set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, indirizzo->num_civico, strlen(indirizzo->num_civico));
    set_binding_param(&param[3], MYSQL_TYPE_TINY, &(indirizzo->fatturazione), strlen(indirizzo->fatturazione));
    set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, fornitore->nome, strlen(fornitore->nome));

	if(mysql_stmt_bind_param(add_address, param) != 0) {
		print_stmt_error(add_address, "Could not bind input parameters");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_address) != 0) {
		print_stmt_error(add_address, "Could not execute add address procedure");
		return;
	}

	mysql_stmt_free_result(add_address);
	mysql_stmt_reset(add_address);
}

void do_remove_address(struct indirizzo *indirizzo)
{
    MYSQL_BIND param[3];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, indirizzo->citta, strlen(indirizzo->citta));
    set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, indirizzo->via, strlen(indirizzo->via));
    set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, indirizzo->num_civico, strlen(indirizzo->num_civico));

	if(mysql_stmt_bind_param(remove_address, param) != 0) {
		print_stmt_error(remove_address, "Could not bind input parameters");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(remove_address) != 0) {
		print_stmt_error(remove_address, "Could not execute remove address procedure");
		return;
	}

	mysql_stmt_free_result(remove_address);
	mysql_stmt_reset(remove_address);
}

void do_add_contact(struct recapito *recapito, struct fornitore *fornitore)
{
    MYSQL_BIND param[3];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, recapito->contatto, strlen(recapito->contatto));
    set_binding_param(&param[3], MYSQL_TYPE_TINY, &(recapito->preferito), sizeof(recapito->preferito));
    set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, fornitore->nome, strlen(fornitore->nome));

	if(mysql_stmt_bind_param(add_contact, param) != 0) {
		print_stmt_error(add_contact, "Could not bind input parameters");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_contact) != 0) {
		print_stmt_error(add_contact, "Could not execute add contact procedure");
		return;
	}

	mysql_stmt_free_result(add_contact);
	mysql_stmt_reset(add_contact);
}

void do_remove_contact(struct recapito *recapito)
{
    MYSQL_BIND param[1];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, recapito->contatto, strlen(recapito->contatto));

	if(mysql_stmt_bind_param(remove_contact, param) != 0) {
		print_stmt_error(remove_contact, "Could not bind input parameters");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(remove_contact) != 0) {
		print_stmt_error(remove_contact, "Could not execute remove contact procedure");
		return;
	}

	mysql_stmt_free_result(remove_contact);
	mysql_stmt_reset(remove_contact);
}

void do_add_box(struct prodotto *prodotto, struct scatola *scatola)
{
    MYSQL_BIND param[5];
    MYSQL_TIME giorno;

    date_to_mysql_time(scatola->scadenza, &giorno);

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prodotto->nome, strlen(prodotto->nome));
    set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prodotto->nome_fornitore, strlen(prodotto->nome_fornitore));
    set_binding_param(&param[2], MYSQL_TYPE_DATE, &giorno, sizeof(giorno));
    set_binding_param(&param[3], MYSQL_TYPE_LONG, &(scatola->cassetto), sizeof(scatola->cassetto));
    set_binding_param(&param[4], MYSQL_TYPE_LONG, &(scatola->scaff.codice), sizeof(scatola->scaff.codice));

	if(mysql_stmt_bind_param(add_box, param) != 0) {
		print_stmt_error(add_box, "Could not bind input parameters");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_box) != 0) {
		print_stmt_error(add_box, "Could not execute add box procedure");
		return;
	}

	mysql_stmt_free_result(add_box);
	mysql_stmt_reset(add_box);
}

struct scatole_in_scadenza *do_get_expiry_report(void)
{
    int status;
	size_t row = 0;
	MYSQL_BIND param[6];

    int codice;
    char nome_prodotto[STR_LEN];
	char nome_fornitore[STR_LEN];
    MYSQL_TIME giorno;
	int cassetto;
	struct scaffale scaff;

	struct scatole_in_scadenza *scatoleInScadenza = NULL;

	// Run procedure
	if(mysql_stmt_execute(get_expiry_report) != 0) {
		print_stmt_error(get_expiry_report, "Could not execute get expiry report procedure");
		goto out;
	}

	scatoleInScadenza = malloc(sizeof(*scatoleInScadenza) + sizeof(scatole_prodotto) * mysql_stmt_num_rows(get_expiry_report));
	if(scatoleInScadenza == NULL)
		goto out;
	memset(scatoleInScadenza, 0, sizeof(*scatoleInScadenza) + sizeof(scatole_prodotto) * mysql_stmt_num_rows(get_expiry_report));
	scatoleInScadenza->num_in_scadenza = mysql_stmt_num_rows(get_expiry_report);

    for(int i = 0; i < mysql_stmt_num_rows(get_expiry_report); i++) {
        scatoleInScadenza->scatole[i].scatole = malloc(sizeof(struct scatola));
        if(scatoleInScadenza->scatole[i].scatole == NULL)
            goto out;
        memset(scatoleInScadenza->scatole[i].scatole, 0, sizeof(struct scatola))
        scatoleInScadenza->scatole[i].num_scatole = 1;
    }

	// Get bound parameters
	mysql_stmt_store_result(get_expiry_report);

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &codice, sizeof(codice));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, nome_prodotto, STR_LEN);
    set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, nome_fornitore, STR_LEN);
    set_binding_param(&param[3], MYSQL_TYPE_DATE, &giorno, sizeof(giorno));
    set_binding_param(&param[4], MYSQL_TYPE_LONG, &cassetto, sizeof(cassetto));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &(scaff.codice), sizeof(scaff.codice));

	if(mysql_stmt_bind_result(get_expiry_report, param)) {
		print_stmt_error(get_expiry_report, "Unable to bind output parameters for get expiry report\n");
		dispose_in_scadenza(scatoleInScadenza);
		scatoleInScadenza = NULL;
		goto out;
	}

	while (true) {
		status = mysql_stmt_fetch(get_expiry_report);

		if (status == 1 || status == MYSQL_NO_DATA)
			break;

        scatoleInScadenza->scatole[row].scatole->codice = codice;
		strcpy(scatoleInScadenza->scatole[row].nome_prodotto, nome_prodotto);
        strcpy(scatoleInScadenza->scatole[row].nome_fornitore, nome_fornitore);
        mysql_date_to_string(&giorno, scatoleInScadenza->scatole[row].scatole->scadenza);
        scatoleInScadenza->scatole[row].scatole->cassetto = cassetto;
        scatoleInScadenza->scatole[row].scatole->scaff.codice = scaff.codice;   //???

		row++;
	}

    out:
	mysql_stmt_free_result(get_expiry_report);
	mysql_stmt_reset(get_expiry_report);
	return scatoleInScadenza;
}

void dispose_in_scadenza(struct scatole_in_scadenza * scatoleInScadenza)
{
    for(int i = 0; i < scatoleInScadenza->num_in_scadenza; i++) {
        free(scatoleInScadenza->scatole[i].scatole);
    }

    free(scatoleInScadenza);
}

void do_add_shelf(struct scaffale *scaffale)
{
    MYSQL_BIND param[1];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, scaffale->categoria, strlen(scaffale->categoria));
    
	if(mysql_stmt_bind_param(add_shelf, param) != 0) {
		print_stmt_error(add_shelf, "Could not bind input parameters");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_shelf) != 0) {
		print_stmt_error(add_shelf, "Could not execute add shelf procedure");
		return;
	}

	mysql_stmt_free_result(add_shelf);
	mysql_stmt_reset(add_shelf);
}

void do_update_shelf_category(struct scaffale *scaffale)
{
    MYSQL_BIND param[2];

	// Bind parameters
    set_binding_param(&param[0], MYSQL_TYPE_LONG, scaffale->codice, sizeof(scaffale->codice));
    set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, scaffale->categoria, strlen(scaffale->categoria));

	if(mysql_stmt_bind_param(update_shelf_category, param) != 0) {
		print_stmt_error(update_shelf_category, "Could not bind input parameters");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(update_shelf_category) != 0) {
		print_stmt_error(update_shelf_category, "Could not execute update shelf category procedure");
		return;
	}

	mysql_stmt_free_result(update_shelf_category);
	mysql_stmt_reset(update_shelf_category);
}

struct lettera_acquisto *do_get_purchase_letter(void)
{
    int status;
	MYSQL_BIND param[2];

	int codice;
	MYSQL_TIME giorno;

	struct lettera_acquisto *letteraAcquisto = NULL;

	// Run procedure
	if(mysql_stmt_execute(get_purchase_letter) != 0) {
		print_stmt_error(get_purchase_letter, "Could not execute get purchase letter procedure");
		goto out;
	}

	letteraAcquisto = malloc(sizeof(struct lettera_acquisto));
	if(letteraAcquisto == NULL)
		goto out;
	memset(letteraAcquisto, 0, sizeof(struct lettera_acquisto));

	// Get bound parameters
	mysql_stmt_store_result(get_purchase_letter);

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &codice, sizeof(codice));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &giorno, sizeof(giorno));

	if(mysql_stmt_bind_result(get_purchase_letter, param)) {
		print_stmt_error(get_purchase_letter, "Unable to bind output parameters for get purchase letter\n");
		free(letteraAcquisto);
		letteraAcquisto = NULL;
		goto out;
	}

	while (true) {
		status = mysql_stmt_fetch(get_purchase_letter);

		if (status == 1 || status == MYSQL_NO_DATA)
			break;

        letteraAcquisto->codice = codice;
        mysql_date_to_string(&giorno, letteraAcquisto->giorno);
    }

    out:
	mysql_stmt_free_result(get_purchase_letter);
	mysql_stmt_reset(get_purchase_letter);
	return letteraAcquisto;
}

void do_add_product_to_letter(struct lettera_acquisto *letteraAcquisto, struct prodotto_richiesto *prodottoRichiesto)
{
    MYSQL_BIND param[4];

	// Bind parameters
	set_binding_param(&param[0], MYSQL_TYPE_LONG, letteraAcquisto->codice, sizeof(letteraAcquisto->codice));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prodottoRichiesto->nome_prodotto, strlen(prodottoRichiesto->nome_prodotto));
    set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, prodottoRichiesto->nome_fornitore, strlen(prodottoRichiesto->nome_fornitore));
    set_binding_param(&param[3], MYSQL_TYPE_LONG, &(prodottoRichiesto->quantita), sizeof(prodottoRichiesto->quantita));

	if(mysql_stmt_bind_param(add_product_to_letter, param) != 0) {
		print_stmt_error(add_product_to_letter, "Could not bind input parameters");
		return;
	}

	// Run procedure
	if(mysql_stmt_execute(add_product_to_letter) != 0) {
		print_stmt_error(add_product_to_letter, "Could not execute add product to letter procedure");
		return;
	}

	mysql_stmt_free_result(add_product_to_letter);
	mysql_stmt_reset(add_product_to_letter);
}

static struct lettere_inviate *extract_letters(void)
{
    int status;
    int i = -1;
    size_t letter = 0;
    MYSQL_BIND param[4];

    int codice;
    MYSQL_TIME giorno;
    char nome_prodotto[STR_LEN];
    int quantita;

    int old_codice = 0;
    int num_lettere = 0;
    int size;

    struct lettere_inviate *lettereInviate = NULL;

    set_binding_param(&param[0], MYSQL_TYPE_LONG, &codice, sizeof(codice));
    set_binding_param(&param[1], MYSQL_TYPE_DATE, &giorno, sizeof(giorno));
    set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, nome_prodotto, STR_LEN);
    set_binding_param(&param[3], MYSQL_TYPE_LONG, &quantita, sizeof(quantita));

    if(mysql_stmt_bind_result(get_letters_to_supplier, param)) {
        print_stmt_error(get_letters_to_supplier, "Unable to bind parameters for extract_letters\n");
        goto out;
    }

    if (mysql_stmt_store_result(get_letters_to_supplier)) {
        print_stmt_error(get_letters_to_supplier, "Unable to store extract letters result set.\n");
        goto out;
    }

    size = mysql_stmt_num_rows(get_letters_to_supplier);
    int *num_richieste;
    num_richieste = malloc(sizeof(int) * size);
    if(num_richieste == NULL) {
        print_error(conn, "Unable to allocate memory for letters struct\n");
        goto out;
    }
    memset(num_richieste, 0, sizeof(int) * size);

    while (true) {
        status = mysql_stmt_fetch(get_letters_to_supplier);

        if (status == 1 || status == MYSQL_NO_DATA)
            break;

        if(old_codice != codice) {
            old_codice = codice;
            num_lettere++;
            i++;
        }

        num_richieste[i]++;
    }

    lettereInviate = malloc(sizeof(*lettereInviate));
    if(lettereInviate == NULL) {
        print_error(conn, "Unable to allocate memory for letters struct\n");
        goto out;
    }
    lettereInviate->num_lettere = num_lettere;

    lettereInviate->lettere = malloc(sizeof(struct lettera_acquisto) * num_lettere);
    if(lettereInviate->lettere == NULL) {
        print_error(conn, "Unable to allocate memory for letters struct\n");
        free(lettereInviate);
        lettereInviate = NULL;
        goto out;
    }

    for(i = 0; i < num_lettere; i++) {
        lettereInviate->lettere[i].num_richieste = num_richieste[i];
        lettereInviate->lettere[i].richieste = malloc(sizeof(struct prodotto_richiesto) * num_richieste[i]);
        if(lettereInviate->lettere[i].richieste == NULL) {
            print_error(conn, "Unable to allocate memory for letters struct\n");
            free(lettereInviate);
            lettereInviate = NULL;
            goto out;
        }
    }

    mysql_stmt_data_seek(get_letters_to_supplier, 0); // reset the row from which to fetch
    old_codice = 0;

    while (true) {
        status = mysql_stmt_fetch(get_letters_to_supplier);

        if (status == 1 || status == MYSQL_NO_DATA)
            break;

        if(old_codice != codice) {
            old_codice = codice;
            i = 0;

            lettereInviate->lettere[letter].codice = codice;
            mysql_date_to_string(&giorno, lettereInviate->lettere[letter].giorno);
            strcpy(lettereInviate->lettere[letter].richieste[i].nome_prodotto, nome_prodotto);
            lettereInviate->lettere[letter].richieste[i].quantita = quantita;

            letter++;
        }
        else {
            strcpy(lettereInviate->lettere[letter].richieste[i].nome_prodotto, nome_prodotto);
            lettereInviate->lettere[letter].richieste[i].quantita = quantita;
        }

        i++;
    }

    out:
    return lettereInviate;
}

struct lettere_inviate *do_get_letters_to_supplier(struct fornitore *fornitore)
{
    MYSQL_BIND param[1];

    struct lettere_inviate *lettereInviate = NULL;

    set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, fornitore->nome, strlen(fornitore->nome));

    if(mysql_stmt_bind_param(get_letters_to_supplier, param)) {
        print_stmt_error(get_letters_to_supplier, "Could not bind input parameters");
        goto out;
    }

    // Run procedure
    if(mysql_stmt_execute(get_letters_to_supplier) != 0) {
        print_stmt_error(get_letters_to_supplier, "Could not execute get letters to supplier procedure");
        goto out;
    }

    lettereInviate = extract_letters();
    if(lettereInviate == NULL) {
        print_error(conn, "Unable to extract letters\n");
        goto out;
    }

    out:
    mysql_stmt_free_result(get_letters_to_supplier);
    mysql_stmt_reset(get_letters_to_supplier);
    return lettereInviate;
}

static struct vendite *extract_sales(void)
{
    int status;
    int i = -1;
    size_t sale = 0;
    MYSQL_BIND param[7];

    int scontrino;
    char nome_prodotto[STR_LEN];
	char nome_fornitore[STR_LEN];
    char tipo;
	int quantita;
    char cf[STR_LEN];
	char medico[STR_LEN];
    
    int old_scontrino = 0;
    int num_vendite = 0;
    int size;

    struct vendite *vendite = NULL;

    set_binding_param(&param[0], MYSQL_TYPE_LONG, &scontrino, sizeof(scontrino));
    set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, nome_prodotto, STR_LEN);
    set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, nome_fornitore, STR_LEN);
    set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, &tipo, sizeof(tipo));
    set_binding_param(&param[4], MYSQL_TYPE_LONG, &quantita, sizeof(quantita));
    set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, cf, STR_LEN);
    set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, medico, STR_LEN);

    if(mysql_stmt_bind_result(get_sales_on_date, param)) {
        print_stmt_error(get_sales_on_date, "Unable to bind parameters for extract_sales\n");
        goto out;
    }

    if (mysql_stmt_store_result(get_sales_on_date)) {
        print_stmt_error(get_sales_on_date, "Unable to store extract sales result set.\n");
        goto out;
    }

    size = mysql_stmt_num_rows(get_sales_on_date);
    int *num_prodotti;
    num_prodotti = malloc(sizeof(int) * size);
    if(num_prodotti == NULL) {
        print_error(conn, "Unable to allocate memory for sales struct\n");
        goto out;
    }
    memset(num_prodotti, 0, sizeof(int) * size);

    while (true) {
        status = mysql_stmt_fetch(get_sales_on_date);

        if (status == 1 || status == MYSQL_NO_DATA)
            break;

        if(old_scontrino != scontrino) {
            old_scontrino = scontrino;
            num_vendite++;
            i++;
        }

        num_prodotti[i]++;
    }

    vendite = malloc(sizeof(*vendite));
    if(vendite == NULL) {
        print_error(conn, "Unable to allocate memory for sales struct\n");
        goto out;
    }
    vendite->num_vendite = num_vendite;

    vendite->listaVendite = malloc(sizeof(struct vendita) * num_vendite);
    if(vendite->listaVendite == NULL) {
        print_error(conn, "Unable to allocate memory for sales struct\n");
        free(vendite);
        vendite = NULL;
        goto out;
    }

    for(i = 0; i < num_vendite; i++) {
        vendite->listaVendite[i].num_prodotti = num_prodotti[i];
        vendite->listaVendite[i].prod_venduti = malloc(sizeof(struct prodotto_venduto) * num_prodotti[i]);
        if(vendite->listaVendite[i].prod_venduti == NULL) {
            print_error(conn, "Unable to allocate memory for sales struct\n");
            free(vendite);
            vendite = NULL;
            goto out;
        }
    }

    mysql_stmt_data_seek(get_sales_on_date, 0); // reset the row from which to fetch
    old_scontrino = 0;

    while (true) {
        status = mysql_stmt_fetch(get_sales_on_date);

        if (status == 1 || status == MYSQL_NO_DATA)
            break;

        if(old_scontrino != scontrino) {
            old_scontrino = scontrino;
            i = 0;

            vendite->listaVendite[sale].scontrino = scontrino;
            strcpy(vendite->listaVendite[sale].prod_venduti[i].nome_prodotto, nome_prodotto);
            strcpy(vendite->listaVendite[sale].prod_venduti[i].nome_fornitore, nome_fornitore);
            strcpy(&(vendite->listaVendite[sale].prod_venduti[i].tipo), &tipo);
            vendite->listaVendite[sale].prod_venduti[i].quantita = quantita;
            strcpy(vendite->listaVendite[sale].prod_venduti[i].cf, cf);
            strcpy(vendite->listaVendite[sale].prod_venduti[i].medico, medico);

            sale++;
        }
        else {
            strcpy(vendite->listaVendite[sale].prod_venduti[i].nome_prodotto, nome_prodotto);
            strcpy(vendite->listaVendite[sale].prod_venduti[i].nome_fornitore, nome_fornitore);
            strcpy(&(vendite->listaVendite[sale].prod_venduti[i].tipo), &tipo);
            vendite->listaVendite[sale].prod_venduti[i].quantita = quantita;
            strcpy(vendite->listaVendite[sale].prod_venduti[i].cf, cf);
            strcpy(vendite->listaVendite[sale].prod_venduti[i].medico, medico);
        }

        i++;
    }

    out:
    return vendite;
}

struct vendite *do_get_sales_on_date(char giorno[DATE_LEN])
{
    MYSQL_BIND param[1];
    MYSQL_TIME data;

    struct vendite *vendite = NULL;

    date_to_mysql_time(giorno, &data);

    set_binding_param(&param[0], MYSQL_TYPE_DATE, &data, sizeof(data));

    if(mysql_stmt_bind_param(get_sales_on_date, param)) {
        print_stmt_error(get_sales_on_date, "Could not bind input parameters");
        goto out;
    }

    // Run procedure
    if(mysql_stmt_execute(get_sales_on_date) != 0) {
        print_stmt_error(get_sales_on_date, "Could not execute get sales on date procedure");
        goto out;
    }

    vendite = extract_sales();
    if(vendite == NULL) {
        print_error(conn, "Unable to extract sales\n");
        goto out;
    }

    out:
    mysql_stmt_free_result(get_sales_on_date);
    mysql_stmt_reset(get_sales_on_date);
    return vendite;
}

static vendite *extract_product_sales(void)
{
    int status;
    size_t row = 0;
    MYSQL_BIND param[5];

    int scontrino;
    MYSQL_TIME giorno;
	int quantita;
    char cf[STR_LEN];
	char medico[STR_LEN];

    struct vendite *vendite = NULL;

    set_binding_param(&param[0], MYSQL_TYPE_LONG, &scontrino, sizeof(scontrino));
    set_binding_param(&param[1], MYSQL_TYPE_DATE, &giorno, sizeof(giorno));
    set_binding_param(&param[2], MYSQL_TYPE_LONG, &quantita, sizeof(quantita));
    set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cf, STR_LEN);
    set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, medico, STR_LEN);

    if(mysql_stmt_bind_result(get_product_sales, param)) {
        print_stmt_error(get_product_sales, "Unable to bind parameters for extract_product_sales\n");
        goto out;
    }

    if (mysql_stmt_store_result(get_product_sales)) {
        print_stmt_error(get_product_sales, "Unable to store extract product sales result set.\n");
        goto out;
    }

    vendite = malloc(sizeof(*vendite) + sizeof(struct vendita) * mysql_stmt_num_rows(get_product_sales));
    if(vendite == NULL) {
        print_error(conn, "Unable to allocate memory for sales struct\n");
        goto out;
    }
    memset(vendite, 0, sizeof(*vendite) + sizeof(struct vendita) * mysql_stmt_num_rows(get_product_sales));

    for(int i = 0; i < mysql_stmt_num_rows(get_product_sales); i++) {
        vendite->listaVendite[i].prod_venduti = malloc(sizeof(struct prodotto_venduto));
        if(vendite->listaVendite[i].prod_venduti == NULL) {
            print_error(conn, "Unable to allocate memory for sales struct\n");
            goto out;
        }
    }

    vendite->num_vendite = mysql_stmt_num_rows(get_product_sales);

    while (true) {
        status = mysql_stmt_fetch(get_product_sales);

        if (status == 1 || status == MYSQL_NO_DATA)
            break;

        vendite->listaVendite[row].scontrino = scontrino;
        mysql_date_to_string(&giorno, vendite->listaVendite[row].giorno);
        vendite->listaVendite[row].prod_venduti[0].quantita = quantita;
        strcpy(vendite->listaVendite[row].prod_venduti[0].cf, cf);
        strcpy(vendite->listaVendite[row].prod_venduti[0].medico, medico);

        row++;
    }

    out:
    return vendite;
}

struct vendite *do_get_product_sales(struct prodotto *prodotto)
{
    MYSQL_BIND param[2];

    struct vendite *vendite = NULL;

    set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prodotto->nome, STR_LEN);
    set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prodotto->nome_fornitore, STR_LEN);

    if(mysql_stmt_bind_param(get_product_sales, param)) {
        print_stmt_error(get_product_sales, "Could not bind input parameters");
        goto out;
    }

    // Run procedure
    if(mysql_stmt_execute(get_product_sales) != 0) {
        print_stmt_error(get_product_sales, "Could not execute get product sales procedure");
        goto out;
    }

    vendite = extract_product_sales();
    if(vendite == NULL) {
        print_error(conn, "Unable to extract product sales\n");
        goto out;
    }

    out:
    mysql_stmt_free_result(get_product_sales);
    mysql_stmt_reset(get_product_sales);
    return vendite;
}

struct prodotti_venduti *do_get_most_sold(void)
{
    int status;
    size_t row = 0;
	MYSQL_BIND param[4];

	char nome_prodotto[STR_LEN];
	char nome_fornitore[STR_LEN];
	char tipo;
	int quantita;

	struct prodotti_venduti *prodottiVenduti = NULL;

	// Run procedure
	if(mysql_stmt_execute(get_most_sold) != 0) {
		print_stmt_error(get_most_sold, "Could not execute get most sold procedure");
		goto out;
	}

	prodottiVenduti = malloc(sizeof(*prodottiVenduti) + sizeof(struct prodotto_venduto) * mysql_stmt_num_rows(get_most_sold));
	if(prodottiVenduti == NULL)
		goto out;
	memset(prodottiVenduti, 0, sizeof(*prodottiVenduti) + sizeof(struct prodotto_venduto) * mysql_stmt_num_rows(get_most_sold));
    prodottiVenduti->num_prodotti = mysql_stmt_num_rows(get_most_sold);

	// Get bound parameters
	mysql_stmt_store_result(get_most_sold);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nome_prodotto, STR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, nome_fornitore, STR_LEN);
    set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, &tipo, sizeof(tipo));
    set_binding_param(&param[3], MYSQL_TYPE_LONG, &quantita, sizeof(quantita));

	if(mysql_stmt_bind_result(get_most_sold, param)) {
		print_stmt_error(get_most_sold, "Unable to bind output parameters for get most sold\n");
		free(prodottiVenduti);
		prodottiVenduti = NULL;
		goto out;
	}

	while (true) {
		status = mysql_stmt_fetch(get_most_sold);

		if (status == 1 || status == MYSQL_NO_DATA)
			break;

        strcpy(prodottiVenduti->prod_venduti[row].nome_prodotto, nome_prodotto);
        strcpy(prodottiVenduti->prod_venduti[row].nome_fornitore, nome_fornitore);
        strcpy(&(prodottiVenduti->prod_venduti[row].tipo), &tipo);
        prodottiVenduti->prod_venduti[row].quantita = quantita;

        row++;
    }

    out:
	mysql_stmt_free_result(get_most_sold);
	mysql_stmt_reset(get_most_sold);
	return prodottiVenduti;
}

