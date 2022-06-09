#include <iostream>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

string nazwaPliku = "KsiazkaAdresowa";

struct Adresat {
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

int wczytajOsobyZPliku(vector <Adresat> &adresaci);
int wczytajLiczbeCalkowita();
int dodajOsobe(vector <Adresat> &adresaci, int &iloscOsob);
char wczytajZnak();
string wczytajLinie();
string konwersjaIntNaString();
void wyszukajPoImieniu(vector <Adresat> adresaci, int &iloscOsob);
void wyszukajPoNazwisku(vector <Adresat> adresaci, int &iloscOsob);
void wyswietlWszystkieOsoby(vector <Adresat> &adresaci, int &iloscOsob);
void usunAdresata(vector <Adresat> &adresaci, int &iloscOsob);
void edytujAdresata(vector <Adresat> &adresaci, int &iloscOsob);
Adresat wyodrebnianieAdresata(Adresat &adresat, int &kolejnePoleObiektuAdresat, string &wyodrebnioneDaneAdresata);
void aktualizujKsiazke(vector <Adresat> &adresaci);
void zakonczProgram();

int main() {
    int iloscOsob = 0;
    char wybor;

    while (true) {
        vector <Adresat> adresaci;
        iloscOsob = wczytajOsobyZPliku(adresaci);
        system("cls");

        cout << "|----- KSIAZKA ADRESOWA -----|" << endl << endl;

        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich znajomych" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz" << endl << endl;

        cout << "Wybierz co chcesz zrobic: ";
        wybor = wczytajZnak();

        switch (wybor) {
        case '1':
            iloscOsob = dodajOsobe(adresaci, iloscOsob);
            break;
        case '2':
            wyszukajPoImieniu(adresaci, iloscOsob);
            break;
        case '3':
            wyszukajPoNazwisku(adresaci, iloscOsob);
            break;
        case '4':
            wyswietlWszystkieOsoby(adresaci, iloscOsob);
            break;
        case '5':
            usunAdresata(adresaci, iloscOsob);
            break;
        case '6':
            edytujAdresata(adresaci, iloscOsob);
            break;
        case '9':
            zakonczProgram();
            break;
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

void zakonczProgram() {
    exit(0);
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
        adresat.imie = wyodrebnioneDaneAdresata;
        break;
    case 3:
        adresat.nazwisko = wyodrebnioneDaneAdresata;
        break;
    case 4:
        adresat.numerTelefonu = wyodrebnioneDaneAdresata;
        break;
    case 5:
        adresat.email = wyodrebnioneDaneAdresata;
        break;
    case 6:
        adresat.adres = wyodrebnioneDaneAdresata;
        break;
    }
    return adresat;
}

int wczytajOsobyZPliku(vector <Adresat> &adresaci) {

    Adresat adresat;
    int ileOsob = 0;
    int numerLini = 1;
    int dlugoscWczytanejLinii;
    int kolejnePoleObiektuAdresat;
    int poczatek;
    string linia;
    string wyodrebnioneDaneAdresata;

    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Ksiazka_adresowa.txt",ios::in);

    if(ksiazkaAdresowa.good() == true) {

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

            adresaci.push_back(adresat);
            numerLini++;
        }

        ileOsob = numerLini - 1;
        ksiazkaAdresowa.close();
    }

    return ileOsob;
}

int dodajOsobe(vector <Adresat> &adresaci, int &iloscOsob) {

    Adresat adresat;
    iloscOsob++;
    system("cls");

    cout << "|----- Dodaj nowego adresata -----|" << endl << endl;

    if(adresaci.empty()) {
        adresat.id = iloscOsob;
    } else {
        adresat.id = adresaci.back().id + 1;
    }
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

    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Ksiazka_adresowa.txt",ios::out | ios::app);

    ksiazkaAdresowa << konwersjaIntNaString(adresat.id)<< "|" << adresat.imie << "|" << adresat.nazwisko;
    ksiazkaAdresowa << "|" << adresat.numerTelefonu << "|" << adresat.email << "|" << adresat.adres << "|" << endl ;

    ksiazkaAdresowa.close();

    cout << endl << "Adresat dodany." << endl;
    system("pause");

    return iloscOsob;
}

void wyszukajPoImieniu(vector <Adresat> adresaci, int &iloscOsob) {
    int ileOsob = 0;
    string imie = "";
    string odmianaKoncowkiSlowaOsoba = "osob";

    system("cls");

    cout << "|----- Wyszukaj adresata po imieniu -----|" << endl << endl;

    cout << "Podaj imie osoby ktora chcesz odnalezc: ";
    imie = wczytajLinie();

    for (int i = 0; i < iloscOsob; i ++) {
        if (adresaci[i].imie == imie) {
            cout << endl << "Id: " << adresaci[i].id << endl;
            cout << "Imie: " << adresaci[i].imie << endl;
            cout << "Nazwisko: " << adresaci[i].nazwisko << endl;
            cout << "Numer telefonu: " << adresaci[i].numerTelefonu << endl;
            cout << "Adres e-mail: " << adresaci[i].email << endl;
            cout << "Adres: " << adresaci[i].adres << endl;
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

void wyszukajPoNazwisku(vector <Adresat> adresaci, int &iloscOsob) {
    int ileOsob = 0;
    string nazwisko = "";
    string odmianaKoncowkiSlowaOsoba = "osob";

    system("cls");

    cout << "|----- Wyszukaj adresata po imieniu -----|" << endl << endl;

    cout << "Podaj nazwisko osoby ktora chcesz odnalezc: ";
    nazwisko = wczytajLinie();

    for (int i = 0; i < iloscOsob; i ++) {
        if (adresaci[i].nazwisko == nazwisko) {
            cout << endl << "Id: " << adresaci[i].id << endl;
            cout << "Imie: " << adresaci[i].imie << endl;
            cout << "Nazwisko: " << adresaci[i].nazwisko << endl;
            cout << "Numer telefonu: " << adresaci[i].numerTelefonu << endl;
            cout << "Adres e-mail: " << adresaci[i].email << endl;
            cout << "Adres: " << adresaci[i].adres << endl;
            ileOsob++;
        }
    }
    if (ileOsob == 1) {
        odmianaKoncowkiSlowaOsoba = "osobe";
    }
    if (ileOsob >= 2 && ileOsob <= 4) {
        odmianaKoncowkiSlowaOsoba = "osoby";
    }

    cout << endl << "Odnaleziono " << ileOsob << " " <<odmianaKoncowkiSlowaOsoba << " o nazwisku " << nazwisko << endl << endl;
    system("pause");
}

void aktualizujKsiazke(vector <Adresat> &adresaci) {
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("temp.txt", ios::out);

    for(long long unsigned int i = 0; i < adresaci.size(); i++) {
        ksiazkaAdresowa << konwersjaIntNaString(adresaci[i].id)<< "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko;
        ksiazkaAdresowa << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" << endl ;
    }

    ksiazkaAdresowa.close();
    remove("Ksiazka_adresowa.txt");
    rename("temp.txt", "Ksiazka_adresowa.txt");
}

void usunAdresata(vector <Adresat> &adresaci, int &iloscOsob) {

    int wybraneId;
    char potwierdzenieUsuniecia;

    system("cls");

    cout << "|----- Usun adresata -----|" << endl << endl;

    cout << "Podaj numer ID adresata ktorego chcesz usunac: ";

    wybraneId = wczytajLiczbeCalkowita();

    for (long long unsigned int i = 0; i < adresaci.size(); i++) {
        if(wybraneId == adresaci[i].id) {

            cout << endl << endl << "Potwierdz wybor naciskajac 't': ";

            potwierdzenieUsuniecia = wczytajZnak();

            if(potwierdzenieUsuniecia == 't') {
                adresaci.erase (adresaci.begin()+ i);

                aktualizujKsiazke(adresaci);

                cout << endl << "Adresat usuniety" << endl;
                system("pause");

            } else {
                cout << endl << "Wybrales inny znak, usuwanie anulowane." << endl;
                system("pause");
            }
        }
    }
}

void edytujAdresata(vector <Adresat> &adresaci, int &iloscOsob) {
    int wybraneId, wybraneDane;
    long long unsigned int i;
    string daneDoZmiany;

    system("cls");

    cout << "|----- Edytuj dane adresata -----|" << endl << endl;

    cout << "Podaj numer ID adresata ktorego chcesz edytowac: ";

    wybraneId = wczytajLiczbeCalkowita();

    for (i = 0; i < adresaci.size(); i++) {
        if(wybraneId == adresaci[i].id) {

            cout << endl << "Ktore dane zaktualizowac: " << endl;
            cout << "1 - Imie" << endl;
            cout << "2 - Nazwisko" << endl;
            cout << "3 - Numer telefonu" << endl;
            cout << "4 - Email" << endl;
            cout << "5 - Adres" << endl;
            cout << "6 - Powrot" << endl;

            cout << endl << "Wybierz 1-6: ";

            wybraneDane = wczytajLiczbeCalkowita();

            if(wybraneDane == 1) {
                cout << "Podaj nowe imie: ";
                daneDoZmiany = wczytajLinie();
                adresaci[i].imie = daneDoZmiany;
                cout << endl << "Imie zostalo zmienione" << endl;
                system("pause");
            } else if(wybraneDane == 2) {
                cout << "Podaj nowe nazwisko: ";
                daneDoZmiany = wczytajLinie();
                adresaci[i].nazwisko = daneDoZmiany;
                cout <<  endl << "Nazwisko zostalo zmienione" << endl;
                system("pause");
            } else if(wybraneDane == 3) {
                cout << "Podaj nowy numer telefonu: ";
                daneDoZmiany = wczytajLinie();
                adresaci[i].numerTelefonu = daneDoZmiany;
                cout <<  endl << "Numer telefonu zostal zmieniony" << endl;
                system("pause");
            } else if(wybraneDane == 4) {
                cout <<  endl << "Podaj nowy email: ";
                daneDoZmiany = wczytajLinie();
                adresaci[i].email = daneDoZmiany;
                cout << "Email zostal zmieniony" << endl;
                system("pause");
            } else if(wybraneDane == 5) {
                cout << "Podaj nowy adres: ";
                daneDoZmiany = wczytajLinie();
                adresaci[i].adres = daneDoZmiany;
                cout <<  endl << "Adres zostal zmieniony" << endl;
                system("pause");
            } else if(wybraneDane == 6) {
                system("pause");
            }
        }
    }

    aktualizujKsiazke(adresaci);

}

void wyswietlWszystkieOsoby(vector <Adresat> &adresaci, int &iloscOsob) {
    system("cls");

    cout << "|----- Wyswietl ksiazke adresowa -----|" << endl << endl;

    if (iloscOsob == 0) {
        cout << endl << "Ksiazka adresowa jest pusta."<< endl;
    } else {
        for (int i = 0; i < iloscOsob; i ++) {
            cout << endl << "Id: " << adresaci[i].id << endl;
            cout << "Imie: " << adresaci[i].imie << endl;
            cout << "Nazwisko: " << adresaci[i].nazwisko << endl;
            cout << "Numer telefonu: " << adresaci[i].numerTelefonu << endl;
            cout << "Adres e-mail: " << adresaci[i].email << endl;
            cout << "Adres: " << adresaci[i].adres << endl;
        }
    }

    cout << endl;
    system("pause");
}
