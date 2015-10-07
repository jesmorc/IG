#ifndef _OBJETO_PLY
#define _OBJETO_PLY

#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <GL/gl.h>
#include <math.h>
using namespace std;
const double PI = 3.14159265359;

class Objeto{
private:
    vector<float> verts;
    vector<int> caras;
    int vertices_perfil;
    vector<float> vnormales_caras;
    vector<float> vnormales_vertices;
public:
    Objeto();
    Objeto(vector<float> Vertices, vector<int> Faces){
        verts = Vertices;
        caras = Faces;
        vertices_perfil = 0;
    };

    void revolucionar_punto_eje_y(float x, float y, float z, GLfloat punto_revolucionado[3], double angulo){
        //multiplicar matriz
        punto_revolucionado[0] = cos(angulo)*x + 0*y + (sin(angulo)*z);
        punto_revolucionado[1] = 0*x + 1*y + 0*z;
        punto_revolucionado[2] = -sin(angulo)*x  + 0*y + cos(angulo)*z;
    }



    /* ---------------------------------**********************-------------------------------------------- */


    void crear_puntos_revolucion(double angulo){

        vertices_perfil = verts.size()/3;
        GLfloat  punto_revolucionado[3];
        double veces_revolucion = 360/angulo-1; //-1 Para no repetir Q1 con Qn
        double radianes;
        double angulo_original = angulo;

        for (double j = 0; j < veces_revolucion; j++){
            radianes=(angulo*PI)/180;
            for (int i = 0; i < vertices_perfil; i++){
                revolucionar_punto_eje_y(verts[i*3], verts[i*3+1],verts[i*3+2], punto_revolucionado, radianes );
                verts.push_back( punto_revolucionado[0]);
                verts.push_back( punto_revolucionado[1]);
                verts.push_back( punto_revolucionado[2]);
            }
            angulo+=angulo_original;
        }
        /*
          Creo las caras primero por revolución y luego añado las puntas de arriba y abajo
          y en ésta última creo las caras de las tapas
        */
        crear_caras_revolucion();
        add_puntas_alta_baja();
        calcular_vectores_normales_caras();
        calcular_vectores_normales_vertices();

    }


    /* ---------------------------------**********************-------------------------------------------- */



    void add_puntas_alta_baja(){
        GLfloat punto[3];

        int punto_mas_alto = 0;
        for (int i = 0; i<vertices_perfil ; i++){
            if (verts[i*3+1] > verts[punto_mas_alto*3+1])
                punto_mas_alto = i;
        }
        punto[0]=0;
        punto[1]=verts[punto_mas_alto*3+1];
        punto[2]=0;
        // Creación de punto mas alto
        verts.push_back( punto[0]);
        verts.push_back( punto[1]);
        verts.push_back( punto[2]);

        int punto_mas_bajo = 0;
        for (int i = 0; i<vertices_perfil ; i++){
            if (verts[i*3+1] < verts[punto_mas_bajo*3+1])
                punto_mas_bajo = i;
        }

        punto[1]=verts[punto_mas_bajo*3+1];
        // Creación de punto mas bajo
        verts.push_back( punto[0]);
        verts.push_back( punto[1]);
        verts.push_back( punto[2]);

        // Creación de tapa superior
        for (int i = punto_mas_alto; i < verts.size()/3-3-vertices_perfil; i+=vertices_perfil){
            caras.push_back(i);
            caras.push_back(i+vertices_perfil);
            caras.push_back(verts.size()/3 -2);
        }
        {        // Unión en la tapa inferior de Qn con Q1->
            caras.push_back(punto_mas_alto);
            caras.push_back(verts.size()/3-2);
            caras.push_back(verts.size()/3 -1);
        }

        // Creación de tapa inferior
        // Nº De vertices -11 vertices perfil - 2 vertices punta
        for (int i = punto_mas_bajo; i < verts.size()/3 -vertices_perfil-2; i+=vertices_perfil){
            caras.push_back(i);
            caras.push_back(i+vertices_perfil);
            caras.push_back(verts.size()/3 -1);
        }

        {        // Unión en la tapa inferior de Qn con Q1->
            caras.push_back(punto_mas_bajo);
            caras.push_back(verts.size()/3-2-vertices_perfil);
            caras.push_back(verts.size()/3 -1);
        }

    }


    /* ---------------------------------**********************-------------------------------------------- */



    void crear_caras_revolucion(){
        for (int i = 0; i < ((verts.size()/3)); i++){
            if (i+vertices_perfil <= verts.size()/3 -2){ //
                caras.push_back(i);
                caras.push_back(i+1);
                caras.push_back(i+vertices_perfil);     //
                if ((i+2)%vertices_perfil == 0){
                    i++;
                }
            }
        }

        for (int i = vertices_perfil; i < ((verts.size()/3)); i++){ // // //
            if (i-vertices_perfil+1 >= 0){ //
                caras.push_back(i);                                        // // //
                caras.push_back(i+1);                                      // // //
                caras.push_back(i-vertices_perfil+1);                      // // //
                if((i+2 ) % vertices_perfil == 0)                          // // //
                    i++;                                                   // // //
            }
        }                                                              // // //

        //Ultimas caras - unión Qn con Q1 (Sin añadir la punta de arriba o abajo)
        int m = 0;
        for (int j = verts.size()/3-vertices_perfil; j< verts.size()/3; j++){
            caras.push_back(j);
            caras.push_back(j+1);
            caras.push_back(m);
            m++;
        }
        int j = verts.size()/3-vertices_perfil+1;
        for (int m=0; m < vertices_perfil-1; m++){
            caras.push_back(m);
            caras.push_back(m+1);
            caras.push_back(j);
            j++;
        }
    }

