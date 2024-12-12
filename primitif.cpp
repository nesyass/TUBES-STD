#include <iostream>
#include <cstdlib>
#include "header.h"
using namespace std;

// IS: List aplikasi kosong.
// FS: List aplikasi diinisialisasi dengan elemen pertama NULL.
void createListAplikasi(ListAplikasi &L){
    L.first = NULL;
}

// IS: Tidak ada node untuk menyimpan data aplikasi.
// FS: Sebuah elemen aplikasi baru dialokasikan dan diisi dengan data.
address_aplikasi allocateAplikasi(infotype_aplikasi data){
    address_aplikasi P;
    P = new ElmAplikasi;
    P->info = data;
    P->next = NULL;
    P->relasi = NULL;
    return P;
}

// IS: List film kosong.
// FS: List film diinisialisasi dengan elemen pertama dan terakhir NULL.
void createListFilm(ListFilm &L){
    L.first = NULL;
    L.last = NULL;
}

// IS: Tidak ada node untuk menyimpan data film.
// FS: Sebuah elemen film baru dialokasikan dan diisi dengan data.
address_film allocateFilm(infotype_film data){
    address_film P;
    P = new ElmFilm;
    P->info_film = data;
    P->next = NULL;
    P->prev = NULL;
    return P;
}

// IS: List aplikasi kosong atau memiliki elemen.
// FS: Elemen aplikasi baru ditambahkan di akhir list.
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
}

// IS: List film kosong atau memiliki elemen.
// FS: Elemen film baru ditambahkan di akhir list.
void insertFilm(ListFilm &L, address_film P){ //insert last//
    if (L.first == NULL){
        L.first = P;
        L.last = P;
    } else {
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
}

// IS: Relasi antara aplikasi dan film belum ada.
// FS: Relasi baru ditambahkan ke aplikasi jika kedua elemen ditemukan.
void insertRelation(ListAplikasi &L_aplikasi, ListFilm &L_film, string nama_aplikasi, string nama_film) {
    address_aplikasi A;
    address_film F;

    A = findAplikasi(L_aplikasi, nama_aplikasi);
    F = findFilm(L_film, nama_film);

    if (A != NULL && F != NULL) {
        address_relasi R;
        bool relasiSudahAda;

        R = A->relasi;
        relasiSudahAda = false;
        while (R != NULL && !relasiSudahAda) {
            if (R->film == F) {
                relasiSudahAda = true;
                cout << "Film sudah tersedia di aplikasi." << endl;
            }
            R = R->next;
        }

        if (!relasiSudahAda) {
            address_relasi newR;
            newR = new ElmRelasi;
            newR->film = F;
            newR->next = A->relasi;
            A->relasi = newR;

            cout << "Film dengan judul " << F->info_film.nama << " berhasil ditambahkan ke aplikasi " << nama_aplikasi << endl;
        }
    } else {
        if (A == NULL) {
            cout << "Aplikasi dengan nama " << nama_aplikasi << " tidak ditemukan." << endl;
        }
        if (F == NULL) {
            cout << "Film dengan judul " << nama_film << " tidak ditemukan." << endl;
        }
    }
}

// IS: List aplikasi berisi elemen, aplikasi dengan nama tertentu mungkin ada.
// FS: Aplikasi dan semua relasi terkait dihapus dari list.
void deleteAplikasi(ListAplikasi &L, ListFilm &L_film, string nama_aplikasi) {
    address_aplikasi P;
    P = findAplikasi(L, nama_aplikasi);
    if (P == NULL) {
        cout << "Aplikasi tidak ditemukan" << endl;
    } else {
        // Hapus semua relasi terkait aplikasi
        address_relasi T, temp;
        T = P->relasi;
        while (T != NULL) {
            temp = T;
            T = T->next;
            temp->next = NULL;
            delete temp;
        }
        P->relasi = NULL;

        // Menghapus aplikasi dari list
        if (L.first == P) {
            L.first = P->next;
            P->next = NULL;
        } else {
            address_aplikasi Q = L.first;
            while (Q->next != P) {
                Q = Q->next;
            }
            Q->next = P->next;
            P->next = NULL;
        }
        delete P;
        cout << "Aplikasi berhasil dihapus" << endl;
    }
    cout << endl;
}


// IS: List film berisi elemen, film dengan judul tertentu mungkin ada.
// FS: Film dan semua relasi terkait dihapus dari list.
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
            address_relasi prev = NULL;
            address_relasi U = T->relasi;

            while (U != NULL) {
                if (U->film == P) {
                    if (prev == NULL) { // Elemen pertama
                        T->relasi = U->next;
                        U->film = NULL;
                        U->next = NULL;
                        U = T->relasi;
                    } else { // Elemen di tengah/akhir
                        prev->next = U->next;
                        U->film = NULL;
                        U->next = NULL;
                        U = prev->next;
                    }
                } else {
                    prev = U;
                    U = U->next;
                }
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

        // Putuskan koneksi elemen film
        P->next = NULL;
        P->prev = NULL;

        cout << "Film berhasil dihapus" << endl;
    }
}

