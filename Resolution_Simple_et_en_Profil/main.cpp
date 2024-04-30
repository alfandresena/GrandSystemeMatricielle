#include"gsm_final.hpp"
#include<iostream>
#include <cstdlib> // pour la fonction system()

using namespace std ;

int main () {
    string rep ;
    cout<<"\nBIENVENUE\n\nCETTE PROGRAMME EST LA DEUXIEME PARTIE  DU PROGRAMME DESTINE A LA RESOLUTION D'UNE MATRICE CREUSE SIMTETRIE DEFINIE PROSITIF "<<endl ;
    cout<<"\nAvez-vous deja lance la premiere programme ? (Oui/Non) : ";
    cin>>rep ;
    if(rep != "Oui"){
        cout<<"\nVeillez le faire s'il vous plait ! Merci :-)"<< endl ;
        //system("cd ..") ;
        //system("cd Cuthil") ;
        //system("g++ -std=c++11 *.cpp -o Programme") ;
        //system("./Programme.exe") ;
        return 0 ;
    }

    cout<<"\n----------------CHARGEMENT DES DONNES----------------\n"<<endl ;
    Factorisation fact("./../Cuthil/new_data.txt");
    fact.affichage_de_la_Matrice();

    cout<<"\n~~~~~~~~PARTIE 1 : Resolution sans optimisation de memoire~~~~~~~~\n"<<endl ;

    cout<<"\n----------------TRAITEMENT DES DONNES----------------"<<endl ;
    fact.methode_factorisation_1();
    fact.methode_resolution_1();
    cout<<"                            ."<<endl;
    cout<<"                            ."<<endl;
    cout<<"                            ."<<endl;
    
    cout<<"\n--------------------LES RESULTATS--------------------\n"<<endl ;
    fact.afficheMat_L();
    fact.affiche_diag();
    fact.afficheResultat();



    cout<<"\n\n#######################################################"<<endl ;
    cout<<"#######################################################"<<endl ;
    cout<<"#######################################################\n\n"<<endl ;


    cout<<"\n\n~~~~~~~~PARTIE 2 : Resolution avec optimisation de memoire~~~~~~~~\n"<<endl ;
    cout<<"\n----------------TRAITEMENT DES DONNES EN PROFIL----------------"<<endl ;

    fact.rangement_en_profil();
    fact.methode_factorisation_profil_2() ;
    fact.methode_resolution_profil_2();
    cout<<"                               ."<<endl;
    cout<<"                               ."<<endl;
    cout<<"                               ."<<endl;

    cout<<"\n-------------------------LES RESULTATS--------------------\n"<<endl ;
    fact.afficheAP() ;
    fact.affiche_LP();
    fact.affiche_Pdiag();
    fact.afficheResultatP();
    fact.~Factorisation() ;

    return 0 ;
}