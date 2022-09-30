readline


//rl_clear_history


//rl_on_new_line


//rl_replace_line


//rl_redisplay


//add_history


//fork


//wait


//waitpid


///wait3


//wait4


//signal


//sigaction


//sigemptyset


//sigaddset


//kill


//exit


//getcwd


//chdir


//stat


//lstat


//fstat


//unlink


//execve


//dup


//dup2


//pipe


//opendir
	DIR *opendir(const char *name);
		name: repertoire a ouvrir

	ouvre un flux répertoire correspondant au répertoire name, et renvoie un pointeur sur ce flux. Le flux est positionné sur la première entrée du répertoire.

	Valeur_de_retour_ou_cas_d_erreur:
		pointeur sur le flux de repertoire en cas de REUSSITE
		NULL en cas d'ECHER

//readdir
	struct dirent *readdir(DIR *dir);

	renvoie un pointeur sur une structure dirent représentant l'entrée suivante du flux répertoire pointé par dir

	Valeur_de_retour_ou_cas_d_erreur:
	pointeur sur une structure dirent REUSSITE
	NULL ECHEC

//closedir


//strerror


//perror


//isatty
	int isatty(int desc);

	renvoie 1 si desc est un descripteur de fichier ouvert connecté à un terminal, ou 0 autrement.  

//tyname


//ttyslot


//ioctl


//getenv
	char	*getenv(const char *name);
		name: env
	
	renvoie un pointeur sur la variable d'environnement passee en parametre

	Exemple:
		printf("%s\n", getenv("USER"));

	output:
		USER=kbrousse

//tcsetattr


//tcgetattr


https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/#4-tget-et-tputs
//tgetent
	int tgetent(char *bp, const char *name);
		bp: adresse d'un buffer dans lequel stocker les informations utiles au fonctionnement interne de Termcap
		name: nom/type du terminal

	An application program that is going to use termcap must first look up the description of the terminal type in use. This is done by calling tgetent, whose declaration in ANSI Standard C looks like:

	Exemple:
		char	*terminal_type;
		terminal_type = getent("TERM");
		tgetent(NULL, terminal_type);

	Valeur_de_retour_ou_cas_d_erreur:
		siterminal_type == NULL -> getent a echoue (au cas ou la variable d'environnement a ete unset)
		-1, la base de données n’est pas accessible.
		0, la base de données est accessible mais elle ne contient pas d’info pour ce type de terminal ou trop peu pour fonctionner convenablement
		1, la base de données est accessible et toutes les infos pour ce terminal ont été chargées en mémoire.

//tgetflag
	int tgetflag(char *id);
		id: ce que l'on souhaite recuperer

	fonctionne de la même manière que tgetnum à la différence prêt qu’il renvoie un booléen au lieu d’une valeur. Cette fonction est utilisée pour vérifier les capacités d’un terminal, savoir s’il est capable de faire tel ou tel action.

	Exemple:
		if (tgetflag("os") != 0)
		{
			code
		}

//tgetnum
	int tgetnum(char *id);
		id: ce que l'on souhaite recuperer

	permet de récupérer des informations numériques en rapport avec votre terminal.
Comme par exemple le nombre de lignes et de colonnes.

	Exemple:
		int column_count = tgetnum("co");
		int line_count = tgetnum("li");


//tgetstr
	char *tgetstr(char *id, char **area);
		id: termcap a executer
		area: adresse du buffer donne a tgetent
		
	permet de récupérer les fameux termcaps sous la forme d’une séquence d’échappement ! On peut par exemple récupérer le termcap « cl » (pour clean) qui permet de nettoyer (vider) un terminal.

	Exemple:
		char *cl_cap = tgetstr("cl", NULL);


//tgoto


//tputs
	int tputs(const char *str, int affcnt, int (*putc)(int));
		str: termcap a executer
		affcnt: nombre de lignes affectees
		putc: pointeur sur la fonction qui servira a afficher (putchar/printf)

	marche de pair avec tgetstr, c’est elle qui va se charger d’exécuter le termcap que l’on vient de récupérer.

	Exemple:
		char *cl_cap = tgetstr("cl", NULL);
		tputs (cl_cap, 1, putchar);
	






Termcap		Description
co			nombre de colonnes affichées à l’écran
li			nombre de lignes affichées à l’écran
AF			définit la couleur du texte
AB			définit la couleur de fond
md			affiche le texte en « gras »
us			affiche le texte en « souligné »
mb			affiche le texte en « clignotant »
cm			déplace le curseur aux coordonnées souhaitées
cl			efface le texte affiché à l’écran
me			annule tous les changements opérés
os			over strike, précise si le terminal efface ou non le contenu lors d’une réécriture par dessus du texte (par exemple à la suite d’un backspace)
