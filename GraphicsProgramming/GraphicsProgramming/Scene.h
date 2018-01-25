#ifndef _SCENE_H
#define _SCENE_H

#include <iostream>

class Scene
{
public:
	Scene();
	virtual ~Scene();

	// Main render function
	virtual void render() = 0;
	// Update function receives delta time from parent (used for frame independent updating).
	virtual void update(float dt) = 0;
	// Resizes the OpenGL output based on new window size.
	virtual void resize(int w, int h) = 0;

protected:
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	virtual void displayText(float x, float y, float r, float g, float b, const char* string) = 0;
	// A function to collate all text output in a single location
	virtual void renderTextOutput() = 0;
};

#endif

