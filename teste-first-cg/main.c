#include <GL/glut.h>
#include <math.h>
# define PI 3.141592654

void desenha(){
    int i; float angulo;

    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glPolygonMode ( GL_FRONT , GL_FILL );
    glBegin(GL_POLYGON);
//        glVertex2f(-0.5, 0.5);
//        glVertex2f(0.5, 0.5);
//        glVertex2f(0.5, -0.5);
//        glVertex2f(-0.5, -0.5);
        for (i =0; i <=50; i ++) {
            angulo = 2 * PI * i / 50.0;
            glVertex2f (0.5* cos( angulo ), 0.5* sin( angulo ));
        }
//        glPolygonMode ( GL_FRONT , GL_LINE );
//        glPolygonMode ( GL_BACK , GL_FILL );
//        glBegin ( GL_TRIANGLE_STRIP );
//        glColor3f (1.0 , 0.0 , 0.0); glVertex3f (0.0 , 0.6 , 0.0);
//        glColor3f (1.0 , 1.0 , 0.0); glVertex3f (0.0 , 0.0 , 0.0);
//        glColor3f (0.0 , 1.0 , 0.0); glVertex3f (0.3 , 0.6 , 0.0);
//        glColor3f (1.0 , 0.0 , 1.0); glVertex3f (0.6 , 0.0 , 0.0);
//        glColor3f (0.0 , 0.0 , 1.0); glVertex3f (0.3 , 0.3 , 0.6);
    glEnd();
    glFlush();
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (400 ,300);
    glutCreateWindow ("Fernando - CG - Circulo");
    glutDisplayFunc (desenha);
    glutMainLoop ();
    return 0;
}
