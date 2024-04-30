#include "cuthil.hpp" // Inclut le fichier d'en-tête contenant les déclarations de classe
#include <iostream> // Inclut le fichier d'en-tête pour les opérations d'entrée/sortie
#include <fstream> // Inclut le fichier d'en-tête pour les opérations de flux de fichiers
#include <cmath> // Inclut le fichier d'en-tête pour les fonctions mathématiques
#include <vector> // Inclut le fichier d'en-tête pour les conteneurs de vecteurs
#include <string> // Inclut le fichier d'en-tête pour les opérations sur les chaînes de caractères

Excentricite::Excentricite(string filename){
    // Ouvrir le fichier
    ifstream fichier(filename.c_str());

    // Lecture de la dimension
    fichier >> dim;

    // Allocation dynamique de la matrice A et du vecteur b
    A = new float*[dim];
    b = new float[dim];
    sommet_1 = new int[dim];
    sommet_2 = new int[dim];
    for (int i = 0; i < dim; ++i){
        A[i] = new float[dim];
        sommet_1[i] = 0;
        sommet_2[i] = 0;
    }

    // Lecture de la matrice et du vecteur b dans le fichier
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            fichier >> A[i][j];
        }
    }

    for (int i = 0; i < dim; ++i){
        fichier >> b[i];
    }

    fichier.close(); // Fermeture du fichier
}

Excentricite::~Excentricite(){
    // Destructeur pour libérer la mémoire
    delete[] sommet_1;
    delete[] sommet_2;
    for (int i = 0; i < dim; ++i) {
        delete[] A[i];
    }
    delete[] A;
    delete[] b;
    cout << "Mémoire libérée. Merci d'avoir utilisé ce programme ! " << endl;
}

// Affichage de la dimension de la matrice
void Excentricite::display_dim() {
    cout << "Dimension de la matrice : " << dim << "\n" << endl;
}

// Affichage de la matrice A
void Excentricite::display_A() {
    cout << "Matrice A :" << endl;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    for(int i=0 ; i<dim; i++) cout<<"b["<<i<<"] = "<<b[i]<<"\t" ;
    cout << endl;
}

// Calcul de l'excentricité et stockage des éléments de chaque niveau de num dans v
int Excentricite::cal_excentricite(int num, vector<vector<int> >& v){
    v.push_back(vector<int>(1, num));
    vector<bool> mark(dim, false);
    mark[num] = true;
    int k(0);
    while (true) {
        // Niveau suivant
        vector<int> tmp;
        // Itérer sur chaque élément du niveau
        for (int i(0); i < v[k].size(); i++) {
            // Trouver les voisins du nœud
            for (int j=0; j < dim; j++) {
                if (A[j][v[k][i]] == 0) continue;
                if (mark[j]) continue;
                tmp.push_back(j);
                mark[j] = true;
            }
        }
        if (tmp.size() == 0) break;
        v.push_back(tmp);
        tmp.clear();
        k++;
    }
    return v.size() - 1;
}

// Calcul du premier sommet de la matrice
void Excentricite::cal_premier_sommet(){
    int n(0), s(0);
    int k(0);
    sommet_1[0] = 0;
    while(true){
        n = cal_excentricite(sommet_1[0], v_n); 
        s = cal_excentricite(v_n[n][k], v_s);
        if(s > n){
            sommet_1[0] = v_n[n][k];
            v_n.clear();
            v_s.clear();
            k = 0;
        } else k++;
        if (v_n[n].size() == k) break;
    }
    cout << endl;
    cout << "Excentricité maximum : " << s << endl;
    cout << "Premier Sommet[0] : " << sommet_1[0] + 1 << endl;
    cout << endl;
}

