#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int TAMANO = 10;
const int VIDAS = 3;
const int INTENTOS = 10;
const string PALABRAS[4] = {"gato", "perro", "ave", "pez"};

void inicializarTablero(char tablero[TAMANO][TAMANO]) {
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            tablero[i][j] = 'a' + rand() % 26;
        }
    }
}

bool colocarPalabra(char tablero[TAMANO][TAMANO], string palabra) {
    int direccion = rand() % 8;
    int fila = rand() % TAMANO;
    int columna = rand() % TAMANO;

    int deltaFila = 0, deltaColumna = 0;
    switch (direccion) {
        case 0: deltaFila = -1; break; 
        case 1: deltaFila = 1; break;  
        case 2: deltaColumna = -1; break; 
        case 3: deltaColumna = 1; break;  
        case 4: deltaFila = -1; deltaColumna = -1; break; 
        case 5: deltaFila = -1; deltaColumna = 1; break;  
        case 6: deltaFila = 1; deltaColumna = -1; break;  
        case 7: deltaFila = 1; deltaColumna = 1; break;   
    }

    for (int i = 0; i < palabra.length(); i++) {
        int nuevaFila = fila + i * deltaFila;
        int nuevaColumna = columna + i * deltaColumna;

        if (nuevaFila < 0 || nuevaFila >= TAMANO || nuevaColumna < 0 || nuevaColumna >= TAMANO) {
            return false; 
        }

        if (tablero[nuevaFila][nuevaColumna] != palabra[i] && tablero[nuevaFila][nuevaColumna] != ' ') {
            return false;
        }
    }

    for (int i = 0; i < palabra.length(); i++) {
        int nuevaFila = fila + i * deltaFila;
        int nuevaColumna = columna + i * deltaColumna;
        tablero[nuevaFila][nuevaColumna] = palabra[i];
    }

    return true;
}

void colocarPalabrasEnTablero(char tablero[TAMANO][TAMANO]) {
    for (int i = 0; i < 4; i++) {
        bool colocada = false;
        while (colocada == false) {
            colocada = colocarPalabra(tablero, PALABRAS[i]);
        }
    }
}

void mostrarTablero(char tablero[TAMANO][TAMANO]) {
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

bool esPalabraValida(string palabra) {
    for (int i = 0; i < 4; i++) {
        if (PALABRAS[i] == palabra) {
            return true;
        }
    }
    return false;
}

int main() {
    char tablero[TAMANO][TAMANO];
    int vidas = VIDAS;
    int intentos = INTENTOS;
    string palabra;

    srand(time(NULL));
    inicializarTablero(tablero);
    colocarPalabrasEnTablero(tablero);

    cout << "Bienvenido a la sopa de letras!" << endl;
    cout << "Encuentra las palabras: gato, perro, ave, pez" << endl;
    cout << "Tienes " << VIDAS << " vidas y " << INTENTOS << " intentos." << endl;

    while (vidas > 0 && intentos > 0) {
        mostrarTablero(tablero);
        cout << "Introduce una palabra: ";
        cin >> palabra;

        if (esPalabraValida(palabra)) {
            cout << "Correcto! Encontraste una palabra." << endl;
        } else {
            if (palabra.length() <= 3) {
                cout << "Palabra no válida pero no pierdes una vida." << endl;
                intentos--;
            } else {
                cout << "Palabra incorrecta! Pierdes una vida." << endl;
                vidas--;
            }
        }

        cout << "Vidas restantes: " << vidas << endl;
        cout << "Intentos restantes: " << intentos << endl;

        if (vidas <= 0) {
            cout << "Te quedaste sin vidas. Fin del juego." << endl;
            break;
        }

        if (intentos <= 0) {
            cout << "Te quedaste sin intentos. Fin del juego." << endl;
            break;
        }
    }

    if (vidas > 0 && intentos > 0) {
        cout << "Felicitaciones! Terminaste el juego." << endl;
    }

    return 0;
}
