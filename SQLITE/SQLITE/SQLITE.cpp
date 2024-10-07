// SQLITE.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include <iostream>
#include <sqlite3.h>  // Llibreria SQLite

using namespace std;

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << endl;
    return 0;
}

int main() {
    sqlite3* db;
    char* errMsg = 0;
    int rc;

    // Connectar a la base de dades (es crea si no existeix)
    rc = sqlite3_open("test.db", &db);
    if (rc) {
        cerr << "No es pot obrir la base de dades: " << sqlite3_errmsg(db) << endl;
        return rc;
    }
    else {
        cout << "Connexió a la base de dades oberta amb èxit!" << endl;
    }

    // Crear una taula si no existeix
    const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS PERSONES ("
        "ID INT PRIMARY KEY NOT NULL, "
        "NOM TEXT NOT NULL, "
        "EDAT INT NOT NULL);";
    rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error creant la taula: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "Taula PERSONES creada o ja existent." << endl;
    }

    // Inserir dades
    const char* sqlInsert = "INSERT INTO PERSONES (ID, NOM, EDAT) "
        "VALUES (1, 'Joan', 30);"
        "INSERT INTO PERSONES (ID, NOM, EDAT) "
        "VALUES (2, 'Anna', 25);";
    rc = sqlite3_exec(db, sqlInsert, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error inserint dades: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "Dades inserides amb èxit!" << endl;
    }

    // Seleccionar i mostrar les dades
    const char* sqlSelect = "SELECT * FROM PERSONES;";
    cout << "Dades de la taula PERSONES:" << endl;
    rc = sqlite3_exec(db, sqlSelect, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error seleccionant dades: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    // Tancar la connexió amb la base de dades
    sqlite3_close(db);
    return 0;
}
