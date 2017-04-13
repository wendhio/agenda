#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <locale.h>

#define MAX_CARACTERES 30
#define DIREITA 1
#define BAIXO 2
#define CIMA 4
#define ESQUERDA 3

char get_char_at_xy( int x, int y )
  {
  CHAR_INFO ci;
  COORD xy = { 0, 0 };
  SMALL_RECT rect = { x, y, x, y };
  return ReadConsoleOutput( GetStdHandle( STD_OUTPUT_HANDLE ), &ci, (COORD){1,1}, xy, &rect )
       ? ci.Char.AsciiChar
       : '\0';
  }


typedef struct{
    int matricula;
    char *nome;
} estudante;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}




void textcolor(unsigned short color) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,color);
}

int le_estudante(estudante *p){
    char nome[81];
    scanf("%s", nome);
    (*p).nome = malloc(strlen(nome));
    strcpy((*p).nome , nome);
}

typedef struct{
    char esq;
    char dir;
    char carac[2];
    int x;
    int y;
    COORD origem;
    COORD mn;
    COORD offset;
    COORD limite_inf;
    COORD limite_sup;
    int dist;
    int offsetX;
    int offsetY;
    int limiteX1;
    int limiteY1;
    int limiteX2;
    int limiteY2;
}mCursor;


void entra_texto(COORD inicio, int tam, char *texto){
    int ox = inicio.X;
    int oy = inicio.Y;
    char c_atual;
    int ncarac=0,i=0;
    gotoxy(ox , oy);
    for(;i<tam;i++) putchar(' ');
    gotoxy(ox,oy);
    while(1){
        c_atual = getch();
        switch (c_atual){
            case 13:
                for (i=0;i<ncarac;i++)
                    texto[i] = get_char_at_xy(inicio.X+i,inicio.Y);
                    texto[i]='\0';
                return 0;
            case 8:
                if (ncarac > 0){
                   putchar(8);
                   putchar(' ');
                   putchar(8);
                   ncarac--;
                }
                break;
            default:
                if(ncarac < tam && (c_atual >=48 && c_atual <= 122 || c_atual == 32)){
                    putchar(c_atual);
                    ncarac++;
                }
        }
    }

}


void apaga_cursor(mCursor curs){
    gotoxy(curs.x,curs.y);
    putchar(' ');
    gotoxy(curs.x+curs.dist,curs.y);
    putchar(' ');
}
void desenha_cursor(mCursor curs){
    gotoxy(curs.x,curs.y);
    printf("%c",curs.esq);
    gotoxy(curs.x+curs.dist,curs.y);
    putchar(curs.dir);
}

void move_cursor(mCursor *curs,int direcao){
switch (direcao){
    case DIREITA:
        if((*curs).limiteX2>=(*curs).x+(*curs).offsetX)(*curs).x+=(*curs).offsetX;
        break;
    case ESQUERDA:
        if((*curs).limiteX1<=(*curs).x-(*curs).offsetX)(*curs).x-=(*curs).offsetX;
        break;
    case CIMA:
        if((*curs).limiteY1<=(*curs).y-(*curs).offsetY)(*curs).y-=(*curs).offsetY;
        break;
    case BAIXO:
        if((*curs).limiteY2>=(*curs).y+(*curs).offsetY)(*curs).y+=(*curs).offsetY;
        break;
    }
}

void criaCursor(mCursor *curs,char esq,char dir,int x,int y,int dist,int offsetX,int offsetY,int limiteX1,int limiteY1,int limiteX2,int limiteY2){
    (*curs).esq = esq;
    (*curs).dir = dir;
//    (*curs).Ox = x;
  //  (*curs).Oy = y;
 //   (*curs).m;
 //   (*curs).n;
    (*curs).x = x;
    (*curs).y = y;
    (*curs).dist = dist;
    (*curs).offsetX = offsetX;
    (*curs).offsetY = offsetY;
    (*curs).limiteX1 = limiteX1;
    (*curs).limiteY1 = limiteY1;
    (*curs).limiteX2 = limiteX2;
    (*curs).limiteY2 = limiteY2;
}

