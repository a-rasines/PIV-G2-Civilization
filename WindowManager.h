/*
 * WindowManager.h
 * Esta clase simplifica las interacciones con SFML
 *  Created on: 3 may 2022
 */

#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <list>
#include "window.h"
class WindowManager {
	public:
		WindowManager(){
			instance = '\0';
			window = '\0';
		}
		/** Genera una ventana de SFML con el título definido
		 * 	title -> Titulo de la ventana
		 */
		WindowManager(const char* title, int posX, int posY, int width, int height, Window *window);
		~WindowManager(){

		}
		/**
		 * Esta clase contiene los generadores de los elementos de SFML
		 */
		void runButton(HWND button);
		void setWindow(Window *w);
		void repaint();
	private:
		HWND window;
		HINSTANCE instance;

};
#endif /* WINDOWMANAGER_H_ */