// IS: Relasi antara aplikasi dan film mungkin ada.
// FS: Relasi tertentu dihapus jika ditemukan.
void deleteRelation(ListAplikasi &L_aplikasi, string nama_aplikasi, string nama_film) {
    if (L_aplikasi.first == NULL) {
        cout << "List Aplikasi kosong" << endl;
    } else {
        address_aplikasi P;
        P = findAplikasi(L_aplikasi, nama_aplikasi);
        if (P == NULL) {
            cout << "Aplikasi dengan nama " << nama_aplikasi << " tidak ditemukan" << endl;
        } else {
            if (P->relasi == NULL) {
                cout << "Tidak ada relasi pada aplikasi " << nama_aplikasi << endl;
            } else {
                //mencari dan menghapus relasi
                address_relasi prev;
                address_relasi curr;
                bool isDeleted; // Status penghapusan

                prev = NULL;
                isDeleted = false;
                curr = P->relasi;
                while (curr != NULL) {
                    if (curr->film->info_film.nama == nama_film) {
                        if (prev == NULL) { // Hapus elemen pertama
                            P->relasi = curr->next;
                        } else { // Hapus elemen tengah/akhir
                            prev->next = curr->next;
                        }
                        curr->next = NULL; // Putuskan hubungan
                        isDeleted = true;  // Tandai bahwa elemen telah dihapus
                    } else {
                        prev = curr; // Perbarui prev jika tidak ada penghapusan
                    }
                    curr = curr->next; // Lanjutkan ke elemen berikutnya
                }

                // Berikan pesan berdasarkan status penghapusan
                if (isDeleted) {
                    cout << "Relasi dengan film " << nama_film << " pada aplikasi " << nama_aplikasi << " berhasil dihapus" << endl;
                } else {
                    cout << "Film dengan nama " << nama_film << " tidak ditemukan dalam relasi aplikasi " << nama_aplikasi << endl;
                }
            }
        }
    }
}

// IS: List aplikasi berisi elemen.
// FS: Elemen aplikasi dengan nama tertentu dikembalikan jika ditemukan.
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
}

void menu() {
    cout << "=================================================================" << endl;
    cout << "                    MENU APLIKASI STREAMING       " << endl;
    cout << "=================================================================" << endl;
    cout << "| 1.  Tambah Aplikasi" << endl;
    cout << "| 2.  Tambah Film" << endl;
    cout << "| 3.  Tampilkan Semua Aplikasi" << endl;
    cout << "| 4.  Tampilkan Semua Film" << endl;
    cout << "| 5.  Buat Relasi Aplikasi dengan Film" << endl;
    cout << "| 6.  Menampilkan Daftar Film dari Suatu Aplikasi" << endl;
    cout << "| 7.  Menampilkan Daftar Aplikasi yang Menyediakan Suatu Film" << endl;
    cout << "| 8.  Hapus Aplikasi" << endl;
    cout << "| 9.  Hapus Film" << endl;
    cout << "| 10. Hapus Relasi" << endl;
    cout << "| 11. Show Data Film Beserta Data Aplikasi yang Dimiliki" << endl;
    cout << "| 12. Show Data Aplikasi yang Berelasi dengan Film Tertentu" << endl;
    cout << "| 13. Count Relation dari Setiap Elemen Aplikasi" << endl;
    cout << "| 14. Count Relation yang Dimiliki oleh Film Tertentu" << endl;
    cout << "| 15. Count Elemen Film yang Tidak Memiliki Relasi" << endl;
    cout << "| 16. Edit Relasi/Mengganti Film dari Aplikasi Tertentu" << endl;
    cout << "| 17. Keluar" << endl;
    cout << "=================================================================" << endl;
    cout << "Masukkan Pilihan: ";
}


