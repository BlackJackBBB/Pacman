#pragma once
#include "Coordinate.h"
#include "MovableObject.h"
#include "Model.h"

class Renderer {
	friend class GlRenderer;

public:

	Renderer();

	virtual ~Renderer();

	// Render objects by passing object's active model, pivot point and moving direction.
	// If no direction is set default one is choosen.
	// Default direction is neather.
	// If direction is set to other than neather object will be rotated accordingly.
	virtual Renderer& renderObject(const Model& model, Coordinate<int> pivotPoint, MovableObject::Direction rotation = MovableObject::Direction::NEITHER) = 0;

	virtual Renderer& swapBuffers() = 0;

	virtual Renderer& clearColorBuffer() = 0;

	// Render text with parameters text, position, channels red, green, blue, alpha.
	// Default values: red = 1, green = 1, blue = 1, alpha = 1.
	virtual Renderer& renderText(const std::string text, Coordinate<int> position, float red = 1.0, float green = 1.0, float blue = 1.0, float alpha = 1.0) = 0;

};


class GlRenderer : public Renderer {
public:

	GlRenderer();

	virtual ~GlRenderer();

	// Render objects by passing object's active model, pivot point and moving direction.
	// If no direction is set default one is choosen.
	// Default direction is neather.
	// If direction is set to other than neather object will be rotated accordingly.
	virtual GlRenderer& renderObject(const Model& model, Coordinate<int> pivotPoint, MovableObject::Direction rotation = MovableObject::Direction::NEITHER);

	virtual GlRenderer& swapBuffers();

	virtual GlRenderer& clearColorBuffer();

	// Render text with parameters text, position, channels red, green, blue, alpha.
	// Default values: red = 1, green = 1, blue = 1, alpha = 1.
	virtual GlRenderer& renderText(const std::string text, Coordinate<int> position, float red = 1.0, float green = 1.0, float blue = 1.0, float alpha = 1.0);

};