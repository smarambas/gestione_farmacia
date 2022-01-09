#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#include "defines.h"

static char *opt_host_name = NULL; /* host (default=localhost) */
static char *opt_user_name = "personale_medico"; /* username (default=login name)*/
static char *opt_password = NULL; /* password (default=none) */
static unsigned int opt_port_num = 0; /* port number (use built-in) */
static char *opt_socket_name = NULL; /* socket name (use built-in) */
static char *opt_db_name = "gestione-farmacia"; /* database name (default=none) */
static unsigned int opt_flags = 0; /* connection flags (none) */
static MYSQL *conn; /* pointer to connection handler */

int main(int argc, char **argv) 
{
    /* initialize connection handler */
    
    printf("Initializing connection handler\n");
    
    conn = mysql_init(NULL);
    if(conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Trying to connect to server...\n");
    
    /* connect to server */
    if (mysql_real_connect (conn, opt_host_name, opt_user_name,
        opt_password, opt_db_name, opt_port_num, opt_socket_name,
        opt_flags) == NULL) {
            fprintf(stderr, "mysql_real_connect() failed\n");
            mysql_close(conn);
            exit(EXIT_FAILURE);
    }
    
    printf("Connection established!\n");
    
    while(1) {
        continue;
    }
    
    /* disconnect from server */
    mysql_close (conn);
    
    exit(EXIT_SUCCESS);
}
