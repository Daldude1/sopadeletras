#include <iostream> // esto incluye la librería estándar para entrada y salida de datos como cout y cin
#include <cstdlib>  // esto permite usar funciones como rand() y srand() para generar números aleatorios
#include <ctime>    // esto permite trabajar con la función time() para inicializar la semilla de números aleatorios
#include <string>   // esto permite trabajar con cadenas de texto o strings

using namespace std; // esto evita que se necesite escribir std:: antes de cout, cin, etc

const int TAMANO = 10; // esto define que el tablero será de 10 por 10
const int VIDAS = 3; // esto establece que el jugador tendrá 3 vidas
const int INTENTOS = 10; // esto establece que el jugador tendrá 10 intentos
const string PALABRAS[4] = {"gato", "perro", "ave", "pez"}; // esto define las palabras que se tendrán que buscar en el tablero

// esta función inicializa el tablero llenándolo con letras aleatorias de la 'a' a la 'z'
void inicializarTablero(char tablero[TAMANO][TAMANO]) {
    for (int i = 0; i < TAMANO; i++) { // este bucle recorre las filas del tablero
        for (int j = 0; j < TAMANO; j++) { // este bucle recorre las columnas del tablero
            tablero[i][j] = 'a' + rand() % 26; // esto asigna una letra aleatoria a cada celda del tablero
        }
    }
}

// esta función intenta colocar una palabra en el tablero en una dirección aleatoria
bool colocarPalabra(char tablero[TAMANO][TAMANO], string palabra) {
    int direccion = rand() % 8; // esto genera una dirección aleatoria del 0 al 7
    int fila = rand() % TAMANO; // esto genera una posición inicial de fila aleatoria
    int columna = rand() % TAMANO; // esto genera una posición inicial de columna aleatoria

    int deltaFila = 0, deltaColumna = 0; // estas variables determinan la dirección del movimiento
    switch (direccion) { // este switch determina la dirección en la que se colocará la palabra
        case 0: deltaFila = -1; break; // esto moverá hacia arriba
        case 1: deltaFila = 1; break;  // esto moverá hacia abajo
        case 2: deltaColumna = -1; break; // esto moverá hacia la izquierda
        case 3: deltaColumna = 1; break;  // esto moverá hacia la derecha
        case 4: deltaFila = -1; deltaColumna = -1; break; // esto moverá en diagonal hacia arriba e izquierda
        case 5: deltaFila = -1; deltaColumna = 1; break;  // esto moverá en diagonal hacia arriba y derecha
        case 6: deltaFila = 1; deltaColumna = -1; break;  // esto moverá en diagonal hacia abajo e izquierda
        case 7: deltaFila = 1; deltaColumna = 1; break;   // esto moverá en diagonal hacia abajo y derecha
    }

    // este bucle verifica si es posible colocar la palabra en la dirección elegida
    for (int i = 0; i < palabra.length(); i++) {
        int nuevaFila = fila + i * deltaFila; // esto calcula la fila de la posición actual
        int nuevaColumna = columna + i * deltaColumna; // esto calcula la columna de la posición actual

        // esto verifica si la posición actual está dentro de los límites del tablero
        if (nuevaFila < 0 || nuevaFila >= TAMANO || nuevaColumna < 0 || nuevaColumna >= TAMANO) {
            return false; // si no está dentro de los límites, no se puede colocar la palabra
        }
    }

    // este bucle coloca la palabra en el tablero
    for (int i = 0; i < palabra.length(); i++) {
        int nuevaFila = fila + i * deltaFila; // esto calcula la fila de la posición actual
        int nuevaColumna = columna + i * deltaColumna; // esto calcula la columna de la posición actual
        tablero[nuevaFila][nuevaColumna] = palabra[i]; // esto asigna la letra actual de la palabra al tablero
    }

    return true; // esto indica que la palabra se colocó exitosamente
}

