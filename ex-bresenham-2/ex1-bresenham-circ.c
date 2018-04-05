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
void Bresenham (int, GLfloat *);
void Write_pixel(int, int, GLfloat *);
void MouseFunc(int, int, int, int);
void FitWindow(GLsizei, GLsizei);

GLfloat preto[]={0,0,0},        branco[]={1,1,1},           verde[]={0,1,0},            vermelho[]={1,0,0},         azul[]={0,0,1},
        furchsia[]={1,0,1},     ciano[]={0,1,1},            amarelo[]={1,1,0},          verdeEsc[]={0, 0.39, 0},    azulEsc[]={0,0,0.55},
        roxo[]={0.5,0,0.5},     cinza[]={0.5,0.5,0.5},      azulCeu[]={0.53,0.81,0.98}, verdeGrama[]={0.49,0.99,0}, jambo[]={1,0.27,0},
        laranja[]={1,0.65,0},   marinho[]={0.07,0.04,0.56}, fuligem[]={0.24,0.17,0.12}, cinzaEsc[]={0.66,0.66,0.66},marrom[]={0.65,0.16,0.16},
        cinzaFosco[]={0.41,0.41,0.41},                      rosa[]={1,0.75,0.8},        rosaBri[]={1,0,0.5},        abobora[]={0.99,0.06,0.75};

GLint sw, sh, winPosX, winPosY;  // sw-> screen_width, sh->screen_height
GLfloat w_width, w_height, *cor = azul,*corEscolhida = azul;
GLfloat ponto1X = 0, ponto1Y = 0;
GLint raio = 100;

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
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
//        glutPassiveMotionFunc(MovimentaMouse);
        glutMouseFunc(MouseFunc);
    glutMainLoop();
}
void SpecialKeys (int key, int x, int y){
}
void Timer(int extra){
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
    glEnd();
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
    case 'r':
    case 'R':
        break;
    case 'e':
    case 'E':
        break;
    default :  break;
    }
    glutPostRedisplay() ;
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


void Desenha(){
    InitScreen();
    Bresenham(raio, cor);

    glutPostRedisplay();
    glFlush();
}
void Bresenham (int raio, GLfloat *cor){
    int x, y, k;
    float pk;
    x = 0; y = raio;

    pk=(5.0/4.0)-raio;

    /* Plot the points */
    /* Plot the first point */
    Write_pixel(x, y, cor);

    /* Find all vertices till x=y */
    while(x < y){
        x = x + 1;
        if(pk < 0)
          pk = pk + 2*x+1;
        else{
          y = y - 1;
          pk = pk + 2*(x - y) + 1;
        }
        Write_pixel(x ,y , cor);
    }
}

void Write_pixel(int x, int y, GLfloat *cor){
    GLfloat px, py, px_m, py_m;
    printf("[ %.4f, %.4f ]\n", w_width, w_height);
    px = (float)(((float)x/(float)w_width));
    py = (float)(((float)y/(float)w_height));
    px_m = ponto1X != 0 ? (float)(((float)ponto1X/(float)w_width)*2.0 -1.0)  : 0;
    py_m = ponto1Y != 0 ? (float)(((float)ponto1Y/(float)w_height)*2.0 - 1.0): 0;
    glColor3fv(cor);
    glBegin(GL_POINTS);
        glVertex2f( px + px_m, py + py_m );
        glVertex2f( px + px_m,-py + py_m );
        glVertex2f(-px + px_m, py + py_m );
        glVertex2f(-px + px_m,-py + py_m );
        glVertex2f( py + px_m, px + py_m );
        glVertex2f( py + px_m,-px + py_m );
        glVertex2f(-py + px_m, px + py_m );
        glVertex2f(-py + px_m,-px + py_m );
    glEnd();
}