void clearScreen() {
    if (_WIN32) {
        system("cls"); // untuk Windows
    } else {
        system("clear"); // untuk Linux/Mac
    }
}

//-------------------------------BATAS SASSA------------------------------------------

// IS: List film berisi elemen.
// FS: Elemen film dengan nama tertentu dikembalikan jika ditemukan.
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
}

// IS: Tidak ada informasi tentang keberadaan relasi antara aplikasi dan film.
// FS: Mengembalikan true jika relasi antara aplikasi dan film ditemukan, false jika tidak.
bool findRelation(ListAplikasi L_aplikasi, string nama_aplikasi, string nama_film){
    address_aplikasi p = findAplikasi(L_aplikasi, nama_aplikasi);

    if(p != NULL) {
        address_relasi r;
        r = p->relasi;
        while(r != NULL){
            if(r->film->info_film.nama == nama_film && r->film != NULL) {
                return true;
            }
            r = r->next;
        }

    }
    return false;
}

// IS: List aplikasi berisi elemen atau kosong.
// FS: Menampilkan semua aplikasi beserta informasi terkait di layar.
void showAllAplikasi(ListAplikasi L){
    address_aplikasi p;

    p = L.first;
    int i = 1;

    if (p == NULL) {
        cout << "Tidak ada aplikasi dalam list. Silahkan tambahkan aplikasi terlebih dahulu!" << endl;
    } else {
        cout << "DAFTAR APLIKASI: " << endl;
        while(p != NULL) {
            cout << "Daftar aplikasi ke-" << i << " :" << endl;
            cout << "Nama Aplikasi    : " << p->info.nama_aplikasi << endl;
            cout << "Kualitas         : " << p->info.kualitas << endl;
            cout << "Rating           : " << p->info.rating << endl;
            cout << "Harga            : " << p->info.harga << endl;
            cout << endl;
            p = p->next;
            i++;
        }
        cout << endl;
    }
}

// IS: List film berisi elemen atau kosong.
// FS: Menampilkan semua film beserta informasi terkait di layar.
void showAllFilm(ListFilm L){
    address_film p;

    p = L.first;
    int i = 1;

    if (p == NULL) {
        cout << "Tidak ada film dalam list. Silahkan tambahkan film terlebih dahulu!" << endl;
    } else {
        cout << "DAFTAR FILM:" << endl;
        while(p != NULL) {
            cout << "Daftar film ke-" << i << " :" << endl;
            cout << "Nama Film    : " << p->info_film.nama << endl;
            cout << "Genre        : " << p->info_film.genre << endl;
            cout << "Tahun        : " << p->info_film.tahun << endl;
            cout << "Rating       : " << p->info_film.rating << endl;
            cout << endl;
            p = p->next;
            i++;
    }
    cout << endl;
    }
}

// IS: List aplikasi `L_aplikasi` dan nama aplikasi `nama_aplikasi` tersedia.
// FS: Menampilkan daftar film yang dimiliki oleh aplikasi dengan nama tertentu. Jika aplikasi atau film tidak ditemukan, pesan kesalahan akan ditampilkan.
void showChildFromParent(ListAplikasi L_aplikasi, string nama_aplikasi) {
    address_aplikasi p = findAplikasi(L_aplikasi, nama_aplikasi);

    if (p == NULL) {
        cout << "Tidak ada aplikasi dengan nama " << nama_aplikasi << " pada list." << endl;
    } else {
        address_relasi r = p->relasi;

        if (r == NULL) {
            cout << "Tidak ada film pada aplikasi " << nama_aplikasi << "." << endl;
        } else {
            int i = 1;
            cout << "=== Daftar film pada aplikasi " << p->info.nama_aplikasi << " ===" << endl;

            while (r != NULL) {
                if (r->film != NULL) {
                    cout << "Daftar film ke-" << i << " :" << endl;
                    cout << "Nama Film    : " << r->film->info_film.nama << endl;
                    cout << "Genre        : " << r->film->info_film.genre << endl;
                    cout << "Tahun        : " << r->film->info_film.tahun << endl;
                    cout << "Rating       : " << r->film->info_film.rating << endl;
                    cout << endl;
                } else {
                    cout << "Film tidak valid pada relasi ke-" << i << "." << endl;
                }
                r = r->next;
                i++;
            }
        }
    }
    cout << endl;
}

