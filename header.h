#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#define first(L) L.first
#define last(L) L.last
#define info(P) P->info
#define next(P) P->next
#define prev(P) P->prev
using namespace std;

struct aplikasi_streaming {
    string nama_aplikasi, kualitas;
    float rating;
    int harga;
};

struct film {
    string nama, genre;
    int tahun;
    float rating;
};

typedef aplikasi_streaming infotype_aplikasi;
typedef struct ElmAplikasi *address_aplikasi;
typedef struct ElmRelasi *address_relasi;
typedef film infotype_film;
typedef struct ElmFilm *address_film;

struct ElmRelasi {
    address_film film;
    address_relasi next;
};

struct ListRelasi {
    address_relasi first;
};

struct ElmAplikasi {
    infotype_aplikasi info;
    address_aplikasi next;
    ListRelasi relation;
};

struct ListAplikasi {
    address_aplikasi first;
};

struct ElmFilm {
    infotype_film info_film;
    address_film next, prev;
};

struct ListFilm {
    address_film first, last;
};

// FUNGSI DAN PROSEDUR
void createListAplikasi(ListAplikasi &L);
address_aplikasi allocateAplikasi(infotype_aplikasi data);
void createListFilm(ListFilm &L);
address_film allocateFilm(infotype_film data);
address_relasi allocateRelasi(address_film child);
void insertAplikasi(ListAplikasi &L, address_aplikasi P);
void insertFilm(ListFilm &L, address_film P);
void insertRelation(ListAplikasi &L_aplikasi, ListFilm &L_film, string nama_aplikasi, string nama_film);
void deleteAplikasi(ListAplikasi &L, ListFilm &L_film, string nama_aplikasi);
void deleteFilm(ListFilm &L, ListAplikasi &L_aplikasi, string nama_film);
void deleteRelation(ListAplikasi &L_aplikasi, string nama_aplikasi, string nama_film);
address_aplikasi findAplikasi(ListAplikasi L, string nama_aplikasi);

address_film findFilm(ListFilm L, string nama_film);
bool findRelation(ListAplikasi L_aplikasi, string nama_aplikasi, string nama_film);
void showAllAplikasi(ListAplikasi L);
void showAllFilm(ListFilm L);
void showChildFromParent(ListAplikasi L_aplikasi, string nama_aplikasi);
void showParentWithChild(ListAplikasi L_aplikasi);

void showChildWithParents(ListFilm L_film, ListAplikasi L_aplikasi);
void showParentsFromChild(ListFilm L_film, ListAplikasi L_aplikasi, string nama_film);
void countRelationFromParent(ListAplikasi L_aplikasi);
void countRelationFromChild(ListFilm L_film, ListAplikasi L_aplikasi, string nama_film);
void countChildWithoutRelation(ListFilm L_film, ListAplikasi L_aplikasi);
void editRelation(ListAplikasi &L_aplikasi, ListFilm &L_film, string nama_aplikasi, string nama_film_lama, string nama_film_baru);

#endif // HEADER_H_INCLUDED
