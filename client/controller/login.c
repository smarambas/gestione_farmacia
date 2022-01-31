#include <stdbool.h>

#include "login.h"
#include "medico.h"
#include "amministrativo.h"
#include "../view/login.h"
#include "../model/db.h"


bool login(void)
{
	struct credentials cred;
	view_login(&cred);
	role_t role = attempt_login(&cred);

	switch(role) {
		case MEDICO:
			medical_controller();
			break;
		case AMMIN:
			administrative_controller();
			break;
		default:
			return false;
	}

	return true;
}
