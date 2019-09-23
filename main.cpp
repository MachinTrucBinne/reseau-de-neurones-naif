/*
Noé Aubin-Cadot.
Codé en juin 2017.
Déposé sur GitHub en septembre 2019.
C'est une simulation d'un réseau de neurones selon une matrice de probabilités qui évolue dans le temps.
*/
// Pour compiler :
// g++ -o main *.cpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>    // pour les probabilités
#include <cmath>     // pour sqrt et pow
#include <ctime>     // pour avoir l'heure
#include <iomanip>   // pour imprimer des nombres "double" selon la précision qu'on veut
#include "header.h"

int main()
{   
    // Pour les nombres aléatoires
    int nombreAleatoireInt;
    double nombreAleatoireDouble;
    double nombreAleatoireBool;
    srand (time(NULL));

    // Pour les itérations
    double t=0.0; // le temps en secondes
    double h=0.0001; // le pas temporel en secondes
    double tMax = 1000.0; // la durée maximale de la simulation en secondes

    // Pour l'affichage
    double DeltaTprintVect; // on imprime les données du vecteur à chaque Delta t secondes.
    double DeltaTprintMat; // on imprime les données de la matrice à chaque Delta t secondes.
    
    double typeAffichage = 0;
    // 0 : affichage vecteur
    // 1 : affichage matrice
    if (typeAffichage == 0)
    {
    	DeltaTprintVect = h;
    	DeltaTprintMat = tMax;
    }
    if (typeAffichage == 1)
    {
    	DeltaTprintVect = tMax;
    	DeltaTprintMat = h;
    }
    
    double NombreDiterations = 0; // nombre total d'itérations depuis le début
    double tPrintMat = 0; // compteur pour savoir quand on imprime la matrice
    double tPrintVect = 0; // compteur pour savoir quand on imprime le vecteur
    double DemieVieConnexionNeuronale = 5.0*60.0; // demi-vie d'une connexion neuronale en secondes (ici 5 minutes)
    double DemieVieMoyenneAutoActivation = 0.01; // demi-vie moyenne d'auto-activation d'un neurone en secondes (ici un dizième de secondes)
    double tauxDeDiminution = pow(0.5 , h/DemieVieConnexionNeuronale); // taux de diminution à chaque itération
    double probabiliteDautoInteraction = pow(0.5 , h/DemieVieMoyenneAutoActivation);
    double probabiliteMaxDinteraction = 0.99;
    double probabiliteMinDinteraction = 0.0001;

    int NombreDeNeuronesActives;
    int NombreDeNeuronesDesactives; // = N - NombreDeNeuronesDesactives

    int N = 100; // nombre de neurones total
    int Ninit = 0; // nombre de neurones actifs à t=0
    //int Ninit = (int)(N/4.0); // nombre de neurones actifs à t=0
    int Ninput = 1; // neurones toujours actifs (pour input d'information, ça sera dynamique plus tard)
    int M = N; // (juste pour dire que A est MxN et carrée)
    // On déclare le vecteur v booléen (chaque composante est un neurone : 0 = éteint, 1 = allumé)
    bool v[N]; // on déclare un vecteur de longueur N
    // On entre des valeurs booléennes alétoires en v
    for (int i=0;i<Ninit;i++){v[i]=1;}
    for (int i=Ninit;i<N;i++){v[i]=0;}
    printVecteurBool(v,N);
    // On entre des probabilités d'activations aléatoires en A
    // On déclare la matrice A qui représente la probabilité que le neurone i active le neurone j.
    double A[M*N]; // une matrice vue comme vecteur de longueur MxN
    for (int i=0;i<M;i++)
    {
    	for (int j=0;j<N;j++)
    	{
    		A[i+M*j] = fRand(0,1) * (2.0/M);
            if (i==j) // on met les termes diagonaux de A (i.e. les probabilités d'auto-interaction)
            {
                A[i+M*j] = probabiliteDautoInteraction;
            }
    	}
    }
	//printMatriceDouble(A,M,N);

    // Pour les données aléatoires :
    bool v_temp[N];
    double A_temp[M*N];

    std::cout<<"\nValeurs du vecteur neuronal booléen (1 ligne = 1 itération)";

    // On commence les itérations
    while (t<tMax)
    {
        NombreDeNeuronesActives = NombreDelementsNonNulsVecteurBool(v,N);
        NombreDeNeuronesDesactives = N - NombreDeNeuronesActives;
        // on réinitialise v_temps
        for (int j=0;j<N;j++) // pour mettre le vecteur neuronal d'arrivé à zéro
        {
            v_temp[j]=0;
        }
        // on peut brancher certaines zone sensorielles à 1
        for (int j=0;j<Ninput;j++)
        {
            v_temp[j]=1;
        }
        // puis on regarde les interactions
        for (int j=0;j<N;j++) // on prend un neurone d'arrivé j
        {
            for (int i=0;i<M;i++) // on regarde si le neurone de départ i allume le neurone d'arrivé j
            {
                if ((v[i] ==1) && (boolAleatoireSelonProbabiliteEntre0et1(A[i+M*j]) == 1)) // si le neurone est allumé et s'il y a interaction
                {
                    v_temp[j]=1; // on allume le prochain neurone
                    //A_temp[i+M*j] = sqrt(A[i+M*j]);
                    A_temp[i+M*j] = pow(A[i+M*j],0.001);
                    // on met un plafond maximal sur la probabilité d'interaction
                    if(A_temp[i+M*j] > (probabiliteMaxDinteraction))
                    {
                        A_temp[i+M*j] = probabiliteMaxDinteraction;
                    }                    
                }
                else
                {
                    A_temp[i+M*j] = A[i+M*j]*tauxDeDiminution*(NombreDeNeuronesDesactives/N);
                    // A_temp[i+M*j] = pow(A[i+M*j],2);
                    // on met un plancher minimal sur la probabilité d'interaction
                    if(A_temp[i+M*j] < probabiliteMinDinteraction)
                    {
                        A_temp[i+M*j] = probabiliteMinDinteraction;
                    }
                }
                if (i==j)
                {
                    A_temp[i+M*j] = probabiliteDautoInteraction;
                }
            }
        }
        // puis on copie les nouvelles données
        for (int i=0;i<M;i++)
        {
            v[i] = v_temp[i];
            for (int j=0;j<N;j++)
            {
                A[i+M*j] = A_temp[i+M*j];
            }
        }    
        NombreDiterations = NombreDiterations + 1; // on incrémente le nombre total d'itérations
        t=t+h; // on incrémente le temps.
        tPrintVect = tPrintVect + h;
        tPrintMat = tPrintMat + h;
        if (tPrintVect > DeltaTprintVect)
        {
            tPrintVect = 0;
            //printVecteurBool(v,N);
            printVecteurBoolJusteLesUn(v,N);
        }
        if (tPrintMat > DeltaTprintMat)
        {
            tPrintMat = 0;
            bool Abool[M*N];
            for (int i=0;i<M;i++)
            {
                for (int j=0;j<N;j++)
                {
                    if (A[i+M*j]>0.5)
                    {
                        Abool[i+M*j]=1;
                    }
                    else
                    {
                        Abool[i+M*j]=0;
                    }
                }
            }
            //std::cout<<"\n Représentation booléenne de la matrice A :";
            printMatriceBoolJusteLesUn(Abool,M,N);
            //printMatriceBool(Abool,M,N);
        }
    }
	std::cout<<"\n\n";
    return 0;
}