#include <iostream>
#include <cstdlib>
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

void insertRelation(ListAplikasi &L_aplikasi, ListFilm &L_film, string nama_aplikasi, string nama_film) {
    // Cari aplikasi yang sesuai di dalam ListAplikasi
    address_aplikasi A = findAplikasi(L_aplikasi, nama_aplikasi);

    // Cari film yang sesuai di dalam ListFilm
    address_film F = findFilm(L_film, nama_film);

    // Jika aplikasi dan film ditemukan
    if (A != NULL && F != NULL) {
        // Cek apakah relasi sudah ada
        address_relasi R = A->relasi;
        bool relasiSudahAda = false; // Flag untuk mengecek apakah relasi sudah ada

        while (R != NULL) {
            if (R->film == F) {
                relasiSudahAda = true; // Tandai bahwa relasi sudah ada
                cout << "Film sudah tersedia di aplikasi" << endl;
                break; // Keluar dari loop jika relasi sudah ada
            }
            R = R->next; // Lanjutkan ke relasi berikutnya
        }

        if (!relasiSudahAda) {
            address_relasi newR = new ElmRelasi; // Alokasikan memori untuk objek baru
            newR->film = F;
            newR->next = A->relasi;
            A->relasi = newR;

            cout << "Film dengan judul " << F->info_film.nama << " berhasil ditambahkan ke aplikasi " << nama_aplikasi << endl;
        }
    } else {
        if (A == NULL) {
            cout << "Aplikasi dengan nama " << nama_aplikasi << " tidak ditemukan" << endl;
        }
        if (F == NULL) {
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

int menu(){
    cout << "=== MENU APLIKASI STREAMING ===" << endl;
    cout << "1. Tambah Aplikasi" << endl;
    cout << "2. Tambah Film" << endl;
    cout << "3. Tampilkan Semua Aplikasi" << endl;
    cout << "4. Tampilkan Semua Film" << endl;
    cout << "5. Buat Relasi Aplikasi dengan Film" << endl;
    cout << "6. Menampilkan Daftar Film dari suatu Aplikasi" << endl;
    cout << "7. Menampilkan Daftar Aplikasi yang menyediakan suatu Film" << endl;
    cout << "8. Hapus Aplikasi" << endl;
    cout << "9. Hapus Film" << endl;
    cout << "10. Hapus Relasi" << endl;
    cout << "11. Show data child beserta data parent yang masing masing child miliki " << endl;
    cout << "12. Show data parent yang berelasi dengan child tertentu" << endl;
    cout << "13. Count relation dari setiap element parent" << endl;
    cout << "14. Count relation yang dimiliki oleh child tertentu" << endl;
    cout << "15. Count element child yang tidak memiliki relasi" << endl;
    cout << "16. Edit relasi/mengganti child dari parent tertentu" << endl;
    cout << "17. Keluar" << endl;
    cout << "Masukkan pilihan: ";
    int pilih;
    cin >> pilih;
    return pilih;
};

void clearScreen() {
    if (_WIN32) {
        system("cls"); // untuk Windows
    } else {
        system("clear"); // untuk Linux/Mac
    }
}

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
};

void showAllAplikasi(ListAplikasi L){
    address_aplikasi p;

    p = L.first;
    int i = 1;

    if (p == NULL) {
        cout << "Tidak ada aplikasi dalam list. Silahkan tambahkan aplikasi terlebih dahulu!" << endl;
    }

    cout << "================ DAFTAR APLIKASI ================" << endl;
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
    cout << "=================================================" << endl;
};

void showAllFilm(ListFilm L){
    address_film p;

    p = L.first;
    int i = 1;

    if (p == NULL) {
        cout << "Tidak ada film dalam list. Silahkan tambahkan film terlebih dahulu!" << endl;
    }

    cout << "================== DAFTAR FILM ==================" << endl;
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
    cout << "=================================================" << endl;

};

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
                    cout << "Film tidak valid." << endl;
                }
                r = r->next;
                i++;
            }
            cout << "=========================================" << endl;
        }
    }
}


