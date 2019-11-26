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

bool is_vector_give_no_cycle(Edge ed, string vect){
    return
    ( ed.v1 == vect && ed.v2 != vect ) ||
    ( ed.v2 == vect && ed.v1 != vect );
}

bool push_to_vertex_selected(Edge ed, vector<string> &vertex_selected, int selected_idx){
    if( vertex_selected[selected_idx] != ed.v1 )
        vertex_selected.push_back( ed.v1 );
    else
        vertex_selected.push_back( ed.v2 );
}

void output_prim_result(vector<Edge> prim_result){
    int jumlah = 0;
    for(int i=0; i<prim_result.size(); i++){
        cout << "[" << prim_result[i].v1 << "," <<  prim_result[i].v2 << "]=" << prim_result[i].bobot << ", ";
        jumlah += prim_result[i].bobot;
    }
    cout << endl << "| total=" << jumlah << endl << endl;
}

int main()
{
    /// Deklarasi awal
    vector<Edge> T;
    vector<Edge> prim_result;
    vector<string> vertex_selected;
    int jumlah_vertex;

    vector<string> list_vertex;

    /** start: untuk membaca file .txt, gak usah dipikir */
    std::ifstream file("input.txt");
    std::string str;
    int first = 2;
    while (std::getline(file, str)) {
        istringstream csvStream(str);
        Edge ins;
        string stri;
        int co = 1;
        while( getline(csvStream, stri, ',') ){
            if(first==2){
                stringstream strtoints(stri);
                if( co==2 ) strtoints >> jumlah_vertex;
            }else if(first==1){
                list_vertex.push_back( stri );
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
        if(first==0) T.push_back(ins);
        else first--;
    }
    /** end: untuk membaca file .txt, gak usah dipikir */

    cout << "List Edge :" << endl;
    for(int i=0; i<T.size(); i++){
        cout << T[i].v1 << " " <<  T[i].v2 << " " << T[i].bobot << endl;
    }

    cout << " - - - " << endl;

    /** Start Algoritma Prim */

    /// Insert Vertex yg ditentukan
    string firstVertex = "C";
    vertex_selected.push_back( firstVertex );

    /// Loop sebanyak jumlah_vertex - 1
    for(int o=0; o<jumlah_vertex-1; o++){
        int decide_to_insert = 0;
        int check_vertex_idx = -1;
        int bobot = 999;
        Edge insert_edge;

        /// Loop untuk mencari edge
        for(int i=0; i<T.size(); i++){
            int selected = 0;
            int selected_idx = -1;

            /// Loop untuk mengecek vector yg sudah masuk dalam spanning tree
            for(int j=0; j<vertex_selected.size(); j++){
                if( is_vector_give_no_cycle(T[i], vertex_selected[j]) ){
                    selected++;
                    selected_idx = j;
                }
            }

            /// Jika vector memenuhi kriteria, pilih bobot yg lebih kecil
            if( selected==1 && T[i].bobot<bobot ){
                bobot = T[i].bobot;
                insert_edge = T[i];
                check_vertex_idx = selected_idx;
                decide_to_insert = 1;
            }
        }
        /// masukkan edge ke prim_result
        if( decide_to_insert==1 ){
            push_to_vertex_selected( insert_edge, vertex_selected, check_vertex_idx );
            prim_result.push_back( insert_edge );
            output_prim_result( prim_result );
        }

    }

    /** End Algoritma Prim */

    cout << "Vektor yg dilewati : ";
    for(int i=0; i<vertex_selected.size(); i++){
        cout << vertex_selected[i] << ",";
    }

    cout << endl;
    return 0;
}
