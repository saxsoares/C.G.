#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void InitScreen();
void MovimentaMouse(int, int);
void MouseFunc(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKeys(int, int, int);
void Timer(int);
void Desenha();
void Reshape(int, int);

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
        glBegin(GL_LINES);
            glColor3fv(cor);
            if(!flag){
                glVertex2f(ponto1X, ponto1Y);
                glVertex2f(ponto2X, ponto2Y);
            }
        glEnd();
    }else if(tipo == 't' ){
        glBegin(GL_TRIANGLES);
            glColor3fv(cor);
            if(!flagT){
                glVertex2f(ponto1X, ponto1Y);
                glVertex2f(ponto2X, ponto2Y);
                glVertex2f(ponto3X, ponto3Y);
            }
        glEnd();
    }
    glutPostRedisplay();
    glFlush();
}
void MouseFunc(int botao, int estado, int x, int y){
    printf("[%.2f | %.2f]\n", mouseX, mouseY);
    switch (botao){
    case GLUT_LEFT_BUTTON :
        if (estado == GLUT_DOWN){
            y = w_height - y;
            mouseX = (float)(((float)x/(float)w_width)*2.0 -1.0);
            mouseY = (float)(((float)y/(float)w_height)*2.0 - 1.0);
            if(tipo == 'r'){
                if(!flag){
                    ponto1X = mouseX;
                    ponto1Y = mouseY;
                }else if(flag){
                    ponto2X = mouseX;
                    ponto2Y = mouseY;
                    cor = corEscolhida;
                }
                flag = (flag+1)%2;
            }else if(tipo == 't'){
                if(flagT == 0){
                    ponto1X = mouseX;
                    ponto1Y = mouseY;
                }else if(flagT == 1){
                    ponto2X = mouseX;
                    ponto2Y = mouseY;
                }else if(flagT == 2){
                    ponto3X = mouseX;
                    ponto3Y = mouseY;
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
    case '0' : corEscolhida = azul;       break;
    case '1' : corEscolhida = amarelo;    break;
    case '2' : corEscolhida = verdeGrama; break;
    case '3' : corEscolhida = vermelho;   break;
    case '4' : corEscolhida = roxo;       break;
    case '5' : corEscolhida = laranja;    break;
    case '6' : corEscolhida = abobora;    break;
    case '7' : corEscolhida = cinza;      break;
    case '8' : corEscolhida = furchsia;   break;
    case '9' : corEscolhida = rosaBri;    break;
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
