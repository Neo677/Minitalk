Minitalk :

Minitalk est un project de ecole 42 qui consiste a cree un programme de communication entre un serveur et un client en utlisant des signaux UNIX. Le client envoie un message au serveur qui est cense l'afficher.

Fonctionnalités:
communications entre un serveur et un client via les signaux UNIX (SIGUSR1 et SIGUSR2), transmission de chaine de caracteres du client au serveur.
Gestions des erreur pour les signaux non reçus ou les mauvais arguments.
Affichage des messages reçus par le serveur.

Fichier du projet:
	  server.c : Contient le code du serveur, qui attend les signaux du client et affiche les messages reçus.
    client.c : Contient le code du client, qui envoie un message caractère par caractère au serveur.
	  minitalk.h : Fichier d’en-tête contenant les prototypes des fonctions et les inclusions nécessaires.
  	Makefile : Automatisation de la compilation avec des règles pour all, clean, fclean et re.

Utilisation
    1. Compilation
Pour compiler le projet, utilisez la commande suivante :
