Projet : 
Problème de tournées de véhicule (VRP) avec contraintes de capacité

Environnement : 
Damier constitué d'obstacles, de clients et de la base du robot.
Robot avec une capacité, clients avec une demande.
La demande du client doit être prise entièrement, le partiellement n'est pas autorisé.


Organisation du problème :
Un fichier texte regroupe toutes les informations du problème
Le programme lit le fichier.txt

Le calcul des distances entre éléments (clients et la base du robot) est fait via l'algorithme de Dijkstra

L'ordonnancement des tournées se fait via un algorithme Glouton de proche en proche.

La solution est affiché sur la console ainsi que stockée dans un fichier txt "solution.txt"

Cadre/limite du travail réalisé :
Il faut respecter la formulation du problème dans le fichier txt à lire, comme ci-dessous :
//plateau
tailleX tailleY
//Robot
positionX positionY capacite
//Clients
nombreDeClients
positionX positionY demande //Client1
positionX positionY demande //Client2
...
positionX positionY demande //Clienti
//Obstacles
nombreObstacles
positionX positionY largeur longueur //Obstacle1
positionX positionY largeur longueur //Obstacle2
...
positionX positionY largeur longueur //Obstaclei


Il faut obligatoirement mettre des obstacles, le programme ne tourne pas sans.

Le chemin d'accès du fichier à lire ou écrire est défini dans le main.