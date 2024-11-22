#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
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
typedef film infotype_film;
typedef struct ElmAplikasi *address_aplikasi;
typedef struct ElmFilm *address_film;
typedef struct ElmRelasi *address_relasi;

struct ElmRelasi {
    address_film film;       // Pointer ke child (film)
    address_relasi next;     // Pointer ke relasi berikutnya
};

struct ElmAplikasi {
    infotype_aplikasi info;  // Informasi aplikasi
    address_aplikasi next;   // Pointer ke aplikasi berikutnya
    address_relasi relasi;   // Pointer ke daftar relasi
};

struct ListAplikasi {
    address_aplikasi first;  // Pointer ke aplikasi pertama
};

struct ElmFilm {
    infotype_film info_film; // Informasi film
    address_film next, prev; // Pointer next dan prev untuk film
};

struct ListFilm {
    address_film first, last; // Pointer ke film pertama dan terakhir
};

// FUNGSI DAN PROSEDUR
void createListAplikasi(ListAplikasi &L);
address_aplikasi allocateAplikasi(infotype_aplikasi data);
void createListFilm(ListFilm &L);
address_film allocateFilm(infotype_film data);
void insertAplikasi(ListAplikasi &L, address_aplikasi P);
void insertFilm(ListFilm &L, address_film P);
void insertRelation(address_aplikasi aplikasi, address_film film);
void deleteAplikasi(ListAplikasi &L, ListFilm &L_film, string nama_aplikasi);
void deleteFilm(ListFilm &L, ListAplikasi &L_aplikasi, string nama_film);
void deleteRelation(address_aplikasi aplikasi, string nama_film);
address_aplikasi findAplikasi(ListAplikasi L, string nama_aplikasi);
//--------------------------------------BATAS SASSA------------------------------------------------------------------------------\

address_film findFilm(ListFilm L, string nama_film);
bool findRelation(address_aplikasi aplikasi, string nama_film);
void showAllAplikasi(ListAplikasi L);
void showAllFilm(ListFilm L);
void showChildFromParent(address_aplikasi aplikasi);
void showParentWithChild(ListAplikasi L_aplikasi);
//--------------------------------------BATAS LYNA------------------------------------------------------------------------------\

void showChildWithParents(ListFilm L_film, ListAplikasi L_aplikasi);
void showParentsFromChild(ListFilm L_film, ListAplikasi L_aplikasi, string nama_film);
void countRelationFromParent(address_aplikasi aplikasi);
void countRelationFromChild(ListFilm L_film, ListAplikasi L_aplikasi, string nama_film);
void countChildWithoutRelation(ListFilm L_film, ListAplikasi L_aplikasi);
void editRelation(address_aplikasi aplikasi, ListFilm &L_film, string nama_film_lama, string nama_film_baru);
//--------------------------------------BATAS ACA------------------------------------------------------------------------------\


#endif // HEADER_H_INCLUDED
