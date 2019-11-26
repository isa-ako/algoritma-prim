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

bool is_connected_to_edge(Edge ed, string vect){
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
    vector<Edge> Graph;
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
        if(first==0) Graph.push_back(ins);
        else first--;
    }
    /** end: untuk membaca file .txt, gak usah dipikir */

    cout << "List Edge :" << endl;
    for(int i=0; i<Graph.size(); i++){
        cout << Graph[i].v1 << " " <<  Graph[i].v2 << " " << Graph[i].bobot << endl;
    }

    cout << " - - - " << endl;

    string firstVertex;
    int input_not_allowed = 1;

    while( input_not_allowed ){
        cout << "Masukkan vertex yang ditentukan : ";
        cin >> firstVertex;
        for(int i=0; i<list_vertex.size(); i++){
            if( firstVertex == list_vertex[i] )
                input_not_allowed = 0;
        }
    }

    /** Start Algoritma Prim */

    /// Insert Vertex yg ditentukan
    vertex_selected.push_back( firstVertex );

    /// Loop sebanyak jumlah_vertex - 1
    for(int o=0; o<jumlah_vertex-1; o++){
        int decide_to_insert = 0;
        int check_vertex_idx = -1;
        int bobot = 999;
        Edge insert_edge;

        /// Loop untuk mencari edge
        for(int i=0; i<Graph.size(); i++){
            int connected = 0;
            int connected_idx = -1;

            /// Loop untuk mengecek vertex yg sudah masuk dalam spanning tree
            for(int j=0; j<vertex_selected.size(); j++){
                if( is_connected_to_edge(Graph[i], vertex_selected[j]) ){
                    connected++;
                    connected_idx = j;
                }
            }
            /// Jika vector memenuhi kriteria, pilih bobot yg lebih kecil
            if( connected==1 && Graph[i].bobot<bobot ){
                bobot = Graph[i].bobot;
                insert_edge = Graph[i];
                check_vertex_idx = connected_idx;
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

    cout << "Vertex yg dilewati : ";
    for(int i=0; i<vertex_selected.size(); i++){
        cout << vertex_selected[i] << ",";
    }

    cout << endl;
    return 0;
}
