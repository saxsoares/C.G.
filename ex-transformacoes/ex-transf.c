#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.141592654
void InitScreen();
void MovimentaMouse(int, int);
void MouseFunc(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKeys(int, int, int);
void Timer(int);
void Desenha();
void Reshape(int, int);
void Circulo(GLfloat raio, GLint ang, GLboolean f);
void flor();
void carro();
void robo();
void Msg(char *, GLfloat , GLfloat );
GLfloat preto[]={0,0,0},        branco[]={1,1,1},           verde[]={0,1,0},            vermelho[]={1,0,0},
        azul[]={0,0,1},         amarelo[]={1,1,0},          furchsia[]={1,0,1},         rosa[]={1,0.75,0.8},
        rosaBri[]={1,0,0.5},    abobora[]={0.99,0.06,0.75}, ciano[]={0,1,1},            verdeEsc[]={0,0.39,0},
        azulEsc[]={0,0,0.55},   marinho[]={0.07,0.04,0.56}, fuligem[]={0.24,0.17,0.12}, roxo[]={0.5,0,0.5},
        jambo[]={1,0.27,0},     laranja[]={1,0.65,0},       marrom[]={0.65,0.16,0.16},  cinza[]={0.5,0.5,0.5},
        cinzaEsc[]={0.66,0.66,0.66},  azulCeu[]={0.53,0.81,0.98}, verdeGrama[]={0.49,0.99,0}, cinzaFosco[]={0.41,0.41,0.41};

GLint sw, sh, winPosX, winPosY;
GLfloat w_width, w_height;
GLfloat mouseX, mouseY, mouseClickX, mouseClickY;

GLfloat rot_pet=0, rot_roda=0, transl_car=0, brEsq=0, brDIr=0, antEsq=0, antDir=0, rotPE=0, rotPD=0,rotPE2=0, rotPD2=0;

void FitWindow(GLsizei w, GLsizei h){
     if (w >= h)
        glutReshapeWindow(h, h);
    else
        glutReshapeWindow(w, w);
}
void Reshape(int w, int h){
    if (w >= h)
        glViewport(0, 0, (GLsizei)h, (GLsizei)h) ;
    else
        glViewport(0, 0, (GLsizei)w, (GLsizei)w) ;
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    gluOrtho2D(-1.0,1.0,-1.0,1.0) ;
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity() ;
    w_width = glutGet(GLUT_WINDOW_WIDTH);
    w_height = glutGet(GLUT_WINDOW_HEIGHT);
}
void InitScreen(){
    w_width = glutGet(GLUT_WINDOW_WIDTH);
    w_height = glutGet(GLUT_WINDOW_HEIGHT);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(-1.0,1.0,-1.0,1.0);
}
void MovimentaMouse(int x, int y){
    y = w_height - y;
    mouseX = (double)(((double)y/(double)w_height)*2.0 - 1.0);
    mouseY = (double)(((double)x/(double)w_width)*2.0 -1.0);
}
void MouseFunc(int botao, int estado, int x, int y){
    switch (botao){
        case GLUT_LEFT_BUTTON :
            if (estado == GLUT_DOWN){
                y = w_height - y;
                mouseClickX = (float)(((float)x/(float)w_width)*2.0 -1.0);
                mouseClickY = (float)(((float)y/(float)w_height)*2.0 - 1.0);
            }
            break ;
        default :
            break ;
    }
    glutPostRedisplay() ;
}
void Keyboard (unsigned char key, int x, int y){
    switch (key)    {
        case 'r' :  rot_pet += 2;  break;
        case 'R' :  rot_pet -= 2;  break;
        case 'a' :
        case 'A' :  rot_roda += 2.5;
                    transl_car -= 0.005;
                    break;
        case 'D' :
        case 'd' :  rot_roda -= 2.5;
                    transl_car += 0.005;
                    break;
        case 'q' :  brEsq = brEsq <= 9.0 ? brEsq + 1: brEsq;  break;
        case 'Q' :  brEsq = brEsq >= -113.0 ? brEsq - 1: brEsq;  break;
        case 'e' :  brDIr = brDIr <= 81.0 ? brDIr + 1: brDIr;  break;
        case 'E' :  brDIr = brDIr >= -48.0 ? brDIr - 1: brDIr;  break;
        case 'z' :  antEsq = antEsq <= 93.0 ? antEsq + 1: antEsq;  break;
        case 'Z' :  antEsq = antEsq >= -120.0 ? antEsq - 1: antEsq;  break;
        case 'c' :  antDir = antDir <= 208.0 ? antDir + 1: antDir;  break;
        case 'C' :  antDir = antDir >= 0.0 ? antDir - 1: antDir;  break;
        case 'w' :  rotPE = rotPE <= 90 ? rotPE + 1: rotPE;  break;
        case 'W' :  rotPE = rotPE > 0.0 ? rotPE - 1: rotPE;  break;
        case 's' :  rotPD = rotPD < 0 ? rotPD + 1: rotPD;  break;
        case 'S' :  rotPD = rotPD >= -90.0 ? rotPD - 1: rotPD;  break;
        case 'T' :  rotPE2 = rotPE2 >= -90 ? rotPE2 - 1: rotPE2;  break;
        case 't' :  rotPE2 = rotPE2 < 0.0 ? rotPE2 + 1: rotPE2;  break;
        case 'G' :  rotPD2 = rotPD2 > 0 ? rotPD2 - 1: rotPD2;  break;
        case 'g' :  rotPD2 = rotPD2 <= 90.0 ? rotPD2 + 1: rotPD2;  break;
        default :
        printf("BE: %.1f - BD: %.1f - AE: %.1f - AD: %.1f\n", brEsq, brDIr, antEsq, antDir);
        break;
    }
    glutPostRedisplay() ;
}

void SpecialKeys (int key, int x, int y){
}
void Circulo(GLfloat raio, GLint ang, GLboolean f){
    int i; float angulo;
    ang = ((float)ang/360.0)*60;
    if(f) glBegin(GL_LINE_LOOP);
    else glBegin(GL_LINE_STRIP);
        for (i=0;i<=ang;i++) {
            angulo= 2 * PI * i / 60.0;
            glVertex2f(raio*2*cos(angulo), raio*2*sin(angulo));
        }
    glEnd();
}
void flor(){
    int i, ang; float angulo;
    glPushMatrix();
        glScalef(0.75,0.75,1);
        glTranslatef(0,0.95,0);
        // Circulo central
        glColor3fv(rosaBri);
        Circulo(0.125, 360, 1);
        //Petalas
        glPushMatrix();
            glRotatef(rot_pet,0,0,1);
            for(i = 0; i < 7; i++){ // Criando 6 petalas
            glPushMatrix();
                glRotatef(i*60,0,0,1);  // Rotacionando cada petala criada por angulo 'i', assim cada uma imprimira na sua posicao
                glTranslatef(0,0.25,0); // Petala foi desenhada no centro, aqui ela é levada para a borda do circulo.
                glRotatef(-15,0,0,1);   // rotacao para ajuste na borda do circulo
                glColor3fv(azul);
                Circulo(0.06125, 210, 0);
            glPopMatrix();
            }
        glPopMatrix();
    glPopMatrix();
}
void carro(){
    int i; float angulo;
    glBegin(GL_LINE_LOOP);
    glColor3fv(roxo);
    glVertex2f(0,0);
    glVertex2f(0,0.05);
    glVertex2f(.1,.1);
    glVertex2f(.25,.1);
    glVertex2f(.3,.06);
    glVertex2f(.4,.025);
    glVertex2f(.4,0);
    glVertex2f(.335,0);
    for (i=0;i<=90;i++) {
            angulo= 2 * PI * i / 60.0;
            glVertex2f(0.035*cos(angulo)+.3, 0.035*sin(angulo));
    }
    glVertex2f(0.12,0);
    for (i=0;i<=90;i++) {
            angulo= 2 * PI * i / 60.0;
            glVertex2f(0.035*cos(angulo)+.085, 0.035*sin(angulo));
    }
    glEnd();
    //rodas();
    glPushMatrix();
    glTranslatef(.085,0,0);
    glRotatef(rot_roda,0,0,1);
    glBegin(GL_LINES);
        glVertex2f(0, 0.035);
        glVertex2f(0,-0.035);
        glVertex2f( 0.035, 0);
        glVertex2f(-0.035, 0);
        glVertex2f( 0.0175, 0.0303108891325);
        glVertex2f(-0.0175,-0.0303108891325);
        glVertex2f( 0.0303108891325, 0.0175);
        glVertex2f(-0.0303108891325,-0.0175 );
        glVertex2f(-0.0175, 0.0303108891325);
        glVertex2f( 0.0175,-0.0303108891325);
        glVertex2f(-0.0303108891325, 0.0175);
        glVertex2f( 0.0303108891325,-0.0175 );
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(.3,0,0);
    glRotatef(rot_roda,0,0,1);
    glBegin(GL_LINES);
        glVertex2f(0, 0.035);
        glVertex2f(0,-0.035);
        glVertex2f( 0.035, 0);
        glVertex2f(-0.035, 0);
        glVertex2f( 0.0175, 0.0303108891325);
        glVertex2f(-0.0175,-0.0303108891325);
        glVertex2f( 0.0303108891325, 0.0175);
        glVertex2f(-0.0303108891325,-0.0175);
        glVertex2f(-0.0175, 0.0303108891325);
        glVertex2f( 0.0175,-0.0303108891325);
        glVertex2f(-0.0303108891325, 0.0175);
        glVertex2f( 0.0303108891325,-0.0175);
    glEnd();
    glPopMatrix();
}
void robo(){
    int i; float angulo;
    glPushMatrix();
    glTranslatef(0,-.6,0);
    glScalef(1,1,1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(  0 , 0);
        glVertex2f(-.1 , 0);
        glVertex2f(-.15,.25);
        glVertex2f(-.05,.3);
        glVertex2f( .05,.3);
        glVertex2f( .15,.25);
        glVertex2f( .1 , 0);
    glEnd();
    //Head
    glBegin(GL_LINE_LOOP);
        glVertex2f( .05,.3);
        glVertex2f( .05,.4);
        for (i=0;i<=30;i++) {
            angulo= 2 * PI * i / 60.0;
            glVertex2f(0.05*cos(angulo), 0.05*sin(angulo)+.4);
        }
        glVertex2f(-.05,.3);
    glEnd();
    glBegin(GL_LINE_LOOP);
        for (i=0;i<=60;i++) {
            angulo= 2 * PI * i / 60.0;
            glVertex2f(0.015*cos(angulo)-.025, 0.015*sin(angulo)+.375);
        }
    glEnd();
    glBegin(GL_LINE_LOOP);
        for (i=0;i<=60;i++) {
            angulo= 2 * PI * i / 60.0;
            glVertex2f(0.015*cos(angulo)+.025, 0.015*sin(angulo)+.375);
        }
    glEnd();
    glBegin(GL_LINES);
    glLineWidth(3.0);
        glVertex2f(.025,.335);
        glVertex2f(-.025,.335);
    glEnd();
    glPopMatrix();
    // Articulacoes
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix();
    glTranslatef(0,-.6,0);
    glBegin(GL_POLYGON);
        for (i=0;i<=60;i++) {
            angulo= 2 * PI * i / 60.0;
            glVertex2f(0.03*cos(angulo)-.144, 0.03*sin(angulo)+.22);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for (i=0;i<=60;i++) {
            angulo= 2 * PI * i / 60.0;
            glVertex2f(0.03*cos(angulo)+.144, 0.03*sin(angulo)+.22);
        }
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(.1,0);
        glVertex2f(.01,0);
        for (i=180;i<=rotPE+180;i++) {
            angulo= PI * i / 180.0;
            glVertex2f(0.09*cos(angulo)+.1, 0.09*sin(angulo));
        }
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-.1,0);
        glVertex2f(-.01,0);
        for (i=360;i>=rotPD+360;i--) {
            angulo= PI * i / 180.0;
            glVertex2f(0.09*cos(angulo)-.1, 0.09*sin(angulo));
        }
    glEnd();
    glPopMatrix();
    // Bracos
    glPushMatrix();
        glPushMatrix();
        glTranslatef(-.144,-.38,0);
        glRotatef(brEsq+68,0,0,1);
            glPolygonMode(GL_FRONT, GL_FILL);
            glBegin(GL_POLYGON);
            for (i=0;i<=60;i++) {
                angulo= 2 * PI * i / 60.0;
                glVertex2f(0.03*cos(angulo)-.1, 0.03*sin(angulo));
            }
            glEnd();
            glPolygonMode(GL_FRONT, GL_LINE);
            glRectf(0,.03,-.1,-.03);
            glPushMatrix();
                glTranslatef(-.1,0,0);
                glRotatef(antEsq+10, 0, 0, 1);
                glTranslatef(.1,0,0);
                glRectf(-.1,.03, -.2, -.03);
                glRectf(-.2, .035, -.25, -.035);
            glPopMatrix();
        glPopMatrix();
        glRotatef(180,0,1,0);
        glPushMatrix();
        glTranslatef(-.144,-.38,0);
        glRotatef(brDIr+2,0,0,1);
            glPolygonMode(GL_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            for (i=0;i<=60;i++) {
                angulo= 2 * PI * i / 60.0;
                glVertex2f(0.03*cos(angulo)-.1, 0.03*sin(angulo));
            }
            glEnd();
            glPolygonMode(GL_BACK, GL_LINE);
            glRectf(0,.03,-.1,-.03);
            glPushMatrix();
                glTranslatef(-.1,0,0);
                glRotatef(antDir-110, 0, 0, 1);
                glTranslatef(.1,0,0);
                glRectf(-.1,.03, -.2, -.03);
                glRectf(-.2, .035, -.25, -.035);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    // Perna dir
    glPushMatrix();
        glTranslatef(-.1,-.6,0);
        glRotatef(rotPD,0,0,1);
        glRectf(0,0,.09,-.15);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        for (i=0;i<=60;i++) {
            angulo= 2 * PI * i / 60.0;
            glVertex2f(0.045*cos(angulo)+.045, 0.045*sin(angulo)-.15);
        }
        glEnd();
        glPolygonMode(GL_FRONT, GL_LINE);
        glPushMatrix();
            glTranslatef(.045,-.15,0);
            glRotatef(rotPD2,0,0,1);
            glTranslatef(-.045,.15,0);
            glRectf(0,-.15,.09,-.3);
        glPopMatrix();
    glPopMatrix();
    // Perna Esq
    glPushMatrix();
        glTranslatef(.1,-.6,0);
        glRotatef(rotPE,0,0,1);
        glRectf(0,0,-.09,-.15);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        for (i=0;i<=60;i++) {
            angulo= 2 * PI * i / 60.0;
            glVertex2f(0.045*cos(angulo)-.045, 0.045*sin(angulo)-.15);
        }
        glEnd();
        glPolygonMode(GL_FRONT, GL_LINE);
        glPushMatrix();
            glTranslatef(-.045,-.15,0);
            glRotatef(rotPE2,0,0,1);
            glTranslatef(.045,.15,0);
            glRectf(0,-.15,-.09,-.3);
        glPopMatrix();
    glPopMatrix();
}
void Desenha(){
    glClear(GL_COLOR_BUFFER_BIT);
        Msg("'R'/'r' para rotacionar petalas", -.99, .95);
        Msg("'A' e 'D' para movimentar o carro", -.99, .90);
        Msg("'Q'/'q' para movimentar braço esq", -.99, .85);
        Msg("'Z'/'z' para movimentar antebraço esq", -.99, .80);
        Msg("'E'/'e' para movimentar braço dir", -.99, .75);
        Msg("'C'/'c' para movimentar antebraço dir", -.99, .70);
        Msg("'W'/'w' para movimentar coxa dir", -.99, .65);
        Msg("'T'/'t' para movimentar perna dir", -.99, .60);
        Msg("'S'/'s' para movimentar coxa Esq", -.99, .55);
        Msg("'G'/'g' para movimentar perna esq", -.99, .50);
        flor();

        glPushMatrix();
        glTranslatef(transl_car-.2, 0, 0);     // fazendo o carro andar
        glScalef(1.2, 1.2,1);               // Aumentando o carro
        carro();
        glPopMatrix();

        robo();
    glutPostRedisplay();
    glFlush();
}
void Msg(char *string, GLfloat x, GLfloat y){
        glRasterPos2f(x,y);
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*string++);
}
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    sw = glutGet(GLUT_SCREEN_WIDTH);
    sh = glutGet(GLUT_SCREEN_HEIGHT);
    winPosX = (sw-sh)/2; winPosY = 0;
    glutInitWindowPosition(winPosX, winPosY);
    glutInitWindowSize(sh, sh);
    glutCreateWindow("CG EX INTERACAO - FERNANDO");
        FitWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        InitScreen();
        glutReshapeFunc(Reshape);
        glutPassiveMotionFunc(MovimentaMouse);
        glutMouseFunc(MouseFunc);
        glutKeyboardFunc(Keyboard);
        glutSpecialFunc(SpecialKeys);
        glutDisplayFunc(Desenha);
    glutMainLoop();
}