// IS: List aplikasi `L_aplikasi` tersedia.
// FS: Menampilkan semua aplikasi beserta daftar film yang dimilikinya. Jika tidak ada aplikasi, menampilkan pesan bahwa list kosong.
void showParentWithChild(ListAplikasi L_aplikasi){
    address_aplikasi p;
    p = L_aplikasi.first;
    int i = 1;
    if (p == NULL) {
        cout << "Tidak ada aplikasi dalam list. Silahkan tambahkan aplikasi terlebih dahulu!" << endl;
    } else {
        cout << "DAFTAR APLIKASI: " << endl;
        while(p != NULL) {
            cout << "Daftar aplikasi ke-" << i << " :" << endl;
            cout << "Nama Aplikasi    : " << p->info.nama_aplikasi << endl;
            cout << "Kualitas         : " << p->info.kualitas << endl;
            cout << "Rating           : " << p->info.rating << endl;
            cout << "Harga            : " << p->info.harga << endl;
            cout << endl;

            address_relasi r;
            r = p->relasi;
            if(r == NULL) {
                cout << "   Tidak ada film pada aplikasi " << p->info.nama_aplikasi << "." << endl;
            } else {
                int j = 1;
                cout << "   === Daftar film pada aplikasi " << p->info.nama_aplikasi << " ===" << endl;
                while(r != NULL){
                    cout << "   Daftar film ke-" << i << " :" << endl;
                    cout << "   Nama Film    : " << r->film->info_film.nama << endl;
                    cout << "   Genre        : " << r->film->info_film.genre << endl;
                    cout << "   Tahun        : " << r->film->info_film.tahun << endl;
                    cout << "   Rating       : " << r->film->info_film.rating << endl;
                    cout << "   ----------------------------------" << endl;
                    r = r->next;
                    j++;
                }
            }
            p = p->next;
            i++;
            cout << endl;
        }
    }
}
//-------------------------------BATAS LYNA------------------------------------------

// IS: List film `L_film` dan list aplikasi `L_aplikasi` tersedia.
// FS: Menampilkan semua film yang ada beserta daftar aplikasi yang memiliki film tersebut.
void showChildWithParents(ListFilm L_film, ListAplikasi L_aplikasi) {
    address_film P = L_film.first;
    int i = 1;

    if (P == NULL) {
        cout << "Tidak ada film dalam daftar." << endl;
    } else {
        while (P != NULL) {
            cout << "   Daftar film ke-" << i << " :" << endl;
            cout << "   Nama Film    : " << P->info_film.nama << endl;
            cout << "   Genre        : " << P->info_film.genre << endl;
            cout << "   Tahun        : " << P->info_film.tahun << endl;
            cout << "   Rating       : " << P->info_film.rating << endl;
            cout << "   Dimiliki oleh aplikasi: ";

            bool found = false;
            address_aplikasi Q = L_aplikasi.first;
            bool firstApp = true; // Untuk mengelola koma

            while (Q != NULL) {
                address_relasi R = Q->relasi;
                while (R != NULL) {
                    if (R->film == P) {
                        if (!firstApp) {
                            cout << ", ";
                        }
                        cout << Q->info.nama_aplikasi;
                        firstApp = false;
                        found = true;
                    }
                    R = R->next;
                }
                Q = Q->next;
            }
            if (!found) {
                cout << "Belum dimiliki aplikasi manapun";
            }
            cout << endl;
            cout << "   ----------------------------------" << endl;

            P = P->next;
            i++;
        }
    }
    cout << endl;
}


