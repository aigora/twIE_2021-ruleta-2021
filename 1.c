#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define N 20

//La utilizaremos para asignar las array y creditos de cada usuario
typedef struct
{
char nick[N];
char contrasena[N];
double creditos;
} jugador;

//La usaremos para imprimir en pantalla los valores optenidos por la ruleta
typedef struct{
int valor;
char rojo[N], impar[N], falta[N];
}resultado;

double checknumeric(char cifra[N], int numentero, int numdecimal, double maxima, double minima);
double tirodebola(int juegot, int apuet, double apuestat);
void borrar();
jugador usuario();
void actualizar(jugador c);
int quitapuntocoma (char cadena[N]);
void eliminarusuario(jugador c);

//FUNCIÓN PRINCIPAL
int main(){
    //definir variables
    char op[3], caracter, checkvalor[N], op2[2];
    double apuesta, cred = 0;
    int i=0, juego, apue;
    jugador registro;
    //En esta estructura guardaremos el nick de usuario, su contraseña, y sus creditos
    resultado r;
    FILE *pf;
    //Vaciamos el fichero resultados.
    borrar();
    //El programa te da la biemvenida.
    printf("Bienvenido al casino ETSIDI.\nEn este casino podras ganar creditos o perderlos, la suerte decide.\n");

    //A traves de esta función, los usuarios se registran o inician sesión.
    registro = usuario();
    do{
        i=1;
        printf("\n\n\n\n\nCREDITOS DE LOS QUE DISPONE ALTUALMENTE:\t %.1f\n", registro.creditos);
        //El ficher mesta contiene el esquema de la mesa de juego.
        pf = fopen("mesa.txt", "r");
        if(pf==NULL){
            printf("Error al leer el fichero mesa\n");
        }
        while(feof(pf) == 0){
            caracter = fgetc(pf);
            printf("%c", caracter);
        }
        fclose(pf);
        //Este es el menú de juego.
        printf("\n\nMENU DE JUEGO\nMarque la opcion de apuesta que desea\n 1\tApostar a un numero\n 2\tApostar a un color\n 3\tApostar a par o impar\n"
               " 4\tApostar a pasa o falta\n 5\tMostrar resultados anteriores\n 6\tCambiar de usuario\n 7\tEliminar usuario\n 8\tSALIR\n");
        //pide una de las opciones, en caso de coincidir con una de las opciones correctas, la función cheknumeric devuelve el valor 0 o inferior
        do{
            printf("\nIndique 1, 2, 3, 4, 5, 6, 7 o 8:\t");
            scanf("%s", checkvalor);
            //Validamos que el valor introduciso esta dentro del ralgo marcado
            juego=checknumeric(checkvalor, 1, 0, 8, 1);
            if(juego <= 0){
                printf("Opcion marcada incorrecta\n\n", checkvalor, juego);
            }
        }while(juego<=0);
        //Apuesta a un número, te pide el numero al aqui quieres aposta y te lo valida para que este dentro de rango.
        if(juego==1){
            do{
                printf("¿A que numero quieres apostar? Del 1 al 36: \t");
                scanf("%s", checkvalor);
                apue = checknumeric(checkvalor, 2, 0, 36, 1);
                if(juego <= 0){
                    printf("Numero marcado incorrecto\n\n");
                }
            } while(apue<=0);
            i=1; //Con este indicador entraremos en las sentencias de final de partda.
        }
        // aupuesta a rojo o negro
        if(juego==2){
            do{
                printf("¿A que quiere apostar, negros o rojos (n/r)? \t");
                scanf("%s", op2);
                //Cambia las letras introducidas en la cadena a mayusculas.
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
                    printf("La respuesta indicada es incorrecta\n\n");
                    apue=2;
                }
            }
            while(apue == 2);
            i=1; //Con este indicador entraremos en las sentencias de final de partda.
        }
        //Apuesta a impar o par
        if(juego==3){
            do{
                printf("¿A que quiere apostar, impar o par (i/p)? \t");
                scanf("%s", op2);
                //Cambia las letras introducidas en la cadena a mayusculas.
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
                    printf("La respuesta indicada es incorrecta\n\n");
                    apue=2;
                }
            }while(apue == 2);
            i=1;//Con este indicador entraremos en las sentencias de final de partda.
        }
        //Apuesta a pasa o falta.
        if(juego==4){
            do{
                printf("¿A que quiere apostar, falta (1-18) o pasa (19-36) (f/p)? \t");
                scanf ("%s", op2);
                //Cambia las letras introducidas en la cadena a mayusculas.
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
                    printf("La respuesta indicada es incorrecta\n\n");
                    apue=2;
                }
            }
            while(apue == 2);
            i=1; //Con este indicador entraremos en las sentencias de final de partda.
        }
        //Muestra los resultados optenidos anteriormente.
        if(juego == 5){
            pf = fopen("resultados.txt", "r");
            if(pf==NULL){
                printf("Error al leer el fichero resultados\n");
            }
            printf("\n\n\n\n");
            //Lee e imprime e pantalla los valores que se han ido saliendo, almacenano en el fichero resultados.
            while(feof(pf)==0){
                fscanf(pf, "\n\n%d,%[^,],%[^,],%[^\n]\n\n", &r.valor, r.rojo, r.impar, r.falta);
                printf("%d\t %s\t %s\t %s\n", r.valor, r.rojo, r.impar, r.falta);
            }
            fclose(pf);
            i=1; //Con este indicador entraremos en las sentencias de final de partda.
        }
        //Puesdes cambiar de usuario o crearte uno nuevo.
        if(juego == 6){
            //Abre la función usuarios
            registro = usuario();
            i = 0; //Con este indicador NO entraremos en las sentencias de final de partda.
        }
        //Esta función elimina el usuario con el que estas jugando
        if(juego == 7){
            eliminarusuario(registro);
            //Te da la opción de iniciar sesión o registrarte con otro usuario, o salir.
            do{
                printf("Quiere iniciar sesion o registrarse? Marquie SI o NO.\nSI\t Iniciar sesion o registrarse.\nNO\t Salir del juego.\n");
                gets(op);
                //Pone la cadena en mayusculas.
                for(i=0;op[i]!='\0';i++){
                    op[i]=toupper(op[i]);
                }
                if((op[0]=='N') && (op[1]=='O') && (op[2]=='\0')){
                    return 0;
                }
               if((op[0]=='S') && (op[1]=='I')  && (op[2]=='\0')){
                    registro = usuario();
                    i = 0;
               }
                else{
                    printf("La respuesta indicada es incorrecta\n");
                    i=1;
                }
            }while(i==1); //Cundo sale del bucle es con i=0, por lo que NO entraremos en las sentencias de final de partda.
        }
        //Salir del juego
        if (juego == 8){
            return 0;
        }
        //Solo te entra en esta opción si has marado una de las opciones con la que puedes jugar.
        if((juego == 1) || (juego == 2) || (juego == 3) || (juego == 4)){
             //Te pide la cantidad que deseas apostar.
            do{
                printf("¿Cuanto quieres apostar? El limite son 999,9 creditos: \t");
                scanf("%s", checkvalor);
                apuesta=checknumeric(checkvalor, 3, 1, registro.creditos, 0);
            }while (apuesta<0);
            //Restamos la apuesta a nuestro número de credios
            registro.creditos = registro.creditos - apuesta;
            //Asignamos a apuesta el valor de creditos optenidos si se gana, o 0 si se pierde.
            apuesta = tirodebola(juego, apue, apuesta);
            if(apuesta>0){
                printf("Has GANADO. Se de devuelven %.1f creditos\n", apuesta);
            }
            if(apuesta==0){
                printf("Has PERDIDO. Se te devuelven %.1f creditos\n", apuesta);
            }
            //Si apuesta tiene un valor menor a 0, es que se a producido un error, por lo que el programa borra el fichero de resultados y se cierra.
            if(apuesta <0){
                printf("Se a producido un error\n");
                borrar();
                return -10;
            }
            //Sumamos lo ganado a nuestros creditos.
            registro.creditos = registro.creditos + apuesta;
            //Actualizamos el valor de creditos del usuario en el fichero usuario.
            actualizar(registro);
        }
        //Fin de la partida.
        while(i==1){
            //Si su saldo es igual a 0, la partida se acaba y el progrma se cierra
            if(registro.creditos<=0){
                printf("Su saldo actual es de %.1f creditos\nFIN DE LA PARTIDA\n", registro.contrasena);
                //Esta función elimina el usuario actual, ya que ha perdido todos sus creditos.
                eliminarusuario(registro);
                //Te da la opción de iniciar sesión / registrarte con otro usuario o salir.
                do{
                    printf("Quiere iniciar sesion o registrarse? Marquie SI o NO.\nSI\t Iniciar sesion o registrarse.\nNO\t Salir del juego.\n");
                    scanf("%s", op);
                    //Pone la cadena en mayusculas.
                    for(i=0;op[i]!='\0';i++){
                        op[i]=toupper(op[i]);
                    }
                    if((op[0]=='N') && (op[1]=='O') && (op[2]=='\0')){
                        return 0;
                    }
                   if((op[0]=='S') && (op[1]=='I')  && (op[2]=='\0')){
                        //Abre la función registro para que el usuario se pueda reistrar de nuevo o iniciar sesión con otra cuenta.
                        registro = usuario();
                        i = 0;
                   }
                    else{
                        printf("La respuesta indicada es incorrecta\n");
                        i=1;
                    }
                }while(i==1);//De este bucle solo se sale con i=0, para poder volver al menu de juego.
            }

            //Te pregunta si quieres volver al menu para jugar otra partida
            printf("Su saldo actual es de %.1f creditos\n¿Quiere volver a jugar? marque SI o NO\n", registro.creditos);
            scanf("%s", op);
            //Cambia las letras introducidas en la cadena a mayusculas.
            for(i=0;op[i]!='\0';i++){
                op[i]=toupper(op[i]);
            }
            if((op[0]=='N') && (op[1]=='O') && (op[2]=='\0')){
                i=2;
                break;
            }
           if((op[0]=='S') && (op[1]=='I')  && (op[2]=='\0')){
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
    return 0;
}
//FUNCIÓN QUE VERIFICA QUE LA CADENA E CARACTERES INTRODUCIDA ES CORRECTA Y ESTA DENTRO DE UNOS DETERMINADOS VALORES
double checknumeric(char cifra[N], int numentero, int numdecimal, double maxima, double minima){

    //Definición de variables
    char cadenanum[10]="0123456789", punto[1]=".", valorresultante[N];
    int i=0, j=0, k=0, longitud, contenteros=0, contdecimales=0, contpuntos=0, longitudmaxima;
    double numcorrecto;
    //Lo primero que hace la función es quitar los ceros sobrantes, tante de la izquierda como de la derecha.
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
    // conocemos si hay decimales y en que posición está el separador decimal
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
    // no tenemos en cuenta el último elemento que contiene la marca dee final de cadena.
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
    //definir la longitud de variable y su validación;
    longitud =strlen(cifra);

    longitudmaxima=numentero;

    if(numdecimal>0){
        longitudmaxima=numentero+numdecimal+1;
    }
    if(longitud>longitudmaxima || longitud==0){
        // mayor longitud de la permitida
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
    //Comparamos que tenga los números de caracteres enteros y decimaes permitidos
    if(contenteros>numentero || contdecimales>numdecimal || contpuntos>1){
        return -1;
    }
    //La función sale aqui si tiene caracteres no permitidos.
    if(k==1){
        return -2;
    }
    //Conversión del la array a un número
    numcorrecto = atof(cifra);
    //La función sale aqui si no le hemos puesto cifra maxima ni minima
    if((maxima==0) && (minima==0)){
        return numcorrecto;
    }
    //Si le hemos puesto a la función una cifra máxima o minima lo compara, entrando o no en el if
    if((numcorrecto < minima) || (numcorrecto > maxima)){
        //Número fuera de rango
        return -3;
    }
        return numcorrecto;
}
//FUNCIÓN QUE TE DEVUELVE LA APUESTA MAS LO GANADO SI HAS GANADO O 0 SI HAS PERDIDO
double tirodebola(int juegot, int apuet, double apuestat){
    FILE *pf;
    resultado bola;
    int num;
    //asigna un valor aleatorio entre el 0 y 36 a la variable num.
    srand (time(NULL));
    num=rand()%37;
    //Abre un fichero en el que aparecen los numeros del 0 al 36, con sus valores correspondientes (Ej: Rojo, par y fata)
    pf = fopen("tablero.txt", "r");
    if(pf==NULL){
        return -1;
    }
    //Buscamos en el el numero aleatorio que nos ha dado la función rand()
    //Guardamos en la estructura resultados bola los valores optenidos.
    while(feof(pf)==0){
        fscanf(pf, "\n%d,%[^,],%[^,],%[^\n]\n", &bola.valor, bola.rojo, bola.impar, bola.falta);
        if(num==bola.valor){
            // Muestra en pantalla lo leído
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
    //Si el usuario juega al juego 1, la función retorna los creditos que se le dan al jugador
    if(juegot==1){
        if(apuet == bola.valor){
            return apuestat*36;
        }
        return 0;
    }
    //Si el usuario juega al juego 2, la función retorna los creditos que se le dan al jugador
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
    //Si el usuario juega al juego 3, la función retorna los creditos que se le dan al jugador
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
    //Si el usuario juega al juego 4, la función retorna los creditos que se le dan al jugador
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
//FUNCIÓN VACIA EL FICHERO RESULTADOS
void borrar(){
    FILE *pf;
   // int matriz[37][3];

    pf = fopen("resultados.txt", "w");
    if(pf==NULL){
        printf("Error al abrir al fichero de resultados\n");
    }
    fclose(pf);
    return;
}
//FUNCIÓN QUE TE PERMITE REGISTRARTE O INICIAR SESIÓN, Dicha función va a ir guardado los datos de los usuarios registrados en el fichero usuarios.
jugador usuario(){
    int i, j, op;
    char nomregistrado[N], contrasena[N], checkvalor[N], creditos[N];
    jugador c[2];
    FILE *pf;
    //En el menu de registro se tiene la opción de iniciar sesión si ya tienes una cuenta creada o registrarte.
    do{
        printf("\nMENU DE REGISTRO\nMarque una de las siguiente opciones:\n1\t Iniciar sesion\n2\t Registrarme\n");
        scanf("%s", checkvalor);
        op = checknumeric(checkvalor, 1, 0, 2, 1);
        if (op<=0){
            printf("\nRespueta incorecta\n");
        }
    }while(op<=0);
    //Se indica el nick de usuario con el cuel quieres iniciar sesión o te quieres registrar.
    printf("\n\nIndique su NICK, al terminar pulse ENTER.\nComo maximo se admiten %i caracteres\nNo puede tener ';'\nNICK:\t", N-1);
    do{
        scanf ("%s", c[0].nick);
        //Se verifica que la longitud de la cadena sea menos o igual a la perimita.
        if(strlen(c[0].nick)>=N){
            printf("Por favor, vuleva a escribir NICK, recuerde que tiene que tener como maximo %i caracteres:\t", N-1);
        }
        //Se asigna a i el valor 0 si el nick no tiene puntos y comas y el valor 1 si lo tiene.
        i=quitapuntocoma(c[0].nick);
        if (i== 1){
            printf("Por favor, vuleva a escribir NICK, recuerde recuerde que no puede tener ';':\t");
        }
    }while((strlen(c[0].nick) >= N) || (i == 1));
    //Opción de registro.
    if(op == 2){
        i = 1;
        //se verifica que no exista ese nick.
        while(i == 1){
            i=0;
            pf = fopen("usuarios.txt", "r");
            if(pf == NULL){
                printf("Error al abrir el fichero usuarios\n");
                return (jugador) {'\0', 0, '\0'};
            }
            //Se busca el nick en el ficheo de usuarios
            while(feof(pf)== 0){
                fscanf(pf, "%[^;];%[^;];%[^\n]\n", c[1].nick, c[0].contrasena, creditos);
                for(j=0; c[0].nick[j] == c[1].nick[j]; j++){
                    if(c[0].nick[j]=='\0'){//Al entrar en este if, es que se ha encontrado un nick igual ya registrados
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
                printf("Este nick no esta disponible, por favor, escoja otro nick:\t");
                do{
                    scanf("%s", c[0].nick);
                    //Verificamos que la longitud de la cadena sea menos o igual a la perimita.
                    if(strlen(c[0].nick) >= N){
                        printf("Por favor, vuleva a escribir nick, recuerde que tiene que tener como maximo %i caracteres:\t", N-1);
                    }
                    //Asignamos a i el valor 0 si el nick no tiene puntos y comas y el valor 1 si lo tiene.
                    i=quitapuntocoma(c[0].nick);
                    if (i == 1){
                        printf("Por favor, vuleva a escribir NICK, recuerde recuerde que no puede tener ';':\t");
                    }
                }while ((strlen(c[0].nick) >= N) || (i == 1));
            }
        }
        //pide la contraseña al jugador
        printf("\n\n\n");
        do{
            i=0;
            printf("Escriba la contraseña\nComo maximo se admiten %i caracteres\nNo puede tener ';'\nCONTRASÑA:\t", N-1);
            do{
                scanf("%s", c[0].contrasena);
                //Se verifica que la longitud de la cadena sea menos o igual a la perimita.
                if(strlen(c[0].contrasena) >= N){
                    printf("Por favor, vuleva a escribir la contraseña, recuerde que tiene que tener como maximo %i caracteres:\t", N-1);
                }
                //Se asigna a i el valor 0 si el nick no tiene puntos y comas y el valor 1 si lo tiene.
                i=quitapuntocoma(c[0].contrasena);
                if (i == 1){
                    printf("Por favor, vuleva a escribir contraseña, recuerde que no puede tener ';':\t");
                }
            }while((strlen(c[0].contrasena) >= N) || (i == 1));
            //Pide repetri la contraseña y se verifica que sea igual.
            printf("Repita su contraseña\nCONTRASEÑA: \t");
            scanf("%s", c[1].contrasena);
            for(i=0; c[0].contrasena[i] == c[1].contrasena[i]; ++i){
                    if (c[0].contrasena[i]=='\0'){
                        i = N+1;
                        break;
                    }
            }
            if(i != N+1){
                printf("Las contraseñas introducidas no coinciden por favor, vuelva a intentarlo.\n");
            }
        } while(i != N+1);
        printf("\n\n\n");
        //Piede el valor de creditos con los que se quiere registar el usuario
        printf("\n\n\n");
        do{
        printf("Indique su número de creditos\ La cifra maxima que puede indicar es 99999\nSolo puede poner un decimal\nCREDITOS\t");
        scanf("%s", checkvalor);
        c[0].creditos = checknumeric(checkvalor, 5, 1, 99999, 0);
            if(c[0].creditos <= 0){
                printf("Valor introducido incorrecto\n");
            }
        }while(c[0].creditos <= 0);

        pf = fopen("usuarios.txt", "a+");
        if(pf == NULL){
            printf("Error al abrir el fichero usuarios\n");
            return c[0];
        }
        fprintf(pf, "%s;%s;%.1f\n", c[0].nick, c[0].contrasena, c[0].creditos);
        fclose(pf);
        return c[0];
    }
    if(op == 1){
        i = 1;
        //Comprueba que ese usuario ya este registrado
        while(i == 1){
            pf = fopen("usuarios.txt", "r");
            if(pf == NULL){
                printf("Error al abrir el fichero usuarios\n");
                return (jugador) {'\0', 0, '\0'};
            }
            //Busca ese nick en el fichero de registro.
            while(feof(pf)==0){
                fscanf(pf, "%[^;];%[^;];%[^\n]\n", c[1].nick, c[0].contrasena, creditos);
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
                printf("nick incorecto, por favor vuelve a indicar su NICK:\t");
                do{
                    scanf("%s", c[0].nick);
                    if(strlen(c[0].nick)>=N){
                        printf("Por favor, vuleva a escribir NICK, recuerde que tiene que tener como maximo %i caracteres:\t", N-1);
                    }
                }while(strlen(c[0].nick)>=N);
            }
        }
        //Pide la contraseña al usuario
        printf("\n\n\n");
        do{
            i=1;
            printf("\nEscriba la contraseña\nCONTRASÑA:\t");
            scanf("%s", c[1].contrasena);
            //Verifica que la contraseña coincide con la del usuario
            for(j=0; c[0].contrasena[j] == c[1].contrasena[j]; j++){
                if(c[0].contrasena[j]=='\0'){
                    i=0;
                    break;
                }
            }
            if(i == 1){
                fclose(pf);
                printf("Contraseña incorecta, por favor vuelve a indicar su contraseña\n");
            }
        }while(i==1);
        //Asigna la array creditos a la variable double c[0].creditos
        c[0].creditos = atof(creditos);
        return c[0];
    }
}
//FUNCIÓN QUE QUE ACTUALIZA EL VALOR DE LOS CREDITOS EN EL FICHERO "usuarios"
void actualizar(jugador c){
    FILE *pf, *pf2;
    int i, j;
    char creditos[N];
    jugador c2;
    //Se crea y/o se vacia el fichero usuarios2
    pf2 = fopen("usuarios2.txt", "w");
    if(pf2==NULL){
        printf("Error al borrar el ficheso usuarios2\n");
    }
    fclose(pf2);
    //Abrimos enmodo lectura el fichero usuarios
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
    //Se les los datos dil fichero usuarios y se compara con el nick de jugador antutal
    //Si no coincide se pegan en el fichero usuarios2
    //Si coincide se pega en el fichero usuarios 2 el nick, la contresaña, pero los creditos se remplazan por los actuales del jugador.
    while(feof(pf)==0){
        i=0;
        fscanf(pf, "%[^;];%[^;];%[^\n]\n", c2.nick, c2.contrasena, creditos);
        c2.creditos = atof(creditos);
        for(j=0; c.nick[j] == c2.nick[j]; j++){
            if((c.nick[j]=='\0') && (c2.nick[j]=='\0')){
                fprintf(pf2, "%s;%s;%.1f\n", c2.nick, c2.contrasena, c.creditos);
                i=1;
                break;
            }
        }
        if (i==0){
       fprintf(pf2, "%s;%s;%.1f\n", c2.nick, c2.contrasena, c2.creditos);
        }
    }
    //Se cierran los dos ficheros
    fclose(pf);
    fclose(pf2);
    //Se vacia el fichero usuarios, para poder escribir en el
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
        fscanf(pf2, "%[^;];%[^;];%[^\n]\n", c.nick, c.contrasena, creditos);
        c.creditos = atof(creditos);
        fprintf(pf, "%s;%s;%.1f\n", c.nick, c.contrasena, c.creditos);
    }
    //Se cierran los dos ficheros
    fclose(pf);
    fclose(pf2);
    //Se vacia el fichero usuarios2
    pf2 = fopen("usuarios2.txt", "w");
    fclose(pf2);
        if(pf2==NULL){
        printf("Error al borrar el ficheso usuarios2\n");
    }
    fclose(pf2);
    return;
}
//FUNCIÓN QUE DETECTA SI UNA ARRAY TIENE PUNTOS Y COMA. TE DEVUELVE UN 0 SI NO TIENE Y UN 1 SI TIENE.
int quitapuntocoma (char cadena[N]){
    int i;
    if(cadena[0] == '\0'){ return 1;}
    for (i=0; cadena[i]!='\0'; i++){
        if (cadena[i] == ';'){
            return 1;
        }
    }
    return 0;
}
//FUNCIÓN QUE BORRA EL USUARIO.
void eliminarusuario(jugador c){
    FILE *pf, *pf2;
    int i=0, j;
    char op[3], creditos[N];
    jugador c2;
    //Crea y/o vacia el fichero usuario 2.
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
    //Te pide una confirmación antes de eliminar el usuario, pero slo si el usuario no a perdido todos sus creditos.
    if(c.creditos > 0){
        do{
            i=1;
            printf("Quieres eliminar la cuenta de %s?\nIntroduzca por teclado SI o NO, a continuacion pulse ENTER.\t", c.nick);
            scanf("%s", op);
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
                printf("La respuesta indicada es incorrecta\n");
                i=1;
            }
        }while(i==1);
    }
    //Copia los datos de un fichreo usuarios al fichero usuarios2 eliminando el usuario del jugador actual.
    while(feof(pf)==0){
        i=0;
        fscanf(pf, "%[^;];%[^;];%[^\n]\n", c2.nick, c2.contrasena, creditos);
        c2.creditos = atof(creditos);
        //Detecta el usuario del jugador actual y no lo copia
        for(j=0; c.nick[j] == c2.nick[j]; j++){
            if((c.nick[j]=='\0') && (c2.nick[j]=='\0')){
                i=1;
                break;
            }
        }
        if (i==0){
       fprintf(pf2, "%s;%s;%.1f\n", c2.nick, c2.contrasena, c2.creditos);
        }
    }
    //Cierra los ficheros
    fclose(pf);
    fclose(pf2);
    //Vacia el fichero usuarios
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
        fscanf(pf2, "%[^;];%[^;];%[^\n]\n", c.nick, c.contrasena, creditos);
        c.creditos = atof(creditos);
        fprintf(pf, "%s;%s;%.1f\n", c.nick, c.contrasena, c.creditos);
    }
    fclose(pf);
    fclose(pf2);
    //Vacia el fichero usuarios2
    pf2 = fopen("usuarios2.txt", "w");
    fclose(pf2);
        if(pf2==NULL){
        printf("Error al borrar el ficheso usuarios2\n");
    }
    fclose(pf2);
    return;
}
