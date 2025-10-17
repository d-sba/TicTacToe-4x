#define victoria 100

typedef struct node{
    int tauler[N][N];
    int n_fills;
    struct node* *fills;
    int *cols;
    int heu;
}Node;


/**<                     ------------------------------ ARBOL ------------------------------                               */
/**<                                    ------------------------------------ */

/**< Funciones para crear los distintos elementos del arbol */
Node *creaArrel(int tauler[N][N]);
Node *creaNode(Node *pare, int profunditat, int col,int jug, int dificultad,int *m);
void crea1Nivell(Node *pare,int profunditat, int jug, int dificultad,int *m);
void crea2Nivell(Node *pare, int profunditat,int dificultad,int *m);

/**< Funciones para el arbol */
void creaArbre (Node *arrel, int profunditat,int dificultad, int *m);
void borrarArbre(Node *arrel, int *f);


/**<                     ------------------------------ MINIMAX ------------------------------                             */
/**<                                    ------------------------------------ */

/**< Funciones para valorar los distintos componentes */
int heuristica(int tauler[N][N]);
void valorarFullas(Node *arrel);
void valoraArbol (Node *arrel, int dificultad);

/**< MiniMax */
int miniMax (Node *arrel,int dificultad);



/**< EXTRAS */
int heuristica2(int tauler[N][N]);
void dibujaPuntos2(Node *arrel);
void dibujaPuntos1(Node *arrel);
