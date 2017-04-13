#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>



#define MAX_CHAR_NOME_EVENTO 80
#define MAX_CHAR_BUSCA 30


#define DIREITA 1
#define BAIXO 2
#define CIMA 4
#define ESQUERDA 3



// ============= funçoes para interface ============================

char get_char_at_xy( int x, int y )
  {
  CHAR_INFO ci;
  COORD xy = { 0, 0 };
  SMALL_RECT rect = { x, y, x, y };
  return ReadConsoleOutput( GetStdHandle( STD_OUTPUT_HANDLE ), &ci, (COORD){1,1}, xy, &rect )
       ? ci.Char.AsciiChar
       : '\0';
  }

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

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
            case 13:return 0;
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
// =================================== FUNÇOES DE SELECAO =========================================


typedef struct{
    char carac[3];
    COORD origem;
    COORD mn;
    COORD offset;
    COORD limites;
    int dist;
}mCursor;

void desenha_cursor(mCursor curs){
    gotoxy(curs.origem.X + curs.offset.X * curs.mn.X, curs.origem.Y + curs.offset.Y * curs.mn.Y);
    putchar(curs.carac[0]);
    gotoxy(curs.origem.X + curs.offset.X * curs.mn.X + curs.dist, curs.origem.Y + curs.offset.Y * curs.mn.Y);
    putchar(curs.carac[1]);
}

void apaga_cursor(mCursor curs){
    gotoxy(curs.origem.X + curs.offset.X * curs.mn.X - curs.dist, curs.origem.Y + curs.offset.Y * curs.mn.Y);
    putchar(curs.carac[0]);
    gotoxy(curs.origem.X + curs.offset.X * curs.mn.X - curs.dist, curs.origem.Y + curs.offset.Y * curs.mn.Y);
    putchar(curs.carac[1]);
}


void move_cursor(mCursor *curs,int direcao){
switch (direcao){
    case DIREITA:
        if(curs->limites.X>=curs->mn.X + curs->offset.X) curs->mn.X+=curs->offset.X;
        break;
   /* case ESQUERDA:
        if((*curs).limiteX1<=(*curs).x-(*curs).offsetX)(*curs).x-=(*curs).offsetX;
        break;
    case CIMA:
        if((*curs).limiteY1<=(*curs).y-(*curs).offsetY)(*curs).y-=(*curs).offsetY;
        break;
    case BAIXO:
        if((*curs).limiteY2>=(*curs).y+(*curs).offsetY)(*curs).y+=(*curs).offsetY;
        break;*/
    }
}

void criaCursor(mCursor* curs, int dist, COORD origem, COORD mn, COORD offset){
    curs->dist = dist;
    curs->mn = mn;
    curs->origem;
    curs->offset;
}


// ============================= Funcoes de data ===================================================

typedef struct{
    int ano;
    int mes;
    int dia;
    int hora;
    int min;
}t_data;

int numero_dias_mes(int mes , int ano){
            int dias;
            if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
              dias = 30;
            else if (mes == 2)
            { int ehBissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
              if (ehBissexto)
                dias = 29;
              else
                dias = 28;
            }
            else
              dias = 31;
            return dias;
}

int dia_semana(int d, int m , int a){
    return (d += m < 3 ? a-- : a - 2, 23*m/9 + d + 4 + a/4- a/100 + a/400)%7;
}
//==============================Funçoes de evento===================================================

typedef struct {
    t_data inicio;
    t_data fim;
    char * nome;
    char * local;
    int recorrente;
    int dias_semana;
}evento;

