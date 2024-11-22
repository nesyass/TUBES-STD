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
    address_aplikasi P, Q, S;

    P = findAplikasi(L, nama_aplikasi);
    if (P == NULL) {
        cout << "Aplikasi tidak ditemukan" << endl;
    } else {
        // Hapus semua relasi yang terhubung dengan aplikasi
        if (P->relasi != NULL) {
            address_relasi T, U;
            T = P->relasi;
            while (T != NULL) {
                U = T;
                T = T->next;
                delete U;
            }
            P->relasi = NULL;
        }

        // Menghapus aplikasi dari list
        if (L.first == NULL) {
            cout << "List aplikasi kosong" << endl;
        } else if (L.first == P && L.first->next == NULL) { // List hanya berisi satu elemen
            P = L.first;
            L.first = NULL;
            delete P;
            cout << "Aplikasi berhasil dihapus" << endl;
        } else if (L.first == P) { //delete first
            S = L.first;
            L.first = S->next;
            S->next = NULL;
            delete S;
            cout << "Aplikasi berhasil dihapus" << endl;
        } else {
            Q = L.first;
            while (Q->next != NULL && Q->next != P) { // Mencari aplikasi dalam list
                Q = Q->next;
            }
            if (Q->next == NULL) {
                cout << "Aplikasi tidak ditemukan dalam list" << endl;
            } else if (Q->next == P && P->next == NULL) { //delete last
                S = Q->next;
                Q->next = NULL;
                delete S;
                cout << "Aplikasi berhasil dihapus" << endl;
            } else { //delete after
                S = Q->next;
                Q->next = S->next;
                S->next = NULL;
                delete S;
                cout << "Aplikasi berhasil dihapus" << endl;
            }
        }
    }
};

void deleteFilm(ListFilm &L, ListAplikasi &L_aplikasi, string nama_film) {
    address_film P = findFilm(L, nama_film);

    if (L.first == NULL) { // List kosong
        cout << "List film kosong" << endl;
    } else if (P == NULL) { // Film tidak ditemukan
        cout << "Film tidak ditemukan" << endl;
    } else {
        // Hapus semua relasi terkait film
        address_aplikasi T = L_aplikasi.first;
        while (T != NULL) {
            address_relasi U = T->relasi;
            while (U != NULL) {
                if (U->film == P) {
                    U->film = NULL; // Putuskan relasi film
                }
                U = U->next;
            }
            T = T->next;
        }

        // Hapus film dari list
        if (L.first == P && L.last == P) { // Hanya ada satu elemen
            L.first = NULL;
            L.last = NULL;
        } else if (L.first == P) { // Elemen berada di awal
            L.first = P->next;
            L.first->prev = NULL;
        } else if (L.last == P) { // Elemen berada di akhir
            L.last = P->prev;
            L.last->next = NULL;
        } else { // Elemen berada di tengah
            P->prev->next = P->next;
            P->next->prev = P->prev;
        }

        // Hapus elemen
        P->next = NULL;
        P->prev = NULL;
        delete P;

        cout << "Film berhasil dihapus" << endl;
    }
}



void deleteRelation(ListAplikasi &L_aplikasi, string nama_aplikasi, string nama_film) {
    if (L_aplikasi.first == NULL) {
        cout << "List Aplikasi kosong" << endl;
    } else {
        address_aplikasi P;
        P = findAplikasi(L_aplikasi, nama_aplikasi);
        if (P == NULL) {
            cout << "Aplikasi dengan nama " << nama_aplikasi << " tidak ditemukan" << endl;
        } else {
            // Cek relasi
            if (P->relasi == NULL) {
                cout << "Tidak ada relasi pada aplikasi " << nama_aplikasi << endl;
            } else {
                address_relasi R;
                address_relasi S;
                R = P->relasi;
                S = NULL;
                bool isDeleted = false; //flag
                while (R != NULL && isDeleted == false) {
                    if (R->film != NULL && R->film->info_film.nama == nama_film) {
                        if (R == P->relasi) {
                            P->relasi = R->next;
                        } else {
                            S->next = R->next;
                        }
                        delete R;
                        isDeleted = true;
                    }
                    S = R;
                    R = R->next;
                }

                //hasil berdasarkan flag
                if (isDeleted) {
                    cout << "Relasi dengan film " << nama_film << " pada aplikasi " << nama_aplikasi << " berhasil dihapus" << endl;
                } else {
                    cout << "Film dengan nama " << nama_film << " tidak ditemukan dalam relasi aplikasi " << nama_aplikasi << endl;
                }
            }
        }
    }
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

