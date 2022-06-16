#include <iostream>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

string nazwaPliku = "KsiazkaAdresowa";

struct Adresat {
    int id = 0, idUzytkownika = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};


int wczytajLiczbeCalkowita();
char wczytajZnak();
string wczytajLinie();
string konwersjaIntNaString();

int wczytajOsobyZPliku(vector <Adresat> &adresaci, int &idUzytkownika);
void dodajOsobe(vector <Adresat> &adresaci, int &idUzytkownika, int &ileRekordow);
void wyszukajPoImieniu(vector <Adresat> &adresaci);
void wyszukajPoNazwisku(vector <Adresat> &adresaci);
void wyswietlWszystkieOsoby(vector <Adresat> &adresaci);
void usunAdresata(vector <Adresat> &adresaci);
void edytujAdresata(vector <Adresat> &adresaci);
Adresat wyodrebnianieAdresata(Adresat &adresat, int &kolejnePoleObiektuAdresat, string &wyodrebnioneDaneAdresata);
string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst);
void aktualizujKsiazkePoDodaniuAdresata(vector <Adresat> &adresaci, int &ileRekordow);
void aktualizujKsiazkePoUsunieciuAdresata(int &wybraneId);
void aktualizujKsiazkePoEdycjiAdresata(vector <Adresat> &adresaci, int &wybraneId, vector<Adresat>::iterator &itr);

Uzytkownik wyodrebnianieUzytkownika(Uzytkownik &uzytkownik, int &kolejnePoleObiektuUzytkownik, string &wyodrebnioneDaneUzytkownik);
void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy);
void aktualizujBazeUzytkownikow(vector <Uzytkownik> &uzytkownicy);
void rejestracjaUzytkownika(vector<Uzytkownik> &uzytkownicy);
int logowanie(vector<Uzytkownik> &uzytkownicy);
void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int &idUzytkownika);


int main() {
    int idUzytkownika = 0, ileRekordow = 0;
    char wybor;

    while (true) {

        vector <Uzytkownik> uzytkownicy;
        wczytajUzytkownikowZPliku(uzytkownicy);

        if (idUzytkownika == 0) {

            system("cls");

            cout << "     >>> MENU GLOWNE <<<     " << endl;
            cout << "-----------------------------" << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz" << endl;
            cout << "-----------------------------" << endl;
            cout << "Wybierz co chcesz zrobic: ";

            wybor = wczytajZnak();

            switch (wybor) {
            case '1':
                rejestracjaUzytkownika(uzytkownicy);
                break;
            case '2':
                idUzytkownika = logowanie(uzytkownicy);
                break;
            case '9':
                exit(0);
                break;
            default:
                cout << endl << "Nie ma takiej opcji w menu!" << endl << endl;
                system("pause");
                break;
            }
        } else {

            vector <Adresat> adresaci;
            ileRekordow =  wczytajOsobyZPliku(adresaci, idUzytkownika);

            system("cls");

            cout << "|----- MENU UZYTKOWNIKA -----|" << endl << endl;

            cout << "1. Dodaj osobe" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich znajomych" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "-----------------------------" << endl;
            cout << "7. Zmiana hasla" << endl;
            cout << "8. Wylogowanie" << endl;
            cout << "-----------------------------" << endl;

            cout << "Wybierz co chcesz zrobic: ";
            wybor = wczytajZnak();

            switch (wybor) {
            case '1':
                dodajOsobe(adresaci, idUzytkownika, ileRekordow);
                break;
            case '2':
                wyszukajPoImieniu(adresaci);
                break;
            case '3':
                wyszukajPoNazwisku(adresaci);
                break;
            case '4':
                wyswietlWszystkieOsoby(adresaci);
                break;
            case '5':
                usunAdresata(adresaci);
                break;
            case '6':
                edytujAdresata(adresaci);
                break;
            case '7':
                zmianaHasla(uzytkownicy, idUzytkownika);
                break;
            case '8':
                idUzytkownika = 0;
                break;
            default:
                cout << endl << "Nie ma takiej opcji w menu!" << endl << endl;
                system("pause");
                break;
            }
        }
    }

    return 0;
}


