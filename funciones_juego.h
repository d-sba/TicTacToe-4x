#define hum 1
#define ord 2
#define N 8


/**< Funciones del tablero */
void iniciar (int tauler[N][N]);
void dibujarTablero (int tauler[N][N]);
void copiaMatriz(int copia[N][N], int original[N][N]);
void espejo(int tauler[N][N]);
void destruirColumna(int tauler[N][N], int n);


/**< Funciones relacionadas con el estado del tablero */
int columnaLlena(int tauler[N][N], int opc);
int contarColumnasLibres(int tauler[N][N]);
int empate (int tauler [N][N]);
void tirar(int tauler[N][N], int col, int jug);
int ganador(int tauler[N][N],int jug);
void ganador2(int tauler[N][N],int jug, int *iAux, int *jAux, int *dir);


/**< Jugadas */
void jugadaHumano(int tauler[N][N], int jug);
void jugadaOrdenador(int tauler[N][N], int dificultad, int *ultimCol);


/**< Modos de juego */
int elegirModo();
void fraseModoJuego(int dif, int com);
void Jugs(int tauler[N][N]);
void CPU(int tauler[N][N]);


/**< Extras */
int dificultad();
int numAleat(int n);
int comodines();
void comodinEspejo(int tauler[N][N],int *com);
void comodinColumna(int tauler[N][N],int *com);


