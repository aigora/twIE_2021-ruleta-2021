#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define N 20
typedef struct
{
char nick[N];
double creditos;
char contrasena[N];
} jugador;
typedef struct{
int valor;
char rojo[N], impar[N], falta[N];
}resultado;

double checknumeric(char cifra[N], int numentero, int numdecimal, double maxima, double minima);
double tirodebola(int juegot, int apuet, double apuestat);
void borrar();
jugador usuario();
void actualizar(jugador c);
//int checkarray (int longitudmax, char checkchar);

//FUNCIÓN PRINCIPAL
int main(){
    //definir variables
    //char roj, imp, fal; //Variables del número optenido
    char op[3], caracter, checkvalor[N], op2[2];
    double apuesta, cred = 0;
    int i=0, juego, apue;
    jugador registro;
    resultado r;
    FILE *pf;
    borrar();
    //cred = usuario();
    //Nombre del usuario
    printf("Bienvenido al casino ETSIDI.\nEn este casino podras ganar creditos o perderlos, la suerte decide.\n");

    registro = usuario();
do{
    i=1;
    printf("\n\n\n\n\n");
    pf = fopen("mesa.txt", "r");
    if(pf==NULL){
        printf("Error al leer el fichero mesa\n");

    }
    while(feof(pf) == 0){
        caracter = fgetc(pf);
        printf("%c", caracter);
    }
    fclose(pf);
   printf("\nMarque la opcion de apuesta que desea\n 1\tApostar a un numero\n 2\tApostar a un color\n 3\tApostar a par o impar\n"
           " 4\tApostar a pasa o falta\n 5\tMostrar resultados anteriores\n 6\tCambiar de usuario\n 7\tSALIR\n");

    do{
        printf("\nIndique 1, 2, 3, 4, 5 o 6\n");
        scanf("%s", checkvalor);
        juego=checknumeric(checkvalor, 1, 0, 7, 1);
    }
    while(juego<=0);

   // printf("%d", i)


    if(juego==1){
        do{
            printf("¿A que número quieres apostar? \n");
            scanf("%s", checkvalor);
            apue = checknumeric(checkvalor, 2, 0, 36, 1);
        }
        while(apue<=0);
    }

    do{
        if(juego==2){
            printf("¿A que quiere apostar, negros o rojos (n/r)? \n");
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
        i=1;
    }
    while(apue == 2);

    do{
        if(juego==3){
            printf("¿A que quiere apostar, impar o par (i/p)? \n");
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
        i=1;
    }
    while(apue == 2);

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

    if(juego == 5){
        pf = fopen("resultados.txt", "r");
        if(pf==NULL){
            printf("Error al leer el fichero resultados\n");
        }

        while(feof(pf)==0){
            fscanf(pf, "\n%d,%[^,],%[^,],%[^\n]\n", &r.valor, r.rojo, r.impar, r.falta);
            //printf("%d\t %s\t %s\t %s\n", vals, rojo, impar, falta);
            printf("%d\t %s\t %s\t %s\n", r.valor, r.rojo, r.impar, r.falta);
                    //i=36;
        }
        fclose(pf);
    }
    if(juego == 6){
        registro = usuario();
        i = 0;
    }
    if (juego == 7){
        return 0;
    }

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
    while(i==1){
        if(registro.creditos<=0){
            printf("Su saldo actual es de %.1f creditos\nFIN DE LA PARTIDA\n", registro.contrasena);
            return 0;
        }
        printf("Su saldo actual es de %.1f creditos\n¿Quiere volver a jugar? marque SI o NO\n", registro.creditos);
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
}
while(i==0);

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
//FUNCIÓN QUE TE DEVUELVE LA APUESTA MAS LO GANADO O 0 SI HAS PERDIDO
double tirodebola(int juegot, int apuet, double apuestat){
//int main(){

    FILE *pf;
    resultado bola;

    int num;

    srand (time(NULL));
    num=rand()%37;

    pf = fopen("tablero.txt", "r");
    if(pf==NULL){
        return -1;
    }

    while(feof(pf)==0){
    fscanf(pf, "\n%d,%[^,],%[^,],%[^\n]\n", &bola.valor, bola.rojo, bola.impar, bola.falta);
    //printf("%d\t %s\t %s\t %s\n", vals, rojo, impar, falta);
        if(num==bola.valor){
            printf("%d\t %s\t %s\t %s\n", bola.valor, bola.rojo, bola.impar, bola.falta);
            //i=36;
            break;
        }
    }

    fclose(pf);

    pf = fopen("resultados.txt", "a+");
    if(pf==NULL){
        return -2;
    }
    fprintf(pf, "%i,%s,%s,%s\n", bola.valor, bola.rojo, bola.impar, bola.falta);
    fclose(pf);

    if(juegot==1){
        if(apuet==bola.valor){
            return apuestat*36;
        }
        return 0;
    }

    //Juego a rojo (0) o negro (1)
    if(juegot==2){
        if((bola.rojo[0] == 'N') && (apuet==1)){
            return apuestat*2;
        }
        if((bola.rojo[0] == 'R') && (apuet==0)){
            return apuestat*2;
        }
        return 0;
    }
    //Juego a impar (0) o par (1)
    if(juegot==3){
        if((bola.impar[0] == 'I') && (apuet==1)){
            return apuestat*2;
        }
        if((bola.impar[0] == 'P') && (apuet==0)){
            return apuestat*2;
        }
        return 0;
    }
    //Juego a falta (0) o pasa (0)
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
//FUNCIÓN QUE TE PERMITE REGISTRARTE O INICIAR SESIÓN
jugador usuario(){
    int i, j, op;
    char nomregistrado[N], contrasena[N], checkvalor[N], creditos[N];
    jugador c;
    //double creditos;
    //jugador registro[2];
    FILE *pf;
    do{
        printf("Marque una de las siguiente opciones:\n1\t Iniciar sesión\n2\t Registrarme\n");
        scanf("%s", &checkvalor);
    //    scanf("%s", checkvalor);
        op = checknumeric(checkvalor, 1, 0, 2, 1);
    }while(op<=0);
    printf("Indique su nick, al terminar pulse ENTER.\nComo maximo se admiten 19 caracteres y no se admiten espacio\nnick:\t");
    scanf ("%s", c.nick);
    if(op == 2){
        i = 1;

        while(i == 1){
            i=0;
            pf = fopen("usuarios.txt", "r");
            if(pf == NULL){
                printf("Error al abrir el fichero usuarios\n");
                return (jugador) {'\0', 0, '\0'};
            }
            while(feof(pf)==0){
                fscanf(pf, "%[^;];%[^;];%[^\n]\n", nomregistrado, c.contrasena, creditos);
                //printf("%s\t %s\t %f\n", nomregistrado, contrasena, c.creditos);
                for(j=0; c.nick[j] == nomregistrado[j]; j++){
                   // printf("%i\t %c\t %c\n", j, nomregistrado[j], c.nick[j]);
                    if((c.nick[j]=='\0') && (nomregistrado[j]=='\0')){
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
                printf("Este nombre de usuario no esta disponible, por favor, escoja otro nombre\n");
                scanf("%s", c.nick);
            }
        }
        c.creditos = atof(creditos);
        printf("Escriba la contraseña\nCONTRASÑA:\t");
        scanf("%s", c.contrasena);

        do{
        printf("Indique su número de creditos\nCREDITOS\t");
        scanf("%s", checkvalor);
        c.creditos = checknumeric(checkvalor, 5, 1, 0, 0);
        if(c.creditos <= 0){
            printf("Valor introducido incorrecto\n");
        }
        }while(creditos <= 0);

        pf = fopen("usuarios.txt", "a+");
        if(pf == NULL){
            printf("Error al abrir el fichero usuarios\n");
            return c;
        }
        fprintf(pf, "%s;%s;%.1f\n", c.nick, c.contrasena, c.creditos);
        fclose(pf);
        return c;
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
                fscanf(pf, "%[^;];%[^;];%[^\n]\n", nomregistrado, contrasena, creditos);
                //printf("%s\t %s\t %f\n", nomregistrado, contrasena, creditos);
                for(j=0; c.nick[j] == nomregistrado[j]; j++){
                   // printf("%i\t %c\t %c\n", j, nomregistrado[j], c.nick[j]);
                    if((c.nick[j]=='\0') && (nomregistrado[j]=='\0')){
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
                printf("nick incorecto, por favor vuelve a indicar su NIC\n");
                scanf("%s", c.nick);
            }
        }
        printf("Escriba la contraseña\nCONTRASÑA:\t");
        scanf("%s", c.contrasena);
        do{
            i=1;
            for(j=0; c.contrasena[j] == contrasena[j]; j++){
                //printf("%i\t %c\t %c\n", j, nomregistrado[j], c.nick[j]);
                if((c.contrasena[j]=='\0') && (contrasena[j]=='\0')){
                    i=0;
                    break;
                }
            }
            if(i == 1){
            fclose(pf);
            printf("Contraseña incorecta, por favor vuelve a indicar su contraseña\n");
            scanf("%s", c.contrasena);
            }

        }while(i==1);
        c.creditos = atof(creditos);
        printf("Su saldo actual es de %.1f creditos\n", c.creditos);
        //printf("%s\t %.1f\t %s\n", c.nick, c.creditos, c.contrasena);
  //      return (jugador) {c.nick, c.creditos, c.contrasena};
        return c;
    }
    return c;
}
//FUNCIÓN QUE QUE ACTUALIZA EL VALOR DE LOS CREDITOS EN EL FICHERO "usuarios"
void actualizar(jugador c){
/*int checkarray (int longitudmax, char checkchar){
    int i=0;

    for(i=0; checkchar[i] != '\0'; ++i){
      if(checkarray[i]==' '){
        return 1;
      }
    }
    if(longitudmax >=i){
        return 1;
    }
    return 0;
}
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
        //printf("%s\t %s\t %f\n", c2.nick, c2.contrasena, c2.creditos);
        for(j=0; c.nick[j] == c2.nick[j]; j++){
           // printf("%i\t %c\t %c\n", j, nomregistrado[j], c.nick[j]);
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
        //printf("%s\t %s\t %f\n", c2.nick, c2.contrasena, c2.creditos);
    }
    fclose(pf);
    pf2 = fopen("usuarios2.txt", "w");
    fclose(pf2);
        if(pf2==NULL){
        printf("Error al borrar el ficheso usuarios2\n");
    }
    fclose(pf2);
    return;
}*/
