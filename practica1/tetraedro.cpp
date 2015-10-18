#include "tetraedro.h"

Tetraedro::Tetraedro() {
	
}

Tetraedro::Tetraedro(float tam, float al){
	// Vertices
	vertices.push_back(_vertex3f(-tam, 0, tam));	
	vertices.push_back(_vertex3f(tam, 0, tam));		
	vertices.push_back(_vertex3f(tam, 0, -tam));	
	vertices.push_back(_vertex3f(-tam, 0, -tam));	
	vertices.push_back(_vertex3f( 0, al, 0));	    
	// Caras
	caras.push_back(_vertex3i(0, 1, 4));		
	caras.push_back(_vertex3i(1, 2, 4));
	caras.push_back(_vertex3i(2, 3, 4));
	caras.push_back(_vertex3i(3, 0, 4));
	caras.push_back(_vertex3i(3, 1, 0));
	caras.push_back(_vertex3i(3, 2, 1));
}