string wczytajLinie() {
    string wejscie = "";
    getline(cin,wejscie);
    return wejscie;
}

char wczytajZnak() {
    string wejscie = "";
    char znak = {0};

    while (true) {
        getline(cin, wejscie);

        if(wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie. ";
    }
    return znak;
}

int wczytajLiczbeCalkowita() {
    string wejscie = "";
    int liczba = 0;

    while (true) {
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba) {
            break;
        }
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;

    }
    return liczba;
}

string konwersjaIntNaString(int liczba) {
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}


Adresat wyodrebnianieAdresata(Adresat &adresat, int &kolejnePoleObiektuAdresat, string &wyodrebnioneDaneAdresata) {

    switch (kolejnePoleObiektuAdresat) {
    case 1:
        adresat.id = atoi(wyodrebnioneDaneAdresata.c_str());
        break;
    case 2:
        adresat.idUzytkownika = atoi(wyodrebnioneDaneAdresata.c_str());
        break;
    case 3:
        adresat.imie = wyodrebnioneDaneAdresata;
        break;
    case 4:
        adresat.nazwisko = wyodrebnioneDaneAdresata;
        break;
    case 5:
        adresat.numerTelefonu = wyodrebnioneDaneAdresata;
        break;
    case 6:
        adresat.email = wyodrebnioneDaneAdresata;
        break;
    case 7:
        adresat.adres = wyodrebnioneDaneAdresata;
        break;
    }
    return adresat;
}

int wczytajOsobyZPliku(vector <Adresat> &adresaci, int &idUzytkownika) {

    Adresat adresat;
    int numerLini = 1;
    int dlugoscWczytanejLinii;
    int kolejnePoleObiektuAdresat;
    int poczatek;
    int ostatniRecord = 0;
    string linia;
    string wyodrebnioneDaneAdresata;

    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Ksiazka_adresowa.txt",ios::in);

    if(ksiazkaAdresowa.good()) {

        while(getline(ksiazkaAdresowa,linia)) {

            dlugoscWczytanejLinii = linia.length();
            kolejnePoleObiektuAdresat = 0;
            poczatek = 0;

            for (int i = 0; i < dlugoscWczytanejLinii; i++) {

                if(linia[i] == '|') {

                    wyodrebnioneDaneAdresata = linia.substr (poczatek,(i - poczatek));
                    kolejnePoleObiektuAdresat++;

                    adresat = wyodrebnianieAdresata(adresat, kolejnePoleObiektuAdresat, wyodrebnioneDaneAdresata);

                    poczatek = i + 1;
                }
            }

            if(adresat.idUzytkownika == idUzytkownika) {
                adresaci.push_back(adresat);
            }
            if(adresat.id > ostatniRecord) {
                ostatniRecord = adresat.id;
            }
            numerLini++;
        }

        ksiazkaAdresowa.close();
    }

    return ostatniRecord;
}

void dodajOsobe(vector <Adresat> &adresaci, int &idUzytkownika, int &ileRekordow) {

    Adresat adresat;
    system("cls");

    cout << "|----- Dodaj nowego adresata -----|" << endl << endl;

    ileRekordow++;
    adresat.id = ileRekordow;

    adresat.idUzytkownika = idUzytkownika;
    cout << "Podaj imie: ";
    adresat.imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    adresat.nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu: ";
    adresat.numerTelefonu = wczytajLinie();
    cout << "Podaj e-mail: ";
    adresat.email = wczytajLinie();
    cout << "Podaj adres: ";
    adresat.adres = wczytajLinie();


    adresaci.push_back(adresat);

    aktualizujKsiazkePoDodaniuAdresata(adresaci, ileRekordow);

    cout << endl << "Adresat dodany." << endl;
    system("pause");

}

