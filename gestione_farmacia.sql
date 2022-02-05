-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema gestione-farmacia
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema gestione-farmacia
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `gestione-farmacia` ;
USE `gestione-farmacia` ;

-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Fornitori`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Fornitori` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Fornitori` (
  `Nome` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Nome`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Indirizzi`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Indirizzi` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Indirizzi` (
  `Citta` VARCHAR(45) NOT NULL,
  `Via` VARCHAR(45) NOT NULL,
  `Numero_civico` VARCHAR(45) NOT NULL,
  `Fatturazione` TINYINT NULL DEFAULT 0,
  `Fornitore` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Citta`, `Via`, `Numero_civico`),
  INDEX `fk_Indirizzo_1_idx` (`Fornitore` ASC) VISIBLE,
  CONSTRAINT `fk_Indirizzo_1`
    FOREIGN KEY (`Fornitore`)
    REFERENCES `gestione-farmacia`.`Fornitori` (`Nome`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Categorie`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Categorie` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Categorie` (
  `Nome` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Nome`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Prodotti`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Prodotti` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Prodotti` (
  `Nome` VARCHAR(45) NOT NULL,
  `Fornitore` VARCHAR(45) NOT NULL,
  `Tipo` VARCHAR(1) NOT NULL,
  `Quantita` INT UNSIGNED NULL DEFAULT 0,
  `Categoria` VARCHAR(45) NULL DEFAULT NULL,
  `Necessita_ricetta` TINYINT NULL DEFAULT 0,
  `Mutuabile` TINYINT NULL DEFAULT 0,
  PRIMARY KEY (`Nome`, `Fornitore`),
  INDEX `fk_Prodotto_1_idx` (`Fornitore` ASC) VISIBLE,
  INDEX `fk_Prodotto_2_idx` (`Categoria` ASC) VISIBLE,
  CONSTRAINT `fk_Prodotto_1`
    FOREIGN KEY (`Fornitore`)
    REFERENCES `gestione-farmacia`.`Fornitori` (`Nome`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Prodotto_2`
    FOREIGN KEY (`Categoria`)
    REFERENCES `gestione-farmacia`.`Categorie` (`Nome`)
    ON DELETE SET NULL
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Interazioni`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Interazioni` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Interazioni` (
  `Categoria1` VARCHAR(45) NOT NULL,
  `Categoria2` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Categoria1`, `Categoria2`),
  INDEX `fk_Interagisce_2_idx` (`Categoria2` ASC) VISIBLE,
  CONSTRAINT `fk_Interagisce_1`
    FOREIGN KEY (`Categoria1`)
    REFERENCES `gestione-farmacia`.`Categorie` (`Nome`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Interagisce_2`
    FOREIGN KEY (`Categoria2`)
    REFERENCES `gestione-farmacia`.`Categorie` (`Nome`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Scaffali`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Scaffali` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Scaffali` (
  `Codice` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Categoria` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Codice`),
  INDEX `fk_Scaffale_1_idx` (`Categoria` ASC) VISIBLE,
  CONSTRAINT `fk_Scaffale_1`
    FOREIGN KEY (`Categoria`)
    REFERENCES `gestione-farmacia`.`Categorie` (`Nome`)
    ON DELETE NO ACTION
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Cassetti`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Cassetti` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Cassetti` (
  `Codice` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Scaffale` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`Codice`, `Scaffale`),
  INDEX `fk_Cassetto_1_idx` (`Scaffale` ASC) VISIBLE,
  CONSTRAINT `fk_Cassetto_1`
    FOREIGN KEY (`Scaffale`)
    REFERENCES `gestione-farmacia`.`Scaffali` (`Codice`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Scatole_medicinale`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Scatole_medicinale` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Scatole_medicinale` (
  `Codice` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Prodotto` VARCHAR(45) NOT NULL,
  `Fornitore` VARCHAR(45) NOT NULL,
  `Scadenza` DATE NOT NULL,
  `Cassetto` INT UNSIGNED NOT NULL,
  `Scaffale` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`Codice`),
  INDEX `fk_Scatola medicinale_1_idx` (`Prodotto` ASC, `Fornitore` ASC) VISIBLE,
  INDEX `fk_Scatola medicinale_2_idx` (`Cassetto` ASC, `Scaffale` ASC) VISIBLE,
  CONSTRAINT `fk_Scatola medicinale_1`
    FOREIGN KEY (`Prodotto` , `Fornitore`)
    REFERENCES `gestione-farmacia`.`Prodotti` (`Nome` , `Fornitore`)
    ON DELETE NO ACTION
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Scatola_medicinale_2`
    FOREIGN KEY (`Cassetto` , `Scaffale`)
    REFERENCES `gestione-farmacia`.`Cassetti` (`Codice` , `Scaffale`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Lettere_acquisto`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Lettere_acquisto` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Lettere_acquisto` (
  `Codice` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Data` DATE NOT NULL,
  PRIMARY KEY (`Codice`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Richieste`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Richieste` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Richieste` (
  `Lettera` INT UNSIGNED NOT NULL,
  `Prodotto` VARCHAR(45) NOT NULL,
  `Fornitore` VARCHAR(45) NOT NULL,
  `Quantita` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`Lettera`, `Prodotto`, `Fornitore`),
  INDEX `fk_Richiede_2_idx` (`Prodotto` ASC, `Fornitore` ASC) VISIBLE,
  CONSTRAINT `fk_Richiede_1`
    FOREIGN KEY (`Lettera`)
    REFERENCES `gestione-farmacia`.`Lettere_acquisto` (`Codice`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Richiede_2`
    FOREIGN KEY (`Prodotto` , `Fornitore`)
    REFERENCES `gestione-farmacia`.`Prodotti` (`Nome` , `Fornitore`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Usi`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Usi` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Usi` (
  `Codice` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Descrizione` VARCHAR(256) NOT NULL,
  PRIMARY KEY (`Codice`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Descrizioni`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Descrizioni` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Descrizioni` (
  `Uso` INT UNSIGNED NOT NULL,
  `Prodotto` VARCHAR(45) NOT NULL,
  `Fornitore` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Uso`, `Prodotto`, `Fornitore`),
  INDEX `fk_Descrive_2_idx` (`Prodotto` ASC, `Fornitore` ASC) VISIBLE,
  CONSTRAINT `fk_Descrive_1`
    FOREIGN KEY (`Uso`)
    REFERENCES `gestione-farmacia`.`Usi` (`Codice`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Descrive_2`
    FOREIGN KEY (`Prodotto` , `Fornitore`)
    REFERENCES `gestione-farmacia`.`Prodotti` (`Nome` , `Fornitore`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Vendite`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Vendite` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Vendite` (
  `Nr_scontrino` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Data` DATE NOT NULL DEFAULT CURRENT_DATE,
  PRIMARY KEY (`Nr_scontrino`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Vendite_cosmetico`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Vendite_cosmetico` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Vendite_cosmetico` (
  `Vendita` INT UNSIGNED NOT NULL,
  `Prodotto` VARCHAR(45) NOT NULL,
  `Fornitore` VARCHAR(45) NOT NULL,
  `Quantita` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`Vendita`, `Prodotto`, `Fornitore`),
  INDEX `fk_Vendita_cosmetico_2_idx` (`Prodotto` ASC, `Fornitore` ASC) VISIBLE,
  CONSTRAINT `fk_Vendita_cosmetico_1`
    FOREIGN KEY (`Vendita`)
    REFERENCES `gestione-farmacia`.`Vendite` (`Nr_scontrino`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Vendita_cosmetico_2`
    FOREIGN KEY (`Prodotto` , `Fornitore`)
    REFERENCES `gestione-farmacia`.`Prodotti` (`Nome` , `Fornitore`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Vendite_senza_ricetta`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Vendite_senza_ricetta` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Vendite_senza_ricetta` (
  `Vendita` INT UNSIGNED NOT NULL,
  `Prodotto` VARCHAR(45) NOT NULL,
  `Fornitore` VARCHAR(45) NOT NULL,
  `Quantita` INT UNSIGNED NOT NULL,
  `CF` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`Vendita`, `Prodotto`, `Fornitore`),
  INDEX `fk_Vendita_senza_ricetta_2_idx` (`Prodotto` ASC, `Fornitore` ASC) VISIBLE,
  CONSTRAINT `fk_Vendita_senza_ricetta_1`
    FOREIGN KEY (`Vendita`)
    REFERENCES `gestione-farmacia`.`Vendite` (`Nr_scontrino`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Vendita_senza_ricetta_2`
    FOREIGN KEY (`Prodotto` , `Fornitore`)
    REFERENCES `gestione-farmacia`.`Prodotti` (`Nome` , `Fornitore`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Vendite_con_ricetta`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Vendite_con_ricetta` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Vendite_con_ricetta` (
  `Vendita` INT UNSIGNED NOT NULL,
  `Prodotto` VARCHAR(45) NOT NULL,
  `Fornitore` VARCHAR(45) NOT NULL,
  `Quantita` INT UNSIGNED NOT NULL,
  `Medico` VARCHAR(45) NOT NULL,
  `CF` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`Vendita`, `Prodotto`, `Fornitore`),
  INDEX `fk_Vendita_con_ricetta_2_idx` (`Prodotto` ASC, `Fornitore` ASC) VISIBLE,
  CONSTRAINT `fk_Vendita_con_ricetta_1`
    FOREIGN KEY (`Vendita`)
    REFERENCES `gestione-farmacia`.`Vendite` (`Nr_scontrino`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Vendita_con_ricetta_2`
    FOREIGN KEY (`Prodotto` , `Fornitore`)
    REFERENCES `gestione-farmacia`.`Prodotti` (`Nome` , `Fornitore`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Recapiti`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Recapiti` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Recapiti` (
  `Contatto` VARCHAR(45) NOT NULL,
  `Preferito` TINYINT NULL DEFAULT 0,
  `Fornitore` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Contatto`),
  INDEX `fk_Recapito_1_idx` (`Fornitore` ASC) VISIBLE,
  CONSTRAINT `fk_Recapito_1`
    FOREIGN KEY (`Fornitore`)
    REFERENCES `gestione-farmacia`.`Fornitori` (`Nome`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `gestione-farmacia`.`Utenti`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Utenti` ;

CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Utenti` (
  `Username` VARCHAR(45) NOT NULL,
  `Password` CHAR(32) NOT NULL,
  `Ruolo` ENUM('p_medico', 'p_ammin') NOT NULL,
  PRIMARY KEY (`Username`))
ENGINE = InnoDB;

USE `gestione-farmacia` ;

-- -----------------------------------------------------
-- Placeholder table for view `gestione-farmacia`.`Volume_vendite_prodotti`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Volume_vendite_prodotti` (`Nome_prodotto` INT, `Nome_fornitore` INT, `Tipo` INT, `Quantita_venduta` INT);

-- -----------------------------------------------------
-- Placeholder table for view `gestione-farmacia`.`Volume_vendite_cosmetici`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Volume_vendite_cosmetici` (`Nome_prodotto` INT, `Nome_fornitore` INT, `Tipo` INT, `Quantita_venduta` INT);

-- -----------------------------------------------------
-- Placeholder table for view `gestione-farmacia`.`Volume_vendite_senza_ricetta`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Volume_vendite_senza_ricetta` (`Nome_prodotto` INT, `Nome_fornitore` INT, `Tipo` INT, `Quantita_venduta` INT);

-- -----------------------------------------------------
-- Placeholder table for view `gestione-farmacia`.`Volume_vendite_con_ricetta`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `gestione-farmacia`.`Volume_vendite_con_ricetta` (`Nome_prodotto` INT, `Nome_fornitore` INT, `Tipo` INT, `Quantita_venduta` INT);

-- -----------------------------------------------------
-- procedure aggiungi_cosmetico
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_cosmetico`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_cosmetico` (IN var_prodotto VARCHAR(45), IN var_fornitore VARCHAR(45))
BEGIN
	insert into `Prodotti`(Nome, Fornitore, Tipo) values (var_prodotto, var_fornitore, 'C');
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_medicinale
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_medicinale`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_medicinale` (IN var_prodotto VARCHAR(45), IN var_fornitore VARCHAR(45), IN var_cat VARCHAR(45), IN var_ricetta TINYINT, IN var_mutuabile TINYINT)
BEGIN
	insert into `Prodotti`(Nome, Fornitore, Tipo, Categoria, Necessita_ricetta, Mutuabile) values (var_prodotto, var_fornitore, 'M', var_cat, var_ricetta, var_mutuabile);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_fornitore
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_fornitore`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_fornitore` (IN var_fornitore VARCHAR(45))
BEGIN
	insert into `Fornitori` values (var_fornitore);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure rimuovi_fornitore
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`rimuovi_fornitore`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `rimuovi_fornitore` (IN var_fornitore VARCHAR(45))
BEGIN
	delete from `Fornitori` where `Nome` = var_fornitore;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_interazione
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_interazione`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_interazione` (IN var_cat1 VARCHAR(45), IN var_cat2 VARCHAR(45))
BEGIN
	insert into `Interazioni` values (var_cat1, var_cat2);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure lista_cat_interagenti
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`lista_cat_interagenti`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `lista_cat_interagenti` (IN var_medicinale VARCHAR(45), IN var_fornitore VARCHAR(45))
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Categoria1`,`Categoria2` 
        from `Prodotti` join `Interazioni` on `Categoria` = `Categoria1` or `Categoria` = `Categoria2` 
        where `Nome` = var_medicinale and `Fornitore` = var_fornitore;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure registra_vendita
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`registra_vendita`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `registra_vendita` ()
BEGIN
	declare var_data date;
    
    declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    set var_data = current_date();	

    set transaction isolation level read uncommitted;
    start transaction;
		insert into `Vendite`(`Data`) values (var_data);
        
		select last_insert_id(), var_data;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_scatola
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_scatola`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_scatola` (IN var_prodotto VARCHAR(45), IN var_fornitore VARCHAR(45), IN var_scadenza DATE, IN var_cassetto INT, IN var_scaffale INT)
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
	set transaction isolation level read uncommitted;
    start transaction;
		insert into `Scatole_medicinale`(`Prodotto`,`Fornitore`,`Scadenza`,`Cassetto`,`Scaffale`) values (var_prodotto, var_fornitore, var_scadenza, var_cassetto, var_scaffale);
        
        call incrementa_giacenza(var_prodotto, var_fornitore, 1);
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure rimuovi_scatola
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`rimuovi_scatola`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `rimuovi_scatola` (IN var_scatola INT)
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    set transaction isolation level read committed;
    start transaction;
		select `Prodotto`, `Fornitore`
        from `Scatole_medicinale`
        where `Codice` = var_scatola;
        
        delete from `Scatole_medicinale` where `Codice` = var_scatola;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure genera_report_magazzino
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`genera_report_magazzino`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `genera_report_magazzino` ()
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;

	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Nome`,`Fornitore`,`Tipo`,`Quantita` 
		from `Prodotti`;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure genera_lettera_acquisto
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`genera_lettera_acquisto`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `genera_lettera_acquisto` ()
BEGIN
	declare var_data date;
        
    declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    set var_data = current_date();	

    set transaction isolation level read uncommitted;
    start transaction;
		insert into `Lettere_acquisto`(`Data`) values (var_data);
        
		select last_insert_id(), var_data;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure genera_report_scadenze
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`genera_report_scadenze`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `genera_report_scadenze` ()
BEGIN
	declare var_curdate date;
    declare var_nextmonth date;

	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    set var_curdate = current_date();
    set var_nextmonth = date_add(var_curdate, interval 1 month);
    
	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Codice`,`Prodotto`,`Fornitore`,`Scadenza`,`Cassetto`,`Scaffale` 
        from `Scatole_medicinale`
        where `Scadenza` between var_curdate and var_nextmonth or `Scadenza` < var_curdate
        order by `Scadenza`;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_scaffale
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_scaffale`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_scaffale` (IN var_cat VARCHAR(45))
BEGIN
	declare var_id int;
    declare var_i int;
    declare var_num_cassetti int;
    
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;

	set transaction isolation level read uncommitted;
    start transaction;
		insert into `Scaffali`(`Categoria`) values (var_cat);
        
        select last_insert_id() into var_id;
        
		set var_i = 0;
		set var_num_cassetti = 10;
		
		ins_loop: loop
			if var_i >= var_num_cassetti then
				leave ins_loop;
			end if;
			
			insert into `Cassetti`(`Scaffale`) values (var_id);
			set var_i = var_i + 1;
		end loop;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure vendite_prodotto
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`vendite_prodotto`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `vendite_prodotto` (IN var_prodotto VARCHAR(45), IN var_fornitore VARCHAR(45), OUT var_tipo_prod VARCHAR(1), OUT var_serve_ricetta TINYINT)
BEGIN
	declare var_tipo VARCHAR(1);
    declare var_ricetta TINYINT;
    
    declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;

	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Tipo`,`Necessita_ricetta` 
		from `Prodotti` 
		where `Nome` = var_prodotto and `Fornitore` = var_fornitore 
		into var_tipo, var_ricetta;
        
        if var_tipo = 'C' then
			select `Nr_scontrino`,`Data`,`Quantita` 
            from `Vendite` join `Vendite_cosmetico` on `Nr_scontrino` = `Vendita`
            where `Prodotto` = var_prodotto and `Fornitore` = var_fornitore
            order by `Data`, `Nr_scontrino`;
		elseif var_tipo = 'M' then
			if var_ricetta = 0 then
				select `Nr_scontrino`,`Data`,`Quantita`,`CF`
				from `Vendite` join `Vendite_senza_ricetta` on `Nr_scontrino` = `Vendita`
				where `Prodotto` = var_prodotto and `Fornitore` = var_fornitore
				order by `Data`, `Nr_scontrino`;
			else 
				select `Nr_scontrino`,`Data`,`Quantita`,`CF`,`Medico`
				from `Vendite` join `Vendite_con_ricetta` on `Nr_scontrino` = `Vendita`
				where `Prodotto` = var_prodotto and `Fornitore` = var_fornitore
				order by `Data`, `Nr_scontrino`;
            end if;
        end if;
        
        set var_tipo_prod = var_tipo;
		set var_serve_ricetta = var_ricetta;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_categoria
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_categoria`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_categoria` (IN var_nuova_cat VARCHAR(45))
BEGIN
	insert into `Categorie` values (var_nuova_cat);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure lista_lettere_inviate
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`lista_lettere_inviate`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `lista_lettere_inviate` (IN var_fornitore VARCHAR(45))
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Codice`,`Data`,`Prodotto`,`Quantita` 
        from `Lettere_acquisto` join `Richieste` on `Codice` = `Lettera`
        where `Fornitore` = var_fornitore
        order by `Codice`;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure rimuovi_prodotto
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`rimuovi_prodotto`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `rimuovi_prodotto` (IN var_prodotto VARCHAR(45), IN var_fornitore VARCHAR(45))
BEGIN
	delete from `Prodotti` where `Nome` = var_prodotto and `Fornitore` = var_fornitore;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure info_fornitore
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`info_fornitore`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `info_fornitore` (IN var_fornitore VARCHAR(45))
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Citta`, `Via`, `Numero_civico`, `Fatturazione`
        from `Fornitori` join `Indirizzi` on `Nome` = `Indirizzi`.`Fornitore`
        where `Nome` = var_fornitore;
        
        select `Contatto`, `Preferito`
        from `Fornitori` join `Recapiti` on `Nome` = `Recapiti`.`Fornitore`
        where `Nome` = var_fornitore;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_richiesta_prodotto
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_richiesta_prodotto`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_richiesta_prodotto` (IN var_lettera INT, IN var_prodotto VARCHAR(45), IN var_fornitore VARCHAR(45), IN var_quantita INT)
BEGIN
	insert into `Richieste` values (var_lettera, var_prodotto, var_fornitore, var_quantita);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_prodotto_venduto
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_prodotto_venduto`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_prodotto_venduto` (IN var_vendita INT, IN var_prodotto VARCHAR(45), IN var_fornitore VARCHAR(45), IN var_quantita INT, IN var_cf VARCHAR(45), IN var_medico VARCHAR(45))
BEGIN
	declare var_tipo VARCHAR(1);
    declare var_ricetta TINYINT;
    
    declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;

    set transaction isolation level read committed;
    start transaction;
        select `Tipo`,`Necessita_ricetta`
        from `Prodotti` 
        where `Nome` = var_prodotto and `Fornitore` = var_fornitore into var_tipo, var_ricetta;
        
        if var_tipo = 'C' then
			insert into `Vendite_cosmetico` values (var_vendita, var_prodotto, var_fornitore, var_quantita);
		elseif var_tipo = 'M' then
			if var_ricetta = 0 then
				insert into `Vendite_senza_ricetta` values (var_vendita, var_prodotto, var_fornitore, var_quantita, var_cf);
			else 
				insert into `Vendite_con_ricetta` values (var_vendita, var_prodotto, var_fornitore, var_quantita, var_medico, var_cf);
            end if;
        end if;
        
        call decrementa_giacenza(var_prodotto, var_fornitore, var_quantita);
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure lista_vendite_data
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`lista_vendite_data`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `lista_vendite_data` (IN var_data DATE)
BEGIN
	declare var_scontrino INT UNSIGNED;
    declare var_prodotto VARCHAR(45);
    declare var_fornitore VARCHAR(45);
    declare var_quantita INT;
    declare var_cf VARCHAR(45);
    declare var_medico VARCHAR(45);
    declare var_curdate DATE;
    
    declare done int default false;
    
	declare cur1 cursor for select `Nr_scontrino`, `Prodotto`, `Fornitore`, `Quantita` 
    from `Vendite` join `Vendite_cosmetico` on `Nr_scontrino` = `Vendita` 
    where `Data` = var_data;
    
    declare cur2 cursor for select `Nr_scontrino`, `Prodotto`, `Fornitore`, `Quantita`, `CF` 
    from `Vendite` join `Vendite_senza_ricetta` on `Nr_scontrino` = `Vendita` 
    where `Data` = var_data;
    
    declare cur3 cursor for select `Nr_scontrino`, `Prodotto`, `Fornitore`, `Quantita`, `CF`, `Medico` 
    from `Vendite` join `Vendite_con_ricetta` on `Nr_scontrino` = `Vendita` 
    where `Data` = var_data;
    
    declare continue handler for not found set done = true;
    
    declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    -- Create a table to store temporary results to be returned to the caller
	-- A temporary table is per-session
    drop temporary table if exists `result`;
	create temporary table `result` (
		`Nr_scontrino` INT UNSIGNED,
        `Prodotto` VARCHAR(45),
        `Fornitore` VARCHAR(45),
        `Tipo` VARCHAR(1),
        `Quantita` INT,
		`CF` VARCHAR(45),
        `Medico` VARCHAR(45)
    );
    
    set var_curdate = current_date();

	set transaction isolation level read committed;
    start transaction;
		if(var_data > var_curdate) then
			signal sqlstate '45002' set message_text = "La data inserita non è valida";
		end if;
        
        open cur1;
		read_loop: loop
        
			fetch cur1 into var_scontrino, var_prodotto, var_fornitore, var_quantita;
            if done then
				leave read_loop;
			end if;
            
            insert into `result` values (var_scontrino, var_prodotto, var_fornitore, 'C', var_quantita, NULL, NULL);

		end loop;
		close cur1;
        
        set done = false;
        open cur2;
		read_loop: loop
        
			fetch cur2 into var_scontrino, var_prodotto, var_fornitore, var_quantita, var_cf;
            if done then
				leave read_loop;
			end if;
            
            insert into `result` values (var_scontrino, var_prodotto, var_fornitore, 'M', var_quantita, var_cf, NULL);

		end loop;
		close cur2;
        
        set done = false;
        open cur3;
		read_loop: loop
        
			fetch cur3 into var_scontrino, var_prodotto, var_fornitore, var_quantita, var_cf, var_medico;
            if done then
				leave read_loop;
			end if;
            
            insert into `result` values (var_scontrino, var_prodotto, var_fornitore, 'M', var_quantita, var_cf, var_medico);

		end loop;
		close cur3;
        
        select * from `result`;
    commit;
    
    drop temporary table `result`;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure info_prodotto
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`info_prodotto`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `info_prodotto` (IN var_prodotto varchar(45), IN var_fornitore varchar(45))
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Nome`,`Prodotti`.`Fornitore` as `Fornitore`,`Tipo`,`Quantita`,`Categoria`,`Necessita_ricetta`,`Mutuabile`,`Descrizione` 
        from `Prodotti` left join `Descrizioni` on `Nome` = `Prodotto` and `Prodotti`.`Fornitore` = `Descrizioni`.`Fornitore` left join `Usi` on `Uso` = `Codice`
        where `Nome` = var_prodotto and `Prodotti`.`Fornitore` = var_fornitore;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_uso
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_uso`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_uso` (IN var_prodotto varchar(45), IN var_fornitore varchar(45), IN var_descrizione varchar(256))
BEGIN
	declare var_id int;

	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
    set transaction isolation level read uncommitted;
    start transaction;
		insert into `Usi`(`Descrizione`) values (var_descrizione);
        
        set var_id = last_insert_id();
        
        insert into `Descrizioni` values (var_id, var_prodotto, var_fornitore);
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure login
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`login`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `login` (in var_username varchar(45), in var_pass varchar(45), out var_role INT)
BEGIN
	declare var_user_role ENUM('p_medico', 'p_ammin');
    
	select `Ruolo` 
	from `Utenti`
	where `Username` = var_username	
	and `Password` = md5(var_pass)
	into var_user_role;
        
	-- See the corresponding enum in the client
	if var_user_role = 'p_medico' then
		set var_role = 1;
	elseif var_user_role = 'p_ammin' then
		set var_role = 2;
	else
		set var_role = 3;
	end if;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure lista_prodotti_fornitore
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`lista_prodotti_fornitore`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `lista_prodotti_fornitore` (in var_fornitore varchar(45))
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Nome`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`
        from `Prodotti`
        where `Fornitore` = var_fornitore;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_indirizzo
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_indirizzo`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_indirizzo` (IN var_citta varchar(45), in var_via varchar(45), IN var_civico varchar(45), in var_fatturazione tinyint, in var_fornitore varchar(45))
BEGIN
	insert into `Indirizzi` values (var_citta, var_via, var_civico, var_fatturazione, var_fornitore);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure rimuovi_indirizzo
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`rimuovi_indirizzo`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `rimuovi_indirizzo` (IN var_citta varchar(45), in var_via varchar(45), IN var_civico varchar(45))
BEGIN
	delete from `Indirizzi` where `Citta` = var_citta and `Via` = var_via and `Numero_civico` = var_civico;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_recapito
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`aggiungi_recapito`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `aggiungi_recapito` (IN var_contatto varchar(45), in var_preferito tinyint, in var_fornitore varchar(45))
BEGIN
	insert into `Recapiti` values (var_contatto, var_preferito, var_fornitore);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure rimuovi_recapito
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`rimuovi_recapito`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `rimuovi_recapito` (IN var_contatto varchar(45))
BEGIN
	delete from `Recapiti` where `Contatto` = var_contatto;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure modifica_cat_scaffale
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`modifica_cat_scaffale`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `modifica_cat_scaffale` (in var_scaffale int, in var_newcat varchar(45))
BEGIN
	update `Scaffali` set `Categoria` = var_newcat
    where `Codice` = var_scaffale;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure lista_scaffali
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`lista_scaffali`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `lista_scaffali` ()
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Codice` as `Codice_scaffale`, `Categoria`
        from `Scaffali`
        order by `Codice_scaffale`;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure lista_prodotti_top
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`lista_prodotti_top`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `lista_prodotti_top` ()
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Nome_prodotto`, `Nome_fornitore`, `Tipo`, `Quantita_venduta`
		from `Volume_vendite_prodotti`
        order by `Quantita_venduta` desc;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure lista_scatole_prodotto
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`lista_scatole_prodotto`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `lista_scatole_prodotto` (IN var_prodotto varchar(45), IN var_fornitore varchar(45))
BEGIN
	declare var_tipo varchar(1);
    
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Tipo`
        from `Prodotti`
        where `Nome` = var_prodotto and `Fornitore` = var_fornitore
        into var_tipo;
        
        if var_tipo = 'M' then
			select `Codice`,`Cassetto`,`Scaffale` 
			from `Prodotti` join `Scatole_medicinale` on `Nome` = `Prodotto` and `Prodotti`.`Fornitore` = `Scatole_medicinale`.`Fornitore`
			where `Nome` = var_prodotto and `Prodotti`.`Fornitore` = var_fornitore
			order by `Codice`;
		else 
			signal sqlstate '45003' set message_text = "Il prodotto inserito è un cosmetico";
		end if;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure decrementa_giacenza
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`decrementa_giacenza`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `decrementa_giacenza` (IN var_prodotto VARCHAR(45), IN var_fornitore VARCHAR(45), IN var_quantita INT)
BEGIN
	update `Prodotti` set `Quantita` = `Quantita` - var_quantita
    where `Nome` = var_prodotto and `Fornitore` = var_fornitore and `Quantita` >= var_quantita;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure lista_prodotti
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`lista_prodotti`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `lista_prodotti` ()
BEGIN
	declare exit handler for sqlexception
    begin
        rollback;  -- rollback any changes made in the transaction
        resignal;  -- raise again the sql exception to the caller
    end;
    
	set transaction read only;
    set transaction isolation level read committed;
    start transaction;
		select `Nome`,  `Fornitore`
        from `Prodotti`
        order by `Nome`;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure incrementa_giacenza
-- -----------------------------------------------------

USE `gestione-farmacia`;
DROP procedure IF EXISTS `gestione-farmacia`.`incrementa_giacenza`;

DELIMITER $$
USE `gestione-farmacia`$$
CREATE PROCEDURE `incrementa_giacenza` (IN var_prodotto VARCHAR(45), IN var_fornitore VARCHAR(45), IN var_quantita_addizionale INT)
BEGIN
	update `Prodotti` set `Quantita` = `Quantita` + var_quantita_addizionale
    where `Nome` = var_prodotto and `Fornitore` = var_fornitore;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- View `gestione-farmacia`.`Volume_vendite_prodotti`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Volume_vendite_prodotti`;
DROP VIEW IF EXISTS `gestione-farmacia`.`Volume_vendite_prodotti` ;
USE `gestione-farmacia`;
CREATE  OR REPLACE VIEW `Volume_vendite_prodotti` AS
select `Nome_prodotto`, `Nome_fornitore`, `Tipo`, `Quantita_venduta`
from `Volume_vendite_cosmetici`
union
select `Nome_prodotto`, `Nome_fornitore`, `Tipo`, `Quantita_venduta`
from `Volume_vendite_senza_ricetta`
union
select `Nome_prodotto`, `Nome_fornitore`, `Tipo`, `Quantita_venduta`
from `Volume_vendite_con_ricetta`;

-- -----------------------------------------------------
-- View `gestione-farmacia`.`Volume_vendite_cosmetici`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Volume_vendite_cosmetici`;
DROP VIEW IF EXISTS `gestione-farmacia`.`Volume_vendite_cosmetici` ;
USE `gestione-farmacia`;
CREATE  OR REPLACE VIEW `Volume_vendite_cosmetici` AS
select `Nome` as `Nome_prodotto`, `Prodotti`.`Fornitore` as `Nome_fornitore`, `Tipo`, sum(`Vendite_cosmetico`.`Quantita`) as `Quantita_venduta`
from `Vendite` join `Vendite_cosmetico` on `Nr_scontrino` = `Vendita` join `Prodotti` on `Prodotto` = `Nome` and `Vendite_cosmetico`.`Fornitore` = `Prodotti`.`Fornitore`
group by `Nome_prodotto`, `Nome_fornitore`, `Tipo`;

-- -----------------------------------------------------
-- View `gestione-farmacia`.`Volume_vendite_senza_ricetta`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Volume_vendite_senza_ricetta`;
DROP VIEW IF EXISTS `gestione-farmacia`.`Volume_vendite_senza_ricetta` ;
USE `gestione-farmacia`;
CREATE  OR REPLACE VIEW `Volume_vendite_senza_ricetta` AS
SELECT `Nome` AS `Nome_prodotto`, `Prodotti`.`Fornitore` AS `Nome_fornitore`, `Tipo`, SUM(`Vendite_senza_ricetta`.`Quantita`) AS `Quantita_venduta`
FROM `Vendite` JOIN `Vendite_senza_ricetta` ON `Nr_scontrino` = `Vendita` JOIN `Prodotti` ON `Prodotto` = `Nome` AND `Vendite_senza_ricetta`.`Fornitore` = `Prodotti`.`Fornitore`
GROUP BY `Nome_prodotto`, `Nome_fornitore`, `Tipo`;

-- -----------------------------------------------------
-- View `gestione-farmacia`.`Volume_vendite_con_ricetta`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gestione-farmacia`.`Volume_vendite_con_ricetta`;
DROP VIEW IF EXISTS `gestione-farmacia`.`Volume_vendite_con_ricetta` ;
USE `gestione-farmacia`;
CREATE  OR REPLACE VIEW `Volume_vendite_con_ricetta` AS
SELECT `Nome` AS `Nome_prodotto`, `Prodotti`.`Fornitore` AS `Nome_fornitore`, `Tipo`, SUM(`Vendite_con_ricetta`.`Quantita`) AS `Quantita_venduta`
FROM `Vendite` JOIN `Vendite_con_ricetta` ON `Nr_scontrino` = `Vendita` JOIN `Prodotti` ON `Prodotto` = `Nome` AND `Vendite_con_ricetta`.`Fornitore` = `Prodotti`.`Fornitore`
GROUP BY `Nome_prodotto`, `Nome_fornitore`, `Tipo`;
SET SQL_MODE = '';
DROP USER IF EXISTS personale_medico;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'personale_medico' IDENTIFIED BY 'medico';

GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_interazione` TO 'personale_medico';
GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_prodotto_venduto` TO 'personale_medico';
GRANT EXECUTE ON procedure `gestione-farmacia`.`lista_cat_interagenti` TO 'personale_medico';
GRANT EXECUTE ON procedure `gestione-farmacia`.`registra_vendita` TO 'personale_medico';
GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_categoria` TO 'personale_medico';
GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_uso` TO 'personale_medico';
GRANT EXECUTE ON procedure `gestione-farmacia`.`info_prodotto` TO 'personale_medico';
GRANT EXECUTE ON procedure `gestione-farmacia`.`rimuovi_scatola` TO 'personale_medico';
GRANT EXECUTE ON procedure `gestione-farmacia`.`lista_scaffali` TO 'personale_medico';
GRANT EXECUTE ON procedure `gestione-farmacia`.`lista_scatole_prodotto` TO 'personale_medico';
GRANT EXECUTE ON procedure `gestione-farmacia`.`decrementa_giacenza` TO 'personale_medico';
GRANT EXECUTE ON procedure `gestione-farmacia`.`lista_prodotti` TO 'personale_medico';
SET SQL_MODE = '';
DROP USER IF EXISTS personale_amministrativo;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'personale_amministrativo' IDENTIFIED BY 'amministrativo';

GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_cosmetico` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_fornitore` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_medicinale` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_richiesta_prodotto` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_scaffale` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_scatola` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`genera_lettera_acquisto` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`genera_report_magazzino` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`genera_report_scadenze` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`info_fornitore` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`lista_lettere_inviate` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`rimuovi_fornitore` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`rimuovi_prodotto` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`rimuovi_scatola` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`vendite_prodotto` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`lista_vendite_data` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`lista_prodotti_fornitore` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_indirizzo` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`rimuovi_indirizzo` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_recapito` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`rimuovi_recapito` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`modifica_cat_scaffale` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`lista_scaffali` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`aggiungi_uso` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`lista_prodotti_top` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`decrementa_giacenza` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`lista_prodotti` TO 'personale_amministrativo';
GRANT EXECUTE ON procedure `gestione-farmacia`.`incrementa_giacenza` TO 'personale_amministrativo';
SET SQL_MODE = '';
DROP USER IF EXISTS login;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'login' IDENTIFIED BY 'login';

GRANT EXECUTE ON procedure `gestione-farmacia`.`login` TO 'login';

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Fornitori`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Fornitori` (`Nome`) VALUES ('Angelini');
INSERT INTO `gestione-farmacia`.`Fornitori` (`Nome`) VALUES ('Pfizer');
INSERT INTO `gestione-farmacia`.`Fornitori` (`Nome`) VALUES ('Giuliani');
INSERT INTO `gestione-farmacia`.`Fornitori` (`Nome`) VALUES ('Curasept');
INSERT INTO `gestione-farmacia`.`Fornitori` (`Nome`) VALUES ('Jowae');
INSERT INTO `gestione-farmacia`.`Fornitori` (`Nome`) VALUES ('Menarini');
INSERT INTO `gestione-farmacia`.`Fornitori` (`Nome`) VALUES ('GSK');
INSERT INTO `gestione-farmacia`.`Fornitori` (`Nome`) VALUES ('Moderna');

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Indirizzi`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Indirizzi` (`Citta`, `Via`, `Numero_civico`, `Fatturazione`, `Fornitore`) VALUES ('Roma', 'Via Napoli', '123', 1, 'Angelini');
INSERT INTO `gestione-farmacia`.`Indirizzi` (`Citta`, `Via`, `Numero_civico`, `Fatturazione`, `Fornitore`) VALUES ('Milano', 'Via Garibaldi', '456', 1, 'Pfizer');
INSERT INTO `gestione-farmacia`.`Indirizzi` (`Citta`, `Via`, `Numero_civico`, `Fatturazione`, `Fornitore`) VALUES ('Saronno', 'Via G. Parini', '19', 1, 'Curasept');
INSERT INTO `gestione-farmacia`.`Indirizzi` (`Citta`, `Via`, `Numero_civico`, `Fatturazione`, `Fornitore`) VALUES ('Verona', 'Via Mazzini', '7', 0, 'Giuliani');
INSERT INTO `gestione-farmacia`.`Indirizzi` (`Citta`, `Via`, `Numero_civico`, `Fatturazione`, `Fornitore`) VALUES ('Parigi', 'Rue de la baguette', '123', 1, 'Jowae');
INSERT INTO `gestione-farmacia`.`Indirizzi` (`Citta`, `Via`, `Numero_civico`, `Fatturazione`, `Fornitore`) VALUES ('Torino', 'Via XX Settembre', '1', 0, 'Angelini');

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Categorie`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Antipiretico');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Analgesico');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Antidepressivo');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Antivirale');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Antinfiammatorio');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Anticoagulante');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Antibatterico');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Vaccino anti Covid19');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Antiepilettico');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Antidolorifico');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Corticosteroide');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('FANS');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Diuretico');
INSERT INTO `gestione-farmacia`.`Categorie` (`Nome`) VALUES ('Oppioide');

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Prodotti`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Tachipirina 500mg', 'Angelini', 'M', 2, 'Antipiretico', 0, 1);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Moment 200mg', 'Angelini', 'M', 0, 'Analgesico', 0, 1);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Comirnaty', 'Pfizer', 'M', 3, 'Vaccino anti Covid19', 0, 0);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Collutorio', 'Curasept', 'M', 2, 'Antibatterico', 1, 1);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Lichtena crema', 'Giuliani', 'C', 5, NULL, 0, 0);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Aulin 100mg', 'Angelini', 'M', 3, 'Antinfiammatorio', 1, 1);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Tantum rosa', 'Angelini', 'C', 5, NULL, 0, 0);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Bioscalin shampoo', 'Giuliani', 'C', 5, NULL, 0, 0);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Gel viso', 'Jowae', 'C', 6, NULL, 0, 0);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Maschera argilla', 'Jowae', 'C', 4, NULL, 0, 0);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Gabapentin', 'Pfizer', 'M', 0, 'Antiepilettico', 1, 1);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Vivin c', 'Menarini', 'M', 0, 'Antidolorifico', 0, 1);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Fastum gel', 'Menarini', 'M', 2, 'Antinfiammatorio', 0, 0);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Voltadol', 'GSK', 'M', 2, 'Antinfiammatorio', 1, 1);
INSERT INTO `gestione-farmacia`.`Prodotti` (`Nome`, `Fornitore`, `Tipo`, `Quantita`, `Categoria`, `Necessita_ricetta`, `Mutuabile`) VALUES ('Spikevax', 'Moderna', 'M', 0, 'Vaccino anti Covid19', 0, 0);

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Interazioni`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Interazioni` (`Categoria1`, `Categoria2`) VALUES ('Antinfiammatorio', 'Anticoagulante');
INSERT INTO `gestione-farmacia`.`Interazioni` (`Categoria1`, `Categoria2`) VALUES ('Analgesico', 'FANS');
INSERT INTO `gestione-farmacia`.`Interazioni` (`Categoria1`, `Categoria2`) VALUES ('Antiepilettico', 'Oppioide');
INSERT INTO `gestione-farmacia`.`Interazioni` (`Categoria1`, `Categoria2`) VALUES ('Antidolorifico', 'Anticoagulante');

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Scaffali`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Scaffali` (`Codice`, `Categoria`) VALUES (1, 'Antipiretico');
INSERT INTO `gestione-farmacia`.`Scaffali` (`Codice`, `Categoria`) VALUES (2, 'Antibatterico');
INSERT INTO `gestione-farmacia`.`Scaffali` (`Codice`, `Categoria`) VALUES (3, 'Antinfiammatorio');
INSERT INTO `gestione-farmacia`.`Scaffali` (`Codice`, `Categoria`) VALUES (4, 'Vaccino anti Covid19');

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Cassetti`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (1, 1);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (2, 1);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (3, 1);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (4, 1);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (5, 1);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (6, 1);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (7, 1);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (8, 1);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (9, 1);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (10, 1);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (11, 2);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (12, 2);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (13, 2);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (14, 2);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (15, 2);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (16, 2);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (17, 2);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (18, 2);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (19, 2);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (20, 2);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (21, 3);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (22, 3);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (23, 3);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (24, 3);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (25, 3);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (26, 3);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (27, 3);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (28, 3);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (29, 3);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (30, 3);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (31, 4);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (32, 4);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (33, 4);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (34, 4);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (35, 4);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (36, 4);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (37, 4);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (38, 4);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (39, 4);
INSERT INTO `gestione-farmacia`.`Cassetti` (`Codice`, `Scaffale`) VALUES (40, 4);

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Scatole_medicinale`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (1, 'Tachipirina 500mg', 'Angelini', '2024-05-01', 1, 1);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (2, 'Tachipirina 500mg', 'Angelini', '2024-05-01', 1, 1);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (3, 'Collutorio', 'Curasept', '2022-03-01', 11, 2);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (4, 'Collutorio', 'Curasept', '2023-02-28', 12, 2);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (5, 'Aulin 100mg', 'Angelini', '2022-02-28', 21, 3);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (6, 'Aulin 100mg', 'Angelini', '2022-04-04', 21, 3);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (7, 'Aulin 100mg', 'Angelini', '2022-03-01', 22, 3);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (8, 'Fastum gel', 'Menarini', '2023-04-01', 23, 3);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (9, 'Fastum gel', 'Menarini', '2022-03-01', 23, 3);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (10, 'Voltadol', 'GSK', '2024-09-11', 24, 3);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (11, 'Voltadol', 'GSK', '2022-03-01', 24, 3);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (12, 'Comirnaty', 'Pfizer', '2023-05-05', 31, 4);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (13, 'Comirnaty', 'Pfizer', '2022-02-28', 32, 4);
INSERT INTO `gestione-farmacia`.`Scatole_medicinale` (`Codice`, `Prodotto`, `Fornitore`, `Scadenza`, `Cassetto`, `Scaffale`) VALUES (14, 'Comirnaty', 'Pfizer', '2024-06-06', 33, 4);

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Lettere_acquisto`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Lettere_acquisto` (`Codice`, `Data`) VALUES (1, '2022-01-10');

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Richieste`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Richieste` (`Lettera`, `Prodotto`, `Fornitore`, `Quantita`) VALUES (1, 'Comirnaty', 'Pfizer', 20);

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Usi`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Usi` (`Codice`, `Descrizione`) VALUES (1, 'Trattamento sintomatico di stati febbrili');
INSERT INTO `gestione-farmacia`.`Usi` (`Codice`, `Descrizione`) VALUES (2, 'Favorisce il benessere dei capelli e del cuoio capelluto');
INSERT INTO `gestione-farmacia`.`Usi` (`Codice`, `Descrizione`) VALUES (3, 'Trattamento locale di stati dolorosi e infiammatori');
INSERT INTO `gestione-farmacia`.`Usi` (`Codice`, `Descrizione`) VALUES (4, 'Detergente per il viso');
INSERT INTO `gestione-farmacia`.`Usi` (`Codice`, `Descrizione`) VALUES (5, 'Trattamento di manifestazioni dolorose di media entità');

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Descrizioni`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Descrizioni` (`Uso`, `Prodotto`, `Fornitore`) VALUES (1, 'Tachipirina 500mg', 'Angelini');
INSERT INTO `gestione-farmacia`.`Descrizioni` (`Uso`, `Prodotto`, `Fornitore`) VALUES (2, 'Bioscalin shampoo', 'Giuliani');
INSERT INTO `gestione-farmacia`.`Descrizioni` (`Uso`, `Prodotto`, `Fornitore`) VALUES (3, 'Voltadol', 'GSK');
INSERT INTO `gestione-farmacia`.`Descrizioni` (`Uso`, `Prodotto`, `Fornitore`) VALUES (4, 'Gel viso', 'Jowae');
INSERT INTO `gestione-farmacia`.`Descrizioni` (`Uso`, `Prodotto`, `Fornitore`) VALUES (5, 'Tachipirina 500mg', 'Angelini');
INSERT INTO `gestione-farmacia`.`Descrizioni` (`Uso`, `Prodotto`, `Fornitore`) VALUES (5, 'Moment 200mg', 'Angelini');

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Vendite`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Vendite` (`Nr_scontrino`, `Data`) VALUES (1, '2022-01-10');
INSERT INTO `gestione-farmacia`.`Vendite` (`Nr_scontrino`, `Data`) VALUES (2, '2022-01-11');

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Vendite_cosmetico`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Vendite_cosmetico` (`Vendita`, `Prodotto`, `Fornitore`, `Quantita`) VALUES (1, 'Lichtena crema', 'Giuliani', 1);

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Vendite_con_ricetta`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Vendite_con_ricetta` (`Vendita`, `Prodotto`, `Fornitore`, `Quantita`, `Medico`, `CF`) VALUES (1, 'Aulin 100mg', 'Angelini', 2, 'Verdi', '');
INSERT INTO `gestione-farmacia`.`Vendite_con_ricetta` (`Vendita`, `Prodotto`, `Fornitore`, `Quantita`, `Medico`, `CF`) VALUES (2, 'Aulin 100mg', 'Angelini', 1, 'Filini', NULL);

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Recapiti`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Recapiti` (`Contatto`, `Preferito`, `Fornitore`) VALUES ('06 616 72 32', 0, 'Angelini');
INSERT INTO `gestione-farmacia`.`Recapiti` (`Contatto`, `Preferito`, `Fornitore`) VALUES ('angelini@support.it', 1, 'Angelini');
INSERT INTO `gestione-farmacia`.`Recapiti` (`Contatto`, `Preferito`, `Fornitore`) VALUES ('74 787 19 77', 0, 'Pfizer');
INSERT INTO `gestione-farmacia`.`Recapiti` (`Contatto`, `Preferito`, `Fornitore`) VALUES ('324 775 67 85', 1, 'Giuliani');
INSERT INTO `gestione-farmacia`.`Recapiti` (`Contatto`, `Preferito`, `Fornitore`) VALUES ('giuliani@support.it', 0, 'Giuliani');
INSERT INTO `gestione-farmacia`.`Recapiti` (`Contatto`, `Preferito`, `Fornitore`) VALUES ('jowae@support.com', 1, 'Jowae');

COMMIT;


-- -----------------------------------------------------
-- Data for table `gestione-farmacia`.`Utenti`
-- -----------------------------------------------------
START TRANSACTION;
USE `gestione-farmacia`;
INSERT INTO `gestione-farmacia`.`Utenti` (`Username`, `Password`, `Ruolo`) VALUES ('mrossi', '5f4dcc3b5aa765d61d8327deb882cf99', 'p_ammin');
INSERT INTO `gestione-farmacia`.`Utenti` (`Username`, `Password`, `Ruolo`) VALUES ('gbianchi', '5f4dcc3b5aa765d61d8327deb882cf99', 'p_medico');

COMMIT;

USE `gestione-farmacia`;

DELIMITER $$

USE `gestione-farmacia`$$
DROP TRIGGER IF EXISTS `gestione-farmacia`.`Prodotti_BEFORE_UPDATE` $$
USE `gestione-farmacia`$$
CREATE DEFINER = CURRENT_USER TRIGGER `gestione-farmacia`.`Prodotti_BEFORE_UPDATE` BEFORE UPDATE ON `Prodotti` FOR EACH ROW
BEGIN
	declare var_giacenza_reale int;
    
    if(old.`Tipo` = 'M') then
		select count(*)
		from `Scatole_medicinale`
		where `Prodotto` = new.`Nome` and `Scatole_medicinale`.`Fornitore` = new.`Fornitore`
		into var_giacenza_reale;
        
		if(new.`Quantita` > var_giacenza_reale) then
			signal sqlstate '45000' set message_text = "Product quantity doesn't correspond to stock quantity!";
		end if;
    end if;
END$$


USE `gestione-farmacia`$$
DROP TRIGGER IF EXISTS `gestione-farmacia`.`Scaffali_BEFORE_UPDATE` $$
USE `gestione-farmacia`$$
CREATE DEFINER = CURRENT_USER TRIGGER `gestione-farmacia`.`Scaffali_BEFORE_UPDATE` BEFORE UPDATE ON `Scaffali` FOR EACH ROW
BEGIN
	declare var_quantita int;
    
    select count(*)
    from `Scatole_medicinale` 
    where `Scaffale` = new.Codice
    into var_quantita;
    
    if(var_quantita > 0) then
		signal sqlstate '45001' set message_text = "The shelf is not empty";
    end if;
END$$


USE `gestione-farmacia`$$
DROP TRIGGER IF EXISTS `gestione-farmacia`.`Scatole_medicinale_BEFORE_INSERT` $$
USE `gestione-farmacia`$$
CREATE DEFINER = CURRENT_USER TRIGGER `gestione-farmacia`.`Scatole_medicinale_BEFORE_INSERT` BEFORE INSERT ON `Scatole_medicinale` FOR EACH ROW
BEGIN
	declare var_cat_scaffale varchar(45);
    declare var_cat varchar(45);
    declare var_scadenza date;
    declare var_cur date;
    
    select `Categoria` from `Scaffali` where `Codice` = new.Scaffale into var_cat_scaffale;
    select `Categoria` from `Prodotti` where `Nome` = new.Prodotto and `Fornitore` = new.Fornitore into var_cat;
    
    set var_scadenza = new.Scadenza;
    set var_cur = current_date();
    
    if(var_cat_scaffale <> var_cat) then
		signal sqlstate '45000' set message_text = "The chosen drawer doesn't correspond to the category";
    end if;
    if(var_scadenza < var_cur) then
		signal sqlstate '45000' set message_text = "The box is already expired!";
    end if;
END$$


USE `gestione-farmacia`$$
DROP TRIGGER IF EXISTS `gestione-farmacia`.`Richieste_BEFORE_INSERT` $$
USE `gestione-farmacia`$$
CREATE DEFINER = CURRENT_USER TRIGGER `gestione-farmacia`.`Richieste_BEFORE_INSERT` BEFORE INSERT ON `Richieste` FOR EACH ROW
BEGIN
	declare var_fornitore varchar(45);
    
    select `Fornitore` 
    from `Richieste`
    where `Lettera` = new.`Lettera`
    limit 1
    into var_fornitore;
    
    if(var_fornitore is not NULL) then
		if(new.`Fornitore` <> var_fornitore) then
			signal sqlstate '45000' set message_text = "You can't send a letter to different suppliers!";
        end if;
    end if;
END$$


USE `gestione-farmacia`$$
DROP TRIGGER IF EXISTS `gestione-farmacia`.`Vendite_cosmetico_BEFORE_INSERT` $$
USE `gestione-farmacia`$$
CREATE DEFINER = CURRENT_USER TRIGGER `gestione-farmacia`.`Vendite_cosmetico_BEFORE_INSERT` BEFORE INSERT ON `Vendite_cosmetico` FOR EACH ROW
BEGIN
	declare var_quantita int;
    declare var_quantita_reale int;
    
    set var_quantita = new.Quantita;
    select `Quantita` from `Prodotti` where `Nome` = new.Prodotto and `Fornitore` = new.Fornitore into var_quantita_reale;
    
    if(var_quantita > var_quantita_reale or var_quantita <= 0) then
		signal sqlstate '45001' set message_text = "You can't sell more products than the stock quantity!";
    end if;
END$$


USE `gestione-farmacia`$$
DROP TRIGGER IF EXISTS `gestione-farmacia`.`Vendite_senza_ricetta_BEFORE_INSERT` $$
USE `gestione-farmacia`$$
CREATE DEFINER = CURRENT_USER TRIGGER `gestione-farmacia`.`Vendite_senza_ricetta_BEFORE_INSERT` BEFORE INSERT ON `Vendite_senza_ricetta` FOR EACH ROW
BEGIN
	declare var_quantita int;
    declare var_quantita_reale int;
    
    set var_quantita = new.Quantita;
    select `Quantita` from `Prodotti` where `Nome` = new.Prodotto and `Fornitore` = new.Fornitore into var_quantita_reale;
    
    if(var_quantita > var_quantita_reale or var_quantita <= 0) then
		signal sqlstate '45001' set message_text = "You can't sell more products than the stock quantity!";
    end if;
END$$


USE `gestione-farmacia`$$
DROP TRIGGER IF EXISTS `gestione-farmacia`.`Vendite_con_ricetta_BEFORE_INSERT` $$
USE `gestione-farmacia`$$
CREATE DEFINER = CURRENT_USER TRIGGER `gestione-farmacia`.`Vendite_con_ricetta_BEFORE_INSERT` BEFORE INSERT ON `Vendite_con_ricetta` FOR EACH ROW
BEGIN
	declare var_quantita int;
    declare var_quantita_reale int;
    
    set var_quantita = new.Quantita;
    select `Quantita` from `Prodotti` where `Nome` = new.Prodotto and `Fornitore` = new.Fornitore into var_quantita_reale;
    
    if(var_quantita > var_quantita_reale or var_quantita <= 0) then
		signal sqlstate '45001' set message_text = "You can't sell more products than the stock quantity!";
    end if;
END$$


DELIMITER ;
