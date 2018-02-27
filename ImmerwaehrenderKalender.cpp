/*
 * --------------------------------------------------------
 * 
 * Aufgabe: Immerwaehrender Kalender
 * Autor: Thorsten Paßfeld
 * 
 * Ein Programm, welches drei Zahlen als Datum einliest und
 * sowohl den ersten Januar eines beliebigen Jahres, als auch
 * den ersten Tag eines Monats und ein beliebiges Datum als 
 * Wochentag ausgibt.
 * 
 * Praktikum Grundlagen Programmierung, HS Osnabrueck
 * --------------------------------------------------------
 */

#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

enum Wochentage {
    Montag, Dienstag, Mittwoch, Donnerstag, Freitag, Samstag, Sonntag
};

/*
 *  Funktion: correctInput
 * 
 *  Prueft eine Eingabe vom Nutzer darauf, ob sie tatsächlich
 *  vom Typ int ist und verlangt sonst eine weitere Eingabe.
 *  Die Eingabe soll im Datumsformat eingelesen werden und die
 *  Werte werden in den Referenzen gespeichert.
 * 
 */

void correctInput(int& tag, int& monat, int& jahr) {
    char punkt1, punkt2;

    cin >> tag >> punkt1 >> monat >> punkt2 >> jahr;
    while (cin.fail() || punkt1 != '.' || punkt2 != '.') //Solange die Eingabe nicht eindeutig von Typ int ist (Sonderzeichen, etc.)
    {
        cin.clear(); //Fehlerstatus wird auf goodbit gesetzt, um weiterhin mit der Eingabe zu arbeiten
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Eingabe wird bis zum newline character gelöscht
        cout << "Fehlerhafte Eingabe. Bitte ein gueltiges Datum eingeben: ";
        cin >> tag >> punkt1 >> monat >> punkt2 >> jahr;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*
 *  Funktion: istSchaltjahr
 * 
 *  Prueft ein Jahr darauf, ob es ein Schaltjahr ist.
 * 
 *  in jahr: int -- Eine Jahreszahl
 * 
 *  return: bool -- true, wenn Schaltjahr; false, wenn kein Schaltjahr
 * 
 */

bool istSchaltjahr(int& jahr) {
    if ((jahr % 100 != 0 && jahr % 4 == 0) || jahr % 400 == 0) {
        return true;
    } else return false;
}

/*
 *  Funktion: istGueltig
 * 
 *  Prueft die eingegebenen Zahlen endgueltig auf ihre
 *  Gueltigkeit bezogen auf die erlaubten Bereiche fuer
 *  die Tage und Monate, also die Zahl fuer die Tage darf
 *  nur einen in diesem Monat vorhandenen Tag darstellen, 
 *  ebenso wie die Zahl fuer den Monat nur einen Wert 
 *  zwischen 1 und 12 annehmen darf. 
 * 
 *  in tag: int -- Ein Tag
 *  in monat: int -- Ein Monat
 *  in jahr: int -- Eine Jahreszahl
 * 
 *  return: bool -- True, wenn Schaltjahr; False, wenn kein Schaltjahr
 * 
 */

bool istGueltig(int& tag, int& monat, int& jahr) {
    vector<int> tageProMonat = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (istSchaltjahr(jahr)) {
        tageProMonat[1] = 29;
    }

    if (tag > tageProMonat[monat - 1] || monat <= 0 || monat > 12 || tag <= 0) {
        return false;
    } else return true;
}

/*
 *  Funktion: anzahlDerSchaltjahreVonBis
 * 
 *  Ermittelt die Anzahl aller Schaltjahre, die echt zwischen zwei
 *  Jahren liegen, auch wenn jahr2 groesser ist als jahr1.
 * 
 *  in jahr1: int -- Eine Jahreszahl als untere Grenze, wenn jahr1 < jahr2, ansonsten als obere Grenze
 *  in jahr2: int -- Eine Jahreszahl als obere Grenze, wenn jahr1 < jahr2, ansonsten als untere Grenze
 * 
 *  return: int -- Die ermittelte Anzahl der Schaltjahre im Intervall
 * 
 */

int anzahlDerSchaltjahreVonBis(int jahr1, int jahr2) {
    int schaltjahre = 0;
    if (jahr1 <= jahr2) {
        for (jahr1; jahr1 <= jahr2; jahr1++) {
            if (istSchaltjahr(jahr1)) {
                schaltjahre++;
            }
        }
    } else if (jahr1 > jahr2) {
        for (jahr2; jahr1 > jahr2; jahr2++) {
            if (istSchaltjahr(jahr2)) {
                schaltjahre++;
            }
        }
    }
    if (istSchaltjahr(jahr2)) {
        return schaltjahre - 1;
    } else return schaltjahre;
}

/*
 *  Funktion: outputWochentag
 * 
 *  Liest einen Wochentag ein und gibt diesen in der Konsole aus.
 * 
 *  in wochentag: enum Wochentage -- Ein Wochentag von Montag bis Sonntag als 
 *                                   Zahl zwischen 0 und 6 korrespondierend mit
 *                                   der Reihenfolge in der Aufzaehlung selbst
 * 
 */

void outputWochentag(enum Wochentage wochentag) {
    switch (wochentag) {
        case Montag: cout << "Montag" << endl;
            break;
        case Dienstag: cout << "Dienstag" << endl;
            break;
        case Mittwoch: cout << "Mittwoch" << endl;
            break;
        case Donnerstag: cout << "Donnerstag" << endl;
            break;
        case Freitag: cout << "Freitag" << endl;
            break;
        case Samstag: cout << "Samstag" << endl;
            break;
        case Sonntag: cout << "Sonntag" << endl;
            break;
    }
}

/*
 *  Funktion: tagAusDifferenzErmitteln
 * 
 *  "Normalisiert" eine eingelesene Differenz in Tagen auf einen Montag, d.h.
 *  die Differenz wird vom jeweiligen Wochentag abhaengig mit einer Zahl zwischen
 *  1 und 6 ergaenzt, damit die Differenz nun immer "bei einem Montag beginnt", sodass
 *  der tatsaechlich ermittelte Wochentag ganz einheitlich mit %7 ermittelt
 *  werden kann.
 * 
 *  in ersterTag: enum Wochentage -- Ein Wochentag, der den Anfangstag darstellt
 *  in differenz: int -- Eine Differenz von Tagen zwischen mehreren Monaten oder innerhalb eines Monats
 * 
 *  return: enum Wochentage -- Der ermittelte Wochentag, wenn man "differenz-viele" Tage von ersten Tag weiter zaehlt
 * 
 */

enum Wochentage tagAusDifferenzErmitteln(enum Wochentage ersterTag, int& differenz) {

    switch (ersterTag) {
        case Montag:
            break;
        case Dienstag: differenz++;
            break;
        case Mittwoch: differenz += 2;
            break;
        case Donnerstag: differenz += 3;
            break;
        case Freitag: differenz += 4;
            break;
        case Samstag: differenz += 5;
            break;
        case Sonntag: differenz += 6;
            break;
    }

    switch (differenz % 7) {
        case 6: return Sonntag;
            break;
        case 5: return Samstag;
            break;
        case 4: return Freitag;
            break;
        case 3: return Donnerstag;
            break;
        case 2: return Mittwoch;
            break;
        case 1: return Dienstag;
            break;
        case 0: return Montag;
            break;
    }
}

/*
 *  Funktion: ersterJanuarDesJahres
 * 
 *  Ermittelt den Wochentag korrespondierend mit dem ersten Januar eines
 *  beliebigen Jahres.
 * 
 *  in jahr: int -- Ein beliebiges Jahr
 * 
 *  return: enum Wochentage -- Der ermittelte Wochentag
 * 
 */

enum Wochentage ersterJanuarDesJahres(int& jahr) {
    //Voraussetzung: 01.01.1900 -> Montag
    int differenz = 0;
    if (1900 < jahr) {
        differenz = 365 * (jahr - 1900 - anzahlDerSchaltjahreVonBis(1900, jahr)) + 366 * (anzahlDerSchaltjahreVonBis(1900, jahr));
    } else {
        differenz = 365 * (1900 - jahr - anzahlDerSchaltjahreVonBis(1900, jahr)) + 366 * (anzahlDerSchaltjahreVonBis(1900, jahr));
    }
    //Differenz bereits "auf Montag normalisiert"
    if (1900 < jahr) {
        switch (differenz % 7) {
            case 6: return Sonntag;
                break;
            case 5: return Samstag;
                break;
            case 4: return Freitag;
                break;
            case 3: return Donnerstag;
                break;
            case 2: return Mittwoch;
                break;
            case 1: return Dienstag;
                break;
            case 0: return Montag;
                break;
        }
    } else {
        switch (differenz % 7) {
            case 6: return Dienstag;
                break;
            case 5: return Mittwoch;
                break;
            case 4: return Donnerstag;
                break;
            case 3: return Freitag;
                break;
            case 2: return Samstag;
                break;
            case 1: return Sonntag;
                break;
            case 0: return Montag;
                break;
        }
    }
}

/*
 *  Funktion: ersterTagDesMonats
 * 
 *  Ermittelt den Wochentag korrespondierend mit dem ersten Tag eines
 *  Monats in einem bestimmten Jahr.
 * 
 *  in monat: int  -- Ein beliebiger Monat im Jahr
 *  in jahr:  int  -- Ein beliebiges Jahr
 * 
 *  return: enum Wochentage -- Der ermittelte Wochentag
 * 
 */

enum Wochentage ersterTagDesMonats(int& monat, int& jahr) {
    vector<int> tageProMonat = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int monatsdifferenz = 0;
    if (istSchaltjahr(jahr)) {
        tageProMonat[1] = 29;
    }

    for (int i = 1; i < monat; i++) {
        monatsdifferenz += tageProMonat[i - 1];
    }

    return tagAusDifferenzErmitteln(ersterJanuarDesJahres(jahr), monatsdifferenz);
}

/*
 *  Funktion: wochentag
 * 
 *  Ermittelt den Wochentag korrespondierend mit einem beliebigen Datum.
 * 
 *  in tag:   int  -- Ein beliebiger Tag im Monat
 *  in monat: int  -- Ein beliebiger Monat im Jahr
 *  in jahr:  int  -- Ein beliebiges Jahr
 * 
 *  return: enum Wochentage -- Der ermittelte Wochentag
 * 
 */

enum Wochentage wochentag(int& tag, int& monat, int& jahr) {
    //-1 weil die Betrachtung beim ersten Tag des Monats beginnt
    int differenz = tag - 1;

    return tagAusDifferenzErmitteln(ersterTagDesMonats(monat, jahr), differenz);
}

int main() {

    cout << "Dieses Programm gibt ihnen den Wochentag des von ihnen eingegebenen Datums ein." << endl;

    int tag, monat, jahr = 0;

    do {
        cout << "Bitte geben sie ein Datum im Datumsformat ein. z.B. 24.12.2017" << endl;
        correctInput(tag,monat,jahr);
        if (!istGueltig(tag, monat, jahr)) cout << "Fehler!" << endl;
    } while (!istGueltig(tag, monat, jahr));

    cout << "Der erste Januar des Jahres " << jahr << " ist ein ";
    outputWochentag(ersterJanuarDesJahres(jahr));
    cout << endl;

    cout << "Der erste Wochentag des " << monat << ". Monats ist ein ";
    outputWochentag(ersterTagDesMonats(monat, jahr));
    cout << endl;

    cout << "Der " << tag << ". Tag des " << monat << ". Monats im Jahr " << jahr << " ist ein ";
    outputWochentag(wochentag(tag, monat, jahr));
    cout << endl;

    return 0;
}