#include <iostream>
#include <vector>

using namespace std;

int mini = -99999999;
int maxi = 99999999;

int FILAS = 6;
int COLUMNAS = 7;

class Conecta4 {
public:
    Conecta4() {
         // Inicializar el tablero con ' ' en todas las posiciones
        for (int i = 0; i < FILAS; ++i) {
            // Crear una fila vacía
            vector<char> fila;
            for (int j = 0; j < COLUMNAS; ++j) {
                 // Llenar la fila con ' ' (espacios en blanco)
                fila.push_back(' ');
            }
            // Agregar la fila al tablero
            tablero.push_back(fila);
        }
        jugadorActual = 'P';
    }
     // Función para mostrar el estado actual del tablero
    void mostrarTablero() {
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                cout << tablero[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
        // Función para realizar una jugada en una columna
    bool realizarJugada(int columna) {
        for (int i = FILAS - 1; i >= 0; --i) {
            if (tablero[i][columna] == ' ') {
                // Encontrar la primera celda vacía en la columna y colocar la ficha del jugador actual
                tablero[i][columna] = jugadorActual;
                return true;  // Jugada realizada con éxito
            }
        }
        return false;  // Columna llena, no se puede realizar la jugada
    }
       bool esVictoria() {
 // Verificar filas
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j <= COLUMNAS - 4; ++j) {
                if (tablero[i][j] != ' ' &&
                    tablero[i][j] == tablero[i][j + 1] &&
                    tablero[i][j] == tablero[i][j + 2] &&
                    tablero[i][j] == tablero[i][j + 3]) {
                    return true;
                }
            }
        }

        // Verificar columnas
        for (int i = 0; i <= FILAS - 4; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                if (tablero[i][j] != ' ' &&
                    tablero[i][j] == tablero[i + 1][j] &&
                    tablero[i][j] == tablero[i + 2][j] &&
                    tablero[i][j] == tablero[i + 3][j]) {
                    return true;
                }
            }
        }

        // Verificar diagonales ascendentes
        for (int i = 3; i < FILAS; ++i) {
            for (int j = 0; j <= COLUMNAS - 4; ++j) {
                if (tablero[i][j] != ' ' &&
                    tablero[i][j] == tablero[i - 1][j + 1] &&
                    tablero[i][j] == tablero[i - 2][j + 2] &&
                    tablero[i][j] == tablero[i - 3][j + 3]) {
                    return true;
                }
            }
        }

        // Verificar diagonales descendentes
        for (int i = 0; i <= FILAS - 4; ++i) {
            for (int j = 0; j <= COLUMNAS - 4; ++j) {
                if (tablero[i][j] != ' ' &&
                    tablero[i][j] == tablero[i + 1][j + 1] &&
                    tablero[i][j] == tablero[i + 2][j + 2] &&
                    tablero[i][j] == tablero[i + 3][j + 3]) {
                    return true;
                }
            }
        }

        return false;
    }
        bool tableroLLeno() {
        // Lógica para verificar si todas las celdas del tablero están ocupadas
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                if (tablero[i][j] == ' ') {
                    return false;  // Todavía hay celdas vacías
                }
            }
        }
        return true;  // Todas las celdas están ocupadas, empate
    }

    // Función para cambiar el turno al siguiente jugador
    void cambiarTurno() {
        jugadorActual = (jugadorActual == 'P') ? 'O' : 'P';
    }
        // Función para obtener el jugador actual
    char obtenerJugadorActual() {
        return jugadorActual;
    }
        // Función para obtener las columnas disponibles para realizar una jugada
    vector<int> obtenerColumnasDisponibles() {
        vector<int> columnasDisponibles;
        for (int j = 0; j < COLUMNAS; ++j) {
            if (tablero[0][j] == ' ') {
                columnasDisponibles.push_back(j);
            }
        }
        return columnasDisponibles;
    }


private:
    vector<vector<char>> tablero;
    char jugadorActual;
};

