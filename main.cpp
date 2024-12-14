#include <iostream>
#include <cstdlib>
#include "header.h"
using namespace std;

int main()
{
    ListAplikasi LA;
    ListFilm LF;
    string nama_app, nama_film;

    createListAplikasi(LA);
    createListFilm(LF);

    int pilih;
    menu();
    cin >> pilih;

    while (pilih >= 1 && pilih < 17) {
        clearScreen();
        cout << "=================================================================" << endl;
        cout << "                            MENU AKTIF                " << endl;
        cout << "=================================================================" << endl;
        if (pilih == 1) {
            cout << ">>> Tambah Aplikasi <<<" << endl;
            address_aplikasi PA;
            infotype_aplikasi IA;
            cout << "Masukkan jumlah aplikasi yang ingin ditambahkan: ";
            int c;
            cin >> c;
            for (int i = 0; i < c; i++) {
                cout << endl;
                cout << "Nama Aplikasi: ";
                IA.nama_aplikasi = inputanKalimat();
                // Cek apakah aplikasi sudah ada
                if (findAplikasi(LA, IA.nama_aplikasi) != NULL) {
                    cout << "Aplikasi dengan nama \"" << IA.nama_aplikasi << "\" sudah ada. Tidak dapat ditambahkan lagi." << endl;
                } else {
                    cout << "Kualitas Video dalam Aplikasi: ";
                    cin >> IA.kualitas;

                    cout << "Rating Aplikasi: ";
                    cin >> IA.rating;

                    cout << "Harga Langganan Bulanan: ";
                    cin >> IA.harga;

                    PA = allocateAplikasi(IA);
                    insertAplikasi(LA, PA);
                    cout << endl;
                    cout << ">> Aplikasi berhasil ditambahkan!" << endl;
                }
            }
            cout << endl;
            menu();
            cin >> pilih;
        } else if (pilih == 2) {
            cout << ">>> Tambah Film <<<" << endl;
            address_film PF;
            infotype_film IF;
            cout << "Masukkan jumlah film yang ingin ditambahkan: ";
            int c;
            cin >> c;
            for (int i = 0; i < c; i++) {
                cout << endl;
                cout << "Nama Film: ";
                IF.nama = inputanKalimat();
                // Cek apakah film sudah ada
                if (findFilm(LF, IF.nama) != NULL) {
                    cout << "Film dengan nama \"" << IF.nama << "\" sudah ada. Tidak dapat ditambahkan lagi." << endl;
                } else {
                    cout << "Genre: ";
                    cin >> IF.genre;
                    cout << "Tahun Rilis: ";
                    cin >> IF.tahun;
                    cout << "Rating: ";
                    cin >> IF.rating;
                    PF = allocateFilm(IF);
                    insertFilm(LF, PF);
                    cout << endl;
                    cout << ">> Film berhasil ditambahkan!" << endl << endl;
                }
            }
            menu();
            cin >> pilih;
        } else if (pilih == 3) {
            cout << ">>> Tampilkan Semua Aplikasi <<<" << endl;
            showAllAplikasi(LA);
            menu();
            cin >> pilih;

        } else if (pilih == 4) {
            cout << ">>> Tampilkan Semua Film <<<" << endl;
            showAllFilm(LF);
            menu();
            cin >> pilih;

        } else if (pilih == 5) {
            cout << ">>> Buat Relasi Aplikasi dengan Film <<<" << endl;
            cout << "Nama Aplikasi: ";
            cin >> nama_app;
            cout << "Nama Film: ";
            cin >> nama_film;
            insertRelation(LA, LF, nama_app, nama_film);
            menu();
            cin >> pilih;

        } else if (pilih == 6) {
            cout << ">>> Tampilkan Daftar Film dari Aplikasi <<<" << endl;
            cout << "Nama Aplikasi: ";
            cin >> nama_app;
            cout << endl;
            showChildFromParent(LA, nama_app);
            menu();
            cin >> pilih;

        } else if (pilih == 7) {
            cout << ">>> Tampilkan Daftar Aplikasi dari Film <<<" << endl;
            cout << "Nama Film: ";
            cin >> nama_film;
            cout << endl;
            showParentsFromChild(LF, LA, nama_film);
            menu();
            cin >> pilih;

        } else if (pilih == 8) {
            cout << ">>> Hapus Aplikasi <<<" << endl;
            cout << "Nama Aplikasi: ";
            cin >> nama_app;
            deleteAplikasi(LA, LF, nama_app);
            menu();
            cin >> pilih;

        } else if (pilih == 9) {
            cout << ">>> Hapus Film <<<" << endl;
            cout << "Nama Film: ";
            cin >> nama_film;
            deleteFilm(LF, LA, nama_film);
            menu();
            cin >> pilih;

        } else if (pilih == 10) {
            cout << ">>> Hapus Relasi <<<" << endl;
            cout << "Nama Aplikasi: ";
            cin >> nama_app;
            cout << "Nama Film: ";
            cin >> nama_film;
            deleteRelation(LA, nama_app, nama_film);
            menu();
            cin >> pilih;

        } else if (pilih == 11) {
            cout << ">>> Show Data Film dan Aplikasi <<<" << endl;
            showChildWithParents(LF, LA); //tampilan kalo kosong masih jelek
            menu();
            cin >> pilih;

        } else if (pilih == 12) {
            cout << ">>> Show Data Aplikasi dengan Film <<<" << endl;
            showParentWithChild(LA);
            menu();
            cin >> pilih;

        } else if (pilih == 13) {
            cout << ">>> Hitung Relasi dari Aplikasi <<<" << endl;
            countRelationFromParent(LA);
            menu();
            cin >> pilih;

        } else if (pilih == 14) {
            cout << ">>> Hitung Relasi dari Film <<<" << endl;
            cout << "Nama Film: ";
            cin >> nama_film;
            countRelationFromChild(LF, LA, nama_film);
            menu();
            cin >> pilih;

        } else if (pilih == 15) {
            cout << ">>> Hitung Film Tanpa Relasi <<<" << endl;
            countChildWithoutRelation(LF, LA);
            menu();
            cin >> pilih;

        } else if (pilih == 16) {
            cout << ">>> Edit Relasi Aplikasi <<<" << endl;
            cout << "Nama Aplikasi: ";
            cin >> nama_app;
            string nama_film_baru;
            cout << "Nama Film Baru: ";
            cin >> nama_film_baru;
            cout << "Nama Film Lama: ";
            cin >> nama_film;
            editRelation(LA, LF, nama_app, nama_film, nama_film_baru);
            menu();
            cin >> pilih;
        }
    }

    if (pilih >= 17 || pilih <= 0) {
        clearScreen();
        cout << "=================================================================" << endl;
        cout << "                     ANDA KELAR DARI PROGRAM          " << endl;
        cout << "=================================================================" << endl;
    }

    return 0;
}
