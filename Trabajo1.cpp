#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#define pi 3.14159265358979323846
using namespace std;

GLfloat xi = 0.0;
GLfloat yi = 0.0;
//Valor inicial de lados de un poligono
GLint numLados=1;
//Valor inicial de escalamiento
GLint escala = 1;
//Vectores de almacen de los poligonos (12 lados maximos)
GLdouble puntosx[13];
GLdouble puntosy[13];
//Angulo inicial para la rotacion
GLdouble angulo = 0;

//Valores para el circulo y linea en caso de elegir la opcion
GLint radio = 3;
float x0 = 0.0;
float yy = 0.0;
float x1 = 5.0;
float yy2 = 3.0;



void init(void) 
{ 
	glClearColor(0.0,0.0,0.0,0.0);  //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha 
	glShadeModel(GL_FLAT); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(-10.0,20.0,-10.0,20); 

}

void tecla(int tecla, int x, int y){
	switch (tecla)
	{
	case GLUT_KEY_RIGHT:
		if (xi < 10)
			xi += 0.5;
		break;

	case GLUT_KEY_LEFT:
		if (xi > -10)
			xi -= 0.5;
		break;

	case GLUT_KEY_UP:
		if (yi < 10)
			yi += 0.5;
		break;

	case GLUT_KEY_DOWN:
		if (yi > -10)
			yi -= 0.5;
		break;

	case GLUT_KEY_F1:
		numLados = 1;
		//recta
		break;
	case GLUT_KEY_F2:
		numLados = 2;
		//circulo
		break;
	case GLUT_KEY_F3:
		numLados = 3;
		//triangulo
		break;

	case GLUT_KEY_F4:
		numLados = 4;
		//cuadrado
		break;
	case GLUT_KEY_F5:
		numLados = 5;
		//pentagono
		break;
	case GLUT_KEY_F6:
		numLados = 6;
		//hexagono
		break;

	case GLUT_KEY_F7:
		numLados = 7;
		//heptagono
		break;
	case GLUT_KEY_F8:
		numLados = 8;
		//octagono
		break;

	case GLUT_KEY_F9:
		numLados = 9;
		//
		break;

	case GLUT_KEY_F10:
		numLados = 10;
		//
		break;
	case GLUT_KEY_F11:
		numLados = 11;
		//
		break;
	case GLUT_KEY_F12:
		numLados = 12;
		//
		break;
	//Escalamiento
	case GLUT_KEY_HOME:
		escala = escala + 1;
		break;
	case GLUT_KEY_PAGE_UP:
		if (escala <=1)
			escala = 1;
		else
			escala = escala - 1;
		break;

	case GLUT_KEY_PAGE_DOWN:
		angulo +=5;
		break;

	case GLUT_KEY_END:
		angulo -=5;
		break;

	default:
		break;
	}


}


void CirclePoints(float x,float y)
{
    glVertex3f(x,y,-1.0f);
    glVertex3f(x,-y,-1.0f);
    glVertex3f(-x,y,-1.0f);
    glVertex3f(-x,-y,-1.0f);
    glVertex3f(y,x,-1.0f);
    glVertex3f(y,-x,-1.0f);
    glVertex3f(-y,x,-1.0f);
    glVertex3f(-y,-x,-1.0f);

}

void circMidPoint(float r)
{

    GLfloat x,y,d, x_inc,y_inc; 
    /* Valores iniciais */
    x = 0.0f;
    y = r;
    d = 1 - r;

    int deltaE = 3;
    int deltaSE = -2*r+5;

    x_inc = 1.0f;
    y_inc = 1.0f;

    glColor3f( 1.0,0.5,0.0);
    glBegin(GL_POINTS);
    
    CirclePoints(x,y);
    while (y > x)
    {
        if (d < 0)
        {
            /* Selecione E */
            d += deltaE;
            deltaE +=x_inc*2;
            deltaSE +=x_inc*2;
            //x+=x_inc;
            }
            else
            {
            /* Selecione SE */
            d += deltaSE;
            deltaE +=x_inc*2;
            deltaSE +=x_inc*4;
            y -= y_inc;
            }/*end if*/
            x += x_inc;
            CirclePoints(x,y);
            //glVertex2f(x,y);
    }
    glEnd();
}

