#include"cuthil.hpp"
#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<string>


Excentricite::Excentricite(string filename){
    // ouvrir le fichier
    ifstream fichier(filename.c_str());

    // lecture de la dimension
    fichier >> dim;

    // allocation dynamique de la matrice A
    A = new float*[dim];
    b = new float[dim];
    sommet_1 = new int[dim] ;
    sommet_2 = new int[dim] ;
    for (int i = 0; i < dim; ++i){
        A[i] = new float[dim] ;
        sommet_1[i]=0 ;
        sommet_2[i]=0 ;
    }

    // lecture de la matrice dans le fichier
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            fichier >> A[i][j];
        }
    }

    for (int i = 0 ; i<dim ; i++ ){
        fichier >>b[i] ;
    }

    fichier.close(); // fermeture de fichier
}

Excentricite :: ~Excentricite(){
    //Destructeur
    delete[] sommet_1;
    delete[] sommet_2;
    for (int i = 0; i < dim; ++i) {
        delete[] A[i];
    }
    delete[] A;
    delete[] b;
    cout<<"Memoire libere. Merci d'avoir utiliser ce programme ! "<<endl ;
}

// affichage de la dimension
void Excentricite::display_dim() {
    cout << "Dimension de la matrice : " << dim << "\n" << endl;
}

// affichage de la matrice 
void Excentricite::display_A() {
    cout << "Matrix A :" << endl;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    for(int i=0 ; i<dim; i++) cout<<"b["<<i<<"] = "<<b[i]<<"\t" ;
    cout << endl;
}

//Calcul Excentricite et stoquage des element de chaque niveaude num dans v.
int Excentricite::cal_excentricite( int num , vector <vector<int> >& v ){
    v.push_back(vector<int>(1,num));
    vector<bool> mark(dim,false);
    mark[num] = true;
    int k(0);
    while (true) {
        // Niveau suivant
        vector<int> tmp;
        // Itérer élement du niveau
        for (int i(0); i < v[k].size(); i++) {
            // Trouver voisins du noeud
            for (int j=0 ; j < dim; j++) {
                if (A[j][v[k][i]] == 0) continue;
                if (mark[j]) continue;
                tmp.push_back(j);
                mark[j] = true;
            }
        }
        if (tmp.size() == 0) break;
        v.push_back(tmp);
        tmp.clear() ;
        k++;
    }
    return v.size() -1;
}

//Calcul du premier sommet de la matrice
void Excentricite::cal_premier_sommet(){
    int n(0) , s(0) ;
    int k(0) ;
    sommet_1[0] = 0;
    while(true){
        n = cal_excentricite( sommet_1[0] , v_n ) ; 
        s = cal_excentricite( v_n[n][k], v_s ) ;
        if( s > n){
            sommet_1[0] = v_n[n][k] ;
            v_n.clear() ;
            v_s.clear() ;
            k = 0 ;
        } else k++ ;
        if (v_n[n].size() == k) break ;
    }
    cout << endl;
    cout<<"Excentricite maximum : "<<s<<endl ;
    cout<<"Preimer Sommet[0] : "<<sommet_1[0]+1<<endl ;
    cout << endl;
}

//Caclul l'ordre du reste du sommet
void Excentricite::cuthil(){
    cout<<"Les voisins de chaque element du niveaux en partant du premier sommet_1 : "<<endl;
    int s(0) ;
    for(int i=0; i<v_n.size() ; i++){
        vector <int> tmp_0 ;
        vector <int> tmp_1 ;

        //Caclul le nombre de voisin des elements du niveau
        for( int j=0 ; j<v_n[i].size() ; j++){
            cout<<v_n[i][j]<<" --> " ;
            for( int k=0 ; k<dim ; k++) {
                if (A[k][v_n[i][j]] == 0) continue;
                cout<<A[k][v_n[i][j]]<<", " ;
                tmp_0.push_back(A[k][v_n[i][j]]) ;
            }
            tmp_1.push_back(tmp_0.size()) ;
            cout<<"( "<<tmp_0.size()<<")" ;
            tmp_0.clear();
            cout<<"\t" ;
        }

        //Arrangement par ordre croissante des elements de chaque niveaux
        for( int j=0 ; j<v_n[i].size() ; j++){
            for( int k=j ; k<v_n[i].size() ; k++) {
                if(tmp_1[j]>tmp_1[k]) {
                    int tmp_a(0) ;
                    tmp_a = tmp_1[j] ;
                    tmp_1[j] = tmp_1[k] ;
                    tmp_1[k] = tmp_a ;
                    tmp_a = v_n[i][j] ;
                    v_n[i][j] = v_n[i][k] ;
                    v_n[i][k] = tmp_a ;
                }
            }        
        }

        //Enregistrement des numeros du sommet
        for( int j=0 ; j<v_n[i].size() ; j++){
            sommet_1[s]=v_n[i][j] ;
            s++ ;
            for( int k=0 ; k<dim ; k++) {
                if (A[k][v_n[i][j]] == 0) continue;
                tmp_0.push_back(A[k][v_n[i][j]]) ;
            }
            tmp_1.push_back(tmp_0.size()) ;
            tmp_0.clear();
            tmp_1.clear();
        }
        cout<<endl ;
    }
    cout<<endl ;
    cout<<"L'order du Sommet : "<<endl ;
    for(int i=0 ; i<dim ; i++) cout<<"Sommet ["<<i<<"] = "<<sommet_1[i]<<endl;
}

