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

GLfloat rot_pet, rot_roda, transl_car;

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
        default :  break;
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
}
void Desenha(){
    glClear(GL_COLOR_BUFFER_BIT);
        Msg("'R' para rotacionar petalas", -.99, .95);
        Msg("'A' e 'D' para movimentar o carro", -.99, .90);

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