#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdbool.h>
#include <bits/stdc++.h>

using namespace std;

struct Edge{
    string v1;
    string v2;
    int bobot;
};

bool compareBobot(Edge a, Edge b){
    return a.bobot < b.bobot;
}

int main()
{
    /// Deklarasi awal
    vector<Edge> T;
    vector<Edge> prim_result;
    vector<string> vector_selected;
    int jumlah_vektor;

    /** start: untuk membaca file .txt, gak usah dipikir */
    std::ifstream file("input.txt");
    std::string str;
    int first = 1;
    while (std::getline(file, str)) {
        istringstream csvStream(str);
        Edge ins;
        string stri;
        int co = 1;
        while( getline(csvStream, stri, ',') ){
            if(first==1){
                stringstream strtoints(stri);
                if( co==2 ) strtoints >> jumlah_vektor;
            }else{
                if( co==1 ) ins.v1 = stri;
                if( co==2 ) ins.v2 = stri;
                if( co==3 ){
                    stringstream strtoint(stri);
                    int val;
                    strtoint >> val;
                    ins.bobot = val;
                }
            }
            co++;
        }
        if(first!=1) T.push_back(ins);
        else first=0;
    }
    /** end: untuk membaca file .txt, gak usah dipikir */

    /// Ascending Sort
    sort(T.begin(), T.end(), compareBobot);
    for(int i=0; i<T.size(); i++){
        cout << T[i].v1 << " " <<  T[i].v2 << " " << T[i].bobot << endl;
    }

    cout << " - - - " << endl;

    /** Start Algoritma Prim */

    /// Insert Edge Terkecil
    prim_result.push_back( T[0] );
    vector_selected.push_back( T[0].v1 );
    vector_selected.push_back( T[0].v2 );

    /// Loop sebanyak jumlah_vektor - 2
    for(int o=0; o<jumlah_vektor-2; o++){
        int selected_vector_edge = -1;
        int decide_to_insert = 0;
        Edge selected_edge;

        /// Loop untuk mencari edge
        for(int i=0; i<T.size(); i++){
            int selected = 0;
            int selected_idx = -1;

            /// Dua Loop untuk mengecek vector yg sudah masuk dalam spanning tree
            for(int j=0; j<vector_selected.size(); j++){
                if( T[i].v1 == vector_selected[j] ){
                    selected++;
                    selected_idx = j;
                    break;
                }
            }
            for(int j=0; j<vector_selected.size(); j++){
                if( T[i].v2 == vector_selected[j] ){
                    selected++;
                    selected_idx = j;
                    break;
                }
            }

            /// Jika vector memenuhi kriteria
            if( selected==1 ){
                if( vector_selected[selected_idx] != T[i].v1 )
                    vector_selected.push_back( T[i].v1 );
                else
                    vector_selected.push_back( T[i].v2 );

                prim_result.push_back(T[i]);
                break;
                /** langsung break loop karena sebelumnya T sudah diurutkan,
                  * jadi yg paling pertama ditemukan pasti yg terkecil
                  */
            }
        }

    }

    /** End Algoritma Prim */

    int jumlah_min_bobot = 0;
    for(int i=0; i<prim_result.size(); i++){
        cout << prim_result[i].v1 << " " <<  prim_result[i].v2 << " " << prim_result[i].bobot << endl;
        jumlah_min_bobot += prim_result[i].bobot;
    }
    cout << "Minimal Bobot Spanning Tree : " << jumlah_min_bobot << endl;

    cout << "Vektor yg dilewati : ";
    for(int i=0; i<vector_selected.size(); i++){
        cout << vector_selected[i] << ",";
    }

    cout << endl;
    return 0;
}