// esta función se encarga de colocar todas las palabras en el tablero
void colocarPalabrasEnTablero(char tablero[TAMANO][TAMANO]) {
    for (int i = 0; i < 4; i++) { // este bucle recorre todas las palabras definidas en el arreglo PALABRAS
        while (true) { // este bucle intenta colocar cada palabra hasta que se logre
            if (colocarPalabra(tablero, PALABRAS[i])) { // esto llama a la función colocarPalabra para colocar la palabra actual
                break; // si la palabra se colocó exitosamente, se rompe el bucle
            }
        }
    }
}

// esta función muestra el tablero en la consola
void mostrarTablero(char tablero[TAMANO][TAMANO]) {
    for (int i = 0; i < TAMANO; i++) { // este bucle recorre todas las filas del tablero
        for (int j = 0; j < TAMANO; j++) { // este bucle recorre todas las columnas de la fila actual
            cout << tablero[i][j] << " "; // esto imprime el contenido de la celda actual seguido de un espacio
        }
        cout << endl; // esto imprime un salto de línea al final de cada fila
    }
}

// esta función verifica si una palabra ingresada es válida
bool esPalabraValida(string palabra) {
    for (int i = 0; i < 4; i++) { // este bucle recorre todas las palabras definidas en el arreglo PALABRAS
        if (PALABRAS[i] == palabra) { // esto compara la palabra ingresada con la palabra actual del arreglo
            return true; // si la palabra coincide, se retorna true
        }
    }
    return false; // si ninguna palabra coincide, se retorna false
}

// esta es la función principal que ejecuta el juego
int main() {
    char tablero[TAMANO][TAMANO]; // esto define el tablero de juego
    int vidas = VIDAS; // esto inicializa las vidas del jugador
    int intentos = INTENTOS; // esto inicializa los intentos del jugador
    string palabra; // esto almacenará la palabra ingresada por el jugador

    srand(time(NULL)); // esto inicializa la semilla de números aleatorios
    inicializarTablero(tablero); // esto llama a la función para inicializar el tablero con letras aleatorias
    colocarPalabrasEnTablero(tablero); // esto llama a la función para colocar las palabras en el tablero

    // esto imprime las instrucciones iniciales del juego
    cout << "bienvenido a la sopa de letras" << endl;
    cout << "encuentra las palabras: gato, perro, ave, pez" << endl;
    cout << "tienes " << VIDAS << " vidas y " << INTENTOS << " intentos" << endl;

    // este bucle principal ejecuta el juego mientras el jugador tenga vidas e intentos
    while (vidas > 0 && intentos > 0) {
        mostrarTablero(tablero); // esto muestra el tablero al jugador
        cout << "introduce una palabra: ";
        cin >> palabra; // esto lee la palabra ingresada por el jugador

        if (esPalabraValida(palabra)) { // esto verifica si la palabra ingresada es válida
            cout << "correcto encontraste una palabra" << endl;
        } else {
            if (palabra.length() <= 3) { // esto verifica si la palabra ingresada tiene 3 letras o menos
                cout << "palabra no válida pero no pierdes una vida" << endl;
                intentos--; // esto reduce los intentos restantes
            } else {
                cout << "palabra incorrecta pierdes una vida" << endl;
                vidas--; // esto reduce las vidas restantes
            }
        }

        // esto imprime las vidas e intentos restantes
        cout << "vidas restantes: " << vidas << endl;
        cout << "intentos restantes: " << intentos << endl;

        if (vidas <= 0) { // esto verifica si el jugador se quedó sin vidas
            cout << "te quedaste sin vidas fin del juego" << endl;
            break; // esto termina el juego
        }

        if (intentos <= 0) { // esto verifica si el jugador se quedó sin intentos
            cout << "te quedaste sin intentos fin del juego" << endl;
            break; // esto termina el juego
        }
    }

    if (vidas > 0 && intentos > 0) { // esto verifica si el jugador terminó el juego exitosamente
        cout << "felicitaciones terminaste el juego" << endl;
    }

    return 0; // esto indica que el programa terminó correctamente
}
