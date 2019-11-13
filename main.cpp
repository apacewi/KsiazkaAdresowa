#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, adres, email, nrTelefonu;
};

char *zamienNaPolskieZnaki(char *str)
{
    static char buff[256];
    char cp[]="\245\206\251\210\344\242\230\276\253\244\217\250\235\343\340\227\275\215����󜿟��ʣ�ӌ��";
    if(strlen(str)>=sizeof(buff))
        return str;
    char *bf=buff;
    while(*str)
    {
        char *pos=strchr(cp+18,*str);
        *(bf++)=pos?*(pos-18):*str;
        ++str;
    }
    *bf=0;
    return buff;
}
int zapiszKontakt(vector <Kontakt> &kontakty,int iloscKontaktow)
{
    string imie, nazwisko, adres, email, numerTelefonu;
    int i = 0;
    Kontakt kontakt;

    cout << zamienNaPolskieZnaki("Podaj imi� i nazwisko: ") << endl;
    cin >> imie >> nazwisko;

    while ( i < iloscKontaktow){
        if (kontakty[i].imie == imie && kontakty[i].nazwisko == nazwisko){
            cout << "Juz masz taki kontakt! " << endl;
            cout << "Podaj inne imie i nazwisko: " << endl;
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

    if (kontakty.size() == 0)
    kontakt.id = 1;
    else
    kontakt.id = kontakty[iloscKontaktow-1].id + 1;

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
void wyswietlKontakty(vector <Kontakt> &kontakty, int iloscKontaktow, string funkcjaWywolujaca)
{
    cout << endl;
    cout << zamienNaPolskieZnaki("Lista Kontakt�w: ") << endl << "--------------------------------" << endl;

    for (int i = 0; i < iloscKontaktow; i++){
        cout << "********************************" << endl;
        cout << "Kontakt " << kontakty[i].id << ":" << endl << endl;
        cout << zamienNaPolskieZnaki("Imi�: ");
        cout << zamienNaPolskieZnaki(&kontakty[i].imie[0]) << endl;
        cout << "Nazwisko: " << zamienNaPolskieZnaki(&kontakty[i].nazwisko[0]) << endl;
        cout << "Numer telefonu: "<< kontakty[i].nrTelefonu << endl;
        cout << "Adres: " << zamienNaPolskieZnaki(&kontakty[i].adres[0]) << endl;
        cout << "Adres e-mail: " << zamienNaPolskieZnaki(&kontakty[i].email[0]) << endl;
    }
    cout << "********************************" << endl;
    cout << "--------------------------------" << endl;
    if (funkcjaWywolujaca == "main"){
        cout << zamienNaPolskieZnaki("Aby przej�� do menu g��wnego, wci�nij dowolny klawisz: ...");
        getch();
        system( "cls" );
    }
}
void zapiszTablice(vector <Kontakt> &kontakty, int iloscKontaktow)
{
    fstream plikTekstowyZListaKontaktow;

    plikTekstowyZListaKontaktow.open("ksiazka_adresowa.txt", ios::out);

    for (int i = 0; i < iloscKontaktow; i++){
        plikTekstowyZListaKontaktow << kontakty[i].id << "|" << kontakty[i].imie << "|" << kontakty[i].nazwisko << "|" << kontakty[i].nrTelefonu << "|" << kontakty[i].email << "|" << kontakty[i].adres << "|" << endl;
    }
    plikTekstowyZListaKontaktow.close();
}
int odczytajPlik(vector <Kontakt> &kontakty)
{
    int j = 0, iloscZnakowOddzielajacych, numerLiniPlikuTekstowego = 1, iloscKontaktow = 0;
    string liniaWPlikuTekstowym, imie, nazwisko,numerTelefonu, adres, email, id;
    Kontakt kontakt;
    fstream plikTekstowyZListaKontaktow;

    plikTekstowyZListaKontaktow.open("ksiazka_adresowa.txt", ios::in);

    while(getline(plikTekstowyZListaKontaktow, liniaWPlikuTekstowym))
    {
        kontakty.push_back(kontakt);
        id = "", imie = "", nazwisko = "", numerTelefonu = "", adres = "", email = "";
        iloscZnakowOddzielajacych = 0;

        for (int i = 0; i < liniaWPlikuTekstowym.length(); i++){
            if (liniaWPlikuTekstowym[i] == '|')
                iloscZnakowOddzielajacych += 1;
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych < 1)
                id += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 1)
                imie += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 2)
                nazwisko += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 3)
                numerTelefonu += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 4)
                email += liniaWPlikuTekstowym[i];
            if (liniaWPlikuTekstowym[i] != '|' && iloscZnakowOddzielajacych == 5)
                adres += liniaWPlikuTekstowym[i];
        }
        kontakty[j].imie = imie;
        kontakty[j].nazwisko = nazwisko;
        kontakty[j].nrTelefonu = numerTelefonu;
        kontakty[j].adres = adres;
        kontakty[j].email = email;
        kontakty[j].id = atoi(id.c_str());
        j++;
        iloscKontaktow++;
        numerLiniPlikuTekstowego++;
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
            cout << zamienNaPolskieZnaki("Imi�: ");
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

    cout << zamienNaPolskieZnaki("Aby wr�ci� do menu g��wnego, wci�nij dowolny klawisz: ...");
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
            cout << zamienNaPolskieZnaki("Imi�: ");
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

    cout << zamienNaPolskieZnaki("Aby wr�ci� do menu g��wnego, wci�nij dowolny klawisz: ...");
    getch();
    system( "cls" );
}
void edytujKontakt(vector <Kontakt> &kontakty, int iloscKontaktow)
{
    char wyborDrugi;
    string wybor, noweImie, noweNazwisko, nowyNumerTelefonu, nowyAdres, nowyEmail, funkcjaWywolujaca = "edytujKontakt";
    int wyborWInt, wybranyKontakt = 0;

    wyswietlKontakty(kontakty, iloscKontaktow, funkcjaWywolujaca);

    cout << "Wybierz kontakt do edycji: ";
    cin >> wybor;
    system( "cls" );

    wyborWInt = atoi(wybor.c_str());

    for (int i = 0; i < iloscKontaktow; i++){
        if (wyborWInt == kontakty[i].id){
            wybranyKontakt = i;
        }
    }
    cout << "--------------------------------" << endl
         << zamienNaPolskieZnaki("1. Imi� ") << endl;
    cout << "2. Nazwisko " << endl
         << "3. Numer Telefonu " << endl
         << "4. Adres " << endl
         << "5. E-mail " << endl
         << "--------------------------------" << endl;
    cout << zamienNaPolskieZnaki("Wybierz kt�r� informacj� chcesz edytowa�? ") << endl;

    cin >> wyborDrugi;
    system( "cls" );

    if (wyborDrugi == '1'){
        cout << zamienNaPolskieZnaki("Podaj nowe imi�: ") << endl;
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

    zapiszTablice(kontakty, iloscKontaktow);
    cout << endl << zamienNaPolskieZnaki("Tw�j kontakt zosta� zmieniony! ") << endl;
    cout << "--------------------------------" << endl;
    getch();
    system( "cls" );
}
int usunKontakt(vector <Kontakt> &kontakty, int iloscKontaktow)
{
    char znak;
    string wybor, funkcjaWywolujaca = "usunKontakt";
    int brakId = 0, wyborWInt, wybranyKontakt = 0;

    wyswietlKontakty(kontakty, iloscKontaktow, funkcjaWywolujaca);

    cout << zamienNaPolskieZnaki("Wybierz kontakt do usuni�cia: ");
    cin >> wybor;
    system( "cls" );

    wyborWInt = atoi(wybor.c_str());

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
            cout << zamienNaPolskieZnaki("B��dny kontakt, spr�buj poda� jeszcze raz. ") << endl;
            wyswietlKontakty(kontakty, iloscKontaktow, funkcjaWywolujaca);
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
    cout << zamienNaPolskieZnaki("Na pewno chcesz usun�� kontakt: ");
    cout << kontakty[wybranyKontakt].id << " ";
    cout << zamienNaPolskieZnaki(&kontakty[wybranyKontakt].imie[0]) << " ";
    cout << zamienNaPolskieZnaki(&kontakty[wybranyKontakt].nazwisko[0]) << " ?" << endl;
    cout << "t/n ?" << endl;

    while (true){
        znak = getch();
        if (znak == 't'){
            kontakty.erase(kontakty.begin()+ wybranyKontakt);
            iloscKontaktow--;
            zapiszTablice(kontakty, iloscKontaktow);
            cout << zamienNaPolskieZnaki("Tw�j kontakt zosta� usuniety! ") << endl;
            break;
        }
        else if (znak == 'n'){
            cout << zamienNaPolskieZnaki("Zmiany nie zosta�y wprowadzone! ") << endl;
            break;
        }
        else
            cout << zamienNaPolskieZnaki("B��dny wyb�r, aby potwierdzi� usuni�cie kontaktu wci�nij t, je�li si� rozmy�lile� wci�nij n. ") << endl;
    }

    getch();
    system( "cls" );
    return iloscKontaktow;
}
int main()
{
    vector <Kontakt> kontakty;
    char wybor;
    int iloscKontaktow = 0;
    string funkcjaWywolujaca = "main";
    fstream plikTekstowyZListaKontaktow;

    plikTekstowyZListaKontaktow.open("ksiazka_adresowa.txt", ios::in);

    if (plikTekstowyZListaKontaktow.good() == true)
    {
        iloscKontaktow = odczytajPlik(kontakty);
        wyswietlKontakty(kontakty, iloscKontaktow, funkcjaWywolujaca);
    }

    plikTekstowyZListaKontaktow.close();

    while (true)
    {
        cout << zamienNaPolskieZnaki("MENU G��WNE") << endl
             << "--------------------------------" << endl
             << "1. Dodaj Adresata " << endl
             << "2. Wyszukaj po imieniu " << endl
             << "3. Wyszukaj po nazwisku " << endl;
        cout << zamienNaPolskieZnaki("4. Wy�wietl wszystkich adresat�w ") << endl;
        cout << zamienNaPolskieZnaki("5. Usu� Adresata ") << endl
             << "6. Edytuj Adresata " << endl;
        cout << zamienNaPolskieZnaki("9. Zako�cz program ") << endl;
        cout << "--------------------------------" << endl;
        cout << zamienNaPolskieZnaki("Tw�j wyb�r : ");

        cin >> wybor;

        if (wybor == '1'){
            system( "cls" );
            iloscKontaktow = zapiszKontakt(kontakty, iloscKontaktow);
            zapiszTablice(kontakty, iloscKontaktow);
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
            wyswietlKontakty(kontakty, iloscKontaktow, funkcjaWywolujaca);
        }
        if (wybor == '6'){
            system( "cls" );
            edytujKontakt(kontakty, iloscKontaktow);
        }
        if (wybor == '5'){
            system( "cls" );
            iloscKontaktow = usunKontakt(kontakty, iloscKontaktow);
        }
        if (wybor == '9'){
            system( "cls" );
            cout << zamienNaPolskieZnaki("Czy na pewno chcesz wyjsc ?: ") << endl;
            cout << "9. Tak " << endl
                 << "2. Nie " << endl;
            cin >> wybor;
            if (wybor == '9')
                exit(0);
        }
    }
    return 0;
}
