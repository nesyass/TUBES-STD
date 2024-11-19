#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#define first(L) L.first
#define last(L) L.last
#define info(P) P->info
#define next(P) P->next
#define prev(P) P->prev
using namespace std;

// ADT LAYANAN STREAMING (PARENT)
struct aplikasi_streaming {
    string nama_aplikasi, kualitas;
    float rating;
    int harga;
};

typedef aplikasi_streaming infotype_aplikasi;
typedef struct ElmAplikasi *address_aplikasi;

struct ElmAplikasi {
    infotype_aplikasi info;    // Data aplikasi
    address_aplikasi next;     // Pointer ke aplikasi berikutnya
    ListRelasi relation;       // List relasi untuk child
};

struct ListAplikasi {
    address_aplikasi first;    // Pointer ke aplikasi pertama
};

// RELASI M:N
typedef struct ElmRelasi *address_relasi;

struct ElmRelasi {
    address_film film;         // Pointer ke film (child)
    address_relasi next;       // Pointer ke relasi berikutnya
};

struct ListRelasi {
    address_relasi first;      // List untuk menyimpan relasi (M:N)
};

// ADT FILM (CHILD)
struct film {
    string nama, genre;
    int tahun;
    float rating;
};

typedef film infotype_film;
typedef struct ElmFilm *address_film;

struct ElmFilm {
    infotype_film info_film;   // Data film
    address_film next, prev;   // Pointer untuk doubly linked list
};

struct ListFilm {
    address_film first, last;  // Pointer ke film pertama dan terakhir
};

// FUNGSI DAN PROSEDUR

// List Parent
void createListAplikasi(ListAplikasi &L);
address_aplikasi allocateAplikasi(infotype_aplikasi data);
void insertAplikasi(ListAplikasi &L, address_aplikasi P);
void deleteAplikasi(ListAplikasi &L, ListFilm &L_film, string nama_aplikasi);

// List Child
void createListFilm(ListFilm &L);
address_film allocateFilm(infotype_film data);
void insertFilm(ListFilm &L, address_film P);
void deleteFilm(ListFilm &L, ListAplikasi &L_aplikasi, string nama_film);

// Relasi
address_relasi allocateRelasi(address_film child);
void insertRelation(ListAplikasi &L_aplikasi, ListFilm &L_film, string nama_aplikasi, string nama_film);
void deleteRelation(ListAplikasi &L_aplikasi, string nama_aplikasi, string nama_film);

// Searching
address_aplikasi findAplikasi(ListAplikasi L, string nama_aplikasi);
address_film findFilm(ListFilm L, string nama_film);
bool findRelation(ListAplikasi L_aplikasi, string nama_aplikasi, string nama_film);

// Show
void showAllAplikasi(ListAplikasi L);
void showAllFilm(ListFilm L);
void showChildFromParent(ListAplikasi L_aplikasi, string nama_aplikasi);
void showParentWithChild(ListAplikasi L_aplikasi);
void showParentFromChild(ListFilm L_film, ListAplikasi L_aplikasi, string nama_film);

// Statistik
void countRelationFromParent(ListAplikasi L_aplikasi);
void countRelationFromChild(ListFilm L_film, ListAplikasi L_aplikasi);
void countChildWithoutRelation(ListFilm L_film);

// Edit Relasi
void editRelation(ListAplikasi &L_aplikasi, ListFilm &L_film, string nama_aplikasi, string nama_film_lama, string nama_film_baru);

#endif // HEADER_H_INCLUDED
