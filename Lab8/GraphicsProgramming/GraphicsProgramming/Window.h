#ifndef WINDOW_H
#define WINDOW_H

class Window
{
public:
	Window();
	~Window();
	int& getWindowWidth();
	int& getWindowHeight();
	int& getHalfWindowWidth();
	int& getHalfWindowHeight();

private:
	int window_width;
	int window_height;
	int half_window_width;
	int half_window_height;
};

#endif

