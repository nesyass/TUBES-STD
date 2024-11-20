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
    P->relation.first = NULL;
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

address_relasi allocateRelasi(address_film child){
    address_relasi P;
    P = new ElmRelasi;
    P->film = child;
    P->next = NULL;
    return P;
};

void insertAplikasi(ListAplikasi &L, address_aplikasi P){
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

void insertFilm(ListFilm &L, address_film P){
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
    A = L_aplikasi.first;
    while (A != NULL && A->info.nama_aplikasi != nama_aplikasi) {
        A = A->next;
    }

    address_film F;
    F = L_film.first;
    while (F != NULL && F->info_film.nama != nama_film) {
        F = F->next;
    }

    if (A != NULL && F != NULL){
        address_relasi R;
        R = A->relation.first;
        while (R != NULL){
            if (R->film == F){
                cout << "Film sudah tersedia di aplikasi" << endl;
            } else {
                R = R->next;
            }
        }
        address_relasi newR;
        newR = allocateRelasi(F);
        newR->next = A->relation.first;
        A->relation.first = newR;
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
    if (L.first == NULL) {
        cout << "List aplikasi kosong" << endl;
    } else {
        address_aplikasi P;
        if (L.first->info.nama_aplikasi == nama_aplikasi) {
            P = L.first;
            L.first = P->next;
            address_relasi rel = P->relation.first;
            while (rel != NULL) {
                address_relasi temp = rel;
                rel = rel->next;
                delete temp;
            }
            delete P;
        } else {
            address_aplikasi prev_app, curr_app;
            prev_app = NULL;
            curr_app = L.first;
            while (curr_app != NULL && curr_app->info.nama_aplikasi != nama_aplikasi) {
                prev_app = curr_app;
                curr_app = curr_app->next;
            }
            if (curr_app == NULL) {
                cout << "Aplikasi dengan nama " << nama_aplikasi << " tidak ditemukan." << endl;
            } else {
                if (curr_app->next == NULL) {
                    prev_app->next = NULL;
                } else {
                    prev_app->next = curr_app->next;
                }
                address_relasi rel;
                rel = curr_app->relation.first;
                while (rel != NULL) {
                    address_relasi temp = rel;
                    rel = rel->next;
                    delete temp;
                }
                delete curr_app;
            }
        }
        cout << "Aplikasi " << nama_aplikasi << " berhasil dihapus." << endl;
    }
};


void deleteFilm(ListFilm &L, ListAplikasi &L_aplikasi, string nama_film){

};

void deleteRelation(ListAplikasi &L_aplikasi, string nama_aplikasi, string nama_film){

};

address_aplikasi findAplikasi(ListAplikasi L, string nama_aplikasi){

};
//-------------------------------BATAS SASSA------------------------------------------

address_film findFilm(ListFilm L, string nama_film);

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

