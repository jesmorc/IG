#include "figura3D.h"
Figura3D::Figura3D()
{
}
void Figura3D::draw(Figura3D::DrawMode mode) const
{
	GLenum draw_mode;
	switch (mode)
	{
		case Figura3D::POINTS:
			draw_mode = GL_POINT;
		break;
		case Figura3D::LINES:
			draw_mode = GL_LINE;
		break;
		default: 
			draw_mode = GL_FILL;
		break;
	}
	int Vertex_1,Vertex_2,Vertex_3;
	glPointSize(2);
	glPolygonMode(GL_FRONT_AND_BACK, draw_mode);
	glBegin(GL_TRIANGLES);
	for (int i= 0; i < caras.size(); i++)
	{
		// color para el ajedrez
		if (mode == CHESS && i %2 == 0)
			glColor3f(1, 0, 0);
		else
			glColor3f(0, 0, 1);

		Vertex_1 = caras[i]._0;
		Vertex_2 = caras[i]._1;
		Vertex_3 = caras[i]._2;
		glVertex3f(vertices[Vertex_1].x, vertices[Vertex_1].y, vertices[Vertex_1].z);
		glVertex3f(vertices[Vertex_2].x, vertices[Vertex_2].y, vertices[Vertex_2].z);
		glVertex3f(vertices[Vertex_3].x, vertices[Vertex_3].y, vertices[Vertex_3].z);
	}
	glEnd();
}
