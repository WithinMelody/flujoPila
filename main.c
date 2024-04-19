//Archivo pila_char.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
int simbolosCorrectos;
int parentesisBalanceados;
typedef struct nodo_s
{
 char dato;
 struct nodo_s *siguiente;
} nodo_t;

typedef nodo_t *ptrNodo;
typedef nodo_t *ptrPila;

/*
    Agrega un nodo al inicio de la lista ligada
    *pila es el apuntador que apunta al primer nodo de la lista ligada (la cima de la pila)
*/
void push(ptrPila *pila, char x)
{
 // Crea un nuevo nodo
 ptrNodo nodo;
 nodo = (ptrNodo)malloc(sizeof(nodo_t));
 if (nodo != NULL)
    {
     nodo->dato = x;
     // El apuntador nodo->siguiente va a apuntar al primer nodo de la lista ligada
     nodo->siguiente = *pila;
     // pila va a apuntar al nuevo nodo, con esto hacemos que el nuevo nodo sea ahora el primer nodo de la lista ligada
     *pila=nodo;
    }
}

/*
    Elimina el primer nodo de la lista ligada
    *pila es el apuntador que apunta al primer nodo de la lista ligada (la cima de la pila)
*/
char pop(ptrPila *pila)
{
 // Crea un nuevo nodo
 ptrNodo nodo;
 char x;

 // El nuevo nodo va a apuntar al primer nodo de la lista ligada
 nodo = *pila;
 x = (*pila)->dato;
 // Ahora el segundo nodo de la lista ligada va a ser el primero
 *pila = (*pila)->siguiente;
 // Borra el primer nodo de la lista ligada
 free(nodo);
 // Regresa el valor que contenía el nodo que se eliminó
 return x;
}

/*
    Regresa 1 si no hay nodos en la lista ligada y cero en caso contrario
    *pila es el apuntador que apunta al primer nodo de la lista ligada (la cima de la pila)
*/
int pila_vacia(ptrPila *pila)
{
 return (*pila == NULL ? 1:0);
}

/*
   Muestra los datos de los nodos
*/
void nodos_pila(ptrNodo nodo)
{
 if (nodo == NULL)
     printf("La pila esta vacia!!!\n");
 else
     {
        printf("Contenido de la pila: ");
      while (nodo != NULL)
            {
             printf("%c",nodo->dato);
             nodo = nodo->siguiente;
            }
      printf("\n");
     }
}
// Archivo pila_parentesis.c

int verifica_balance(char expresion[], char cabre, char ccierra);

int main()
{
    char cadena[100];
    char op;
    printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    printf("° Programa hecho por: Mariana Graciela Gallardo Garibay °\n");
    printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    system("pause");
    do
    {
        system("cls");
        simbolosCorrectos = 0;
        parentesisBalanceados = 0;
        memset(cadena,100,'\0');
        printf("Ingresa una cadena: ");
        //scanf("%s",cadena);
        fgets(cadena,100,stdin);
        fflush(stdin);
        printf("Cadena a analizar: \n%s\n",cadena);
        if(validarCadena(cadena)==1)
        {
            // Verifica si los paréntesis están balanceados
            if (verifica_balance(cadena, '(', ')') == 1){
                printf("Los parentesis estan balanceados\n");
                parentesisBalanceados = 1;
            }
            else{
                printf("Los parentesis no estan balanceados\n");
                parentesisBalanceados = 0;
            }
        }
        if(simbolosCorrectos == 1 && parentesisBalanceados == 1){
            printf("Cadena Valida!!!\n\n");
        }else{
            printf("Cadena Invalida!!!\n\n");
        }
        printf("Presione N o n para salir del programa:");
        op = getch();
        printf("\n");
    }
    while(op!='n'&&op!='N');
    return 0;
}
int validarCadena(char cadena[]){
    int tam = strlen(cadena)-1;
    if(tam==0){
            printf("Cadena vacia aceptada!!!\n");
            simbolosCorrectos = 1;
            parentesisBalanceados = 1;
        return 1;
    }

    for(int i=0; i < tam; i++){
        if(cadena[i]!='0'&&cadena[i]!='1'&&cadena[i]!='('&&cadena[i]!=')'){
                printf("Error en la posicion %i\n",i+1);
                simbolosCorrectos = 0;
                return 0;
        }
    }
    simbolosCorrectos = 1;
    return 1;
}
int verifica_balance(char expresion[], char cabre, char ccierra)
{
 int x=0, balanceados=1;
 ptrPila pila = NULL;

 // Recorre la cadena
 while (expresion[x] != '\0' && balanceados == 1)
       {
        // Si el elemento coincide con el caracter que abre, lo ingresa en la pila
        if (expresion[x]==cabre)
            push(&pila, expresion[x]);
        else
            // Si el elemento coincide con el caracter que cierra, lo saca de la pila
            if (expresion[x]==ccierra)
               {
                /* Si la pila está vacía, significa que los caracteres no están balanceados
                   porque se encontró un caracter que cierra sin que exista antes un caracter que abre
                */
                if (pila_vacia(&pila) != 1)
                    pop(&pila);
                else
                    balanceados = 0;
               }
        x++;
       }

 /* Si balanceados = 1 pero la pila no está vacía, los caracteres no están balanceados
    porque quedaron caracteres que abren sin tener su caracter que cierra
 */
 if (balanceados == 1 && pila_vacia(&pila) != 1)
     balanceados = 0;
nodos_pila(pila);
 // Se asegura de dejar la pila vacia
 while (pila_vacia(&pila) != 1)
        pop(&pila);
 return balanceados;
}