void wyszukajPoImieniu(vector <Adresat> &adresaci) {
    int ileOsob = 0;
    string imie = "";
    string odmianaKoncowkiSlowaOsoba = "osob";

    system("cls");

    cout << "|----- Wyszukaj adresata po imieniu -----|" << endl << endl;

    cout << "Podaj imie osoby ktora chcesz odnalezc: ";
    imie = wczytajLinie();

    for (auto itr = adresaci.begin(); itr != adresaci.end(); itr++) {
        if (itr -> imie == imie) {

            cout << endl << "Id: " << itr -> id << endl;
            cout << "Imie: " << itr -> imie << endl;
            cout << "Nazwisko: " << itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Adres e-mail: " << itr -> email << endl;
            cout << "Adres: " << itr -> adres << endl;

            ileOsob++;

        }
    }

    if (ileOsob == 1) {
        odmianaKoncowkiSlowaOsoba = "osobe";
    }
    if (ileOsob >= 2 && ileOsob <= 4) {
        odmianaKoncowkiSlowaOsoba = "osoby";
    }

    cout << endl << "Odnaleziono " << ileOsob << " " << odmianaKoncowkiSlowaOsoba << " o imieniu " << imie << endl << endl;
    system("pause");
}

void wyszukajPoNazwisku(vector <Adresat> &adresaci) {
    int ileOsob = 0;
    string szukaneNazwisko = "";
    string odmianaKoncowkiSlowaOsoba = "osob";

    system("cls");

    cout << "|----- Wyszukaj adresata po imieniu -----|" << endl << endl;

    cout << "Podaj nazwisko osoby ktora chcesz odnalezc: ";
    szukaneNazwisko = wczytajLinie();

    for (auto itr = adresaci.begin(); itr != adresaci.end(); itr++) {
        if (itr -> nazwisko == szukaneNazwisko) {

            cout << endl << "Id: " << itr -> id << endl;
            cout << "Imie: " << itr -> imie << endl;
            cout << "Nazwisko: " << itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Adres e-mail: " << itr -> email << endl;
            cout << "Adres: " << itr -> adres << endl;

            ileOsob++;

        }
    }

    if (ileOsob == 1) {
        odmianaKoncowkiSlowaOsoba = "osobe";
    }
    if (ileOsob >= 2 && ileOsob <= 4) {
        odmianaKoncowkiSlowaOsoba = "osoby";
    }

    cout << endl << "Odnaleziono " << ileOsob << " " <<odmianaKoncowkiSlowaOsoba << " o nazwisku " << szukaneNazwisko << endl << endl;
    system("pause");
}

void aktualizujKsiazkePoDodaniuAdresata(vector <Adresat> &adresaci, int &ileRekordow) {

    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Ksiazka_adresowa.txt", ios::out | ios::app);

    auto itr = adresaci.end() - 1;

    ksiazkaAdresowa << konwersjaIntNaString(itr -> id)<< "|" << itr -> idUzytkownika << "|";
    ksiazkaAdresowa << itr -> imie << "|" << itr -> nazwisko << "|" << itr -> numerTelefonu;
    ksiazkaAdresowa << "|" << itr -> email << "|" << itr -> adres << "|" << endl ;
    ksiazkaAdresowa.close();
}

