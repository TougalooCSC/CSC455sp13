// SGLDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif

#include "sgl.h"
#include "st.h"

using namespace std;

STImage* buff;

void display( void )
{
	glClear( GL_COLOR_BUFFER_BIT );

	// --- Make drawing calls here ---+
	sglLoadIdentity();
	sglBeginTriangles();
     sglColor(.8f, .1f, 0.f);
     sglVertex(150.f, 150.f);
     sglVertex(320.f, 150.f);
     sglVertex(150.f, 350.f);
     sglVertex(320.f, 350.f);
    sglEnd();


	// --- End of drawing calls ------+

	buff->Draw();
	glutSwapBuffers();
}

void reshape( int w, int h )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  glOrtho( 0., w, 0., h, -1., 1. );
  glViewport( 0, 0, w, h );
  setBufferSize(w, h);

  glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y )
{
	switch(key)
	{
	case 27: // Escape key
		exit(0);
		break;
	case 's': // Save
		buff->Save("output.png");
		break;
	}
}


int _tmain(int argc, char* argv[])
{
	int win_width = 512;
	int win_height = 512;
	buff = new STImage(win_width, win_height, STColor4ub(0, 0, 0, 255));
	setBuffer(buff);

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize( win_width, win_height );

	glutCreateWindow( "Intro Graphics Assignment 2" );

	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );

	glutMainLoop();

	delete buff;
}

