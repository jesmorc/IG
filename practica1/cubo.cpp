#include "cubo.h"


Cubo::Cubo()
{
}

Cubo::Cubo(float tam)
{
// Vertices
	vertices.push_back(_vertex3f(-tam, -tam, tam));
	vertices.push_back(_vertex3f(tam, -tam, tam));
	vertices.push_back(_vertex3f(tam, tam, tam));
	vertices.push_back(_vertex3f(-tam, tam, tam));
	vertices.push_back(_vertex3f(-tam, -tam, -tam));
	vertices.push_back(_vertex3f(tam, -tam, -tam));
	vertices.push_back(_vertex3f(tam, tam, -tam));
	vertices.push_back(_vertex3f(-tam, tam, -tam));
	// Caras
	caras.push_back(_vertex3i(0, 1, 3));
	caras.push_back(_vertex3i(3, 1, 2));
	caras.push_back(_vertex3i(1, 5, 2));
	caras.push_back(_vertex3i(5, 6, 2));
	caras.push_back(_vertex3i(5, 4, 6));
	caras.push_back(_vertex3i(4, 7, 6));
	caras.push_back(_vertex3i(0, 7, 4));
	caras.push_back(_vertex3i(0, 3, 7));
	caras.push_back(_vertex3i(3, 2, 7));
	caras.push_back(_vertex3i(2, 6, 7));
	caras.push_back(_vertex3i(0, 1, 4));
	caras.push_back(_vertex3i(1, 5, 4));
}





