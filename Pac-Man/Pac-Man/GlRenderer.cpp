#include "Renderer.h"
#include "System.h"


GlRenderer::GlRenderer() {}


GlRenderer::~GlRenderer() {}


GlRenderer& GlRenderer::renderObject(const Model& model, Coordinate<int> pivotPoint, MovableObject::Direction rotation) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, model.getTexture().getId());
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor4f(0.0, 0.0, 0.0, 1.0);

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(pivotPoint.getX() * System::getInstance().getScaleFactor(), pivotPoint.getY() * System::getInstance().getScaleFactor(), 0);
	switch (rotation) {
		case MovableObject::Direction::RIGHT:
			glRotatef(0.0, 0.0, 0.0, 1.0);
			break;
		case MovableObject::Direction::UP:
			glRotatef(90.0, 0.0, 0.0, 1.0);
			break;
		case MovableObject::Direction::LEFT:
			glRotatef(180.0, 0.0, 0.0, 1.0);
			break;
		case MovableObject::Direction::DOWN:
			glRotatef(270.0, 0.0, 0.0, 1.0);
		default:
			break;
	}

	glScalef(System::getInstance().getScaleFactor(), System::getInstance().getScaleFactor(), 1);
	for (const auto polygon : model.getPolygons()) {
		glBegin(GL_POLYGON);
		for (unsigned i = 0; i < 4; i++) {
			glTexCoord2f(model.getTextureCoordinate(polygon.at(i)).getX(), model.getTextureCoordinate(polygon.at(i)).getY());
			glVertex2i(model.getVertexCoordinate(polygon.at(i)).getX(), model.getVertexCoordinate(polygon.at(i)).getY());
		}
		glEnd();
	}

	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, NULL);

	return *this;
}


GlRenderer& GlRenderer::renderText(const std::string text, Coordinate<int> position, float red, float green, float blue, float alpha) {
	glColor4f(red, green, blue, alpha);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRasterPos2i(position.getX(), position.getY());
	glutBitmapString(GLUT_BITMAP_9_BY_15, reinterpret_cast<const unsigned char*>(text.c_str()));
	glPopMatrix();

	return *this;
}


GlRenderer& GlRenderer::swapBuffers() {
	glutSwapBuffers();
	return *this;
}


GlRenderer& GlRenderer::clearColorBuffer() {
	glClear(GL_COLOR_BUFFER_BIT);
	return *this;
}