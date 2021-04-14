
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define N 20
double checknumeric(char cifra[N], int numentero, int numdecimal, double maxima, double minima);
//char mayusminu (char valor[], int tipo);
double tirodebola(int juegot, int apuet, double apuestat);

int main()
{//definir variables
    char roj, imp, fal; //Variables del número optenido
    char nom[N], op[3], ap, checkvalor[N], op2[2];
    double apuesta, cred = 0;
    int num=0, i=0, x=0, apue, juego;
    int matriz[37][3];
    //Nombre del usuario
    printf("Indique su nomre, al terminar pulse ENTER.\n");
    scanf ("%s", &nom);

    //Dar la Bielvenida
    printf("\n\n%s ,bienvenido al casino ETSIDI.\nEn este casino podras ganar creditos o perderlos, la suerte decide.\n\n", nom);

    //Indicar el número de creditos del que dispone el usuario del programa.
    while (cred <= 0){
        printf ("Por favor indica el numero de creditos del que dispone, y a continuacion puse ENTER.\n "
                "Recuerde que los decimales se marcan a traves de un PUNTO (.) \n ");

           scanf("%s", checkvalor);
            cred = checknumeric(checkvalor, 5, 1, 0, 0);
//El valor de creditos tiene que ser mayor que 0.
        if (cred <= 0){
            printf ("El valor de los creditos inicados es incorrecto\n");
        }
        else {
            printf("El valor los creditos es %.1f.\n¿Es correcto?\nResponda SI o NO.\n", cred);
            scanf("%s", op);
            for(i=0;op[i]!='\0';i++){
                op[i]=toupper(op[i]);
            }
            //printf("%i\n", sizeof(op));
//El usuario verifica que la cifra introducida de creditos es correcta, en caso de respuesta incorrecta te vuelve a pedir el valor de creditos.
           if((op[0]=='S') && (op[1]=='I')  && (op[2]=='\0')){
                break;
           }
            if((op[0]=='N') && (op[1]=='O') && (op[2]=='\0')){
                cred=0;
           }
           else{
                printf("La respuesta indicada es incorrecta\n");
                cred=0;
           }
        }
    }

do{
    printf("\n\n\n\n\n\n\nMarque la opcion de apuesta que desea\n 1     Apostar a un numero\n 2     Apostar a un color\n 3     Apostar a par o impar\n 4     Apostar a pasa o falta\n");

    do{
        printf("\nIndique 1, 2, 3 o 4\n");
        scanf("%s", checkvalor);
        juego=checknumeric(checkvalor, 1, 0, 4, 1);
    }
    while(juego<=0);

   // printf("%d", i)

    do{
    printf("¿Cuanto quieres apostar?\n");
    scanf("%s", checkvalor);
    apuesta=checknumeric(checkvalor, 5, 1, cred, 0);
    }
    while (apuesta<=0);
    cred = cred - apuesta;
    if(juego==1){
        do{
            printf("¿A que número quieres apostar?\n");
            scanf("%s", checkvalor);
            apue = checknumeric(checkvalor, 2, 0, 36, 1);
        }
        while(apue<=0);
    }

    do{
        if(juego==2){
            printf("¿A que quiere apostar, negros o rojos (n/r)?\n");
            scanf ("%s", op2);
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
    }
    while(apue == 2);

    do{
        if(juego==3){
            printf("¿A que quiere apostar, impar o par (i/p)\n?");
            scanf ("%s", op2);
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
    }
    while(apue == 2);

    do{
        if(juego==4){
            printf("¿A que quiere apostar, falta (1-18) o pasa (19-36) (f/p)?\n");
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
    }
    while(apue == 2);

    apuesta = tirodebola(juego, apue, apuesta);
    if(apuesta>0){
        printf("Has GANADO %.1f creditos\n", apuesta);
    }
    if(apuesta==0){
        printf("Has PERDIDO %.1f creditos\n", apuesta);
    }
    cred = cred + apuesta;
    do{
        printf("Su saldo actual es de %.1f creditos\n¿Quiere volver a jugar? marque SI o NO\n", cred);
        scanf(" %s", op);
        for(i=0;op[i]!='\0';i++){
            op[i]=toupper(op[i]);
        }
        //printf("%i\n", sizeof(op));
    //El usuario verifica que la cifra introducida de creditos es correcta, en caso de respuesta incorrecta te vuelve a pedir el valor de creditos.
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
    while(i==1);
}
while(i==0);


return 0;
}



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
        //numcorecto = 0;
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
        //numcorecto = 0;
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
//    if((maxima < 0 && numcorrecto <= maxima)){

    if((numcorrecto < minima) || (numcorrecto > maxima)){
        //Número fuera de rango
        return -3;
    }
        return numcorrecto;
}

double tirodebola(int juegot, int apuet, double apuestat){
//int main(){

    FILE *pf;
    pf = fopen("tablero.txt", "r");
    if(pf==NULL){
        return -1;
    }

    int valor, num;
    //int juegot=2, apuet=1, numt=2;
    char rojo[N], impar[N], falta[N];
    //double apuestat=10;

    srand (time(NULL));
    num=rand()%37;

    while(feof(pf)==0){
    fscanf(pf, "\n%d,%[^,],%[^,],%[^\n]\n", &valor, rojo, impar, falta);
    //printf("%d\t %s\t %s\t %s\n", vals, rojo, impar, falta);
        if(num==valor){
            printf("%d\t %s\t %s\t %s\n", valor, rojo, impar, falta);
            //i=36;
            break;
        }
    }

    fclose(pf);
    if(juegot==1){
        if(apuet==valor){
            return apuestat*36;
        }
        return 0;
    }
    //Juego a rojo (0) o negro (1)
    if(juegot==2){
        if((rojo[0] == 'N') && (apuet==1)){
            return apuestat*2;
        }
        if((rojo[0] == 'R') && (apuet==0)){
            return apuestat*2;
        }
        return 0;
    }
    //Juego a impar (0) o par (1)
    if(juegot==3){
        if((impar[0] == 'P') && (apuet==1)){
            return apuestat*2;
        }
        if((impar[0] == 'I') && (apuet==0)){
            return apuestat*2;
        }
        return 0;
    }
    //Juego a falta (0) o pasa (0)
    if(juegot==4){
        if((falta[0] == 'P') && (apuet==1)){
            return apuestat*2;
        }
        if((falta[0] == 'F') && (apuet==0)){
            return apuestat*2;
        }
        return 0;
    }
// Mostramos en pantalla lo leído
}
