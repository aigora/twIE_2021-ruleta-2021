
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#define N 20

//Se usa para asignar las array y cr�ditos de cada usuario
typedef struct{
char nick[N], contrasena[N];
double creditos;
} jugador;
//Se usa para almacenar los valores que han salido(Ej: 1    rojo    impar   falta).
typedef struct{
int valor;
char rojo[N], impar[N], falta[N];
}resultado;
//FUNCI�N QUE VERIFICA QUE LA CADENA DE CARACTERES INTRODUCIDA ES CORRECTA Y ESTA DENTRO DE UNOS DETERMINADOS VALORES
double checknumeric(char cifra[N], int numentero, int numdecimal, double maxima, double minima);
//FUNCI�N QUE TE DEVUELVE LA APUESTA MAS LO GANADO SI HAS GANADO O 0 SI HAS PERDIDO
double tirodebola(int juegot, int apuet, double apuestat);
//FUNCI�N VAC�A EL FICHERO RESULTADOS
void borrar();
//FUNCI�N QUE TE PERMITE REGISTRARTE O INICIAR SESI�N. Dicha funci�n va a ir guardando los datos de los usuarios registrados en el fichero "usuarios".
jugador usuario();
//FUNCI�N QUE ACTUALIZA EL VALOR DE LOS CR�DITOS EN EL FICHERO "usuarios"
void actualizar(jugador c);
//FUNCI�N QUE DETECTA SI UN ARRAY TIENE PUNTOS Y COMA. TE DEVUELVE UN 0 SI NO TIENE Y UN 1 SI TIENE.
int quitapuntocoma (char cadena[N]);
//FUNCI�N QUE BORRA LOS DATOS DEL USUARIO.
void eliminarusuario(jugador c);
//FUNCI�N QUE DETECTA LA CADENA 'SALIR'. TE DEVUELVE UN 0 SI LA DETECTA Y UN 1 SI NO LA DETECTA
int salirdeljuego(char salir[N]);
//FUNCI�N QUE CODIFICA Y DESCODIFICA EL MENSAJE
void codificar(char cadena[N],int numero);
//FUNCI�N PRINCIPAL
int main(){
    //Para poder imprimir en pantalla los acentos
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    //definir variables
    char caracter, checkvalor[N], op2[N];
    double apuesta, cred = 0;
    int i=0, juego, apue;
    jugador registro;
    //En esta estructura guardaremos el nick de usuario, su contrase�a, y sus cr�ditos
    resultado r;
    FILE *pf;
    //Vaciamos el fichero resultados.
    borrar();
    //El programa te da la biemvenida.
    printf("Bienvenido al casino ETSIDI.\nEn este casino podr�s ganar creditos o perderlos, la suerte decide.\n\n"
           "IMPORTANTE\n\tSi durante el juego metes por teclado la palabra SALIR y a continuaci�n pulsas ENTER,\n"
           "\tel juego finalizar� autom�ticamente.\n\tA no ser que el propio juego te de la opci�n de salir\n");
    //A traves de esta funci�n, los usuarios se registran o inician sesi�n.
    registro = usuario();
    //Salir del juego
    if((registro.nick[0] == '\0') && (registro.contrasena[0] == '\0') && (registro.creditos == 0)){
        return 0;
    }
    //Este bucle no
    do{
        i=1;
        printf("\n\n\n\n\nCR�DITOS DE LOS QUE DISPONEs ALTUALMENTE:\t %.1f\n", registro.creditos);
        //El fichero mesa contiene el esquema de la mesa de juego.
       pf = fopen("mesa.txt", "r");
        if(pf==NULL){
            printf("Error al leer el fichero mesa\n");
            return 0;
        }
        while(feof(pf) == 0){
            caracter = fgetc(pf);
            if(caracter != '�'){
                printf("%c", caracter);
            }
        }
        //Se cierra el fichero mesa
        fclose(pf);
        //Si por error ha entrado un usuario con 0 creditos.
        if(registro.creditos < 0.1){
            //Elimina el usuario.
            eliminarusuario(registro);
            //Descodifica el nick
            codificar(registro.nick, -2);
            printf("El usuario %s ha sido eliminado.\n", registro.nick);
            return 0;
        }
        //Este es el men� de juego.
        printf("\n\nMEN� DE JUEGO\nMarca la opci�n de apuesta que deseas\n 1\tApostar a un n�mero\n 2\tApostar a un color\n 3\tApostar a par o impar\n"
               " 4\tApostar a pasa o falta\n 5\tMostrar resultados anteriores\n 6\tCambiar de usuario\n 7\tEliminar usuario\n 8\tSALIR\n");
        //pide una de las opciones, en caso de coincidir con una de las opciones correctas, la funci�n cheknumeric devuelve el valor 0 o inferior
        do{
            printf("\nIndique 1, 2, 3, 4, 5, 6, 7 o 8:\t");
            scanf(" %[^\n]", checkvalor);
            //Salir del juego
            if(salirdeljuego(checkvalor) == 0){
                return 0;
            }
            //Validamos que el valor introducido esta dentro del rango marcado
            juego=checknumeric(checkvalor, 1, 0, 8, 1);
            if(juego <= 0){
                printf("\nOpci�n marcada incorrecta\n", checkvalor, juego);
            }
        }while(juego<=0);
        switch (juego){
        //Apuesta a un n�mero: Te pide el n�mero al que quieres apostar y te lo valida para que est� dentro de rango.
            case 1:{
                do{
                    printf("�A qu� n�mero quieres apostar? Del 1 al 36: \t");
                    scanf(" %[^\n]", checkvalor);
                    //Salir del juego
                    if(salirdeljuego(checkvalor) == 0){
                        return 0;
                    }
                    apue = checknumeric(checkvalor, 2, 0, 36, 1);
                    if(juego <= 0){
                        printf("\nN�mero marcado incorrecto\n");
                    }
                } while(apue<=0);
                i=1; //Con este indicador entraremos en las sentencias de final de partda.
                break;
            }
            // Apuesta a rojo o negro:
            case 2:{
                do{
                    printf("�A qu� quieres apostar, negros o rojos (n/r)? \t");
                    scanf(" %[^\n]", op2);
                    //Salir del juego
                    if(salirdeljuego(op2) == 0){
                        return 0;
                    }
                    //Cambia las letras introducidas en la cadena a may�sculas.
                    for(i=0;op2[i]!='\0';i++){
                    op2[i]=toupper(op2[i]);
                    }
                    if((op2[0]=='N') && (op2[1]=='\0')){
                        apue = 1;
                   }
                    if((op2[0]=='R') && (op2[1]=='\0')){
                        apue = 0;
                   }
                   if(((op2[0]!='N') && (op2[0]!='R')) || (op2[1]!='\0')){
                        printf("\nLa respuesta indicada es incorrecta\n");
                        apue=2;
                    }
                }
                while(apue == 2);
                i=1; //Con este indicador entraremos en las sentencias de final de partida.
                break;
            }
            //Apuesta a impar o par
            case 3:{
                do{
                    printf("�A qu� quieres apostar, impar o par (i/p)? \t");
                    scanf(" %[^\n]", op2);
                    //Salir del juego
                    if(salirdeljuego(op2) == 0){
                        return 0;
                    }
                    //Cambia las letras introducidas en la cadena a may�sculas.
                    for(i=0;op2[i]!='\0';i++){
                    op2[i]=toupper(op2[i]);
                    }
                    if((op2[0]=='I') && (op2[1]=='\0')){
                        apue = 1;
                   }
                    if((op2[0]=='P') && (op2[1]=='\0')){
                        apue = 0;
                   }
                    if(((op2[0]!='I') && (op2[0]!='P')) || (op2[1]!='\0')){
                        printf("\nLa respuesta indicada es incorrecta\n");
                        apue=2;
                    }
                }while(apue == 2);
                i=1;//Con este indicador entraremos en las sentencias de final de partida.
                break;
            }
            //Apuesta a pasa o falta.
            case 4:{
                do{
                    printf("�A qu� quieres apostar, falta (1-18) o pasa (19-36) (f/p)? \t");
                    scanf(" %[^\n]", op2);
                    //Salir del juego
                    if(salirdeljuego(op2) == 0){
                        return 0;
                    }
                    //Cambia las letras introducidas en la cadena a may�sculas.
                    for(i=0;op2[i]!='\0';i++){
                    op2[i]=toupper(op2[i]);
                    }
                    if((op2[0]=='F') && (op2[1]=='\0')){
                        apue = 1;
                   }
                    if((op2[0]=='P') && (op2[1]=='\0')){
                        apue = 0;
                   }
                     if(((op2[0]!='F') && (op2[0]!='P')) || (op2[1]!='\0')){
                        printf("\nLa respuesta indicada es incorrecta\n");
                        apue=2;
                    }
                }
                while(apue == 2);
                i=1; //Con este indicador entraremos en las sentencias de final de partida.
                break;
            }
            //Muestra los resultados obtenidos anteriormente.
            case 5:{
                pf = fopen("resultados.txt", "r");
                if(pf==NULL){
                    printf("Error al leer el fichero resultados\n");
                }
                printf("\n\n\n\n");
                //Lee e imprime en pantalla los valores que han ido saliendo, almacenados en el fichero resultados.
                while(feof(pf)==0){
                    fscanf(pf, "\n\n%d,%[^,],%[^,],%[^\n]\n\n", &r.valor, r.rojo, r.impar, r.falta);
                    printf("%d\t %s\t %s\t %s\n", r.valor, r.rojo, r.impar, r.falta);
                }
                fclose(pf);
                i=1; //Con este indicador se entra en las sentencias de final de partida.
                break;
            }
            //Cambiar de usuario o crearte uno nuevo.
            case 6:{
                //Abre la funci�n usuarios
                registro = usuario();
                //Salir del juego
                if((registro.nick[0] == '\0') && (registro.contrasena[0] == '\0') && (registro.creditos == 0)){
                    return 0;
                }
                i = 0; //Con este indicador NO se entra en las sentencias de final de partida.
                break;
            }
            //Esta funci�n elimina el usuario con el que est�s jugando
            case 7:{
                eliminarusuario(registro);
                //Te da la opci�n de iniciar sesi�n o registrarte con otro usuario, o salir.
                do{
                    printf("Quieres iniciar sesi�n o registrarte? Marque SI o NO.\nSI\t Iniciar sesi�n o Reg�strarme.\nNO\t Salir del juego.\n");
                    scanf(" %[^\n]", op2);
                    //Salir del juego
                    if(salirdeljuego(op2) == 0){
                        return 0;
                    }
                    //Pone la cadena en may�sculas.
                    for(i=0;op2[i]!='\0';i++){
                        op2[i]=toupper(op2[i]);
                    }
                    if((op2[0]=='N') && (op2[1]=='O') && (op2[2]=='\0')){
                        return 0;
                    }
                   if((op2[0]=='S') && (op2[1]=='I')  && (op2[2]=='\0')){
                        registro = usuario();
                        i = 0;
                   }
                    else{
                        printf("La respuesta indicada es incorrecta\n");
                        i=1;
                    }
                }while(i==1); //Cuando sale del bucle es con i=0, por lo que NO se entra en las sentencias de final de partida.
                break;
            }
            //Salir del juego
            case 8:{
                return 0;
                break;
            }
        }
        //Solo te entra en esta opci�n si has marcado una de las opciones con la que puedes jugar.
        if((juego == 1) || (juego == 2) || (juego == 3) || (juego == 4)){
             //Te pide la cantidad que deseas apostar, validando que la cantidad sea correcta.
            do{
                printf("�Cu�nto quieres apostar? El l�mite son 999.9 cr�ditos: \t");
                scanf(" %[^\n]", checkvalor);
                //Salir del juego
                if(salirdeljuego(checkvalor) == 0){
                    return 0;
                }
                apuesta = checknumeric(checkvalor, 3, 1, registro.creditos, 0);
                if(apuesta <= 0){
                    printf("\nLa apuesta es incorrecta\n Recuerda que tiene que estar comprendida estre el 0.1 y sus cr�ditos actuales\n");
                }
            }while(apuesta <= 0);
            //Restamos la apuesta a nuestro n�mero de cr�dios
            registro.creditos = registro.creditos - apuesta;
            //Asignamos a apuesta el valor de cr�ditos optenidos si se gana, o 0 si se pierde.
            apuesta = tirodebola(juego, apue, apuesta);
            if(apuesta > 0){
                printf("\nHas GANADO. Se te devuelven %.1f cr�ditos\n", apuesta);
            }
            if(apuesta == 0){
                printf("\nHas PERDIDO. Se te devuelven %.1f creditos\n", apuesta);
            }
            //Si apuesta tiene un valor menor a 0, es que se ha producido un error, por lo que el programa borra el fichero de resultados y se cierra.
            if(apuesta < 0){
                printf("\nSe a producido un error\n");
                borrar();
                return -10;
            }
            //Sumamos lo ganado a nuestros cr�ditos.
            registro.creditos = registro.creditos + apuesta;
            //Actualizamos el valor de cr�ditos del usuario en el fichero usuario.
            actualizar(registro);
        }
        //Fin de la partida.
        while(i==1){
            //Si su saldo es igual a 0, la partida se acaba y el progrma se cierra
            if(registro.creditos<=0){
                printf("Tu saldo actual es de %.1f cr�ditos\nFIN DE LA PARTIDA\n", registro.creditos);
                //Esta funci�n elimina el usuario actual, ya que ha perdido todos sus creditos.
                eliminarusuario(registro);
                //Descodifica el nick
                codificar(registro.nick, -2);
                printf("El usuario %s ha sido eliminado.\n", registro.nick);
                //Te da la opci�n de iniciar sesi�n / registrarte con otro usuario o salir.
                do{
                    printf("\nQuieres iniciar sesi�n o registrarte? Marca SI o NO.\nSI\t Iniciar sesi�n o Reg�strame.\nNO\t Salir del juego.\n");
                    scanf(" %[^\n]", op2);
                    //Salir del juego
                    if(salirdeljuego(op2) == 0){
                        return 0;
                    }
                    //Pone la cadena en may�sculas.
                    for(i=0;op2[i]!='\0';i++){
                        op2[i]=toupper(op2[i]);
                    }
                    if((op2[0]=='N') && (op2[1]=='O') && (op2[2]=='\0')){
                        return 0;
                    }
                   if((op2[0]=='S') && (op2[1]=='I')  && (op2[2]=='\0')){
                        //Abre la funci�n registro para que el usuario se pueda reistrar de nuevo o iniciar sesi�n con otra cuenta.
                        registro = usuario();
                        i = 0;
                   }
                    else{
                        printf("La respuesta indicada es incorrecta\n");
                        i=1;
                    }
                }while(i==1);//De este bucle solo se sale con i=0, para poder volver al menu de juego.
            }

            //Te pregunta si quieres volver al men� para jugar otra partida
            printf("Tu saldo actual es de %.1f cr�ditos\n�Quieres volver a jugar? marca SI o NO\n", registro.creditos);
            scanf(" %[^\n]", op2);
            //Salir del juego
            if(salirdeljuego(op2) == 0){
                return 0;
            }
            //Cambia las letras introducidas en la cadena a may�sculas.
            for(i=0;op2[i]!='\0';i++){
                op2[i]=toupper(op2[i]);
            }
            if((op2[0]=='N') && (op2[1]=='O') && (op2[2]=='\0')){
                i=2;
                break;
            }
           if((op2[0]=='S') && (op2[1]=='I')  && (op2[2]=='\0')){
                i=0;
           }
            else{
                printf("La respuesta indicada es incorrecta\n");
                i=1;
            }
        }
    }while(i==0);
    //Antes de cerrar el programa borra el fichero registro donde se han ido alamacenando todos lo resultados de la partida.
    borrar();
    printf("\n\n\n\n\nHasta la pr�xima partida\n\n");
    return 0;
}
//FUNCI�N QUE VERIFICA QUE LA CADENA DE CARACTERES INTRODUCIDA ES CORRECTA Y ESTA DENTRO DE UNOS DETERMINADOS VALORES
double checknumeric(char cifra[N], int numentero, int numdecimal, double maxima, double minima){

    //Definici�n de variables
    char cadenanum[10]="0123456789", punto[1]=".", valorresultante[N];
    int i=0, j=0, k=0, longitud, contenteros=0, contdecimales=0, contpuntos=0, longitudmaxima;
    double numcorrecto;
    //Lo primero que hace la funci�n es quitar los ceros sobrantes, tanto de la izquierda como de la derecha.
    // recorremos el valor de izquierda a derecha y quitamos todos los ceros no significativos de la izquiera manteniendo al menos un 0 en la parte entera
    while (cifra[i] != '\0'){
        if ((cifra[i] != '0') || (j > 0)){
            if ((cifra[i] == '.') && (j==0)){
                valorresultante[j] = '0';
                j++;
            }
            valorresultante[j] = cifra[i];
            j++;
        }
        i++;
    }
    if (j==0){
      valorresultante[j] = '0';
      ++j;
    }
    valorresultante[j] = '\0';
    // Pasamos el contenido de la variable ValorResult a Valor para seguir operando
    i = 0;
    for(i=0;valorresultante[i]!='\0';i++){
        cifra[i] = valorresultante[i];
    }
    cifra[i] = '\0';
    // j es la longitud del vector resultante
    // conocemos si hay decimales y en que posici�n est� el separador decimal
    i = 0;
    while (cifra[i] != '\0'){
        if (cifra[i] == '.'){
            k = i+1;
            break;
        }
        ++i;
    }
    // Recorremos el ValorResultante de derecha a izquierda y quitamos todos los ceros no significativos de la derecha
    // Recuerda que j es la longitud del vector resultante en Valor
    // no tenemos en cuenta el �ltimo elemento que contiene la marca del final de cadena.
    i = 0;
    --j;
    while ((j > 0) && (k != 0)){
        if (cifra[j] != '0' || i == j){
            if (i == 0){
                cifra[j + 1] = '\0';
                i = j;
            }
            --i;
        }
        --j;
    }
    //Reinicializar variables.
    i=0, j=0, k=1;
    //definir la longitud de la variable y su validaci�n;
    longitud =strlen(cifra);

    longitudmaxima=numentero;

    if(numdecimal>0){
        longitudmaxima=numentero+numdecimal+1;
    }
    if(longitud>longitudmaxima || longitud==0){
        // mayor longitud que la permitida
        return -1;
    }
    //Recorre la cadena dede su inicio, en busca de caracteres no permitidos.
    while(i<longitud){
        j=0;
        while (j<10){
            if(cifra[i]==cadenanum[j]||cifra[i]==punto[0]){
                k=0;
                if(cifra[i]==punto[0]){
                    ++contpuntos;
                }
                else{
                    if(contpuntos>0){
                        ++contdecimales;
                    }
                    else{
                        ++contenteros;
                    }
                }
                break;
            }
            ++j;
            k=1;
        }
        if(k==1){
            break;
        }
        ++i;
    }
    //Comparamos que tenga los n�meros de caracteres enteros y decimales permitidos
    if(contenteros>numentero || contdecimales>numdecimal || contpuntos>1){
        return -1;
    }
    //La funci�n sale aqu� si tiene caracteres no permitidos.
    if(k==1){
        return -2;
    }
    //Conversi�n del array a un n�mero
    numcorrecto = atof(cifra);
    //La funci�n sale aqu� si no le hemos puesto cifra m�xima ni m�nima
    if((maxima==0) && (minima==0)){
        return numcorrecto;
    }
    //Si le hemos puesto a la funci�n una cifra m�xima o m�nima lo compara, entrando o no en el if
    if((numcorrecto < minima) || (numcorrecto > maxima)){
        //N�mero fuera de rango
        return -3;
    }
        return numcorrecto;
}
//FUNCI�N QUE TE DEVUELVE LA APUESTA MAS LO GANADO SI HAS GANADO O 0 SI HAS PERDIDO
double tirodebola(int juegot, int apuet, double apuestat){
    FILE *pf;
    resultado bola;
    int num;
    //asigna un valor aleatorio entre el 0 y 36 a la variable num.
    srand (time(NULL));
    num=rand()%37;
    //Abre un fichero en el que aparecen los n�meros del 0 al 36, con sus valores correspondientes (Ej: Rojo, par y fata)
    pf = fopen("tablero.txt", "r");
    if(pf==NULL){
        return -1;
    }
    //Buscamos el n�mero aleatorio que nos ha dado la funci�n rand()
    //Guardamos en la estructura resultados bola los valores optenidos.
    while(feof(pf)==0){
        fscanf(pf, "\n%d,%[^,],%[^,],%[^\n]\n", &bola.valor, bola.rojo, bola.impar, bola.falta);
        if(num==bola.valor){
            // Muestra en pantalla lo le�do
            printf("\n\n\n%d\t %s\t %s\t %s\n", bola.valor, bola.rojo, bola.impar, bola.falta);
            break;
        }
    }
    fclose(pf);
    //Guardamos los resultados en un fichero, para poder consultar todos los resultados a medida que pasen las partidas.
    pf = fopen("resultados.txt", "a+");
    if(pf==NULL){
        return -2;
    }
    fprintf(pf, "%i,%s,%s,%s\n", bola.valor, bola.rojo, bola.impar, bola.falta);
    fclose(pf);
    //Si el usuario juega al juego 1, la funci�n retorna los cr�ditos que se le dan al jugador
    if(juegot==1){
        if(apuet == bola.valor){
            return apuestat*36;
        }
        return 0;
    }
    //Si el usuario juega al juego 2, la funci�n retorna los cr�ditos que se le dan al jugador
    //Juego a rojo (1) o negro (0)
    if(juegot==2){
        if((bola.rojo[0] == 'N') && (apuet==1)){
            return apuestat*2;
        }
        if((bola.rojo[0] == 'R') && (apuet==0)){
            return apuestat*2;
        }
        return 0;
    }
    //Si el usuario juega al juego 3, la funci�n retorna los cr�ditos que se le dan al jugador
    //Juego a impar (1) o par (0)
    if(juegot==3){
        if((bola.impar[0] == 'I') && (apuet==1)){
            return apuestat*2;
        }
        if((bola.impar[0] == 'P') && (apuet==0)){
            return apuestat*2;
        }
        return 0;
    }
    //Si el usuario juega al juego 4, la funci�n retorna los cr�ditos que se le dan al jugador
    //Juego a falta (1) o pasa (0)
    if(juegot==4){
        if((bola.falta[0] == 'F') && (apuet==1)){
            return apuestat*2;
        }
        if((bola.falta[0] == 'P') && (apuet==0)){
            return apuestat*2;
        }
        return 0;
    }
}
//FUNCI�N VAC�A EL FICHERO RESULTADOS
void borrar(){
    FILE *pf;
   // int matriz[37][3];

    pf = fopen("resultados.txt", "w");
    if(pf == NULL){
        printf("Error al abrir al fichero de resultados\n");
    }
    fclose(pf);
    return;
}
//FUNCI�N QUE TE PERMITE REGISTRARTE O INICIAR SESI�N, Dicha funci�n va a ir guardando los datos de los usuarios registrados en el fichero "usuarios".
jugador usuario(){
    //Para poder imprimir en pantalla los acentos
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    //Se definen la variables
    int i, j, k;
    char nomregistrado[N], contrasena[N], checkvalor[N], creditos[N];
    jugador c[2];
    FILE *pf;
    //En el men� de registro se tiene la opci�n de iniciar sesi�n si ya tienes una cuenta creada o registrarte.
    do{
        printf("\nMEN� DE REGISTRO\nMarca una de las siguiente opciones:\n1\t Iniciar sesi�n\n2\t Reg�strarme\n");
        scanf(" %[^\n]", checkvalor);
        //Salir del juego
        if(salirdeljuego(checkvalor) == 0){
            return (jugador) {'\0', '\0', 0};
        }
        if (checknumeric(checkvalor, 1, 0, 2, 1) <= 0){
            printf("\nRespueta incorecta\n");
        }
    }while(checknumeric(checkvalor, 1, 0, 2, 1)<=0);
    //Se indica el nick de usuario con el que quieres iniciar sesi�n o te quieres registrar.
    printf("\n\nIndique su NICK, al terminar pulse ENTER.\nComo m�ximo se admiten %i caracteres\nNo puede tener ';' ni espacios.\nNICK:\t", N-1);
    do{
        scanf(" %[^\n]", c[0].nick);
        //Salir del juego
        if(salirdeljuego(c[0].nick) == 0){
            return (jugador) {'\0', '\0', 0};
        }
        //Se verifica que la longitud de la cadena sea menor o igual a la permitida.
        if(strlen(c[0].nick)>=N){
            printf("Por favor, vuelve a escribir NICK, recuerda que tienes que tener como m�ximo %i caracteres:\t", N-1);
        }
        //Se asigna a i el valor 0 si el nick no tiene puntos y comas y el valor 1 si lo tiene.
        i=quitapuntocoma(c[0].nick);
        //i=detectacaracteres(c[0].nick, caracteresprohibidos);
        if (i== 1){
            printf("Por favor, vuelve a escribir NICK, recuerda, recuerda que no puede tener ';' ni espacios:\t");
        }
    }while((strlen(c[0].nick) >= N) || (i == 1));
    //Codifica el nick
    codificar(c[0].nick, 2);
    //Opci�n de registro.
    if(checknumeric(checkvalor, 1, 0, 2, 1) == 2){
        i = 1;
        //se verifica que no exista ese nick.
        while(i == 1){
            i=0;
            pf = fopen("usuarios.txt", "r");
            if(pf == NULL){
                printf("Error al abrir el fichero usuarios\n");
                return (jugador) {'\0', '\0', 0};
            }
            //Se busca el nick en el ficheo de usuarios
            while(feof(pf)== 0){
                fscanf(pf, "%[^=]=%[^=]=%[^\n]\n", c[1].nick, c[0].contrasena, creditos);
                for(j=0; c[0].nick[j] == c[1].nick[j]; j++){
                    if(c[0].nick[j]=='\0'){//Al entrar en este if, es que se ha encontrado un nick igual, ya registrado
                        i=1;
                        break;
                    }
                }
                if(i==1){
                    break;
                }
            }
            //Se cierra el fichero usuarios
            fclose(pf);
            if(i == 1){
                printf("Este nick no esta disponible, por favor, escoge otro nick:\t");
                do{
                    scanf(" %[^\n]", c[0].nick);
                    //Salir del juego
                    if(salirdeljuego(c[0].nick) == 0){
                        return (jugador) {'\0', '\0', 0};
                    }
                    //Verificamos que la longitud de la cadena sea menor o igual a la permitida.
                    if(strlen(c[0].nick) >= N){
                        printf("Por favor, vuelve a escribir nick, recuerda que tiene que tener como m�ximo %i caracteres:\t", N-1);
                    }
                    //Asignamos a i el valor 0 si el nick no tiene puntos y comas y el valor 1 si lo tiene.
                    i=quitapuntocoma(c[0].nick);
                    if (i == 1){
                        printf("Por favor, vuelve a escribir NICK, recuerda, recuerda que no puede tener ';':\t");
                    }
                    //Codifica el nick
                    codificar(c[0].nick, 2);
                }while ((strlen(c[0].nick) >= N) || (i == 1));
            }
        }
        //pide la contrase�a al jugador
        printf("\n\n\n");
        do{
            i=0;
            printf("Escribe la contrase�a\nComo m�ximo se admiten %i caracteres\nNo puede tener ';' ni espacios\nCONTRAS�A:\t", N-1);
            do{
                scanf(" %[^\n]", c[0].contrasena);
                //Salir del juego
                if(salirdeljuego(c[0].contrasena) == 0){
                    return (jugador) {'\0', '\0', 0};
                }
                //Se verifica que la longitud de la cadena sea menor o igual a la permitida.
                if(strlen(c[0].contrasena) >= N){
                    printf("Por favor, vuelve a escribir la contrase�a, recuerda que tiene que tener como m�ximo %i caracteres:\t", N-1);
                }
                //Se asigna a i el valor 0 si el nick no tiene puntos y comas y el valor 1 si lo tiene.
                i=quitapuntocoma(c[0].contrasena);
                if (i == 1){
                    printf("Por favor, vuelve a escribir la contrase�a, recuerda que no puede tener ';' ni espacios:\t");
                }
            }while((strlen(c[0].contrasena) >= N) || (i == 1));
            //Pide repetri la contrase�a y se verifica que sea igual.
            printf("Repite tu contrase�a\nCONTRASE�A: \t");
            scanf(" %[^\n]", c[1].contrasena);
            //Salir del juego
            if(salirdeljuego(c[1].contrasena) == 0){
                return (jugador) {'\0', '\0', 0};
            }
            for(i=0; c[0].contrasena[i] == c[1].contrasena[i]; ++i){
                    if (c[0].contrasena[i]=='\0'){
                        i = N+1;
                        break;
                    }
            }
            if(i != N+1){
                printf("Las contrase�as introducidas no coinciden por favor, vuelve a intentarlas.\n");
            }
        } while(i != N+1);
        //Codifica el la contrase�a
        codificar(c[0].contrasena, 2);
        printf("\n\n\n");
        //Pide el valor de cr�ditos con los que se quiere registar el usuario
        do{
        printf("Indica tu n�mero de cr�ditos\ La cifra m�xima que puedes indicar es 10000 cr�ditos y la m�nima es 0.1 cr�ditos\n"
               "Solo puedes poner un decimal\nCR�DITOS\t");
        scanf(" %[^\n]", checkvalor);
        //Salir del juego
        if(salirdeljuego(checkvalor) == 0){
            return (jugador) {'\0', '\0', 0};
        }
        c[0].creditos = checknumeric(checkvalor, 5, 1, 10000, 0);
            if(c[0].creditos <= 0){
                printf("\nValor introducido incorrecto\n");
            }
        }while(c[0].creditos <= 0);

        pf = fopen("usuarios.txt", "a+");
        if(pf == NULL){
            printf("Error al abrir el fichero usuarios\n");
            return c[0];
        }
        //imprimimos los resultados codificados en el fichero usuarios
        fprintf(pf, "%s=%s=%.1f\n", c[0].nick, c[0].contrasena, c[0].creditos);
        fclose(pf);
        return c[0];
    }
    if(checknumeric(checkvalor, 1, 0, 2, 1) == 1){
        i = 1;
        //Comprueba que ese usuario ya este registrado
        while(i == 1){
            pf = fopen("usuarios.txt", "r");
            if(pf == NULL){
                printf("Error al abrir el fichero usuarios\n");
                return (jugador) {'\0','\0', 0};
            }
            //Busca ese nick en el fichero de registro.
            while(feof(pf)==0){
                fscanf(pf, "%[^=]=%[^=]=%[^\n]\n", c[1].nick, c[0].contrasena, creditos);
                for(j=0; c[0].nick[j] == c[1].nick[j]; j++){
                    if(c[0].nick[j]=='\0'){
                        i=0;
                        break;
                    }
                }
                if(i==0){

                    break;
                }
            }
            fclose(pf);
            if(i == 1){
                printf("nick incorrecto, por favor vuelve a indicar tu NICK:\t");
                do{
                    scanf(" %[^\n]", c[0].nick);
                    //Salir del juego
                    if(salirdeljuego(c[0].nick) == 0){
                        return (jugador) {'\0', '\0', 0};
                    }
                    if(strlen(c[0].nick)>=N){
                        printf("Por favor, vuelve a escribir tu NICK, recuerda que tiene que tener como m�ximo %i caracteres:\t", N-1);
                    }
                    //Codifica el nick
                    codificar(c[0].nick, 2);
                }while(strlen(c[0].nick)>=N);
            }
        }
        //Pide la contrase�a al usuario
        printf("\n\n\n");
        k=3;//Intentos de los que dispone el usuario para poner la contrase�a.
        do{
            i=1;
            printf("\nEscribe la contrase�a\nCONTRAS�A:\t");
            scanf(" %[^\n]", c[1].contrasena);
            //Salir del juego
            if(salirdeljuego(c[1].contrasena) == 0){
                return (jugador) {'\0', '\0', 0};
            }
            //Codifica la contrase�a
            codificar(c[1].contrasena, 2);
            //Verifica que la contrase�a coincide con la del usuario
            for(j=0; c[0].contrasena[j] == c[1].contrasena[j]; j++){
                if(c[0].contrasena[j]=='\0'){
                    i=0;
                    break;
                }
            }
            //Si el usuario pone 3 veces mal la contrase�a, el programa se cierra
            if((k == 1) && (i == 1)){
                printf("\n\n\nEl programa se cerrar� para la protecci�n de sus usuarios\n");
                return (jugador) {'\0', '\0', 0};
            }
            if(i == 1){
                fclose(pf);
                k--;
                printf("\nContrase�a incorecta, por favor vuelve a indicar tu contrase�a\nTe quedan %i intentos\n", k);
            }
        }while(i==1);
        //Asigna la array creditos a la variable double c[0].creditos
        c[0].creditos = atof(creditos);
        return c[0];
    }
}
//FUNCI�N QUE QUE ACTUALIZA EL VALOR DE LOS CREDITOS EN EL FICHERO "usuarios"
void actualizar(jugador c){
    FILE *pf, *pf2;
    int i, j;
    char creditos[N];
    jugador c2;
    //Se crea y/o se vac�a el fichero usuarios2
    pf2 = fopen("usuarios2.txt", "w");
    if(pf2==NULL){
        printf("Error al borrar el ficheso usuarios2\n");
    }
    fclose(pf2);
    //Abrimos en modo lectura el fichero usuarios
    pf = fopen("usuarios.txt", "r");
    if(pf == NULL){
        printf("Error al abrir el fichero usuarios\n");
        return;
    }
    //Abrimos en modo escritura el fichero usuarios 2
    pf2 = fopen("usuarios2.txt", "a+");
    if(pf2 == NULL){
        printf("Error al abrir el fichero usuarios\n");
        return;
    }
    //Se leen los datos del fichero usuarios y se compara con el nick de jugador actual
    //Si no coincide se pega en el fichero usuarios2
    //Si coincide se pega en el fichero usuarios 2 el nick, la contresa�a, pero los cr�ditos se reemplazan por los actuales del jugador.
    while(feof(pf)==0){
        i=0;
        fscanf(pf, "%[^=]=%[^=]=%[^\n]\n", c2.nick, c2.contrasena, creditos);
        c2.creditos = atof(creditos);
        for(j=0; c.nick[j] == c2.nick[j]; j++){
            if((c.nick[j]=='\0') && (c2.nick[j]=='\0')){
                fprintf(pf2, "%s=%s=%.1f\n", c2.nick, c2.contrasena, c.creditos);
                i=1;
                break;
            }
        }
        if (i==0){
       fprintf(pf2, "%s=%s=%.1f\n", c2.nick, c2.contrasena, c2.creditos);
        }
    }
    //Se cierran los dos ficheros
    fclose(pf);
    fclose(pf2);
    //Se vac�a el fichero usuarios, para poder escribir en �l
    pf = fopen("usuarios.txt", "w");
    if(pf==NULL){
        printf("Error al borrar el ficheso usuarios\n");
        return;
    }
    //Se abre el fichero usuarios2 en modo lectura
    pf2 = fopen("usuarios2.txt", "r");
    if(pf2 == NULL){
        printf("Error al abrir el fichero usuarios2\n");
        return;
    }
    //Se pegan los datos del fichero usuarios2 en el fichero usuarios
    while(feof(pf2)==0){
        fscanf(pf2, "%[^=]=%[^=]=%[^\n]\n", c.nick, c.contrasena, creditos);
        c.creditos = atof(creditos);
        fprintf(pf, "%s=%s=%.1f\n", c.nick, c.contrasena, c.creditos);
    }
    //Se cierran los dos ficheros
    fclose(pf);
    fclose(pf2);
    //Se vac�a el fichero usuarios2
    pf2 = fopen("usuarios2.txt", "w");
    fclose(pf2);
        if(pf2==NULL){
        printf("Error al borrar el ficheso usuarios2\n");
    }
    fclose(pf2);
    return;
}
//FUNCI�N QUE DETECTA SI UN ARRAY TIENE PUNTOS Y COMA O UN ESPACIO. TE DEVUELVE UN 0 SI NO TIENE Y UN 1 SI TIENE.
int quitapuntocoma(char cadena[N]){
    int i;
    if(cadena[0] == '\0'){ return 1;}
    for (i=0; (cadena[i]!='\0'); i++){
        if ((cadena[i] == ';') || (cadena[i] == ' ')){
            return 1;
        }
    }
    return 0;
}
//FUNCI�N QUE BORRA LOS DATOS DEL USUARIO.
void eliminarusuario(jugador c){

    FILE *pf, *pf2;
    int i=0, j;
    char op[N], creditos[N];
    jugador c2;
    //Crea y/o vac�a el fichero usuario 2.
    pf2 = fopen("usuarios2.txt", "w");
    if(pf2==NULL){
        printf("Error al borrar el ficheso usuarios2\n");
        return;
    }
    //El programa va a leer el fichero usuario y pegar los datos en el fichero usuarios 2.
    pf = fopen("usuarios.txt", "r");
    if(pf == NULL){
        printf("Error al abrir el fichero usuarios\n");
        return;
    }
    pf2 = fopen("usuarios2.txt", "a+");
    if(pf2 == NULL){
        printf("Error al abrir el fichero usuarios\n");
        return;
    }
    printf("\n\n\n");
    //Te pide una confirmaci�n antes de eliminar el usuario, pero slo si el usuario no ha perdido todos sus cr�ditos.
    if(c.creditos >= 0.1){
        do{
            i=1;
            //Decodifica el nick
            codificar(c.nick, -2);
            printf("(Opci�n salir deshabilitada)\n�Quieres eliminar la cuenta de %s?\nIntroduce por teclado SI o NO, a continuaci�n pulse ENTER.\t", c.nick);
            //Codifica el nick
            codificar(c.nick, 2);
            scanf(" %[^\n]", op);
            //Combierte a mayusculas los caracteres de la cadena.
            for(i=0;op[i]!='\0';i++){
                op[i]=toupper(op[i]);
            }
            if((op[0]=='N') && (op[1]=='O') && (op[2]=='\0')){
                fclose(pf);
                fclose(pf2);
                return;
            }
           if((op[0]=='S') && (op[1]=='I')  && (op[2]=='\0')){
                i=0;
           }
            else{
                printf("\nLa respuesta indicada es incorrecta\n");
                i=1;
            }
        }while(i==1);
    }
    //Copia los datos de un fichreo usuarios al fichero usuarios2 eliminando el usuario del jugador actual.
    while(feof(pf)==0){
        i=0;
        fscanf(pf, "%[^=]=%[^=]=%[^\n]\n", c2.nick, c2.contrasena, creditos);
        c2.creditos = atof(creditos);
        //Detecta el usuario del jugador actual y no lo copia
        for(j=0; c.nick[j] == c2.nick[j]; j++){
            if((c.nick[j]=='\0') && (c2.nick[j]=='\0')){
                i=1;
                break;
            }
        }
        if (i==0){
       fprintf(pf2, "%s=%s=%.1f\n", c2.nick, c2.contrasena, c2.creditos);
        }
    }
    //Cierra los ficheros
    fclose(pf);
    fclose(pf2);
    //Vac�a el fichero usuarios
    pf = fopen("usuarios.txt", "w");
    if(pf==NULL){
        printf("Error al borrar el ficheso usuarios\n");
        return;
    }
    //Abre al fichero usuarios2 en modo lectura
    pf2 = fopen("usuarios2.txt", "r");
    if(pf2 == NULL){
        printf("Error al abrir el fichero usuarios2\n");
        return;
    }
    //Lee los datos del fichero usuarios2 y los copia en el fichero usuarios
    while(feof(pf2)==0){
        fscanf(pf2, "%[^=]=%[^=]=%[^\n]\n", c.nick, c.contrasena, creditos);
        c.creditos = atof(creditos);
        fprintf(pf, "%s=%s=%.1f\n", c.nick, c.contrasena, c.creditos);
    }
    fclose(pf);
    fclose(pf2);
    //Vac�a el fichero usuarios2
    pf2 = fopen("usuarios2.txt", "w");
    fclose(pf2);
        if(pf2==NULL){
        printf("Error al borrar el ficheso usuarios2\n");
    }
    fclose(pf2);
    return;
}
//FUNCI�N QUE DETECTA LA CADENA 'SALIR'. TE DEVUELVE UN 0 SI LA DETECTA Y UN 1 SI NO LA DETECTA
int salirdeljuego(char salir[N]){
    //Salir del juego
     if ((toupper(salir[0]) == 'S') && (toupper(salir[1]) == 'A') && (toupper(salir[2]) == 'L') && (toupper(salir[3]) == 'I') && (toupper(salir[4]) == 'R') && (salir[5] == '\0')){
        //Antes de cerrar el programa borra el fichero registro donde se han ido alamacenando todos lo resultados de la partida.
        borrar();
        printf("\n\n\n\n\nHasta la pr�xima partida\n\n");
        return 0;
     }
    return 1;
}
void codificar(char cadena[N], int numero){
    int i;
    for(i=0; cadena[i]!= '\0' ; i++){
        cadena[i]=cadena[i]+numero;
    }
    return;
}
