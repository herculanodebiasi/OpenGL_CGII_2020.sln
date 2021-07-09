#include <gl/freeglut.h>

float angulo, aspecto;			 //gluPerspective
float zNear = 0.1, zFar = 500;   //gluPerspective
int posX=0, posY = 80, posZ=200; //Par�metros da gluLookAt

void visualizacao() {
	glMatrixMode(GL_PROJECTION);	//Matriz de proje��o
	glLoadIdentity();				//Zera transforma��es
	//Configura perspectiva
	gluPerspective(angulo, aspecto, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);		//Muda p/matriz de visualiza��o
	glLoadIdentity();				//Zera transforma��es
	gluLookAt(posX, posY, posZ,		//Configura c�mera
		0, 0, 0,	//Para onde a c�mera aponta na cena
		0, 1, 0);	//Vetor 'up'
}
void teclado(unsigned char key, int x, int y) {
	switch (key) {
	case 27:	//Tecla ESC
		exit(0);break;
	case 'a':	//Aumenta �ngulo do 'campo de vis�o' vertical
		angulo++;break;
	case 'A':	//Diminui �ngulo do 'campo de vis�o' vertical
		angulo--;break;
	case 's':	//Aumenta 'raz�o de aspecto' (aspect ratio)
		aspecto++;break;
	case 'S':	//Diminui 'raz�o de aspecto' (aspect ratio)
		aspecto--;break;
	case 'x':	//Aumenta posi��o 'x' do observador
		posX++;break;
	case 'X':	//Diminui posi��o 'x' do observador
		posX--; break;
	case 'y':	//Aumenta posi��o 'y' do observador
		posY++; break;
	case 'Y':	//Diminui posi��o 'y' do observador
		posY--; break;
	case 'z':	//Aumenta posi��o 'z' do observador
		posZ++; break;
	case 'Z':	//Diminui posi��o 'z' do observador
		posZ--; break;
	case 'n':	//Aumenta o plano de corte mais pr�ximo ao observador
		zNear++; break;
	case 'N':	//Diminui o plano de corte mais pr�ximo ao observador
		zNear--; break;
	case 'f':	//Aumenta o plano de corte mais longe do observador
		zFar++; break;
	case 'F':	//Diminui o plano de corte mais longe ao observador
		zFar--; break;
	}
	visualizacao();			//M�todo que aplica os novos par�metros
	glutPostRedisplay();	//For�a redesenho
}
//Fun��o chamada quando o tamanho da tela � alterado
void tamanhoJanela(int w, int h) { //w: width (comprimento)|h: height (altura)
	if (h == 0) { h = 1; }	//Evita divis�o por zero
	glViewport(0, 0, w, h);	//Redefine o viewport para o tamanho da janela
	aspecto = (float)w / (float)h;	//Calcula o 'aspect ratio'
	visualizacao();			//Aplica os novos par�metros de visualiza��o
}
//Fun��o callback do mouse (modifica perspectiva para efeito de zoom in/out)
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {	//Bot�o esquerdo do mouse
		if (state == GLUT_DOWN) {		//Bot�o pressionado
			if (angulo >= 10) { angulo -= 5; }
		}
	}
	if (button == GLUT_RIGHT_BUTTON) {	//Bot�o direito do mouse
		if (state == GLUT_DOWN) {		//Bot�o pressionado
			if (angulo <= 130) { angulo += 5; }
		}
	}
	visualizacao();
	glutPostRedisplay();
}
void desenha() {
	glClearColor(0.0f, 0.0f, 0.1f, 0.0);//Define cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);		//Limpa tela
	glutWireTeapot(50.0f);				//Desenha bule (glutSolidTeapot())
	//glutWireTorus(10,50,10,50);
	glutSwapBuffers();					//Renderiza
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);			//Inicializa biblioteca GLUT
	glutInitWindowSize(500, 500);	//Define tamanho da janela
	glutInitWindowPosition(50, 50);	//Define posi��o inicial da janela
	glutCreateWindow("CG - Unoesc");//Cria janela
	angulo = 45;	//Campo de vis�o (eixo y) inicial � de 45 graus
	glutDisplayFunc(desenha);		//Fun��o callback de redesenho
	glutReshapeFunc(tamanhoJanela);	//Callback quando tamanho janela alterado
	glutMouseFunc(mouse);			//Callback para tratamento do mouse
	glutKeyboardFunc(teclado);		//Callback para tratamento de teclado
	glutMainLoop();					//Loop do GLUT
}