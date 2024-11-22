#include <iostream>
#include <cstdlib>
#include "header.h"
using namespace std;

int main()
{
    ListAplikasi LA;
    ListFilm LF;

    createListAplikasi(LA);
    createListFilm(LF);

    int pilih;
    pilih = menu();
    while (pilih != 9){
        if (pilih == 1){
            clearScreen();
            address_aplikasi PA;
            infotype_aplikasi IA;

            cout << "Nama Aplikasi: ";
            cin >> IA.nama_aplikasi;

            cout << "Kualitas Video dalam Aplikasi: ";
            cin >> IA.kualitas;

            cout << "Rating Aplikasi: ";
            cin >> IA.rating;

            cout << "Harga Langganan Bulanan: ";
            cin >> IA.harga;

            PA = allocateAplikasi(IA);
            insertAplikasi(LA, PA);

            cout << "Aplikasi berhasil di tambahkan!" << endl;
            cout << endl;

            pilih = menu();
        } else if (pilih == 2){
            clearScreen();
            address_film PF;
            infotype_film IF;

            cout << "Nama Film: ";
            cin >> IF.nama;

            cout << "Genre: ";
            cin >> IF.genre;

            cout << "Tahun Rilis: ";
            cin >> IF.tahun;

            cout << "Rating: ";
            cin >> IF.rating;

            PF = allocateFilm(IF);
            insertFilm(LF, PF);

            cout << "Film berhasil di tambahkan!" << endl;
            cout << endl;

            pilih = menu();
        } else if (pilih == 3){
            pilih = menu();
        } else if (pilih == 4){
            pilih = menu();
        } else if (pilih == 5){
            pilih = menu();
        } else if (pilih == 6) {
            pilih = menu();
        } else if (pilih == 7) {
            pilih = menu();
        } else if (pilih == 8) {
            pilih = menu();
        }
    }
    if (pilih == 9) {
        cout << "Anda keluar dari program" << endl;
    }
    return 0;
};
