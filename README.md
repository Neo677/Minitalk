Minitalk 
Minitalk est un project de ecole 42 qui consiste a cree un programme de communication entre un serveur et un client en utlisant des signaux UNIX. Le client envoie un message au serveur qui est cense l'afficher.

Fonctionnalités 
communications entre un serveur et un client via les signaux UNIX (SIGUSR1 et SIGUSR2), transmission de chaine de caracteres du client au serveur.
Gestions des erreur pour les signaux non reçus ou les mauvais arguments.
Affichage des messages reçus par le serveur.

Fichier du projet 
  server.c : Contient le code du serveur, qui attend les signaux du client et affiche les messages reçus.
  client.c : Contient le code du client, qui envoie un message caractère par caractère au serveur.
  minitalk.h : Fichier d’en-tête contenant les prototypes des fonctions et les inclusions nécessaires.
  Makefile : Automatisation de la compilation avec des règles pour all, clean, fclean et re.

Utilisation 
 A) Compilation
Pour compiler le projet, utilisez la commande suivante :
		make
Cela génère les exécutables server et client.

 B) Lancement du serveur
Lancez le serveur pour obtenir son PID (Process ID) :
			./server
Le serveur affiche son PID dans le terminal. Notez-le pour le client.

 C) Envoi d’un message avec le client
Utilisez le PID du serveur pour envoyer un message :
			'''./client <PID_SERVER> "Votre message ici" '''
Exemple :
			./client 12345 "Bonjour server, ça va ? ..."

Rules :

Norme

Le projet respecte les règles suivantes :
  
  Code conforme à la Norme de l’école 42.
  
  Pas de variables globales.
  
  Gestion propre de la mémoire et des erreurs.

Signaux Utilisés
  
  SIGUSR1 : Utilisé pour transmettre un bit de valeur 0.
  
  SIGUSR2 : Utilisé pour transmettre un bit de valeur 1.



Rules of the Makefile :

make : Compile le projet et génère server et client.

make clean : Supprime les fichiers objets.

make fclean : Supprime les fichiers objets et les exécutables.

make re : Réexécute un nettoyage complet suivi d’une recompilation.


Exemple D'utilisation :
  Demarage du server :
			./server

  Sortie du server :
			PID = 12345

  Send the message:
			./client 12345 "Hello My friend welcome to my world ..."

  Sortie du server :
			Message reçu : "Hello My friend welcome to my world ..."
	
Limitations
  Le serveur ne gère qu’un client a la fois.
  En cas de mauvais PID ou d’interruption des signaux, le message peut ne pas etre reçu correctement.


Crédits :

Projet réalisé dans le cadre de l’école 42.

N’hésitez pas à me dire si vous souhaitez ajouter d’autres sections ou modifier certains points !