void incremental_basico( int x_0, int y_0, int x_f, int y_f)
{
	float x, y;
	float a;
	int valor;

	a= ( y_f - y_0 ) / ( x_f - x_0 );

	glColor3f( 1.0,0.5,0.0);
	glBegin(GL_POINTS);
	for ( x = x_0; x <= x_f ;)
	{	
		y = ( y_0 + a * ( x- x_0));
		glVertex2f(x, y);
		x  = x + 0.01;
		cout << "x: "<< x <<" , y: " << y << endl;
	}
	glEnd();

}

void draw_recta_punto_medio(float x_0, float y_0, float x_f, float y_f)
{
	GLfloat x,y,dx,dy,incrementoE,incrementoNE,d,inc_x,inc_y; 
	x = x_0;
	y = y_0;

	dx = x_f - x_0;
	dy = y_f - y_0;

	incrementoE = 2 * dy;
	incrementoNE = 2 * ( dy - dx);
	
	d = 2 * dy - dx;

	inc_x = 0.0001;
	inc_y = dy * inc_x / dx ;
	//Color del pixel
	glColor3f( 1.0,0.5,0.0);
	glVertex2f(x, y); //dibujado del pixel
	glBegin(GL_POINTS);
	glVertex2f(x, y);

		while( x < x_f)
		{
			if ( d <= 0 )
			{
				d = d + incrementoE;
				x = x + inc_x;
				y = y + inc_y;

			}
			else
			{	
				d = d + incrementoNE;
				x = x + inc_x;
				y = y + inc_y;

			}
			glVertex2f(x, y);
		}
	glEnd();

}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(xi, yi, 0);
	glScaled(escala, escala, 1.0);
	glRotated(angulo, 0.0, 0.0, 1.0);



	double grados = (360 / numLados);
	double aux = grados;

	if(numLados==1){
		draw_recta_punto_medio(x0,yy,x1,yy2);
	}else if(numLados==2){
		circMidPoint(radio);
	}

	for (int i = 0; i<numLados; i++)
	{

		GLdouble px = ((2 * (cos((pi*grados) / 180))) + xi);
		GLdouble py = ((2 * (sin((pi*grados) / 180))) + yi);

		puntosx[i] = px;
		puntosy[i] = py;
		grados = grados + aux;

	}
	
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.5,0.0);
	for (int i = 0; i<numLados; i++)
	{
		glVertex2d(puntosx[i], puntosy[i]);
   }

	glEnd();
	glPopMatrix(); // Cierra la matriz
	glFlush();
	glutSwapBuffers();
}



void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//Inicializa la matriz de proyeccion
	glOrtho(-10.0, 10.0, -10.00, 10.0, 0.1, 20.0); // WorkSpace
	glMatrixMode(GL_MODELVIEW); // cambiamos la matrix :D

}
void keyboard(unsigned char tecla, int x, int y){
	if(tecla==27)
		cout<<"HOLI"<<endl;
}


int main(int argc, char** argv)
{
	cout<<"*******************************************************************"<<endl;
	cout<<"Menu de uso:"<<endl;
	cout<<"*******************************************************************"<<endl;
	cout<<"Teclas de direccion para translacion || Home-Aumentar escalado || Page_UP-Disminuir escalado"<<endl;
	cout<<"Page_Down-Rotacion positiva || End-Rotacion negativa"<<endl;
	cout<<"F1-Recta(predefinida al inicio del codigo)-F2-circulo"<<endl;
	cout<<"F3-triangulo,F4-rectangulo, ... -F12 para el numero de lados de los poligonos"<<endl;
	cout<<"*******************************************************************"<<endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500); 
	glutInitWindowPosition(100,100); 
	glutCreateWindow("Poligonos");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(tecla);
	glutMainLoop();



	return 0;
}