void showParentWithChild(ListAplikasi L_aplikasi){
    address_aplikasi p;

    p = L_aplikasi.first;
    int i = 1;

    if (p == NULL) {
        cout << "Tidak ada aplikasi dalam list. Silahkan tambahkan aplikasi terlebih dahulu!" << endl;
    }

    cout << "================ DAFTAR APLIKASI ================" << endl;
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
            cout << "   Tidak ada film pada aplikasi" << p->info.nama_aplikasi << "." << endl;
        }

        int j = 1;
        cout << "   === Daftar film pada aplikasi" << p->info.nama_aplikasi << " ===" << endl;
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
        cout << "   ===================================" << endl;
        p = p->next;
        i++;
    }
    cout << "=================================================" << endl;

};
//-------------------------------BATAS LYNA------------------------------------------

void showChildWithParents(ListFilm L_film, ListAplikasi L_aplikasi) {
    address_film P = L_film.first;
    int i = 1;

    if (P == NULL) {
        cout << "Tidak ada film dalam daftar." << endl;
        return;
    }

    while (P != NULL) {
        cout << "   Daftar film ke-" << i << " :" << endl;
        cout << "   Nama Film    : " << P->info_film.nama << endl;
        cout << "   Genre        : " << P->info_film.genre << endl;
        cout << "   Tahun        : " << P->info_film.tahun << endl;
        cout << "   Rating       : " << P->info_film.rating << endl;
        cout << "   Dimiliki oleh aplikasi: ";

        bool found = false;
        address_aplikasi Q = L_aplikasi.first;

        while (Q != NULL) {
            address_relasi R = Q->relasi;
            while (R != NULL) {
                if (R->film == P) {
                    cout << Q->info.nama_aplikasi << " ";
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
};

void showParentsFromChild(ListFilm L_film, ListAplikasi L_aplikasi, string nama_film) {
 address_film F = findFilm(L_film, nama_film); // Cari film berdasarkan nama
    if (F == NULL) {
        cout << "Film dengan nama '" << nama_film << "' tidak ditemukan." << endl;
        return;
    }

    cout << "=== Daftar aplikasi yang memiliki film '" << nama_film << "' ===" << endl;

    address_aplikasi Q = L_aplikasi.first; // Mulai dari aplikasi pertama
    address_relasi R;
    int i = 1;
    bool found = false;

    while (Q != NULL) {
        R = Q->relasi; // Mulai dari daftar relasi aplikasi
        while (R != NULL) {
            if (R->film == F) { // Jika film ditemukan di relasi
                cout << "Aplikasi ke-" << i << " :" << endl;
                cout << "Nama Aplikasi : " << Q->info.nama_aplikasi << endl;
                cout << endl;
                found = true;
                i++;
                break; // Tidak perlu memeriksa relasi lain pada aplikasi ini
            }
            R = R->next; // Lanjut ke relasi berikutnya
        }
        Q = Q->next; // Lanjut ke aplikasi berikutnya
    }

    if (!found) {
        cout << "Film '" << nama_film << "' belum dimiliki oleh aplikasi mana pun." << endl;
    }

    cout << "=========================================" << endl;
};

void countRelationFromParent(ListAplikasi L_aplikasi) {
     address_aplikasi P = L_aplikasi.first;


    if (P == NULL) {
        cout << "Tidak ada film dalam daftar." << endl;
        return;
    }

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
void countRelationFromChild(ListFilm L_film, ListAplikasi L_aplikasi, string nama_film) {
    address_film F = findFilm(L_film, nama_film); // Cari film berdasarkan nama
    if (F == NULL) {
        cout << "Film dengan nama '" << nama_film << "' tidak ditemukan." << endl;
        return;
    }

    cout << "=== Daftar aplikasi yang memiliki film '" << nama_film << "' ===" << endl;

    address_aplikasi Q = L_aplikasi.first; // Mulai dari aplikasi pertama
    address_relasi R;

    int count = 0; // Counter untuk jumlah aplikasi
    while (Q != NULL) {
        R = Q->relasi; // Mulai dari daftar relasi aplikasi
        while (R != NULL) {
            if (R->film == F) { // Jika film ditemukan di relasi
                count++;
                cout << "   Aplikasi: " << Q->info.nama_aplikasi << endl;
                break; // Tidak perlu memeriksa relasi lain pada aplikasi ini
            }
            R = R->next; // Lanjut ke relasi berikutnya
        }
        Q = Q->next; // Lanjut ke aplikasi berikutnya
    }

    if (count == 0) {
        cout << "Film '" << nama_film << "' belum dimiliki oleh aplikasi mana pun." << endl;
    } else {
        cout << "Film ini ada di " << count << " aplikasi." << endl;
    }

    cout << "=========================================" << endl;
}


void countChildWithoutRelation(ListFilm L_film, ListAplikasi L_aplikasi) {
     address_film F = L_film.first; // Mulai dari film pertama
    int count = 0; // Counter untuk film tanpa relasi

    while (F != NULL) {
        bool hasRelation = false; // Flag untuk cek relasi

        // Iterasi semua aplikasi untuk mencari relasi dengan film ini
        address_aplikasi Q = L_aplikasi.first;
        while (Q != NULL) {
            address_relasi R = Q->relasi;
            while (R != NULL) {
                if (R->film == F) { // Jika relasi ditemukan
                    hasRelation = true;
                    break; // Keluar dari loop relasi
                }
                R = R->next; // Lanjut ke relasi berikutnya
            }
            if (hasRelation) break; // Keluar dari loop aplikasi jika sudah ditemukan
            Q = Q->next; // Lanjut ke aplikasi berikutnya
        }

        if (!hasRelation) {
            count++; // Tambahkan counter jika tidak ada relasi
            cout << "Film tanpa relasi: " << F->info_film.nama << endl;
        }

        F = F->next; // Lanjut ke film berikutnya
    }

    cout << "Jumlah film tanpa relasi: " << count << endl;
    cout << "=========================================" << endl;
}

void editRelation(ListAplikasi &L_aplikasi, ListFilm &L_film, string nama_aplikasi, string nama_film_lama, string nama_film_baru) {
    // Cari parent (aplikasi) berdasarkan nama
    address_aplikasi P = findAplikasi(L_aplikasi, nama_aplikasi);
    if (P == NULL) {
        cout << "Aplikasi dengan nama '" << nama_aplikasi << "' tidak ditemukan." << endl;
        return;
    }

    // Cari child lama dan child baru berdasarkan nama
    address_film F_lama = findFilm(L_film, nama_film_lama);
    address_film F_baru = findFilm(L_film, nama_film_baru);

    if (F_lama == NULL) {
        cout << "Film dengan nama '" << nama_film_lama << "' tidak ditemukan." << endl;
        return;
    }

    if (F_baru == NULL) {
        cout << "Film dengan nama '" << nama_film_baru << "' tidak ditemukan." << endl;
        return;
    }

    // Cari relasi di parent (aplikasi) yang menghubungkan dengan child lama
    address_relasi R = P->relasi;
    while (R != NULL) {
        if (R->film == F_lama) {
            // Ubah relasi ke child baru
            R->film = F_baru;
            cout << "Relasi berhasil diubah: '" << nama_film_lama << "' diganti menjadi '" << nama_film_baru << "' pada aplikasi '" << nama_aplikasi << "'." << endl;
            return;
        }
        R = R->next; // Lanjut ke relasi berikutnya
    }

    // Jika relasi lama tidak ditemukan
    cout << "Relasi dengan film '" << nama_film_lama << "' pada aplikasi '" << nama_aplikasi << "' tidak ditemukan." << endl;
}



//-------------------------------BATAS ACA---------------------------------------------