//Inverstion de l'ordre du sommet
void Excentricite :: cuthil_inverse(){
    for(int i=0 ; i<dim ; i++){
        sommet_2[i] = dim - 1 - sommet_1[i] ;
    }
    cout<<endl ;
    cout<<"L'order du Sommet apres inversion : "<<endl ;
    for(int i=0 ; i<dim ; i++) cout<<"Sommet ["<<i<<"] = "<<sommet_2[i]<<endl;
}

//Permutation de la matrice en utilisant la rangement du sommet sans inversion
void Excentricite:: permutation(){
    cout<<endl ;
    cout<<"Permutation sans inversion \n" ;

    float **B ;
    float *c;

    B = new float*[dim] ;
    c = new float[dim] ;

    for (int i = 0; i < dim; ++i){
        B[i] = new float[dim] ;
        c[i] = 0 ;
    }


    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            B[i][j] = 0 ;
        }
    }


    for(int i=0 ; i<dim ; i++){
        for(int j=0 ; j<dim ; j++){
            B[j][i] = A[j][sommet_1[i]] ;
        }
        c[i]=b[sommet_1[i]] ;
    }
    for(int i=0 ; i<dim ; i++){
        for(int j=0 ; j<dim ; j++){
            A[i][j] = B[sommet_1[i]][j] ;
        }
        b[i]=c[i] ;     
    }
}

//Permutation de la matrice en utilisant la rangement du sommet avec inversion de la matrice
void Excentricite:: permutation_avec_inversion(){
    cout<<endl ;
    cout<<"Permutation avec inversion \n" ;

    float **B ;
    float *c;

    B = new float*[dim] ;
    c = new float[dim] ;

    for (int i = 0; i < dim; ++i){
        B[i] = new float[dim] ;
        c[i] = 0 ;
    }


    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            B[i][j] = 0 ;
        }
    }


    for(int i=0 ; i<dim ; i++){
        for(int j=0 ; j<dim ; j++){
            B[j][i] = A[j][sommet_2[i]] ;
        }
        c[i]=b[sommet_2[i]] ;
    }
    for(int i=0 ; i<dim ; i++){
        for(int j=0 ; j<dim ; j++){
            A[i][j] = B[sommet_2[i]][j] ;
        }
        b[i]=c[i] ;     
    }
}

bool Excentricite:: get_resp(){
    return response ;
}

void Excentricite:: set_resp(){
    string f ;
    cout<<"\nVouler vous la matrice avec permutation inverse ou non ? (Oui / Non)" ;
    cin>>f ;
    if(f=="Oui") response=false ;
    else response=true ;
}

//Sauvgarde la nouvelle matrice A et sans b correspondante
void Excentricite:: enregistrement(string nomFichier){
    ofstream fichier(nomFichier.c_str());
        if (fichier.is_open()) {
            // Écriture de la taille de la matrice dans le fichier
            fichier << dim << endl;
            // Écriture de chaque élément de la matrice dans le fichier
            for (int i = 0; i < dim; i++) {
                for (int j = 0; j < dim; ++j) {
                    fichier << A[i][j] << " ";
                }
                fichier << endl; // Nouvelle ligne pour chaque ligne de la matrice
            }
            for(int i=0 ; i<dim ; i++){
                fichier << b[i] <<endl ;
            }
            for(int i=0 ; i<dim ; i++){
                if(response) fichier << sommet_1[i] <<endl ;
                else fichier << sommet_2[i] <<endl ;

            }
            cout << "Matrice enregistree avec succes dans " << nomFichier << endl;
            fichier.close();
        } else {
            cerr << "Impossible d'ouvrir le fichier " << nomFichier <<endl;
        }
}