int evaluarTablero(Conecta4& juego) {
    if (juego.esVictoria()) {
        return (juego.obtenerJugadorActual() == 'P') ? mini + 1 : maxi - 1;
    } else if (juego.tableroLLeno()) {
        return 0;
    }
    return 0;
}
// Intenté hacer la función minimax pero al parecer no logré hacerla funcionar.
int minimax(Conecta4& juego, int profundidad, bool esMaximizador) {
    if (profundidad == 0 || juego.esVictoria() || juego.tableroLLeno()) {
        return evaluarTablero(juego);
    }

    if (esMaximizador) {
        int mejorValor = mini;
        vector<int> columnasDisponibles = juego.obtenerColumnasDisponibles();

        for (int columna : columnasDisponibles) {
            Conecta4 copiaJuego = juego;
            copiaJuego.realizarJugada(columna);
            int valor = minimax(copiaJuego, profundidad - 1, false);
            mejorValor = max(mejorValor, valor);
        }

        return mejorValor;
    } else {
        int mejorValor = maxi;
        vector<int> columnasDisponibles = juego.obtenerColumnasDisponibles();

        for (int columna : columnasDisponibles) {
            Conecta4 copiaJuego = juego;
            copiaJuego.realizarJugada(columna);
            int valor = minimax(copiaJuego, profundidad - 1, true);
            mejorValor = min(mejorValor, valor);
        }

        return mejorValor;
    }
}

int obtenerMejorMovimiento(Conecta4& juego) {
    int mejorMovimiento = -1;
    int mejorValor = mini;
    vector<int> columnasDisponibles = juego.obtenerColumnasDisponibles();

    for (int columna : columnasDisponibles) {
        Conecta4 copiaJuego = juego;
        copiaJuego.realizarJugada(columna);
        int valor = minimax(copiaJuego, 3, false);
        if (valor > mejorValor) {
            mejorValor = valor;
            mejorMovimiento = columna;
        }
    }

    return mejorMovimiento;
}
int dificultad() {
    int dif;
    cout << "DIFICULTAD\n";
    cout << "1. FACIL\n";
    cout << "2. MEDIO\n";
    cout << "3. DIFICIL\n";
    cin >> dif;
    switch (dif){
    case 1:
        return dif;
        break;
    case 2:
        return dif;
        break;
    case 3:
        return dif;
        break;

    }
}
void menu() {
    int dif;
    cout << "BIENVENIDO AL JUEGO DE CONECTA 4\n";
    cout << "PRESIONE 1 PARA INICIAR EL JUEGO\n";
    cout << "PRESIONE 2 PARA SALIR\n";
    int op;
    cin >> op;
    switch (op)
    {
    case 1:{
        dif = dificultad();
        break;
    }
    case 2:
        break;
    default:
        cout << "OPCION INVALIDA";
    }
}

int main() {
    Conecta4 juego; 
    menu();
    
    while (true) {
        juego.mostrarTablero();

        if (juego.obtenerJugadorActual() == 'P') {
            int columna;
            cout << "TURNO DEL JUGADOR " << juego.obtenerJugadorActual() << "\n";
            do {
                cout << "INGRESE LA COLUMNA (0-" << COLUMNAS - 1 << "): ";
                cin >> columna;
            } while (columna < 0 || columna >= COLUMNAS || !juego.realizarJugada(columna));
        } else {
            cout << "TURNO DE LA COMPUTADORA\n";
            int mejorMovimiento = obtenerMejorMovimiento(juego);
            juego.realizarJugada(mejorMovimiento);
        }

        if (juego.esVictoria()) {
            juego.mostrarTablero();
            cout << "¡EL JUGADOR " << juego.obtenerJugadorActual() << " HA GANADO!\n";
            break;
        } else if (juego.tableroLLeno()) {
            juego.mostrarTablero();
            cout << "EMPATE, EL TABLERO ESTA LLENO\n";
            break;
        }

        juego.cambiarTurno();
    }

    return 0;

}