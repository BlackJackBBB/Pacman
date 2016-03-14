#include <GL\freeglut.h>
#include "System.h"

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	
	System* system = &System::getInstance();

	system->createWindow("Pacman.ini", "PAC-MAN");

	glutReshapeFunc(System::bindHandleReshape);
	glutDisplayFunc(System::bindHandleRender);
	glutTimerFunc(0, System::bindHandleTimer, 0);
	glutSpecialFunc(System::bindHandleSpecialKeyInput);
	
	glutMainLoop();
	
	return 0;
}