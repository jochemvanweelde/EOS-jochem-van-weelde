#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void hussel(const string & woord, const int & husselen){
    string husselwoord = "";
    int aantal = husselen;
    if(husselen == 0){
        husselwoord = woord;
    }
    while(aantal > 0) {
        for (int i = husselen - aantal; i < woord.length(); i=i+husselen) {
            husselwoord += woord[i];
        }
        aantal--;
    }
    cout << "Gelukt! We hebben je ingegeven string gehusseld. Het restultaat is: " << husselwoord << endl;
    string bestandsnaam;
    cout << "Nu hebben we nog een leuke naam voor een file nodig die je wilt gaan maken. Geef een naam op: ";
    cin >> bestandsnaam;
    ofstream bestand(bestandsnaam + ".txt");
    bestand << husselwoord << endl;
    cout << "Klaar is kees! De file is gemaakt en kan je vinden in dit mapje als je hem gecompiled hebt via de commandline anders staat tie in een cmake mapje als je die hebt aangemaakt";
    bestand.close();
}

int main(){
    string woord;
    int husselen;
    cout << "Een hele goede dag! We gaan een string husselen op een speciale manier. Welke string? Dat mag u bepalen" << endl;
    cout << "Vul nu een string in:";
    getline(cin, woord);
    cout << endl << "Geweldig! Nu gaan we deze string husselen en dat werkt zo:" << endl;
    cout << "Bij een integer van 2 pakt het programma elke keer de tweede char van de string. Dus 0 2 4 6 etc. Daarna 1 3 5 etc." << endl;
    cout << "Welke integer wil je mee husselen?:";
    cin >> husselen;
    hussel(woord, husselen);
}