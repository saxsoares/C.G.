#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void Desenha();
void InitScreen();
void Reshape(int , int );
void MovimentaMouse(int, int);
void Keyboard (unsigned char , int , int );
void SpecialKeys (int , int , int );
void Timer(int );

void FitWindow(GLsizei, GLsizei);

GLfloat preto[]={0,0,0},        branco[]={1,1,1},           verde[]={0,1,0},            vermelho[]={1,0,0},         azul[]={0,0,1},
        furchsia[]={1,0,1},     ciano[]={0,1,1},            amarelo[]={1,1,0},          verdeEsc[]={0, 0.39, 0},    azulEsc[]={0,0,0.55},
        roxo[]={0.5,0,0.5},     cinza[]={0.5,0.5,0.5},      azulCeu[]={0.53,0.81,0.98}, verdeGrama[]={0.49,0.99,0}, jambo[]={1,0.27,0},
        laranja[]={1,0.65,0},   marinho[]={0.07,0.04,0.56}, fuligem[]={0.24,0.17,0.12}, cinzaEsc[]={0.66,0.66,0.66},marrom[]={0.65,0.16,0.16},
        cinzaFosco[]={0.41,0.41,0.41},                      rosa[]={1,0.75,0.8},        rosaBri[]={1,0,0.5},        abobora[]={0.99,0.06,0.75};

GLint sw, sh, winPosX, winPosY;  // sw-> screen_width, sh->screen_height
GLfloat w_width, w_height;
GLfloat mouseX, mouseY;


int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    sw = glutGet(GLUT_SCREEN_WIDTH);
    sh = glutGet(GLUT_SCREEN_HEIGHT);
    winPosX = 0; winPosY = 0;
    glutInitWindowPosition(winPosX, winPosY);
    glutInitWindowSize(sw, sh);
    glutCreateWindow("CG Fernando");
        FitWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        glutDisplayFunc(Desenha);
        glutReshapeFunc(Reshape);
        glutTimerFunc(0,Timer,0);
        glutKeyboardFunc(Keyboard);
        glutSpecialFunc(SpecialKeys);
        glutPassiveMotionFunc(MovimentaMouse);
    glutMainLoop();
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

}
void FitWindow(GLsizei w, GLsizei h){
     if (w >= h)
        glutReshapeWindow(h, h);
    else
        glutReshapeWindow(w, w);
}
void InitScreen(){
    w_width = glutGet(GLUT_WINDOW_WIDTH);
    w_height = glutGet(GLUT_WINDOW_HEIGHT);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0);
}
void Keyboard (unsigned char key, int x, int y){
}

void SpecialKeys (int key, int x, int y){
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
                ponto1X = x;
                ponto1Y = y;
            }
            break ;
        default :
            break ;
    }
    glutPostRedisplay() ;
}

void Timer(int extra){
}

void Desenha(){
    InitScreen();
    glBegin(GL_POINTS);
        glColor3fv(azul);
        glVertex2d(0,0);
    glutPostRedisplay();
    glutSwapBuffers();
    glFlush();
}




