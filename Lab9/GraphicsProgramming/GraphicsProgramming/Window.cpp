#include "Window.h"

Window::Window() {
	window_width = 800;
	window_height = 600;
	half_window_width = (window_width / 2);
	half_window_height = (window_height / 2);
}

Window::~Window() {}


int& Window::getWindowWidth() {
	return window_width;
}
int& Window::getWindowHeight() {
	return window_height;
}

int& Window::getHalfWindowWidth() {
	return half_window_width;
}
int& Window::getHalfWindowHeight() {
	return half_window_height;
}