// IS: Diberikan ListFilm `L_film`, ListAplikasi `L_aplikasi`, dan nama film (`nama_film`) yang akan dicari.
// FS: Menampilkan daftar aplikasi yang memiliki relasi dengan film `nama_film`.
void showParentsFromChild(ListFilm L_film, ListAplikasi L_aplikasi, string nama_film) {
    address_film F = findFilm(L_film, nama_film); // Cari film berdasarkan nama

    if (F == NULL) {
        cout << "Film dengan nama '" << nama_film << "' tidak ditemukan." << endl;
    } else {
        address_aplikasi Q = L_aplikasi.first; // Mulai dari aplikasi pertama
        bool found = false;
        int i = 1;

        while (Q != NULL) {
            address_relasi R = Q->relasi; // Mulai dari daftar relasi aplikasi
            bool foundInCurrentApp = false; // Penanda untuk aplikasi saat ini

            while (R != NULL) {
                if (R->film == F) { // Jika film ditemukan di relasi
                    if (!foundInCurrentApp) { // Pastikan aplikasi hanya ditampilkan sekali
                        if (!found) {
                            cout << "=== Daftar aplikasi yang memiliki film '" << nama_film << "' ===" << endl;
                        }
                        cout << "Aplikasi ke-" << i << " :" << endl;
                        cout << "Nama Aplikasi : " << Q->info.nama_aplikasi << endl;
                        cout << endl;
                        foundInCurrentApp = true;
                        found = true;
                        i++;
                    }
                }
                R = R->next; // Lanjut ke relasi berikutnya
            }
            Q = Q->next; // Lanjut ke aplikasi berikutnya
        }

        if (!found) {
            cout << "Film '" << nama_film << "' belum dimiliki oleh aplikasi mana pun." << endl;
        }
    }
    cout << endl;
}

// IS: Diberikan ListAplikasi `L_aplikasi` yang berisi aplikasi dan relasinya dengan film.
// FS: Menampilkan jumlah film yang dimiliki oleh setiap aplikasi dalam `L_aplikasi`.
void countRelationFromParent(ListAplikasi L_aplikasi) {
     address_aplikasi P = L_aplikasi.first;
    if (P == NULL) {
        cout << "Tidak ada film dalam daftar." << endl;
    } else {
        while (P != NULL) {
            cout << "   Nama Aplikasi   : " << P->info.nama_aplikasi<< endl;
            cout << "   Kualitas        : " << P->info.kualitas<< endl;
            cout << "   Harga           : " << P->info.harga << endl;
            cout << "   Rating          : " << P->info.rating << endl;
            address_relasi R = P->relasi;
            int i = 0;
            while (R != NULL) {
                i++;
                R = R->next;
            }
            cout << "   Memiliki " << i << " Film" << endl;
            cout << endl;
            cout << "   ----------------------------------" << endl;
            P = P->next;

        }
    }
    cout << endl;
}

// IS: Diberikan ListFilm `L_film`, ListAplikasi `L_aplikasi`, dan nama film (`nama_film`) yang akan dihitung.
// FS: Menampilkan jumlah aplikasi yang memiliki relasi dengan film `nama_film` beserta nama aplikasi tersebut.
void countRelationFromChild(ListFilm L_film, ListAplikasi L_aplikasi, string nama_film) {
    address_film F = findFilm(L_film, nama_film); // Cari film berdasarkan nama
    if (F == NULL) {
        cout << "Film dengan nama '" << nama_film << "' tidak ditemukan." << endl;
    } else {
        address_aplikasi Q = L_aplikasi.first; // Mulai dari aplikasi pertama
        address_relasi R;

        int count = 0; // Counter untuk jumlah aplikasi
        while (Q != NULL) {
            R = Q->relasi; // Mulai dari daftar relasi aplikasi
            bool found = false; // Indikator untuk menentukan apakah film ditemukan pada aplikasi ini
            while (R != NULL && !found) {
                if (R->film == F) { // Jika film ditemukan di relasi
                    count++;
                    found = true; // Tandai bahwa film ditemukan
                } else {
                    R = R->next; // Lanjut ke relasi berikutnya
                }
            }
            Q = Q->next; // Lanjut ke aplikasi berikutnya
        }

        if (count == 0) {
            cout << "Film '" << nama_film << "' belum dimiliki oleh aplikasi mana pun." << endl;
        } else {
            cout << "=== Daftar aplikasi yang memiliki film '" << nama_film << "' ===" << endl;

            Q = L_aplikasi.first; // Reset ke aplikasi pertama untuk mencetak nama aplikasi
            while (Q != NULL) {
                R = Q->relasi; // Mulai dari daftar relasi aplikasi
                bool found = false; // Indikator untuk menentukan apakah film ditemukan pada aplikasi ini
                while (R != NULL && !found) {
                    if (R->film == F) { // Jika film ditemukan di relasi
                        cout << "   Aplikasi: " << Q->info.nama_aplikasi << endl;
                        found = true; // Tandai bahwa film ditemukan
                    } else {
                        R = R->next; // Lanjut ke relasi berikutnya
                    }
                }
                Q = Q->next; // Lanjut ke aplikasi berikutnya
            }
            cout << "Film ini ada di " << count << " aplikasi." << endl;
        }
    }
    cout << endl;
}