    /* ---------------------------------**********************-------------------------------------------- */

    void calcular_vectores_normales_caras(){
        vector<float> vectorab;
        vector<float> vectorbc;

        int v1,v2,v3;

        for (int i = 0; i < caras.size()/3-1; i+=3){
            /*
              Primero saco los vertices de la cara i por en orden del reloj analógico
            */
            v1=caras[i];
            v2=caras[i+1];
            v3=caras[i+2];

            /*
              Calculo los vectores AB y BC de los 3 vertices dados
            */
            vectorab.push_back( verts[v2*3] - verts[v1*3] );
            vectorab.push_back( verts[v2*3+1] - verts[v1*3+1] );
            vectorab.push_back(verts[v2*3+2] - verts[v1*3+2] );

            vectorbc.push_back( verts[v3*3] - verts[v2*3] );
            vectorbc.push_back( verts[v3*3+1] - verts[v2*3+1] );
            vectorbc.push_back( verts[v3*3+2] - verts[v2*3+2] );

            /*
              Calculo los vectores  normales a partir del producto vectorial de vAB y vBC
            */
            vnormales_caras.push_back(vectorab[1]*vectorbc[2] - vectorab[2]*vectorbc[1]);
            vnormales_caras.push_back(-1*(vectorab[0]*vectorbc[2] - vectorab[2]*vectorbc[0]));
            vnormales_caras.push_back(vectorab[0]*vectorbc[1] - vectorab[1]*vectorbc[0]);

            vectorab.clear();
            vectorbc.clear();
        }
    }


    /* ---------------------------------**********************-------------------------------------------- */


    void calcular_vectores_normales_vertices(){
        int n = 0; // Numero de caras que se reúnen en el vertice
        vector<int> caras_reunidas_en_j;
        float sumax = 0;
        float sumay = 0;
        float sumaz = 0;

        for (int j = 0; j< verts.size()/3; j++){
            n=0;
            caras_reunidas_en_j.clear();
            sumax=0;
            sumay=0;
            sumaz=0;


            //              Busco ahora las caras que se reunen en el vertice j

            for (int i = 0; i < caras.size()/3; i+=3){ //Para encontrar el numero de caras que ser reunen en el vértice j
                if ((caras[i] == j) || (caras[i+1] == j) || (caras[i+2] == j)){
                    n++;
                    caras_reunidas_en_j.push_back(i);
                }
            }

            for (int i = 0; i < caras_reunidas_en_j.size(); ++i){
                sumax+=vnormales_caras[i];
                sumay+=vnormales_caras[i+1];
                sumaz+=vnormales_caras[i+2];
            }

            sumax = sumax/n;
            sumay = sumay/n;
            sumaz = sumaz/n;

            vnormales_vertices.push_back(sumax);
            vnormales_vertices.push_back(sumay);
            vnormales_vertices.push_back(sumaz);

        }

        cout << vnormales_vertices[3*11] << " , " << vnormales_vertices[3*11+1] << " , " << vnormales_vertices[3*11+2] << endl;
    }


    void pintar(){
        glColor3f(0,1,0);
        GLfloat punto1[3];
        GLfloat punto2[3];
        GLfloat punto3[3];
        glBegin(GL_TRIANGLES);
        for (unsigned i=0;i<caras.size() ;i+=3){
            int coor_x_1 = caras[i]*3;
            int coor_x_2 = caras[i+1]*3;
            int coor_x_3 = caras[i+2]*3;

            for (int k = 0; k < 3; k++){
                punto1[k] = verts[coor_x_1+k];
                punto2[k] = verts[coor_x_2+k];
                punto3[k] = verts[coor_x_3+k];
            }

            glVertex3fv((GLfloat *) &punto1);
            glVertex3fv((GLfloat *) &punto2);
            glVertex3fv((GLfloat *) &punto3);
        }
        glEnd();
    }


    void pintar_ajedrez(){

        glColor3f(0,1,0);
        srand (time(NULL));

        GLfloat punto1[3];
        GLfloat punto2[3];
        GLfloat punto3[3];
        glBegin(GL_TRIANGLES);
        for (unsigned i=0;i<caras.size() ;i+=3){
            int coor_x_1 = caras[i]*3;
            int coor_x_2 = caras[i+1]*3;
            int coor_x_3 = caras[i+2]*3;

            for (int k = 0; k < 3; k++){
                punto1[k] = verts[coor_x_1+k];
                punto2[k] = verts[coor_x_2+k];
                punto3[k] = verts[coor_x_3+k];
            }
            glColor3f((rand()%11)*0.1, (rand()%11)*0.1,(rand()%11)*0.1);
            glVertex3fv((GLfloat *) &punto1);
            glVertex3fv((GLfloat *) &punto2);
            glVertex3fv((GLfloat *) &punto3);
        }
        glEnd();

    }

    void pintar_puntos(){

        glColor3f(1,0,0);
        glPointSize(4);

        GLfloat punto1[3];

        glBegin(GL_POINTS);
        for (unsigned i=0;i<verts.size() ;i+=3){

            for (int k = 0; k < 3; k++){
                punto1[k] = verts[i+k];
            }

            glVertex3fv((GLfloat *) &punto1);
        }
        glEnd();
    }


    ~Objeto();
};


#endif
