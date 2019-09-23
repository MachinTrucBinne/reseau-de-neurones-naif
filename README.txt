2019-09-21

		☍ RÉSEAU DE NEURONES NAIF ☍

######################################################################
######################################################################

		DESCRIPTION

Ce code simule un réseau de neurones (RDN) naïf.

On considère un ensemble de N neurones.
Chaque neurone est dans un état binaire activé/désactivé.
Cet ensemble d'états de neurones est décrit par une chaîne binaire de longueur N.

L'évolution du réseau de neurone se fait par itérations.
L'état du RDN à l'itération suivante ne dépend que de son état à l'itération qui précède et non de ses états antérieurs.

L'évolution du RDN à chaque itération est aléatoire selon une matrice de probabilités de taille N×N.
La probabilité que le neurone activé i active le neurone j est la composante (i,j) de la matrice de probabilités.

La matrice de probabilités évolue dans le temps.
Plus le neurone i active souvent le neurone j, plus la probabilité qu'une telle activation se reproduise augmente.
À l'inverse, moins le neurone i active le neurone j, plus faible sera la probabilité que le neurone i active le neurone j.

Il y a un plancher non nul sur la probabilité que le neurone i active le neurone j.

La durée d'activation d'un neurone dépend de sa demi-vie.
La probabilité d'auto-interaction d'un neurone est dans les termes diagonaux (i,i) de la matrice de probabilités.

L'évolution temporelle de la matrice de probabilités dépend de plusieurs paramètres.
C'est le problèmes du fine-tuning.
À terme il faudrait faire une sélection naturelle sur les RDN et sur leurs paramètres.

Codé en juin 2017.
Déposé sur GitHub en septembre 2019.

######################################################################
######################################################################

		COMPILATION

g++ -o main *.cpp

######################################################################
######################################################################

Noé Aubin-Cadot, 2019.