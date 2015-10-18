#ifndef _FIGURA3D
#define	_FIGURA3D

#include <GL/gl.h>
#include <stdlib.h> 
#include <vector>
#include <vertex.h>

using namespace std;

class Figura3D {
	protected:
		vector<_vertex3f> vertices;
		vector<_vertex3i> caras;
	public:
		Figura3D();
		enum DrawMode {
			POINTS, LINES, SOLID, CHESS
		};
		void draw(DrawMode mode) const;
		
};

#endif



