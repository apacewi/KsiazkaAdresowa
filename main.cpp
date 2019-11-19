#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

struct Kontakt
{
    int id, idUzytkownika;
    string imie, nazwisko, adres, email, nrTelefonu;
};
struct Uzytkownik
{
    int idUzytkownika;
    string nazwa, haslo;
};

char *zamienNaPolskieZnaki(char *str)
{
    static char buff[256];
    char cp[]="\245\206\251\210\344\242\230\276\253\244\217\250\235\343\340\227\275\215¹æê³ñóœ¿Ÿ¥ÆÊ£ÑÓŒ¯";
    if(strlen(str)>=sizeof(buff))
        return str;
    char *bf=buff;
    while(*str){
        char *pos=strchr(cp+18,*str);
        *(bf++)=pos?*(pos-18):*str;
        ++str;
    }
    *bf=0;
    return buff;
}
int utworzKonto(vector <Uzytkownik> &uzytkownicy, int liczbaKontaktow)
{
    string nazwaUzytkownika, hasloUzytkownika, hasloUzytkownikaDrugie;
    int i = 0;
    Uzytkownik uzytkownik;

    system( "cls" );
    cout << zamienNaPolskieZnaki("Podaj nazwê u¿ytkownika: ") << endl;
    cin >> nazwaUzytkownika;

    while (i < liczbaKontaktow){
        if (uzytkownicy[i].nazwa == nazwaUzytkownika){
            system( "cls" );
            cout << zamienNaPolskieZnaki("Taka nazwa u¿ytkownika jest ju¿ zajêta! ") << endl;
            cout << zamienNaPolskieZnaki("Podaj inn¹ nazwê u¿ytkownika: ") << endl;
            cin >> nazwaUzytkownika;
            i = 0;
        }
        else
            i++;
    }

    while (true){
        cout << zamienNaPolskieZnaki("Podaj has³o u¿ytkownika: ") << endl;
        cin >> hasloUzytkownika;
        cout << zamienNaPolskieZnaki("Powtórz has³o u¿ytkownika: ") << endl;
        cin >> hasloUzytkownikaDrugie;

        if (hasloUzytkownika == hasloUzytkownikaDrugie)
            break;
        else{
            system( "cls" );
            cout << zamienNaPolskieZnaki("Coœ posz³o nie tak, has³a siê nie zgadzaj¹! Sprobój jeszcze raz: ") << endl;
        }
    }

    if (uzytkownicy.size() == 0)
        uzytkownik.idUzytkownika = 1;
    else
        uzytkownik.idUzytkownika = uzytkownicy[liczbaKontaktow-1].idUzytkownika + 1;

    uzytkownik.nazwa = nazwaUzytkownika;
    uzytkownik.haslo = hasloUzytkownika;
    uzytkownicy.push_back(uzytkownik);
    system( "cls" );
    cout << "Utworzono nowe konto! " << endl;

    return ++liczbaKontaktow;
}
int sprawdzPoprawnoscLogowania(vector <Uzytkownik> &uzytkownicy, int liczbaKontaktow, string funkcjaWywolujaca)
{
    string nazwaUzytkownika, hasloUzytkownika;
    int wybranaNazwa, idZalogowanegoUzytkownika;
    bool prawidlowaNazwa = false;
    system( "cls" );
    cout << "Podaj Login: " << endl;
    cin >> nazwaUzytkownika;
    cout << zamienNaPolskieZnaki("Podaj has³o: ") << endl;
    cin >> hasloUzytkownika;

    for (int i = 0; i < liczbaKontaktow; i++){
        if (uzytkownicy[i].nazwa == nazwaUzytkownika){
            prawidlowaNazwa = true;
            wybranaNazwa = i;
        }
    }
    if (prawidlowaNazwa == true){
        idZalogowanegoUzytkownika = uzytkownicy[wybranaNazwa].idUzytkownika;
        if(hasloUzytkownika == uzytkownicy[wybranaNazwa].haslo){
            system( "cls" );
            if (funkcjaWywolujaca == "otworzPanelLogowania"){
                cout << zamienNaPolskieZnaki("Uda³o siê zalogowaæ! ") << endl;
                return idZalogowanegoUzytkownika;
            }
            else if (funkcjaWywolujaca == "zmienHaslo")
                return idZalogowanegoUzytkownika;
        }
        else{
            system( "cls" );
            if (funkcjaWywolujaca == "otworzPanelLogowania"){
                cout << zamienNaPolskieZnaki("Nie uda³o siê zalogowaæ, b³êdne has³o! ") << endl;
                return 0;
            }
            else if (funkcjaWywolujaca == "zmienHaslo")
                return 0;
        }
    }
    else{
        system( "cls" );
        cout << zamienNaPolskieZnaki("Nie ma takiego u¿ytkownika! ") << endl;
        return 0;
    }
}
void zapiszUzytkownikow(vector <Uzytkownik> &uzytkownicy, int iloscKontaktow)
{
    fstream plikTekstowyZUzytkownikami;

    plikTekstowyZUzytkownikami.open("Uzytkownicy.txt", ios::out);

    for (int i = 0; i < iloscKontaktow; i++){
        plikTekstowyZUzytkownikami << uzytkownicy[i].idUzytkownika << "|" << uzytkownicy[i].nazwa << "|" << uzytkownicy[i].haslo<< endl;
    }
    plikTekstowyZUzytkownikami.close();
}
int wczytajUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    int j = 0, iloscZnakowOddzielajacych, numerLiniPlikuTekstowego = 1, iloscUzytkownikow = 0;
    string liniaWPlikuTekstowym, nazwa, haslo, id;
    Uzytkownik uzytkownik;
    fstream plikTekstowyZUzytkownikami;

    plikTekstowyZUzytkownikami.open("Uzytkownicy.txt", ios::in);

    while(getline(plikTekstowyZUzytkownikami, liniaWPlikuTekstowym)){
        uzytkownicy.push_back(uzytkownik);
        id = "", nazwa = "", haslo = "";
        iloscZnakowOddzielajacych = 0;

        for (int i = 0; i < liniaWPlikuTekstowym.length(); i++){
            if (liniaWPlikuTekstowym[i] == '|')
                iloscZnakowOddzielajacych += 1;
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych < 1)
                id += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 1)
                nazwa += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 2)
                haslo += liniaWPlikuTekstowym[i];
        }
        uzytkownicy[j].nazwa = nazwa;
        uzytkownicy[j].haslo = haslo;
        uzytkownicy[j].idUzytkownika = atoi(id.c_str());
        j++;
        iloscUzytkownikow++;
        numerLiniPlikuTekstowego++;
    }
    plikTekstowyZUzytkownikami.close();
    return iloscUzytkownikow;
}
int sprawdzNumerPorzadkowyWVectorze(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    int numerElementu;

    for (int i = 0; i < uzytkownicy.size(); i++){
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika){
            numerElementu = i;
        }
    }
    return numerElementu;
}
void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string noweHaslo, noweHaslo2;
    int numerElementuVectora, idDoSprawdzenia, liczbaUzytkownikow;

    cout << zamienNaPolskieZnaki("WprowadŸ ponownie swoje dane logowania: ") << endl;
    getch();
    liczbaUzytkownikow = wczytajUzytkownikow(uzytkownicy);
    idDoSprawdzenia = sprawdzPoprawnoscLogowania(uzytkownicy, liczbaUzytkownikow, "zmienHaslo");

    if (idZalogowanegoUzytkownika == idDoSprawdzenia){
        if (idZalogowanegoUzytkownika > 0){
            cout << zamienNaPolskieZnaki("Podaj nowe has³o: ") << endl;
            cin >> noweHaslo;
            cout << zamienNaPolskieZnaki("PotwierdŸ nowe has³o: ") << endl;
            cin >> noweHaslo2;
            numerElementuVectora = sprawdzNumerPorzadkowyWVectorze(uzytkownicy, idZalogowanegoUzytkownika);
            uzytkownicy[numerElementuVectora].haslo = noweHaslo;
            zapiszUzytkownikow(uzytkownicy, liczbaUzytkownikow);
        }
        else{
            cout << zamienNaPolskieZnaki("Wprowadzone dane s¹ niepoprawne!") << endl;
        }
    }
    else{
        cout << zamienNaPolskieZnaki("Nie mo¿esz zmieniaæ hase³ dostêpu innym u¿ytkownikom!") << endl;
    }
}
int otworzPanelLogowania(vector <Uzytkownik> uzytkownicy)
{
    char wybor;
    int idZalogowanegoUzytkownika,liczbaUzytkownikow = 0;

    while (true){
        cout << "------------------" << endl
             << "1. Logowanie. " << endl
             << "2. Rejestracja. " << endl
             << "3. Zamknij Program. " << endl
             << "------------------" << endl;

        cout << zamienNaPolskieZnaki("Twój wybór: ");
        cin  >> wybor;

        if (wybor == '1'){
            liczbaUzytkownikow = wczytajUzytkownikow(uzytkownicy);
            idZalogowanegoUzytkownika = sprawdzPoprawnoscLogowania(uzytkownicy, liczbaUzytkownikow, "otworzPanelLogowania");
            if (idZalogowanegoUzytkownika > 0)
                break;
        }
        if (wybor == '2'){
            if (liczbaUzytkownikow == 0){
                liczbaUzytkownikow = wczytajUzytkownikow(uzytkownicy);
            }
            liczbaUzytkownikow = utworzKonto(uzytkownicy, liczbaUzytkownikow);
            zapiszUzytkownikow(uzytkownicy, liczbaUzytkownikow);
        }
        if (wybor =='9'){
            system( "cls" );
            cout << zamienNaPolskieZnaki("Czy na pewno chcesz wyjœæ ?: ") << endl;
            cout << "9. Tak " << endl
                 << "2. Nie " << endl;
            cin >> wybor;
            if (wybor == '9')
                exit(0);
        }
    }
    return idZalogowanegoUzytkownika;
}
int odczytajOstatnieId()
{
    int id, idOstatniegoKontaktu = 0, iloscZnakowOddzielajacych = 0;
    string liniaWPlikuTekstowym, trescLinii, idWString;
    fstream plikTekstowyZListaKontaktow;

    plikTekstowyZListaKontaktow.open("Adresaci.txt", ios::in);
    while(getline(plikTekstowyZListaKontaktow, liniaWPlikuTekstowym)){
        trescLinii = "", idWString = "";
        iloscZnakowOddzielajacych = 0;
        for (int i = 0; i < liniaWPlikuTekstowym.length(); i++){
            if (liniaWPlikuTekstowym[i] == '|')
                iloscZnakowOddzielajacych += 1;
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych < 1)
                idWString += liniaWPlikuTekstowym[i];
        }
        id = atoi(idWString.c_str());
    }
    idOstatniegoKontaktu = id;
    plikTekstowyZListaKontaktow.close();
    return idOstatniegoKontaktu;
}
int odczytajIloscLini()
{
    int iloscLiniWPliku = 0;
    string liniaWPlikuTekstowym;
    fstream plikTekstowyZListaKontaktow;

    plikTekstowyZListaKontaktow.open("Adresaci.txt", ios::in);
    while(getline(plikTekstowyZListaKontaktow, liniaWPlikuTekstowym)){
        iloscLiniWPliku += 1;
    }
    plikTekstowyZListaKontaktow.close();
    return iloscLiniWPliku;
}
int zapiszKontakt(vector <Kontakt> &kontakty,int iloscKontaktow, int idZalogowanegoUzytkownika)
{
    string imie, nazwisko, adres, email, numerTelefonu;
    int ostatnieId, iloscLinii, i = 0;
    Kontakt kontakt;

    cout << zamienNaPolskieZnaki("Podaj imiê i nazwisko: ") << endl;
    cin >> imie >> nazwisko;

    while ( i < iloscKontaktow){
        if (kontakty[i].imie == imie && kontakty[i].nazwisko == nazwisko){
            cout << zamienNaPolskieZnaki("Ju¿ masz taki kontakt! ") << endl;
            cout << zamienNaPolskieZnaki("Podaj inne imiê i nazwisko: ") << endl;
            cin >> imie >> nazwisko;
            i = 0;
        }
        else
            i++;
    }
    system( "cls" );

    cout << "Podaj numer telefonu: " << endl;
    cin.ignore();
    getline(cin, numerTelefonu);
    system( "cls" );

    cout << "Podaj adres: " << endl;
    cin.ignore();
    getline(cin, adres);
    system( "cls" );

    cout << "Podaj adres e-mail: " << endl;
    cin >> email;
    system( "cls" );

    iloscLinii = odczytajIloscLini();
    ostatnieId = odczytajOstatnieId();

    if (iloscLinii == 0)
        kontakt.id = 1;
    else
        kontakt.id = ++ostatnieId;

    kontakt.idUzytkownika = idZalogowanegoUzytkownika;
    kontakt.imie = imie;
    kontakt.nazwisko = nazwisko;
    kontakt.nrTelefonu = numerTelefonu;
    kontakt.adres = adres;
    kontakt.email = email;

    kontakty.push_back(kontakt);

    cout << "Kontakt zapisany! " << endl << endl;
    getch();
    system( "cls" );
    return ++iloscKontaktow;
}
void wyswietlKontakty(vector <Kontakt> &kontakty, int iloscKontaktow, string funkcjaWywolujaca, int idZalogowanegoUzytkownika)
{
    cout << endl;
    cout << zamienNaPolskieZnaki("Lista Kontaktów: ") << endl << "--------------------------------" << endl;

    for (int i = 0; i < iloscKontaktow; i++){
        if (kontakty[i].idUzytkownika == idZalogowanegoUzytkownika){
            cout << "********************************" << endl;
            cout << "Kontakt " << kontakty[i].id << ":" << endl << endl;
            cout << zamienNaPolskieZnaki("Imiê: ");
            cout << zamienNaPolskieZnaki(&kontakty[i].imie[0]) << endl;
            cout << "Nazwisko: " << zamienNaPolskieZnaki(&kontakty[i].nazwisko[0]) << endl;
            cout << "Numer telefonu: "<< kontakty[i].nrTelefonu << endl;
            cout << "Adres: " << zamienNaPolskieZnaki(&kontakty[i].adres[0]) << endl;
            cout << "Adres e-mail: " << zamienNaPolskieZnaki(&kontakty[i].email[0]) << endl;
        }
    }
    cout << "********************************" << endl;
    cout << "--------------------------------" << endl;
    if (funkcjaWywolujaca == "main"){
        cout << zamienNaPolskieZnaki("Aby przejœæ do menu g³ównego, wciœnij dowolny klawisz: ...");
        getch();
        system( "cls" );
    }
}
void zapiszTablice(vector <Kontakt> &kontakty, int iloscKontaktow, int idModyfikowanegoKontaktu, int poczatkowaWielkoscWektora)
{
    int nrElementu, id, iloscZnakowOddzielajacych, j = 0, numerLiniPlikuTekstowego = 1;
    string liniaWPlikuTekstowym, idWString;
    string trescLinii;
    fstream plikTekstowyZListaKontaktow, plikTymczasowy;

    plikTekstowyZListaKontaktow.open("Adresaci.txt", ios::in);
    plikTymczasowy.open("AdresaciTymczasowy.txt", ios::out);

    while(getline(plikTekstowyZListaKontaktow, liniaWPlikuTekstowym)){
        trescLinii = "", idWString = "";
        iloscZnakowOddzielajacych = 0;
        for (int i = 0; i < liniaWPlikuTekstowym.length(); i++){
            if (liniaWPlikuTekstowym[i] == '|')
                iloscZnakowOddzielajacych += 1;
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych < 1)
                idWString += liniaWPlikuTekstowym[i];
            if (iloscZnakowOddzielajacych >= 1)
                trescLinii += liniaWPlikuTekstowym[i];
        }
        id = atoi(idWString.c_str());
        if (id == idModyfikowanegoKontaktu && kontakty.size() >= poczatkowaWielkoscWektora){
            for (int i = 0; i < kontakty.size(); i++){
                if (id == kontakty[i].id)
                    nrElementu = i;
            }
            plikTymczasowy << kontakty[nrElementu].id << "|"
                           << kontakty[nrElementu].idUzytkownika << "|" << kontakty[nrElementu].imie << "|"
                           << kontakty[nrElementu].nazwisko << "|" << kontakty[nrElementu].nrTelefonu << "|"
                           << kontakty[nrElementu].email << "|" << kontakty[nrElementu].adres << "|" << endl;
        }
        if (id != idModyfikowanegoKontaktu){
            plikTymczasowy << id << trescLinii << endl;
        }
        j++;
        numerLiniPlikuTekstowego++;
    }
    if (kontakty.size() > poczatkowaWielkoscWektora){
        for (int i = iloscKontaktow - (iloscKontaktow - poczatkowaWielkoscWektora); i < iloscKontaktow; i++){
            plikTymczasowy << kontakty[i].id << "|" << kontakty[i].idUzytkownika << "|"
            << kontakty[i].imie << "|" << kontakty[i].nazwisko << "|" << kontakty[i].nrTelefonu
            << "|" << kontakty[i].email << "|" << kontakty[i].adres << "|";
        }
    }
    plikTymczasowy.close();
    plikTekstowyZListaKontaktow.close();

    remove( "Adresaci.txt" );
    rename( "AdresaciTymczasowy.txt", "Adresaci.txt" );
}
int odczytajPlik(vector <Kontakt> &kontakty, int idZalogowanegoUzytkownika)
{
    int idWpisywanegoUzytkownika, j = 0, iloscZnakowOddzielajacych, numerLiniPlikuTekstowego = 1, iloscKontaktow = 0;
    string liniaWPlikuTekstowym, imie, nazwisko,numerTelefonu, adres, email, id, idUzytkownika;
    Kontakt kontakt;
    fstream plikTekstowyZListaKontaktow;

    plikTekstowyZListaKontaktow.open("Adresaci.txt", ios::in);

    while(getline(plikTekstowyZListaKontaktow, liniaWPlikuTekstowym)){
        idUzytkownika = "", id = "", imie = "", nazwisko = "", numerTelefonu = "", adres = "", email = "";
        iloscZnakowOddzielajacych = 0;
        for (int i = 0; i < liniaWPlikuTekstowym.length(); i++){
            if (liniaWPlikuTekstowym[i] == '|')
                iloscZnakowOddzielajacych += 1;
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych < 1)
                id += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 1)
                idUzytkownika += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 2)
                imie += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 3)
                nazwisko += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 4)
                numerTelefonu += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 5)
                email += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 6)
                adres += liniaWPlikuTekstowym[i];
        }
        idWpisywanegoUzytkownika = atoi(idUzytkownika.c_str());
        if(idWpisywanegoUzytkownika == idZalogowanegoUzytkownika){
            kontakt.imie = imie;
            kontakt.nazwisko = nazwisko;
            kontakt.nrTelefonu = numerTelefonu;
            kontakt.adres = adres;
            kontakt.email = email;
            kontakt.idUzytkownika = atoi(idUzytkownika.c_str());
            kontakt.id = atoi(id.c_str());
            kontakty.push_back(kontakt);
            j++;
            iloscKontaktow++;
            numerLiniPlikuTekstowego++;
        }
        else{
            numerLiniPlikuTekstowego++;
        }
    }
    plikTekstowyZListaKontaktow.close();
    return iloscKontaktow;
}
void szukajPoImieniu(vector <Kontakt> &kontakty, int iloscKontaktow)
{
    string szukaneImie, imieZPolskimiZnakami;
    int brakKontaktu = 0;

    cout << "Jakiego imienia szukasz?: " << endl;
    cin >> szukaneImie;

    for (int i = 0; i < iloscKontaktow; i++){
        imieZPolskimiZnakami = zamienNaPolskieZnaki(&kontakty[i].imie[0]);
        if (imieZPolskimiZnakami.find(szukaneImie) != string::npos){
            cout << "********************************" << endl;
            cout << "Kontakt " << kontakty[i].id << ":" << endl << endl;
            cout << zamienNaPolskieZnaki("Imiê: ");
            cout << zamienNaPolskieZnaki(&kontakty[i].imie[0]) << endl;
            cout << "Nazwisko: " << zamienNaPolskieZnaki(&kontakty[i].nazwisko[0]) << endl;
            cout << "Numer telefonu: " << kontakty[i].nrTelefonu << endl
                 << "Adres: " << zamienNaPolskieZnaki(&kontakty[i].adres[0]) << endl;
            cout << "Adres e-mail: " << zamienNaPolskieZnaki(&kontakty[i].email[0]) << endl;
        }
        if (imieZPolskimiZnakami.find(szukaneImie) == string::npos){
            brakKontaktu += 1;
        }
    }
    if (iloscKontaktow == brakKontaktu){
        cout << "********************************" << endl;
        cout << "Nie masz takiego kontaktu! " << endl;
        cout << "********************************" << endl;
    }
    if (iloscKontaktow != brakKontaktu)
        cout << "********************************" << endl;

    cout << zamienNaPolskieZnaki("Aby wróciæ do menu g³ównego, wciœnij dowolny klawisz: ...");
    getch();
    system( "cls" );
}
void szukajPoNazwisku(vector <Kontakt> &kontakty, int iloscKontaktow)
{
    string szukaneNazwisko,nazwiskoZPolskimiZnakami;
    int brakKontaktu = 0;

    cout << "Jakiego nazwiska szukasz?: " << endl;
    cin >> szukaneNazwisko;

    for (int i = 0; i < iloscKontaktow; i++){
        nazwiskoZPolskimiZnakami = zamienNaPolskieZnaki(&kontakty[i].nazwisko[0]);
        if (nazwiskoZPolskimiZnakami.find(szukaneNazwisko) != string::npos){
            cout << "********************************" << endl;
            cout << "Kontakt " << kontakty[i].id << ":" << endl << endl;
            cout << zamienNaPolskieZnaki("Imiê: ");
            cout << zamienNaPolskieZnaki(&kontakty[i].imie[0]) << endl;
            cout << "Nazwisko: " << zamienNaPolskieZnaki(&kontakty[i].nazwisko[0]) << endl;
            cout << "Numer telefonu: " << kontakty[i].nrTelefonu << endl
                 << "Adres: " << zamienNaPolskieZnaki(&kontakty[i].adres[0]) << endl;
            cout << "Adres e-mail: " << zamienNaPolskieZnaki(&kontakty[i].email[0]) << endl;
        }
        if (nazwiskoZPolskimiZnakami.find(szukaneNazwisko) == string::npos){
            brakKontaktu += 1;
        }
    }
    if (iloscKontaktow == brakKontaktu){
        cout << "********************************" << endl;
        cout << "Nie masz takiego kontaktu! " << endl;
        cout << "********************************" << endl;
    }
    if (iloscKontaktow != brakKontaktu)
        cout << "********************************" << endl;

    cout << zamienNaPolskieZnaki("Aby wróciæ do menu g³ównego, wciœnij dowolny klawisz: ...");
    getch();
    system( "cls" );
}
int sprawdzId(vector <Kontakt> &kontakty, int wyborWInt)
{
    int sprawdzaneId;
    for (int i = 0; i < kontakty.size(); i++){
        if (wyborWInt == kontakty[i].id)
            sprawdzaneId = kontakty[i].idUzytkownika;
    }
    return sprawdzaneId;
}
void edytujKontakt(vector <Kontakt> &kontakty, int iloscKontaktow, int idZalogowanegoUzytkownika, int poczatkowaWielkoscWektora)
{
    char wyborDrugi;
    string wybor, noweImie, noweNazwisko, nowyNumerTelefonu, nowyAdres, nowyEmail, funkcjaWywolujaca = "edytujKontakt";
    int sprawdzaneId, wyborWInt, wybranyKontakt = 0;

    wyswietlKontakty(kontakty, iloscKontaktow, funkcjaWywolujaca, idZalogowanegoUzytkownika);
    cout << "Wybierz kontakt do edycji: ";
    cin >> wybor;
    system( "cls" );
    wyborWInt = atoi(wybor.c_str());
    sprawdzaneId = sprawdzId(kontakty, wyborWInt);
    if (sprawdzaneId == idZalogowanegoUzytkownika){
        for (int i = 0; i < iloscKontaktow; i++){
            if (wyborWInt == kontakty[i].id){
                wybranyKontakt = i;
            }
        }
        cout << "--------------------------------" << endl
             << zamienNaPolskieZnaki("1. Imiê ") << endl;
        cout << "2. Nazwisko " << endl
             << "3. Numer Telefonu " << endl
             << "4. Adres " << endl
             << "5. E-mail " << endl
             << "--------------------------------" << endl;
        cout << zamienNaPolskieZnaki("Wybierz któr¹ informacjê chcesz edytowaæ? ") << endl;

        cin >> wyborDrugi;
        system( "cls" );
        if (wyborDrugi == '1'){
            cout << zamienNaPolskieZnaki("Podaj nowe imiê: ") << endl;
            cin >> noweImie;
            kontakty[wybranyKontakt].imie = noweImie;
        }
        if (wyborDrugi == '2'){
            cout << "Podaj nowe nazwisko: " << endl;
            cin >> noweNazwisko;
            kontakty[wybranyKontakt].nazwisko = noweNazwisko;
        }
        if (wyborDrugi == '3'){
            cout << "Podaj nowy numer telefonu: " << endl;
            cin.ignore();
            getline(cin, nowyNumerTelefonu);
            kontakty[wybranyKontakt].nrTelefonu = nowyNumerTelefonu;
        }
        if (wyborDrugi == '4'){
            cout << "Podaj nowy adres: " << endl;
            cin.ignore();
            getline(cin, nowyAdres);
            kontakty[wybranyKontakt].adres = nowyAdres;
        }
        if (wyborDrugi == '5'){
            cout << "Podaj nowy adres e-mail: " << endl;
            cin >> nowyEmail;
            kontakty[wybranyKontakt].email = nowyEmail;
        }
        zapiszTablice(kontakty, iloscKontaktow, wyborWInt, poczatkowaWielkoscWektora);
        cout << endl << zamienNaPolskieZnaki("Twój kontakt zosta³ zmieniony! ") << endl;
        cout << "--------------------------------" << endl;
        getch();
        system( "cls" );
    }
    else
        cout << zamienNaPolskieZnaki("Nie wolno Ci zmieniaæ kontaktów innych ni¿ w³asne!") << endl;
}
int usunKontakt(vector <Kontakt> &kontakty, int iloscKontaktow, int idZalogowanegoUzytkownika, int &poczatkowaWielkoscWektora)
{
    char znak;
    string wybor, funkcjaWywolujaca = "usunKontakt";
    int idModyfikowanegoKontaktu, sprawdzaneId = -1, brakId = 0, wyborWInt, wybranyKontakt = 0;

    wyswietlKontakty(kontakty, iloscKontaktow, funkcjaWywolujaca, idZalogowanegoUzytkownika);
    cout << zamienNaPolskieZnaki("Wybierz kontakt do usuniêcia: ");
    cin >> wybor;
    system( "cls" );
    wyborWInt = atoi(wybor.c_str());
    sprawdzaneId = sprawdzId(kontakty, wyborWInt);
    if (sprawdzaneId == idZalogowanegoUzytkownika){
        while (true){
            for (int i = 0; i < iloscKontaktow; i++){
                if (kontakty[i].id != wyborWInt ){
                    brakId += 1;
                }
                else{
                    brakId = 0;
                    break;
                }
            }
            if (brakId > 0){
                cout << zamienNaPolskieZnaki("B³êdny kontakt, spróbuj podaæ jeszcze raz. ") << endl;
                wyswietlKontakty(kontakty, iloscKontaktow, funkcjaWywolujaca, idZalogowanegoUzytkownika);
                cin >> wybor;
                system( "cls" );
                wyborWInt = atoi(wybor.c_str());
            }
            else
                break;
        }
        for (int i = 0; i < iloscKontaktow; i++){
            if (wyborWInt == kontakty[i].id){
                wybranyKontakt = i;
            }
        }
        idModyfikowanegoKontaktu = kontakty[wybranyKontakt].id;
        cout << zamienNaPolskieZnaki("Na pewno chcesz usun¹æ kontakt: ");
        cout << kontakty[wybranyKontakt].id << " ";
        cout << zamienNaPolskieZnaki(&kontakty[wybranyKontakt].imie[0]) << " ";
        cout << zamienNaPolskieZnaki(&kontakty[wybranyKontakt].nazwisko[0]) << " ?" << endl;
        cout << "t/n ?" << endl;
        while (true){
            znak = getch();
            if (znak == 't'){
                kontakty.erase(kontakty.begin() + wybranyKontakt);
                iloscKontaktow--;
                zapiszTablice(kontakty, iloscKontaktow, idModyfikowanegoKontaktu, poczatkowaWielkoscWektora);
                poczatkowaWielkoscWektora --;
                cout << zamienNaPolskieZnaki("Twój kontakt zosta³ usuniety! ") << endl;
                break;
            }
            else if (znak == 'n'){
                cout << zamienNaPolskieZnaki("Zmiany nie zosta³y wprowadzone! ") << endl;
                break;
            }
            else
                cout << zamienNaPolskieZnaki("B³êdny wybór, aby potwierdziæ usuniêcie kontaktu wciœnij t, jeœli siê rozmyœlileœ wciœnij n. ") << endl;
        }
        getch();
        system( "cls" );
        return iloscKontaktow;
    }
    else{
        cout << zamienNaPolskieZnaki("Mo¿esz usuwaæ tylko w³asne kontakty!") << endl;
        return iloscKontaktow;
    }
}
int main()
{
    vector <Kontakt> kontakty;
    vector <Uzytkownik> uzytkownicy;
    char wybor;
    int idZalogowanegoUzytkownika, poczatkowaWielkoscWektora, iloscKontaktow = 0;
    string funkcjaWywolujaca = "main";
    fstream plikTekstowyZListaKontaktow;

    idZalogowanegoUzytkownika = otworzPanelLogowania(uzytkownicy);
    plikTekstowyZListaKontaktow.open("Adresaci.txt", ios::in);

    if (plikTekstowyZListaKontaktow.good() == true){
        iloscKontaktow = odczytajPlik(kontakty, idZalogowanegoUzytkownika);
        wyswietlKontakty(kontakty, iloscKontaktow, funkcjaWywolujaca, idZalogowanegoUzytkownika);
    }

    plikTekstowyZListaKontaktow.close();
    poczatkowaWielkoscWektora = kontakty.size();

    while (true){
        cout << zamienNaPolskieZnaki("MENU G£ÓWNE") << endl
             << "--------------------------------" << endl
             << "1. Dodaj Adresata " << endl
             << "2. Wyszukaj po imieniu " << endl
             << "3. Wyszukaj po nazwisku " << endl;
        cout << zamienNaPolskieZnaki("4. Wyœwietl wszystkich adresatów ") << endl;
        cout << zamienNaPolskieZnaki("5. Usuñ Adresata ") << endl
             << "6. Edytuj Adresata " << endl;
        cout << zamienNaPolskieZnaki("7. Zmieñ has³o") << endl;
        cout << zamienNaPolskieZnaki("9. Wyloguj siê ") << endl;
        cout << "--------------------------------" << endl;
        cout << zamienNaPolskieZnaki("Twój wybór : ");

        cin >> wybor;

        if (wybor == '1'){
            system( "cls" );
            iloscKontaktow = zapiszKontakt(kontakty, iloscKontaktow, idZalogowanegoUzytkownika);
            zapiszTablice(kontakty, iloscKontaktow, 0, poczatkowaWielkoscWektora);
            poczatkowaWielkoscWektora++;
        }
        if (wybor == '2'){
            system( "cls" );
            szukajPoImieniu(kontakty, iloscKontaktow);
        }
        if (wybor == '3'){
            system( "cls" );
            szukajPoNazwisku(kontakty, iloscKontaktow);
        }
        if (wybor == '4'){
            system( "cls" );
            wyswietlKontakty(kontakty, iloscKontaktow, funkcjaWywolujaca, idZalogowanegoUzytkownika);
        }
        if (wybor == '6'){
            system( "cls" );
            edytujKontakt(kontakty, iloscKontaktow, idZalogowanegoUzytkownika, poczatkowaWielkoscWektora);
        }
        if (wybor == '5'){
            system( "cls" );
            iloscKontaktow = usunKontakt(kontakty, iloscKontaktow, idZalogowanegoUzytkownika, poczatkowaWielkoscWektora);
        }
        if (wybor == '7'){
            system( "cls" );
            zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika);
        }
        if (wybor == '9'){
            system( "cls" );
            cout << zamienNaPolskieZnaki("Czy na pewno chcesz siê wylogowaæ?: ") << endl;
            cout << "9. Tak " << endl
                 << "2. Nie " << endl;
            cin >> wybor;
            if (wybor == '9'){
                iloscKontaktow = 0;
                kontakty.clear();
                system( "cls" );
                idZalogowanegoUzytkownika = otworzPanelLogowania(uzytkownicy);
                plikTekstowyZListaKontaktow.open("Adresaci.txt", ios::in);
                if (plikTekstowyZListaKontaktow.good() == true){
                    iloscKontaktow = odczytajPlik(kontakty, idZalogowanegoUzytkownika);
                    wyswietlKontakty(kontakty, iloscKontaktow, funkcjaWywolujaca, idZalogowanegoUzytkownika);
                }
                plikTekstowyZListaKontaktow.close();
                poczatkowaWielkoscWektora = kontakty.size();
            }
        }
    }
    return 0;
}