// IS: Diberikan ListFilm `L_film` dan ListAplikasi `L_aplikasi` yang berisi data relasi antara aplikasi dan film.
// FS: Menampilkan film yang tidak memiliki relasi dengan aplikasi mana pun dan total jumlahnya.
void countChildWithoutRelation(ListFilm L_film, ListAplikasi L_aplikasi) {
    address_film F = L_film.first; // Mulai dari film pertama
    int count = 0; // Counter untuk film tanpa relasi

    while (F != NULL) {
        bool hasRelation = false; // Flag untuk cek relasi

        // Iterasi semua aplikasi untuk mencari relasi dengan film ini
        address_aplikasi Q = L_aplikasi.first;
        while (Q != NULL && !hasRelation) {
            address_relasi R = Q->relasi;
            while (R != NULL && !hasRelation) {
                if (R->film == F) { // Jika relasi ditemukan
                    hasRelation = true; // Tandai bahwa relasi ditemukan
                } else {
                    R = R->next; // Lanjut ke relasi berikutnya
                }
            }
            Q = Q->next; // Lanjut ke aplikasi berikutnya jika relasi belum ditemukan
        }

        if (!hasRelation) {
            count++; // Tambahkan counter jika tidak ada relasi
            cout << "Film tanpa relasi: " << F->info_film.nama << endl;
        }

        F = F->next; // Lanjut ke film berikutnya
    }

    cout << "Jumlah film tanpa relasi: " << count << endl;
    cout << endl;
}

// IS: Diberikan referensi ListAplikasi `L_aplikasi`, ListFilm `L_film`, nama aplikasi (`nama_aplikasi`),
//     nama film lama (`nama_film_lama`), dan nama film baru (`nama_film_baru`).
// FS: Relasi antara aplikasi `nama_aplikasi` dan film `nama_film_lama` diubah menjadi `nama_film_baru`.
//     Menampilkan pesan sukses jika relasi berhasil diubah, atau pesan error jika tidak ditemukan.
void editRelation(ListAplikasi &L_aplikasi, ListFilm &L_film, string nama_aplikasi, string nama_film_lama, string nama_film_baru) {
    // Cari aplikasi berdasarkan nama
    address_aplikasi P = findAplikasi(L_aplikasi, nama_aplikasi);
    if (P == NULL) {
        cout << "Aplikasi dengan nama '" << nama_aplikasi << "' tidak ditemukan." << endl;
    } else {
        // Cari film lama dan baru berdasarkan nama
        address_film F_lama = findFilm(L_film, nama_film_lama);
        address_film F_baru = findFilm(L_film, nama_film_baru);

        if (F_lama == NULL) {
            cout << "Film dengan nama '" << nama_film_lama << "' tidak ditemukan." << endl;
        } else if (F_baru == NULL) {
            cout << "Film dengan nama '" << nama_film_baru << "' tidak ditemukan." << endl;
        } else {
            // Cek jika film lama dan baru adalah film yang sama
            if (F_lama == F_baru) {
                cout << "Film yang lama dan baru sama, tidak ada perubahan." << endl;
            } else {
                // Cari relasi di aplikasi yang menghubungkan dengan film lama
                address_relasi R = P->relasi;
                bool relationFound = false; // Indikator apakah relasi ditemukan

                while (R != NULL && relationFound == false) {
                    if (R->film == F_lama) {
                        // Ubah relasi ke film baru
                        R->film = F_baru;
                        cout << "Relasi berhasil diubah: '" << nama_film_lama << "' diganti menjadi '" << nama_film_baru << "' pada aplikasi '" << nama_aplikasi << "'." << endl;
                        relationFound = true;
                    }
                    R = R->next; // Lanjutkan ke relasi berikutnya
                }

                // Jika relasi lama tidak ditemukan
                if (!relationFound) {
                    cout << "Relasi dengan film '" << nama_film_lama << "' pada aplikasi '" << nama_aplikasi << "' tidak ditemukan." << endl;
                }
            }
        }
    }
    cout << endl;
}
//-------------------------------BATAS ACA---------------------------------------------

