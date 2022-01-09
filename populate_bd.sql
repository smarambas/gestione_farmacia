insert into `Fornitore` values ("Angelini");
insert into `Fornitore` values ("Pfizer");
insert into `Fornitore` values ("Giuliani");
insert into `Fornitore` values ("Curasept");

insert into `Sede` values ("Angelini", "Roma", "123", "Via Napoli", "06-616-72-32", "angelini@support.it", "11-25-22-39-45");
insert into `Sede` values ("Pfizer", "Milano", "456", "Via Garibaldi", "74-787-19-77", "pfizer_ita@support.it", "67-22-34-60-73");
insert into `Sede` values ("Curasept", "Saronno", "19", "Via G. Parini", "215-651-33-54", "curaseptspa@support.it", NULL);
insert into `Sede` values ("Giuliani", "Verona", "7", "Via Mazzini", "324-775-67-85", "giuliani@support.it", NULL);

insert into `Categoria` values ("Antipiretico");
insert into `Categoria` values ("Vaccino anti-Covid19");
insert into `Categoria` values ("Colluttorio");
insert into `Categoria` values ("Analgesico");
insert into `Categoria` values ("Antinfiammatorio");
insert into `Categoria` values ("Anticoagulante");

insert into `Interagisce` values ("Antinfiammatorio", "Anticoagulante");

insert into `Prodotto` values ("Tachipirina 500mg", "Angelini", "M", 0, "Antipiretico", 0, 0);
insert into `Prodotto` values ("Moment 200mg", "Angelini", "M", 0, "Analgesico", 0, 0);
insert into `Prodotto` values ("Comirnaty", "Pfizer", "M", 0, "Vaccino anti-Covid19", 0, 0);
insert into `Prodotto` values ("Colluttorio", "Curasept", "M", 0, "Colluttorio", 0, 0);
insert into `Prodotto` values ("Lichtena Crema", "Giuliani", "C", 5, NULL, 0, 0);
insert into `Prodotto` values ("Aulin 100mg", "Angelini", "M", 0, "Antinfiammatorio", 1, 1);
insert into `Prodotto` values ("Tantum rosa", "Angelini", "C", 5, NULL, 0, 0);
insert into `Prodotto` values ("Bioscalin shampoo", "Giuliani", "C", 5, NULL, 0, 0);

call genera_lettera_acquisto();

call aggiungi_richiesta_prodotto(1, "Tachipirina 500mg", "Angelini", 10);
call aggiungi_richiesta_prodotto(1, "Aulin 100mg", "Angelini", 10);

call aggiungi_scaffale("Antipiretico");
call aggiungi_scaffale("Analgesico");
call aggiungi_scaffale("Antinfiammatorio");

call aggiungi_scatola("Tachipirina 500mg", "Angelini", "2021-12-01", 1, 1);
call aggiungi_scatola("Tachipirina 500mg", "Angelini", "2022-12-01", 1, 1);
call aggiungi_scatola("Aulin 100mg", "Angelini", "2023-12-01", 17, 3);

call registra_vendita();
call aggiungi_prodotto_venduto(1, "Tantum rosa", "Angelini", 2, NULL, NULL);
call aggiungi_prodotto_venduto(1, "Tachipirina 500mg", "Angelini", 1, "PSNMRC92D14A433S", NULL);

call registra_vendita();
call aggiungi_prodotto_venduto(2, "Aulin 100mg", "Angelini", 1, "PSNMRC92D14A433S", "Rossi");
call aggiungi_prodotto_venduto(2, "Tachipirina 500mg", "Angelini", 1, "PSNMRC92D14A433S", NULL);

call aggiungi_uso("Tachipirina 500mg", "Angelini", "Per il trattamento di febbre e cefalee");