void usunAdresata(vector <Adresat> &adresaci) {

    int wybraneId;
    char potwierdzenieUsuniecia;
    bool czyIstniejeAdresat = false;

    system("cls");

    if (!adresaci.empty()) {
        cout << "|----- Usun adresata -----|" << endl << endl;

        cout << "Podaj numer ID adresata ktorego chcesz usunac: ";

        wybraneId = wczytajLiczbeCalkowita();

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if(itr -> id == wybraneId) {

                czyIstniejeAdresat = true;
                cout << endl << endl << "Potwierdz wybor naciskajac 't': ";

                potwierdzenieUsuniecia = wczytajZnak();

                if(potwierdzenieUsuniecia == 't') {
                    adresaci.erase(itr);

                    aktualizujKsiazkePoUsunieciuAdresata(wybraneId);

                    cout << endl << "Adresat usuniety" << endl;
                    break;

                } else {
                    cout << endl << "Wybrales inny znak, usuwanie anulowane." << endl;
                    break;
                }
            }
        }
        if (czyIstniejeAdresat == false) {
            cout << endl << "Nie ma takiego adresata w ksiazce adresowej" << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    system("pause");
}

void aktualizujKsiazkePoUsunieciuAdresata(int &wybraneId) {

    Adresat adresat;
    int numerLini = 1;
    int dlugoscWczytanejLinii;
    int kolejnePoleObiektuAdresat;
    int poczatek;
    string linia;
    string wyodrebnioneDaneAdresata;
    fstream ksiazkaAdresowa;
    fstream ksiazkaAdresowaTemp;
    ksiazkaAdresowa.open("Ksiazka_adresowa.txt", ios::in);
    ksiazkaAdresowaTemp.open("Ksiazka_adresowa_temp.txt", ios::out);

    if(ksiazkaAdresowa.good()) {

        while(getline(ksiazkaAdresowa,linia)) {

            dlugoscWczytanejLinii = linia.length();
            kolejnePoleObiektuAdresat = 0;
            poczatek = 0;

            for (int i = 0; i < dlugoscWczytanejLinii; i++) {

                if(linia[i] == '|') {

                    wyodrebnioneDaneAdresata = linia.substr (poczatek,(i - poczatek));
                    kolejnePoleObiektuAdresat++;

                    adresat = wyodrebnianieAdresata(adresat, kolejnePoleObiektuAdresat, wyodrebnioneDaneAdresata);

                    poczatek = i + 1;
                }
            }
            if (adresat.id == wybraneId) {
                continue;
            } else {
                ksiazkaAdresowaTemp << linia << endl;
            }
            numerLini++;
        }

        ksiazkaAdresowa.close();
        ksiazkaAdresowaTemp.close();
        remove("Ksiazka_adresowa.txt");
        rename("Ksiazka_adresowa_temp.txt", "Ksiazka_adresowa.txt");
    }
}

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst) {
    if (!tekst.empty()) {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

void edytujAdresata(vector <Adresat> &adresaci) {
    int wybraneId = 0;
    char wybraneDane;
    bool czyIstniejeAdresat = false;
    string daneDoZmiany;

    system("cls");

    if (!adresaci.empty()) {

        cout << "|----- Edytuj dane adresata -----|" << endl << endl;

        cout << "Podaj numer ID adresata ktorego chcesz edytowac: ";

        wybraneId = wczytajLiczbeCalkowita();

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if(itr->id == wybraneId) {

                czyIstniejeAdresat = true;

                cout << endl << "Ktore dane zaktualizowac: " << endl;
                cout << "1 - Imie" << endl;
                cout << "2 - Nazwisko" << endl;
                cout << "3 - Numer telefonu" << endl;
                cout << "4 - Email" << endl;
                cout << "5 - Adres" << endl;
                cout << "6 - Powrot" << endl;

                cout << endl << "Wybierz 1-6: ";

                wybraneDane = wczytajZnak();

                switch (wybraneDane) {
                case '1':
                    cout << "Podaj nowe imie: ";
                    itr->imie = wczytajLinie();
                    itr->imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->imie);
                    aktualizujKsiazkePoEdycjiAdresata(adresaci, wybraneId, itr);
                    cout << endl << "Imie zostalo zmienione" << endl;
                    break;

                case '2':
                    cout << "Podaj nowe nazwisko: ";
                    itr->nazwisko = wczytajLinie();
                    itr->nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->nazwisko);
                    aktualizujKsiazkePoEdycjiAdresata(adresaci, wybraneId, itr);
                    cout <<  endl << "Nazwisko zostalo zmienione" << endl;
                    break;
                case '3':
                    cout << "Podaj nowy numer telefonu: ";
                    itr->numerTelefonu = wczytajLinie();
                    aktualizujKsiazkePoEdycjiAdresata(adresaci, wybraneId, itr);
                    cout <<  endl << "Numer telefonu zostal zmieniony" << endl;
                    break;
                case '4':
                    cout << "Podaj nowy Email: ";
                    itr->email = wczytajLinie();
                    aktualizujKsiazkePoEdycjiAdresata(adresaci, wybraneId, itr);
                    cout <<  endl << "Email zostal zmieniony" << endl;
                    break;
                case '5':
                    cout << "Podaj nowy adres: ";
                    itr->adres = wczytajLinie();
                    aktualizujKsiazkePoEdycjiAdresata(adresaci, wybraneId, itr);
                    cout <<  endl << "Adres zostal zmieniony" << endl;
                    break;
                case '6':
                    cout << endl << "Powrot do menu glownego" << endl << endl;
                    break;
                default:
                    cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                    break;
                }
            }
        }
        if (czyIstniejeAdresat == false) {
            cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

void aktualizujKsiazkePoEdycjiAdresata(vector <Adresat> &adresaci, int &wybraneId, vector<Adresat>::iterator &itr) {

    Adresat adresat;
    int numerLini = 1;
    int dlugoscWczytanejLinii;
    int kolejnePoleObiektuAdresat;
    int poczatek;
    string linia;
    string wyodrebnioneDaneAdresata;
    fstream ksiazkaAdresowa;
    fstream ksiazkaAdresowaTemp;
    ksiazkaAdresowa.open("Ksiazka_adresowa.txt", ios::in);
    ksiazkaAdresowaTemp.open("Ksiazka_adresowa_temp.txt", ios::out);

    if(ksiazkaAdresowa.good()) {

        while(getline(ksiazkaAdresowa,linia)) {

            dlugoscWczytanejLinii = linia.length();
            kolejnePoleObiektuAdresat = 0;
            poczatek = 0;

            for (int i = 0; i < dlugoscWczytanejLinii; i++) {

                if(linia[i] == '|') {

                    wyodrebnioneDaneAdresata = linia.substr (poczatek,(i - poczatek));
                    kolejnePoleObiektuAdresat++;

                    adresat = wyodrebnianieAdresata(adresat, kolejnePoleObiektuAdresat, wyodrebnioneDaneAdresata);

                    poczatek = i + 1;

                }
            }
            if (adresat.id == wybraneId) {

                ksiazkaAdresowaTemp << konwersjaIntNaString(itr -> id)<< "|" << itr -> idUzytkownika << "|";
                ksiazkaAdresowaTemp << itr -> imie << "|" << itr -> nazwisko << "|" << itr -> numerTelefonu;
                ksiazkaAdresowaTemp << "|" << itr -> email << "|" << itr -> adres << "|" << endl ;
            } else {

                ksiazkaAdresowaTemp << linia << endl;
            }
            numerLini++;
        }

    }
    ksiazkaAdresowa.close();
    ksiazkaAdresowaTemp.close();
    remove("Ksiazka_adresowa.txt");
    rename("Ksiazka_adresowa_temp.txt", "Ksiazka_adresowa.txt");
}

void wyswietlWszystkieOsoby(vector <Adresat> &adresaci) {
    system("cls");

    cout << "|----- Wyswietl ksiazke adresowa -----|" << endl << endl;

    if (adresaci.size() == 0) {
        cout << endl << "Ksiazka adresowa jest pusta."<< endl;
    } else {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {

            cout << endl << "Id: " << itr -> id << endl;
            cout << "Imie: " << itr -> imie << endl;
            cout << "Nazwisko: " << itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Adres e-mail: " << itr -> email << endl;
            cout << "Adres: " << itr -> adres << endl;

        }
    }

    cout << endl;
    system("pause");
}


Uzytkownik wyodrebnianieUzytkownika(Uzytkownik &uzytkownik, int &kolejnePoleObiektuUzytkownik, string &wyodrebnioneDaneUzytkownika) {

    switch (kolejnePoleObiektuUzytkownik) {
    case 1:
        uzytkownik.id = atoi(wyodrebnioneDaneUzytkownika.c_str());
        break;
    case 2:
        uzytkownik.nazwa = wyodrebnioneDaneUzytkownika;
        break;
    case 3:
        uzytkownik.haslo = wyodrebnioneDaneUzytkownika;
        break;
    }
    return uzytkownik;
}

void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy) {

    Uzytkownik uzytkownik;
    int numerLini = 1;
    int dlugoscWczytanejLinii;
    int kolejnePoleObiektuUzytkownik;
    int poczatek;
    string linia;
    string wyodrebnioneDaneUzytkownika;

    fstream bazaUzytkownikow;
    bazaUzytkownikow.open("Uzytkownicy.txt",ios::in);

    if(bazaUzytkownikow.good() == true) {

        while(getline(bazaUzytkownikow,linia)) {

            dlugoscWczytanejLinii = linia.length();
            kolejnePoleObiektuUzytkownik = 0;
            poczatek = 0;

            for (int i = 0; i < dlugoscWczytanejLinii; i++) {

                if(linia[i] == '|') {

                    wyodrebnioneDaneUzytkownika = linia.substr (poczatek,(i - poczatek));
                    kolejnePoleObiektuUzytkownik++;

                    uzytkownik = wyodrebnianieUzytkownika(uzytkownik, kolejnePoleObiektuUzytkownik, wyodrebnioneDaneUzytkownika);

                    poczatek = i + 1;
                }
            }

            uzytkownicy.push_back(uzytkownik);
            numerLini++;
        }
        bazaUzytkownikow.close();
    }
}

void aktualizujBazeUzytkownikow(vector <Uzytkownik> &uzytkownicy) {
    fstream bazaUzytkownikow;
    bazaUzytkownikow.open("temp.txt", ios::out);

    for(auto itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        bazaUzytkownikow << konwersjaIntNaString(itr -> id)<< "|" << itr -> nazwa << "|" << itr -> haslo << "|" << endl;
    }

    bazaUzytkownikow.close();
    remove("Uzytkownicy.txt");
    rename("temp.txt", "Uzytkownicy.txt");
}

void rejestracjaUzytkownika(vector<Uzytkownik> &uzytkownicy) {

    Uzytkownik uzytkownik;
    string nazwa, haslo;
    auto itr = uzytkownicy.begin();

    cout << endl << "Podaj nazwe uzytkownika: ";
    nazwa = wczytajLinie();

    while (itr < uzytkownicy.end()) {
        if (itr -> nazwa == nazwa) {

            cout << "Taki uzytkownik istnieje.Wpisz inna nazwe uzytkownika: ";
            nazwa = wczytajLinie();
            itr = uzytkownicy.begin();

        } else {
            itr++;
        }
    }

    if(uzytkownicy.empty()) {
        uzytkownik.id = 1;
    } else {
        uzytkownik.id = uzytkownicy.back().id + 1;
    }

    cout << "Podaj haslo: ";
    haslo = wczytajLinie();

    uzytkownik.nazwa = nazwa;
    uzytkownik.haslo = haslo;
    uzytkownicy.push_back(uzytkownik);
    aktualizujBazeUzytkownikow(uzytkownicy);

    cout << "Konto zalozone";
    Sleep(1000);
}

int logowanie(vector<Uzytkownik> &uzytkownicy) {

    string nazwa, haslo;
    auto itr = uzytkownicy.begin();

    cout << endl << "Podaj login: ";
    nazwa = wczytajLinie();

    while (itr < uzytkownicy.end()) {
        if (itr -> nazwa == nazwa) {

            for (int proby = 0; proby < 3; proby++) {

                cout << "Podaj haslo. Pozostalo prob " << 3 - proby << ": ";
                haslo = wczytajLinie();

                if (itr -> haslo == haslo) {

                    cout << "Zalogowales sie." << endl;
                    return itr -> id;

                }
            }
            cout << "Podales 3 razy bledne haslo. Powrot do Menu glownego." << endl;
            Sleep(3000);
            return 0;
        }
        itr++;
    }
    cout << "Nie ma uzytkownika z takim loginem. Powrot do Menu glownego." << endl;
    Sleep(1500);
    return 0;
}

void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int &idUzytkownika) {

    Uzytkownik uzytkownik;
    string haslo;

    cout << endl << "Podaj nowe haslo: ";
    haslo = wczytajLinie();

    for (auto itr = uzytkownicy.begin(); itr <= uzytkownicy.end(); itr++) {
        if (itr -> id == idUzytkownika) {

            itr -> haslo = haslo;
        }
    }

    aktualizujBazeUzytkownikow(uzytkownicy);
    cout << "Haslo zostalo zmienione";
    Sleep(1500);
}

