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

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//signal
		Permet au processus apellant la fonction signal de recevoir un signal d'un autre processus.

		sighandler_t	signal(int signum, sighandler_t handler);
	
		signum  : le signal ressus.
		handler : SIG_IGN -> le signal est ignoré.
				  SIG_DFL -> l'action par défaut associé au signal est entreprise.
				  handler -> configuration à SIG_DFL puis la fonction handler est apellé
				  			 avec signum en argument.
				  Les signaux SIGKILL et SIGSTOP ne peuvent être ni ignorés, ni interceptés.
		EXEMPLE:
					void	get_bin(int sig)
					{
					}
	
					int	main(void)
					{
						signal(SIGINT, get_bin);  ->  Une fois le signal SIGINT intercepté par
					}								  la fonction singal, signal va apeller la
													  fonction get_bin en lui passant en argument
													  SIGINT.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//sigaction
		L'appel système sigaction() sert à modifier laction effectuée par un processus
		à la réception d'un signal spécifique.
	
		int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	
		signum	: signal concerné, à l'exception de SIGKILL et SIGSTOP.
		act		: si non nul, défini la nouvelle action pour le signal signum.
		oldact	: si non nul, sauvegarde l'ancienne action dans oldact.
	
		struct sigaction 
		{
	    	void     (*sa_handler) (int);
	    	void     (*sa_sigaction) (int, siginfo_t *, void *);
	    	sigset_t   sa_mask;
	    	int        sa_flags;
	    	void     (*sa_restorer) (void);
		};

		RETOUR ERREUR : 0 -> reussite.
					   -1 -> erreur.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//sigemptyset
		sigemptyset() vide l'ensemble de signaux fourni par set,
		tous les signaux étant exclus de cet ensemble.
	
		int sigemptyset(sigset_t *set);

		RETOUR ERREUR : 0 -> si signum n'est pas un membre de set.
						1 -> si signum est un membre de set.
					   -1 -> erreur.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//sigaddset
		La fonction sigaddset () ajoute le signal individuel spécifié par 
    	signo à l'ensemble de signaux pointé par set.

		int sigaddset(sigset_t * set , int signo );

		RETOUR ERREUR : 0 -> reussite.
					   -1 -> erreur.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//kill
		L'appel système kill() permet un envoie de signal
		à un processus ou un groupe de processus.

		int kill(pid_t pid, int sig);

		pid	: pid du processus destinataire,  si > 0  -> envoie du signal au processus
											  si = 1  -> envoie du signal à tous les processus
											  			 appartenant au même groupe que le processus
														 appelant.
											  si = -1 -> le signal sig est envoyé à tous les
											  			 processus pour lesquels le processus
														 appelant à la permission d'envoyer des
														 signaux, sauf celui de PID 1 (init).
											 si < -1  -> le signal sig est envoyé à tous les
											 			 processus du groupe dont l'identifiant
														 est -pid.

		sig	: signal à envoyer, si = 0 -> aucun signal n'est envoyé mais
										  les conditions d'erreur sont 
										  vérifiées.

		EXEMPLE:
					kill(33568, SIGUSR1);  	Envoie le signal SIGUSR1 au processus
											possédant le pid 33568.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//opendir
	DIR *opendir(const char *name);
		name: repertoire a ouvrir

	ouvre un flux répertoire correspondant au répertoire name, et renvoie un pointeur sur ce flux. Le flux est positionné sur la première entrée du répertoire.

	Valeur_de_retour_ou_cas_d_erreur:
		pointeur sur le flux de repertoire en cas de REUSSITE
		NULL en cas d'ECHEC

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//readdir
	struct dirent *readdir(DIR *dir);

	renvoie un pointeur sur une structure dirent représentant l'entrée suivante du flux répertoire pointé par dir

	Valeur_de_retour_ou_cas_d_erreur:
	pointeur sur une structure dirent REUSSITE
	NULL ECHEC

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//closedir


//strerror


//perror

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//isatty
	int isatty(int desc);

	renvoie 1 si desc est un descripteur de fichier ouvert connecté à un terminal, ou 0 autrement.  

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//tyname


//ttyslot


//ioctl

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//getenv
	char	*getenv(const char *name);
		name: env
	
	renvoie un pointeur sur la variable d'environnement passee en parametre

	Exemple:
		printf("%s\n", getenv("USER"));

	output:
		USER=kbrousse

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//tcsetattr


//tcgetattr


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//tgetflag
	int tgetflag(char *id);
		id: ce que l'on souhaite recuperer

	fonctionne de la même manière que tgetnum à la différence prêt qu’il renvoie un booléen au lieu d’une valeur. Cette fonction est utilisée pour vérifier les capacités d’un terminal, savoir s’il est capable de faire tel ou tel action.

	Exemple:
		if (tgetflag("os") != 0)
		{
			code
		}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//tgetnum
	int tgetnum(char *id);
		id: ce que l'on souhaite recuperer

	permet de récupérer des informations numériques en rapport avec votre terminal.
Comme par exemple le nombre de lignes et de colonnes.

	Exemple:
		int column_count = tgetnum("co");
		int line_count = tgetnum("li");

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//tgetstr
	char *tgetstr(char *id, char **area);
		id: termcap a executer
		area: adresse du buffer donne a tgetent
		
	permet de récupérer les fameux termcaps sous la forme d’une séquence d’échappement ! On peut par exemple récupérer le termcap « cl » (pour clean) qui permet de nettoyer (vider) un terminal.

	Exemple:
		char *cl_cap = tgetstr("cl", NULL);

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//tgoto

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//tputs
	int tputs(const char *str, int affcnt, int (*putc)(int));
		str: termcap a executer
		affcnt: nombre de lignes affectees
		putc: pointeur sur la fonction qui servira a afficher (putchar/printf)

	marche de pair avec tgetstr, c’est elle qui va se charger d’exécuter le termcap que l’on vient de récupérer.

	Exemple:
		char *cl_cap = tgetstr("cl", NULL);
		tputs (cl_cap, 1, putchar);
	
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------






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
