/*
 * WindowManager.cpp
 *
 *  Created on: 3 may 2022
 *      Author: algtc
 */

#include "WindowManager.h"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <cmath>
#include <iostream>
#include <SFML/Window.hpp>
#include "Window.h"

WindowManager *windowInstance;
Window *activeWindow;
LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message){
			// Quit when we close the main window
		case WM_CLOSE:{
			PostQuitMessage(0);
			break;
		}case WM_COMMAND:{
			windowInstance->runButton(reinterpret_cast<HWND>(lParam));
			break;
		}case WM_PAINT:{
			windowInstance->repaint();
		}
	}
	return DefWindowProc(handle, message, wParam, lParam);
}
MSG message;
WindowManager::WindowManager(const char* title, int posX, int posY, int width, int height, Window *window) {
	activeWindow = window;
	instance = GetModuleHandle(NULL);
	windowInstance = this;
	// Define a class for our main window
	WNDCLASS windowClass;
	windowClass.style         = 0;
	windowClass.lpfnWndProc   = &onEvent;
	windowClass.cbClsExtra    = 0;
	windowClass.cbWndExtra    = 0;
	windowClass.hInstance     = instance;
	windowClass.hIcon         = NULL;
	windowClass.hCursor       = 0;
	windowClass.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	windowClass.lpszMenuName  = NULL;
	windowClass.lpszClassName = TEXT("SFML App");
	RegisterClass(&windowClass);

	// Let's create the main window
	this->window = CreateWindow(TEXT("SFML App"), TEXT(title), WS_SYSMENU | WS_VISIBLE, posX, posY, width, height, NULL, NULL, instance, NULL);
	//Reloj para calcular el deltatime y tiempo transcurrido
	sf::Clock clock;
	float timeElapsed = clock.getElapsedTime().asMilliseconds();
	message.message = static_cast<UINT>(~WM_QUIT);
	Window::instance = instance;
	Window::window = this->window;
	window->start();
	while (message.message != WM_QUIT){
		//Aqui busca los eventos no recogidos
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&message);
			DispatchMessage(&message);
		} else{
			float time = clock.getElapsedTime().asMilliseconds();
			activeWindow->deltatime = (-timeElapsed) + time;
			timeElapsed = time;
			activeWindow->update();
		}
	}
	DestroyWindow(this->window);
	UnregisterClass(TEXT("SFML App"), instance);
	// Loop until a WM_QUIT message is received
}
void WindowManager::setWindow(Window *w){
	activeWindow->destroyComponents();
	activeWindow = w;
	activeWindow->start();
}
void WindowManager::runButton(HWND button){
	activeWindow->onButtonPress(button);
}

void WindowManager::repaint(){
	PAINTSTRUCT ps;
	BeginPaint( window, &ps);
	EndPaint( window, &ps );
}