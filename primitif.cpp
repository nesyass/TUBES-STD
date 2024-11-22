#include <iostream>
#include "header.h"
using namespace std;

void createListAplikasi(ListAplikasi &L){
    L.first = NULL;
};

address_aplikasi allocateAplikasi(infotype_aplikasi data){
    address_aplikasi P;
    P = new ElmAplikasi;
    P->info = data;
    P->next = NULL;
    P->relasi = NULL;
    return P;
};

void createListFilm(ListFilm &L){
    L.first = NULL;
    L.last = NULL;
};

address_film allocateFilm(infotype_film data){
    address_film P;
    P = new ElmFilm;
    P->info_film = data;
    P->next = NULL;
    P->prev = NULL;
    return P;
};

void insertAplikasi(ListAplikasi &L, address_aplikasi P){ //insert last//
    if (L.first == NULL){
        L.first = P;
    } else {
        address_aplikasi Q;
        Q = L.first;
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = P;
    }
};

void insertFilm(ListFilm &L, address_film P){ //insert last//
    if (L.first == NULL){
        L.first = P;
        L.last = P;
    } else {
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
};

void insertRelation(ListAplikasi &L_aplikasi, ListFilm &L_film, string nama_aplikasi, string nama_film){
    address_aplikasi A;
    A = findAplikasi(L_aplikasi, nama_aplikasi);

    address_film F;
    F = findFilm(L_film, nama_film);

    if (A != NULL && F != NULL){
        address_relasi R;
        R = A->relasi;
        while (R != NULL){
            if (R->film == F){
                cout << "Film sudah tersedia di aplikasi" << endl;
            } else {
                R = R->next;
            }
        }
        address_relasi newR;
        newR->next = A->relasi;
        A->relasi = newR;
        cout << "Film dengan judul " << nama_film << " berhasil di tambahkan ke aplikasi " << nama_aplikasi << endl;
    } else {
        if (A == NULL){
            cout << "Aplikasi dengan nama " << nama_aplikasi << " tidak ditemukan" << endl;
        } else {
            cout << "Film dengan judul " << nama_film << " tidak ditemukan" << endl;
        }
    }
};

void deleteAplikasi(ListAplikasi &L, ListFilm &L_film, string nama_aplikasi) {
    address_aplikasi P, Q, R, S;
    P = findAplikasi(L, nama_aplikasi); // Cari aplikasi berdasarkan nama

    if (P == NULL) {
        cout << "Aplikasi tidak ditemukan" << endl;
    } else {
        // Periksa apakah ada relasi
        if (P->relasi != NULL) {
            address_relasi T, U;
            T = P->relasi;
            while (T != NULL) {
                U = T;
                T = T->next;
                delete U; // Hapus elemen relasi
            }
            P->relasi = NULL; // aplikasi di-set ke NULL setelah semua relasi dihapus
        }
        //hapus aplikasi
        if (L.first == NULL) {
            cout << "List aplikasi kosong" << endl;
        } else if (L.first == P) { //delete first
            S = L.first;
            L.first = S->next;
            S->next = NULL;
            delete S;
        } else {
            Q = L.first;
            while (Q->next != NULL && Q->next != P) { //mencari posisi aplikasi
                Q = Q->next;
            }
            if (Q->next == NULL) {
                cout << "Aplikasi tidak ditemukan dalam list" << endl; // Aplikasi tidak ditemukan
            } else if (Q->next == P) { // delete last
                S = Q->next;
                Q->next = NULL;
                delete S;
            } else { // delete after
                S = Q->next;
                Q->next = S->next;
                S->next = NULL;
                delete S;
            }
        }
    }
}



void deleteFilm(ListFilm &L, ListAplikasi &L_aplikasi, string nama_film) {
    address_film P, S;
    P = findFilm(L, nama_film); // Mencari film berdasarkan nama

    if (P == NULL) {
        cout << "Film tidak ditemukan" << endl;
    } else {
        // Menghapus relasi
        address_relasi U;
        address_aplikasi T;
        T = L_aplikasi.first;
        while (T != NULL) {
            U = T->relasi;
            while (U != NULL) {
                if (U->film == P) {  // Jika relasi film ditemukan
                    U->film = NULL;   // Hapus relasi film
                }
                U = U->next;
            }
            T = T->next;
        }

        // Menghapus film dari list
        if (L.first == P && L.last == P) { // List hanya berisi satu elemen
            S = L.first;
            L.first = NULL;
            L.last = NULL;
            delete S;
        } else if (L.first == P) { // Menghapus elemen pertama
            S = L.first;
            L.first = S->next;
            L.first->prev = NULL;
            S->next = NULL;
            delete S;
        } else if (L.last == P) { // Menghapus elemen terakhir
            S = L.last;
            L.last = S->prev;
            L.last->next = NULL;
            S->prev = NULL;
            delete S;
        } else { // Menghapus elemen di tengah
            S = P;
            S->prev->next = S->next;
            S->next->prev = S->prev;
            S->next = NULL;
            S->prev = NULL;
            delete S;
        }
    }
};


void deleteRelation(ListAplikasi &L_aplikasi, string nama_aplikasi, string nama_film){

};

address_aplikasi findAplikasi(ListAplikasi L, string nama_aplikasi){
    address_aplikasi P;
    P = L.first;
    while (P != NULL){
        if (P->info.nama_aplikasi == nama_aplikasi){
            return P;
        }
        P = P->next;
    }
    return NULL;
};
//-------------------------------BATAS SASSA------------------------------------------

address_film findFilm(ListFilm L, string nama_film){
    address_film P;
    P = L.first;
    while ( P != NULL){
        if (P->info_film.nama == nama_film){
            return P;
        }
        P = P->next;
    }
    return NULL;
};

bool findRelation(ListAplikasi L_aplikasi, string nama_aplikasi, string nama_film);

void showAllAplikasi(ListAplikasi L);

void showAllFilm(ListFilm L);

void showChildFromParent(ListAplikasi L_aplikasi, string nama_aplikasi);

void showParentWithChild(ListAplikasi L_aplikasi);
//-------------------------------BATAS LYNA------------------------------------------

void showChildWithParents(ListFilm L_film, ListAplikasi L_aplikasi);

void showParentsFromChild(ListFilm L_film, ListAplikasi L_aplikasi, string nama_film);

void countRelationFromParent(ListAplikasi L_aplikasi);

void countRelationFromChild(ListFilm L_film, ListAplikasi L_aplikasi, string nama_film);

void countChildWithoutRelation(ListFilm L_film, ListAplikasi L_aplikasi);

void editRelation(ListAplikasi &L_aplikasi, ListFilm &L_film, string nama_aplikasi, string nama_film_lama, string nama_film_baru);


//-------------------------------BATAS ACA---------------------------------------------

