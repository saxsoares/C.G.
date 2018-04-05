#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED
#include <GL/glut.h>

//={[0-9]+\.?[0-9]*\,[0-9]+\.?[0-9]*\,[0-9]+\.?[0-9]*}
extern GLfloat  preto[], branco[], verde[], vermelho[], azul[], amarelo[], furchsia[],
        rosa[], rosaBri[], abobora[], ciano[], verdeEsc[], azulEsc[], marinho[], fuligem[],
        roxo[],azulCeu[],verdeGrama[],cinzaFosco[], jambo[],laranja[],marrom[],cinza[], cinzaEsc[];

GLint sw, sh, winPosX, winPosY;  // sw-> screen_width, sh->screen_height
GLfloat w_width, w_height;
GLfloat mouseX, mouseY;
#endif // DISPLAY_H_INCLUDED