int main(){
    char texto_busca[41];
       setlocale(LC_ALL, "");
    mCursor cursor1;
    criaCursor(&cursor1,'[',']',6,10,5,5,2,6,10,40,18);
    //printf("%d - %d", cursor1.x,cursor1.y);
    estudante v_estudante;
    //le_estudante(&v_estudante);
    textcolor(2);
    //printf(v_estudante.nome);
     system("Color 06");
    //gotoxy(23,5);
    //scanf("%d");
    //printf(v_estudante.nome);
    /*textcolor(6);
    printf("\t\n\t26\t27\t28\t29\t30\t31\t");

    textcolor(5);
    printf("\t1\n\t2\t3\t4\t5\t6\t7\t8\n\t9\t10\t11\t12\t13\t14\t15\n");
    textcolor(4);
    printf("\t16");
    textcolor(5);
    printf("\t17\t18\t19\t20\t21\t22\n\t23\t24\t25\t26\t27\t28\t29\n30");

    textcolor(6);
    printf("\t1\t2\t3\t4\t5\t6\t");
    desenha_cursor(cursor1);*/

    printf("%ls",L"=======================================================================================================\nArquivo     Opcoes                                    ┌───────────────────────────────────────────────┐\n                                                      │ Buscar:                                       │   \n   AGENDA DE COMPROMISSOS - MENU PRINCIPAL            └───────────────────────────────────────────────┘\n╔═════════════════════╤════════════════════════╦══════════════════════════════════════════════════════╗\n║       DEZEMBRO      │         2017           ║                 QUARTA-FEIRA 8                       ║\n╠═════════════════════╧════════════════════════╬══════════════════════════════════════════════════════╣\n║                                              ║   Dia    Reunião de trabalho                         ║\n║       D    S    T    Q    Q    S    S        ║   Todo                                               ║\n║                                              ╟──────────────────────────────────────────────────────╢\n║                      1    2    3    4        ║┌  9:00   Prova de Programaçao Imperativa            ┐║\n║                                              ║└ 11:00                                              ┘║\n║        5    6    7  [8]   9   10   11        ╟──────────────────────────────────────────────────────╢\n║                                              ║  12:00   Almoço na casa de Joana                     ║\n║       12   13   14  15   16   17   18        ║  13:00                                               ║\n║                                              ╟──────────────────────────────────────────────────────╢\n║       19   20   21  22   23   24   25        ║  18:00  Show de arrocha                              ║\n║                                              ║  21:00                                               ║\n║       26   27   28  29   30   31             ╟──────────────────────────────────────────────────────╢\n║                                              ║  22:00  Jogar videogame                              ║\n║                                              ║  02:00                                               ║\n║                                              ║                                                      ║\n║                                              ║                                                      ║\n║                                              ║                                                      ║\n╠══════════════════════════════════════════════║                                                      ║\n║ Prova de Programacao imperativa              ║                                                      ║\n║ Horario: 8:30 8/12/2017                      ║                                                      ║\n║ Local: Laboratório do DCOMP                  ║                                                      ║\n║ Alarme: Ligado                               ║                                                      ║\n║ Recorrente: Não                              ║                                                      ║\n║                                              ║                                                      ║\n║                                              ║                                                      ║\n║                                              ║                                                      ║\n║                                              ║                                                      ║\n║                                              ║                                                      ║\n╚══════════════════════════════════════════════╩══════════════════════════════════════════════════════╝\n Aperte B para busca");
    //printf("ouviram do ipiranga as margens palcidas de um povo\nheroico um brado retumbante");
    int a,b;
    textcolor(6);
    //while(1){
    //        textcolor(6);
            //scanf("%d %d",&a,&b);
            textcolor(4);
   // printf("%c",get_char_at_xy(a,b));}

    while(1){
        a=getch();
        if(a==66||a==98){
            entra_texto((COORD){65,2},35,texto_busca);
            printf(texto_busca);
        }
        else
        a=getch();
        apaga_cursor(cursor1);
        if(a==80)move_cursor(&cursor1,BAIXO);
        if(a==72)move_cursor(&cursor1,CIMA);
        if(a==75)move_cursor(&cursor1,ESQUERDA);
        if(a==77)move_cursor(&cursor1,DIREITA);

        desenha_cursor(cursor1);
        //gotoxy(50,50);
        //printf("(%d,%d)",cursor1.x,cursor1.y);
    }
}

/*
main()
{

   cprintf("C programming");

   getch();
   return 0;
*/


//wendhio.wendhio@hotmail.com
