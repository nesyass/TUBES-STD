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
    pilih = menu();
    while (pilih != 17){
        if (pilih == 1){
            clearScreen();
            address_aplikasi PA;
            infotype_aplikasi IA;
            cout << "Masukan berapa kali loop ";
            int c;
            cin >> c;
            for (int i = 0; i< c;i++) {
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


            }


            pilih = menu();
        } else if (pilih == 2){
            clearScreen();
            address_film PF;
            infotype_film IF;
            cout << "Masukan berapa kali loop";
            int c;
            cin >> c;
            for (int i = 0; i< c;i++) {
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
            }

            pilih = menu();
        } else if (pilih == 3){
            clearScreen();
            showAllAplikasi(LA);
            cout << endl;
            pilih = menu();
        } else if (pilih == 4){
            clearScreen();
            showAllFilm(LF);
            cout << endl;
            pilih = menu();
        } else if (pilih == 5){
            clearScreen();
            cout << "Nama Aplikasi: ";
            cin >> nama_app;
            cout << "Nama Film: ";
            cin >> nama_film;
            insertRelation(LA, LF, nama_app, nama_film);
            cout << endl;
            pilih = menu();
        } else if (pilih == 6) {
            clearScreen();
            cout << "Nama Aplikasi: ";
            cin >> nama_app;
            showChildFromParent(LA, nama_app);
            pilih = menu();
        } else if (pilih == 7) {
            clearScreen();
            cout << "Nama Film: ";
            cin >> nama_film;
            showParentsFromChild(LF, LA, nama_film);
            pilih = menu();
        } else if (pilih == 8) {
            clearScreen();
            cout << "Nama Aplikasi: ";
            cin >> nama_app;
            deleteAplikasi(LA, LF, nama_app);
            pilih = menu();
        } else if (pilih == 9) {
            clearScreen();
            cout << "Nama Film: ";
            cin >> nama_film;
            deleteFilm(LF, LA, nama_film);
            pilih = menu();
        } else if (pilih == 10) {
            clearScreen();
            cout << "Nama Aplikasi: ";
            cin >> nama_app;
            cout << "Nama Film: ";
            cin >> nama_film;
            deleteRelation(LA, nama_app, nama_film);
            pilih = menu();
        } else if (pilih == 11) {
            clearScreen();
            showChildWithParents(LF,LA);
            pilih = menu();
        } else if (pilih == 12) {
           clearScreen();
            cout << "Nama Film: ";
            cin >> nama_film;
            showParentsFromChild(LF, LA, nama_film);
            pilih = menu();
        } else if (pilih == 13) {
            clearScreen();
            countRelationFromParent(LA);
            pilih = menu();
        } else if (pilih == 14) {
            clearScreen();
            cout << "Nama Film: ";
            cin >> nama_film;
            countRelationFromChild(LF,LA, nama_film);
            pilih = menu();
        } else if(pilih == 15) {
            clearScreen();
            countChildWithoutRelation(LF,LA);
            pilih = menu();
        } else if (pilih == 16) {
            clearScreen();
            cout << "Masukan nama aplikasi";
            cin >> nama_app;
            string nama_film_baru;
            cout << "masukan nama film baru";
            cin >> nama_film_baru;
            cout << "masukan nama film lama";
            cin >> nama_film;
            editRelation(LA,LF,nama_app, nama_film, nama_film_baru);
            pilih = menu();
        }
    }
    if (pilih == 17) {
        cout << "Anda keluar dari program" << endl;
    }
    return 0;
};
