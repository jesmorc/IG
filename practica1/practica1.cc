//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <vector>
#include <vertex.h>
#include "tetraedro.h"
#include "cubo.h"

//modo
int modo=2;

float tam=3;
float al=5;
Cubo c(tam);
Tetraedro t(tam,al);
Figura3D figura;


// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}

//Funcion circulo
void Circle (GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo){
int i;
if (modo==GL_LINE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
else if (modo==GL_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
else glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
glBegin( GL_POLYGON );
for (i=0;i<n;i++)
glVertex2f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n));
glEnd();
}

void munieco(){

	//BORDE CARA
	glColor3f(0.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1);
	glBegin (GL_POLYGON);
	glVertex3f (-2.0,4.0,-0.1);
	glVertex3f (-2.0,0.0,-0.1);
	glVertex3f (2.0,0.0,-0.1);
	glVertex3f (2.0,4.0,-0.1);
	glEnd ( );

	//BORDE OREJA 1
	glColor3f(0.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1);
	glBegin (GL_POLYGON);
	glVertex3f (-3.0,3.0,0.0);
	glVertex3f (-3.0,1.0,0.0);
	glVertex3f (-2.0,1.0,0.0);
	glVertex3f (-2.0,3.0,0.0);
	glEnd ( );

	//BORDE OREJA 2
	glColor3f(0.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1);
	glBegin (GL_POLYGON);
	glVertex3f (3.0,3.0,0.0);
	glVertex3f (3.0,1.0,0.0);
	glVertex3f (2.0,1.0,0.0);
	glVertex3f (2.0,3.0,0.0);
	glEnd ( );


	//COPA
	glColor3f(0.0,0.0,0.0); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin (GL_POLYGON);
	glVertex3f (-2.0,8.0,0.0);
	glVertex3f (-2.0,5.0,0.0);
	glVertex3f (2.0,5.0,0.0);
	glVertex3f (2.0,8.0,0.0);
	glEnd ( );

	//ALA
	glBegin (GL_POLYGON);
	glVertex3f (-3.0,5.0,0.0);
	glVertex3f (-3.0,4.0,0.0);
	glVertex3f (3.0,4.0,0.0);
	glVertex3f (3.0,5.0,0.0);
	glEnd ( );



	//CARA
	glColor3f(0.6,0.4,0.0);

	glBegin (GL_POLYGON);
	glVertex3f (-2.0,4.0,-0.1);
	glVertex3f (-2.0,0.0,-0.1);
	glVertex3f (2.0,0.0,-0.1);
	glVertex3f (2.0,4.0,-0.1);
	glEnd ( );



	//OREJA 1

	glBegin (GL_POLYGON);
	glVertex3f (-3.0,3.0,0.0);
	glVertex3f (-3.0,1.0,0.0);
	glVertex3f (-2.0,1.0,0.0);
	glVertex3f (-2.0,3.0,0.0);
	glEnd ( );

	//OREJA 2
	glBegin (GL_POLYGON);
	glVertex3f (3.0,3.0,0.0);
	glVertex3f (3.0,1.0,0.0);
	glVertex3f (2.0,1.0,0.0);
	glVertex3f (2.0,3.0,0.0);
	glEnd ( );

	//OJOS
	glColor3f(0.0,0.0,1.0);
	Circle(0.5,-1.0,3.0,20,GL_FILL);
	Circle(0.5,1.0,3.0,20,GL_FILL);


	//BOCA
	glColor3f(0.2,0.2,0.1);
	Circle(0.2,-1.0,1.0,20,GL_FILL);
	Circle(0.2,1.0,1.0,20,GL_FILL);

	glBegin (GL_POLYGON);
	glVertex3f (-0.9,1.2,0.0);
	glVertex3f (-0.9,0.8,0.0);
	glVertex3f (1.0,0.8,0.0);
	glVertex3f (1.0,1.2,0.0);
	glEnd ( );


	//NARIZ
	glColor3f(0.3,0.2,0.1);
	glBegin (GL_TRIANGLES);
	glVertex3f (0.9,1.7,0.0);
	glVertex3f (0.0,3.0,0.0);
	glVertex3f (-0.9,1.7,0.0);
	glEnd ( );

}

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
	switch (modo)
	{
		case 1: //Puntos
			figura.draw(Figura3D::POINTS);
		break;
		case 2: //Aristas
			figura.draw(Figura3D::LINES);
		break;
		case 3: //Solido
			figura.draw(Figura3D::SOLID);
		break;
		case 4: //Ajedrez
			figura.draw(Figura3D::CHESS);
		break;
		case 7: //5 objetos
			figura.draw(Figura3D::LINES);
		break;
	}

	//PINTO EL OBJETO EXTRA


	glTranslatef(-tam,0.0,0.0);
	glRotatef(90,0,0,1);
	glScalef(0.5,0.5,0.5);

	munieco();

	glTranslatef(0.0,-tam*4,0.0);
	glRotatef(-180,0,0,1);

	munieco();



	
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

if (toupper(Tecla1)=='Q') exit(0);
else if (Tecla1 == '1'){
		modo = 1;
	}
	else if (Tecla1 == '2'){
		modo = 2;
	}
	else if (Tecla1 == '3'){
		modo = 3;
	}
	else if (Tecla1 == '4'){
		modo = 4;
	}
	else if (Tecla1 == '5'){
		figura = c;
	}
	else if (Tecla1 == '6'){
		figura = t;
	}
	glutPostRedisplay(); 
}
//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
	figura = c;
	
// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Practica 1");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