// Calcul de l'ordre du reste des sommets
void Excentricite::cuthil(){
    cout << "Les voisins de chaque élément du niveau en partant du premier sommet_1 : " << endl;
    int s(0);
    for(int i=0; i<v_n.size(); i++){
        vector<int> tmp_0;
        vector<int> tmp_1;

        // Calcul du nombre de voisins des éléments du niveau
        for(int j=0; j<v_n[i].size(); j++){
            cout << v_n[i][j] << " --> ";
            for(int k=0; k<dim; k++) {
                if (A[k][v_n[i][j]] == 0) continue;
                cout << A[k][v_n[i][j]] << ", ";
                tmp_0.push_back(A[k][v_n[i][j]]);
            }
            tmp_1.push_back(tmp_0.size());
            cout << "( " << tmp_0.size() << ")";
            tmp_0.clear();
            cout << "\t";
        }

        // Tri des éléments de chaque niveau par ordre croissant
        for(int j=0; j<v_n[i].size(); j++){
            for(int k=j; k<v_n[i].size(); k++) {
                if(tmp_1[j] > tmp_1[k]) {
                    int tmp_a(0);
                    tmp_a = tmp_1[j];
                    tmp_1[j] = tmp_1[k];
                    tmp_1[k] = tmp_a;
                    tmp_a = v_n[i][j];
                    v_n[i][j] = v_n[i][k];
                    v_n[i][k] = tmp_a;
                }
            }
        }

        // Enregistrement des numéros de sommet
        for(int j=0; j<v_n[i].size(); j++){
            sommet_1[s] = v_n[i][j];
            s++;
            for(int k=0; k<dim; k++) {
                if (A[k][v_n[i][j]] == 0) continue;
                tmp_0.push_back(A[k][v_n[i][j]]);
            }
            tmp_1.push_back(tmp_0.size());
            tmp_0.clear();
            tmp_1.clear();
        }
        cout << endl;
    }
    cout << endl;
    cout << "L'ordre du Sommet : " << endl;
    for(int i=0; i<dim; i++) cout << "Sommet [" << i << "] = " << sommet_1[i] << endl;
}

// Inversion de l'ordre des sommets
void Excentricite::cuthil_inverse(){
    for(int i=0; i<dim; i++){
        sommet_2[i] = dim - 1 - sommet_1[i];
    }
    cout << endl;
    cout << "L'ordre du Sommet après inversion : " << endl;
    for(int i=0; i<dim; i++) cout << "Sommet [" << i << "] = " << sommet_2[i] << endl;
}

// Permutation de la matrice en utilisant le rangement des sommets sans inversion
void Excentricite::permutation(){
    cout << endl;
    cout << "Permutation sans inversion \n";

    float **B;
    float *c;

    B = new float*[dim];
    c = new float[dim];

    for (int i = 0; i < dim; ++i){
        B[i] = new float[dim];
        c[i] = 0;
    }

    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            B[i][j] = 0;
        }
    }

    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            B[j][i] = A[j][sommet_1[i]];
        }
        c[i] = b[sommet_1[i]];
    }
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            A[i][j] = B[sommet_1[i]][j];
        }
        b[i] = c[i];     
    }
}

// Permutation de la matrice en utilisant le rangement des sommets avec inversion de la matrice
void Excentricite::permutation_avec_inversion(){
    cout << endl;
    cout << "Permutation avec inversion \n";

    float **B;
    float *c;

    B = new float*[dim];
    c = new float[dim];

    for (int i = 0; i < dim; ++i){
        B[i] = new float[dim];
        c[i] = 0;
    }

    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            B[i][j] = 0;
        }
    }

    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            B[j][i] = A[j][sommet_2[i]];
        }
        c[i] = b[sommet_2[i]];
    }
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            A[i][j] = B[sommet_2[i]][j];
        }
        b[i] = c[i];     
    }
}

// Obtenir la réponse de l'utilisateur pour l'inversion de la permutation
bool Excentricite::get_resp(){
    return response;
}

// Définir la réponse de l'utilisateur pour l'inversion de la permutation
void Excentricite::set_resp(){
    string f;
    cout << "\nVoulez-vous la matrice avec permutation inverse ou non ? (Oui / Non)";
    cin >> f;
    if(f == "Oui") response = false;
    else response = true;
}

// Enregistrement de la nouvelle matrice A et de b correspondante dans un fichier
void Excentricite::enregistrement(string nomFichier){
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
        for(int i=0; i<dim; i++){
            fichier << b[i] << endl;
        }
        for(int i=0; i<dim; i++){
            if(response) fichier << sommet_1[i] << endl;
            else fichier << sommet_2[i] << endl;
        }
        cout << "Matrice enregistrée avec succès dans " << nomFichier << endl;
        fichier.close();
    } else {
        cerr << "Impossible d'ouvrir le fichier " << nomFichier << endl;
    }
}
