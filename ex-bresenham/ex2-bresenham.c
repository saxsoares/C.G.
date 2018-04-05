#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <GL/glut.h>

void InitScreen();
void MovimentaMouse(int, int);
void MouseFunc(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKeys(int, int, int);
void Timer(int);
void Desenha();
void Reshape(int, int);
void bresenham (int ,int , int ,int, GLfloat *);
void write_pixel(int, int, GLfloat *);

GLfloat preto[]={0,0,0},        branco[]={1,1,1},           verde[]={0,1,0},            vermelho[]={1,0,0},
        azul[]={0,0,1},         amarelo[]={1,1,0},          furchsia[]={1,0,1},         rosa[]={1,0.75,0.8},
        rosaBri[]={1,0,0.5},    abobora[]={0.99,0.06,0.75}, ciano[]={0,1,1},            verdeEsc[]={0,0.39,0},
        azulEsc[]={0,0,0.55},   marinho[]={0.07,0.04,0.56}, fuligem[]={0.24,0.17,0.12}, roxo[]={0.5,0,0.5},
        jambo[]={1,0.27,0},     laranja[]={1,0.65,0},       marrom[]={0.65,0.16,0.16},  cinza[]={0.5,0.5,0.5},
        cinzaEsc[]={0.66,0.66,0.66},  azulCeu[]={0.53,0.81,0.98}, verdeGrama[]={0.49,0.99,0}, cinzaFosco[]={0.41,0.41,0.41};
GLfloat w_width, w_height, *cor = azul,*corEscolhida = azul;
GLfloat mouseX = 0, mouseY = 0, ponto1X = 0, ponto1Y = 0, ponto2X = 0, ponto2Y = 0,ponto3X = 0, ponto3Y = 0;
GLint flag = 0, flagT = 0;
GLchar tipo = 'r';

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("CG EX INTERACAO - FERNANDO");
        InitScreen();
        glutDisplayFunc(Desenha);
        glutMouseFunc(MouseFunc);
        glutKeyboardFunc(Keyboard);
    glutMainLoop();
}
void InitScreen(){
    w_width = glutGet(GLUT_WINDOW_WIDTH);
    w_height = glutGet(GLUT_WINDOW_HEIGHT);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0);
}
void Desenha(){
    InitScreen();
    if(tipo == 'r'){
        if(!flag){
            bresenham(ponto1X, ponto2X, ponto1Y, ponto2Y, cor);
        }
    }else if(tipo == 't'){
        if(!flagT){
            bresenham(ponto1X, ponto2X, ponto1Y, ponto2Y, cor);
            bresenham(ponto2X, ponto3X, ponto2Y, ponto3Y, cor);
            bresenham(ponto3X, ponto1X, ponto3Y, ponto1Y, cor);
        }
    }
    glutPostRedisplay();
    glFlush();
}
void bresenham (int x1,int x2, int y1,int y2, GLfloat *cor){
    int dx,dy, incSup, incInf, p, x, y, auxX, auxY;
    GLfloat *valor=cor;

    if(x1 > x2 && y1 > y2){
        auxX = x1; auxY = y1;
        x1 = x2; y1 = y2;
        x2 = auxX; y2 = auxY;
    }
    dx = x2 > x1 ? x2-x1 : x1 - x2;
    dy = y2 > y1 ? y2-y1 : y1 - y2;

    if(dx >= dy){
        p = 2*dy-dx;

        incInf = 2*dy;
        incSup = 2*(dy-dx);

        x = x1; y = y1;
        write_pixel(x,y,valor);
        if( x2 >= x1)
            while (x < x2){
                if (p < 0){
                    p = p + incInf;
                }
                else{
                    p = p + incSup;
                    y = y2 > y1 ? y+1 : y-1;
                }
                x++;
                write_pixel (x, y, valor);
            }
        else
            while (x > x2){
                if (p < 0){
                    p = p + incInf;
                }
                else{
                    p = p + incSup;
                    y = y2 > y1 ? y+1 : y-1;
                }
                x--;
                write_pixel (x, y, valor);
            }
    } else{
        p = 2*dx-dy;

        incInf = 2*dx;
        incSup = 2*(dx-dy);

        x = x1; y = y1;
        write_pixel(x,y,valor);
        if(y2 >= y1)
            while (y < y2){
                if (p < 0){
                    p = p + incInf;
                }else{
                    p = p + incSup;
                    x = x2 > x1 ? x+1 : x-1;
                }
                y++;
                write_pixel (x, y, valor);
            }
        else
            while (y > y2){
                if (p < 0){
                    p = p + incInf;
                }else{
                    p = p + incSup;
                    x = x2 > x1 ? x+1 : x-1;
                }
                y--;
                write_pixel (x, y, valor);
            }
    }
}

void write_pixel(int x, int y, GLfloat *cor){
    GLfloat px, py;
//    y = w_height - y;
    px = (float)(((float)x/(float)w_width)*2.0 -1.0);
    py = (float)(((float)y/(float)w_height)*2.0 - 1.0);
    glColor3fv(cor);
    glBegin(GL_POINTS);
        glVertex2f(px, py);
    glEnd();
}

void MouseFunc(int botao, int estado, int x, int y){
    switch (botao){
        case GLUT_LEFT_BUTTON :
            if (estado == GLUT_DOWN){
                y = w_height - y;
                printf("[%d | %d]\n", x, y);
                if(tipo == 'r'){
                    if(!flag){
                        ponto1X = x;
                        ponto1Y = y;
                    }else if(flag){
                        ponto2X = x;
                        ponto2Y = y;
                        cor = corEscolhida;
                    }
                    flag = (flag+1)%2;
                }else if(tipo == 't'){
                    if(flagT == 0){
                        ponto1X = x;
                        ponto1Y = y;
                    }else if(flagT == 1){
                        ponto2X = x;
                        ponto2Y = y;
                    }else if(flagT == 2){
                        ponto3X = x;
                        ponto3Y = y;
                        cor = corEscolhida;
                    }
                    flagT = (flagT+1)%3;
                }
            }
            break ;
        default :
            break ;
    }
    glutPostRedisplay() ;
}

void Keyboard (unsigned char key, int x, int y){
    switch (key)    {
    case '0' : cor = azul;       break;
    case '1' : cor = amarelo;    break;
    case '2' : cor = verdeGrama; break;
    case '3' : cor = vermelho;   break;
    case '4' : cor = roxo;       break;
    case '5' : cor = laranja;    break;
    case '6' : cor = abobora;    break;
    case '7' : cor = cinza;      break;
    case '8' : cor = furchsia;   break;
    case '9' : cor = rosaBri;    break;
    case 'r' :
    case 'R' :
        tipo = 'r';
        ponto1X = 0;
        ponto1Y = 0;
        ponto2X = 0;
        ponto2Y = 0;
        ponto3X = 0;
        ponto3Y = 0;
        break;
    case 't' :
    case 'T' :
        tipo = 't';
        ponto1X = 0;
        ponto1Y = 0;
        ponto2X = 0;
        ponto2Y = 0;
        ponto3X = 0;
        ponto3Y = 0;
       break;
    default :  break;
    }
    glutPostRedisplay() ;
}
