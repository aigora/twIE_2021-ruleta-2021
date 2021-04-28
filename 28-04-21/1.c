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

//FUNCIÓN PRINCIPAL
int main(){
    //definir variables
    char op[3], caracter, checkvalor[N], op2[2];
    double apuesta, cred = 0;
    int i=0, juego, apue;
    jugador registro;
    resultado r;
    FILE *pf;
    borrar();
    //El programa te da la biemvenida.
    printf("Bienvenido al casino ETSIDI.\nEn este casino podras ganar creditos o perderlos, la suerte decide.\n");

    //A traves de esta función, los usuarios se registran o inician sesión.
    registro = usuario();
    do{
        i=1;
        printf("\n\n\n\n\n");
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
        //Este es el menú de opciones.
        printf("\nMarque la opcion de apuesta que desea\n 1\tApostar a un numero\n 2\tApostar a un color\n 3\tApostar a par o impar\n"
               " 4\tApostar a pasa o falta\n 5\tMostrar resultados anteriores\n 6\tCambiar de usuario\n 7\tSALIR\n");
        //pide una de las opciones, en caso de coincidir con una de las opciones correctas, la función cheknumeric devuelve el valor 0 o inferior
        juego=0;
        while(juego<=0){
            printf("\nIndique 1, 2, 3, 4, 5 o 6:\t");
            scanf("%s", checkvalor);
            juego=checknumeric(checkvalor, 1, 0, 7, 1);
            if(juego <= 0){
                printf("Opcion marcada incorrecta %s\t%f", checkvalor, juego);
            }
        }
        //Apuesta a un número
        if(juego==1){
            do{
                printf("¿A que número quieres apostar? \n");
                scanf("%s", checkvalor);
                apue = checknumeric(checkvalor, 2, 0, 36, 1);
                if(juego <= 0){
                    printf("Numero marcado incorrecta");
                }
            } while(apue<=0);
        }
        // aupuesta a rojo o negro
        do{
            if(juego==2){
                printf("¿A que quiere apostar, negros o rojos (n/r)? \n");
                scanf("%s", op2);
                for(i=0;op2[i]!='\0';i++){
                op2[i]=toupper(op2[i]);
                }
                if((op2[0]=='N') && (op2[1]=='\0')){
                    apue = 1;
               }
                if((op2[0]=='R') && (op2[1]=='\0')){
                    apue = 0;
               }
               if((op2[0]!='N') && (op2[0]!='R') || (op2[1]!='\0')){
                    printf("La respuesta indicada es incorrecta\n");
                    apue=2;
                }
            }
            i=1;
        }
        while(apue == 2);
        //Apuesta a impar o par
        do{
            if(juego==3){
                printf("¿A que quiere apostar, impar o par (i/p)? \n");
                gets(op2);
                for(i=0;op2[i]!='\0';i++){
                op2[i]=toupper(op2[i]);
                }
                if((op2[0]=='I') && (op2[1]=='\0')){
                    apue = 1;
               }
                if((op2[0]=='P') && (op2[1]=='\0')){
                    apue = 0;
               }
                if((op2[0]!='I') && (op2[0]!='P') || (op2[1]!='\0')){
                    printf("La respuesta indicada es incorrecta\n");
                    apue=2;
                }
            }
            i=1;
        }
        while(apue == 2);
        //Apuesta a pasa o falta.
        do{
            if(juego==4){
                printf("¿A que quiere apostar, falta (1-18) o pasa (19-36) (f/p)? \n");
                scanf ("%s", op2);
                for(i=0;op2[i]!='\0';i++){
                op2[i]=toupper(op2[i]);
                }
                if((op2[0]=='F') && (op2[1]=='\0')){
                    apue = 1;
               }
                if((op2[0]=='P') && (op2[1]=='\0')){
                    apue = 0;
               }
                 if((op2[0]!='F') && (op2[0]!='P') || (op2[1]!='\0')){
                    printf("La respuesta indicada es incorrecta\n");
                    apue=2;
                }
            }
            i=1;
        }
        while(apue == 2);
        //Muestra los resultados optenidos anteriormente.
        if(juego == 5){
            pf = fopen("resultados.txt", "r");
            if(pf==NULL){
                printf("Error al leer el fichero resultados\n");
            }

            while(feof(pf)==0){
                fscanf(pf, "\n%d,%[^,],%[^,],%[^\n]\n", &r.valor, r.rojo, r.impar, r.falta);
                printf("%d\t %s\t %s\t %s\n", r.valor, r.rojo, r.impar, r.falta);
            }
            fclose(pf);
        }
        //Puesdes cambiar de usuario o crearte uno nuevo.
        if(juego == 6){
            registro = usuario();
            i = 0;
        }
        //Salir del juego
        if (juego == 7){
            return 0;
        }
        //Te pide la cantidad que deseas apostar.
        if((juego == 1) || (juego == 2) || (juego == 3) || (juego == 4)){
            do{
                printf("¿Cuanto quieres apostar? \n");
                scanf("%s", checkvalor);
                apuesta=checknumeric(checkvalor, 5, 1, registro.creditos, 0);
            }
            while (apuesta<=0);
            registro.creditos = registro.creditos - apuesta;

            apuesta = tirodebola(juego, apue, apuesta);
            if(apuesta>0){
                printf("Has GANADO. Se de devuelven %.1f creditos\n", apuesta);
            }
            if(apuesta==0){
                printf("Has PERDIDO. Se te devuelven %.1f creditos\n", apuesta);
            }
            if(apuesta <0){
                printf("Se a producido un error\n");
                borrar();
                return apuesta;
            }

            registro.creditos = registro.creditos + apuesta;
            actualizar(registro);
        }
        //Fin de la partida.
        while(i==1){
            //Si su saldo es igual a 0, la partida se acaba y el progrma se cierra
            if(registro.creditos<=0){
                printf("Su saldo actual es de %.1f creditos\nFIN DE LA PARTIDA\n", registro.contrasena);
                return 0;
            }
            //Te pregunta si quieres volver al menu para jugar otra partida
            printf("Su saldo actual es de %.1f creditos\n¿Quiere volver a jugar? marque SI o NO\n", registro.creditos);
            scanf(" %s", op);
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

    borrar();
    return 0;
}
//FUNCIÓN QUE VERIFICA QUE LA CADENA E CARACTERES INTRODUCIDA ES CORRECTA Y ESTA DENTRO DE UNOS DETERMINADOS VALORES
double checknumeric(char cifra[N], int numentero, int numdecimal, double maxima, double minima){

    //Definición de variables
    char cadenanum[10]="0123456789", punto[1]=".";
    int i=0, x=0, k=1, longitud, contenteros=0, contdecimales=0, contpuntos=0, longitudmaxima;
    double numcorrecto;

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

    while(i<longitud){
        x=0;
        while (x<10){
            if(cifra[i]==cadenanum[x]||cifra[i]==punto[0]){
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
            ++x;
            k=1;
        }
        if(k==1){
            break;
        }
        ++i;
    }
    if(contenteros>numentero || contdecimales>numdecimal || contpuntos>1){
//     mas carecteres esteros, decimales o más puntos
        return -1;
    }

    if(k==1){
        //Caracteres no numericos
        return -2;
    }
    numcorrecto = atof(cifra);
    if((maxima==0) && (minima==0)){
        return numcorrecto;
    }
    if((numcorrecto < minima) || (numcorrecto > maxima)){
        //Número fuera de rango
        return -3;
    }
        return numcorrecto;
}
//FUNCIÓN QUE TE DEVUELVE LA APUESTA MAS LO GANADO O 0 SI HAS PERDIDO
double tirodebola(int juegot, int apuet, double apuestat){
    FILE *pf;
    resultado bola;
    int num;
    //asigna un valor aleatorio entre el 0 y 36 a la variable num.
    srand (time(NULL));
    num=rand()%37;
    //Abre un fichero en el que aparecen los valores del 0 al 36,
    pf = fopen("tablero.txt", "r");
    if(pf==NULL){
        return -1;
    }
    //Guardamos en una estructura los resultados optenidos.
    while(feof(pf)==0){
        if(num == 0){
            bola.valor = 0;
            bola.rojo[0] = '0';
            bola.impar[0] = '0';
            bola.falta[0] = '0';
            printf("%d\t %c\t %c\t %c\n", bola.valor, bola.rojo[0], bola.impar[0], bola.falta[0]);
            break;
        }
        fscanf(pf, "\n%d,%[^,],%[^,],%[^\n]\n", &bola.valor, bola.rojo, bola.impar, bola.falta);
        if(num==bola.valor){
            printf("%d\t %s\t %s\t %s\n", bola.valor, bola.rojo, bola.impar, bola.falta);
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

    if(juegot==1){
        if(apuet == bola.valor){
            return apuestat*36;
        }
        return 0;
    }

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
// Mostramos en pantalla lo leído
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
    int i, j, op, longitud;
    char nomregistrado[N], contrasena[N], checkvalor[N], creditos[N];
    jugador c[2];

    FILE *pf;
    //Tienes la opción de iniciar sesión si ya tienes una cuenta creada o registrarte.
    do{
        printf("Marque una de las siguiente opciones:\n1\t Iniciar sesión\n2\t Registrarme\n");
        gets(checkvalor);
        op = checknumeric(checkvalor, 1, 0, 2, 1);
    }while(op<=0);

    printf("Indique su NICK, al terminar pulse ENTER.\nComo maximo se admiten %i caracteres\nNo puede tener ';'\nNICK:\t", N-1);
    longitud=N+1;
    while(longitud>=N){
        gets(c[0].nick);
        longitud =strlen(c[0].nick);
        if(longitud>=N){
            printf("Por favor, vuleva a escribir NICK, recuerde que tiene que tener como maximo %i caracteres:\t", N-1);
        }
        i=quitapuntocoma(c[0].nick);
        if (i== 1){
            printf("Por favor, vuleva a escribir NICK, recuerde recuerde que no puede tener ';':\t");
            longitud=N+1;
        }
    }
    if(op == 2){
        i = 1;
        //Verifica que el o haya ningun usuario con ese nombre
        while(i == 1){
            i=0;
            pf = fopen("usuarios.txt", "r");
            if(pf == NULL){
                printf("Error al abrir el fichero usuarios\n");
                return (jugador) {'\0', 0, '\0'};
            }
            while(feof(pf)== 0){
                fscanf(pf, "%[^;];%[^;];%[^\n]\n", c[1].nick, c[0].contrasena, creditos);
                for(j=0; c[0].nick[j] == c[1].nick[j]; j++){
                    if(c[0].nick[j]=='\0'){
                        i=1;
                        break;
                    }
                }
                if(i==1){
                    break;
                }
            }
            if(i == 1){
                fclose(pf);
                printf("Este nick no esta disponible, por favor, escoja otro nick:\t");
                longitud = N+1;
                while (longitud>=N){
                    gets(c[0].nick);
                    longitud =strlen(c[0].nick);
                    if(longitud>=N){
                        printf("Por favor, vuleva a escribir nick, recuerde que tiene que tener como maximo %i caracteres:\t", N-1);
                    }
                }
            }
        }


        //pide la contraseña al jugador
        do{
            printf("Escriba la contraseña\nComo maximo se admiten %i caracteres\nNo puede tener ';'\nCONTRASÑA:\t");
            longitud=N+1;
            while(longitud>=N){
                gets(c[0].contrasena);
                longitud =strlen(c[0].contrasena);
                if(longitud>=N){
                    printf("Por favor, vuleva a escribir la contraseña, recuerde que tiene que tener como maximo %i caracteres:\t", N-1);
                }
                i=quitapuntocoma(c[0].contrasena);
                if (i == 1){
                    printf("Por favor, vuleva a escribir contraseña, recuerde recuerde que no puede tener ';':\t");
                    longitud=N+1;
                }
            }
            printf("Repita su contraseña\nCONTRASEÑA: \t");
            gets(c[1].contrasena);
            for(i=0; c[0].contrasena[i] == c[1].contrasena[i]; ++i){
                    if (c[0].contrasena[i]=='\0'){ break;}
            }
            if((longitud != strlen(c[1].contrasena)) || (longitud != i)){
                printf("Las contraseñas introducidas no coinciden por favor, vuelva a intentarlo.\n");
            }
        } while((longitud != strlen(c[1].contrasena)) || (longitud != i));
        do{
        printf("Indique su número de creditos\ La cifra maxima que puede indicar es 99999\nSolo puede poner un decimal\nCREDITOS\t");
        gets(checkvalor);
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
        while(i == 1){
            pf = fopen("usuarios.txt", "r");
            if(pf == NULL){
                printf("Error al abrir el fichero usuarios\n");
                return (jugador) {'\0', 0, '\0'};
            }
            while(feof(pf)==0){
                fscanf(pf, "%[^;];%[^;];%[^\n]\n", c[1].nick, c[0].contrasena, creditos);
                printf("%s;\t%s;\t%s;\n", c[1].nick, c[0].contrasena, creditos);
                for(j=0; c[0].nick[j] == c[1].nick[j]; j++){
                    if(c[0].nick[j]=='\0'){
                        i=0;
                        break;
                    }
                }
                if(i==0){
                    fclose(pf);
                    break;
                }
            }
            if(i == 1){
                fclose(pf);
                printf("nick incorecto, por favor vuelve a indicar su NICK\n");
                longitud=N+1;
                while(longitud>=N){
                    gets(c[0].nick);
                    longitud =strlen(c[0].nick);
                    if(longitud>=N){
                        printf("Por favor, vuleva a escribir NICK, recuerde que tiene que tener como maximo %i caracteres:\t", N-1);
                    }
                }
            }
        }
        printf("Escriba la contraseña\nCONTRASÑA:\t");
        longitud=N+1;
        while(longitud>=N){
            gets(c[1].contrasena);
            longitud =strlen(c[1].contrasena);
            if(longitud>=N){
                printf("Por favor, vuleva a escribir la contraseña, recuerde que tiene que tener como maximo %i caracteres:\t", N-1);
            }
        }
        do{
            i=1;
            for(j=0; c[0].contrasena[j] == c[1].contrasena[j]; j++){
                if(c[0].contrasena[j]=='\0'){
                    i=0;
                    break;
                }
            }
            if(i == 1){
                fclose(pf);
                printf("Contraseña incorecta, por favor vuelve a indicar su contraseña\n");
                longitud=N+1;
                while(longitud>=N){
                    gets(c[1].contrasena);
                    longitud =strlen(c[1].contrasena);
                    if(longitud>=N){
                        printf("Por favor, vuleva a escribir la contraseña, recuerde que tiene que tener como maximo %i caracteres:\t", N-1);
                    }
                }
            }

        }while(i==1);
        printf("\t\t\t%s\n", creditos);
        c[0].creditos = atof(creditos);
        printf("Su saldo actual es de %.1f creditos\n", c[0].creditos);
        return c[0];
    }
    return c[0];
}
//FUNCIÓN QUE QUE ACTUALIZA EL VALOR DE LOS CREDITOS EN EL FICHERO "usuarios"
void actualizar(jugador c){
    FILE *pf, *pf2;
    int i, j;
    char creditos[N];
    jugador c2;
    pf2 = fopen("usuarios2.txt", "w");
    if(pf2==NULL){
        printf("Error al borrar el ficheso usuarios2\n");
    }
    fclose(pf2);

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
    fclose(pf);
    fclose(pf2);
    pf = fopen("usuarios.txt", "w");
    if(pf==NULL){
        printf("Error al borrar el ficheso usuarios\n");
        return;
    }
    fclose(pf);
    pf = fopen("usuarios.txt", "a+");
    if(pf == NULL){
        printf("Error al abrir el fichero usuarios\n");
        return;
    }
    pf2 = fopen("usuarios2.txt", "r");
    if(pf2 == NULL){
        printf("Error al abrir el fichero usuarios2\n");
        return;
    }
    while(feof(pf2)==0){
        fscanf(pf2, "%[^;];%[^;];%[^\n]\n", c.nick, c.contrasena, creditos);
        c.creditos = atof(creditos);
        fprintf(pf, "%s;%s;%.1f\n", c.nick, c.contrasena, c.creditos);
    }
    fclose(pf);
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
    for (i=0; cadena[i]!='\0'; i++){
        if (cadena[i] == ';'){
            return 1;
        }
    }
    return 0;
}
