/*
 * example.cpp
 *
 *  Created on: 5 may 2022
 *      Author: algtc
 */
#include "Example.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "WindowObjects/WindowManager.h"
#include "Ejemplo2.h"
#include "menuEjemplo.h"
#include <string.h>
void Example::start(){
	//Se crea una ventana de render (un container dentro de la ventana donde se pueden meter sprites)
	view = generateView(0, 100, 1000, 900);
	SFMLView1.create(view);
	//Se muetra
	SFMLView1.display();
	//Se define la cantidad de vertices
	shape.setPointCount(128);
	//El color a rellenar el circulo
	shape.setFillColor(sf::Color::Green);
	blue = generateButton("Azul", 0, 0, 200, 100);
	red = generateButton("Rojo", 200, 0, 200, 100);
	green = generateButton("Verde", 400, 0, 200, 100);
	next = generateButton("Sprites", 600, 0, 200, 100);
	textField = generateTextField(800, 0, 200, 100);
	textButton = generateButton("", 1000, 0, 200, 100);
	comboBox = generateComboBox(1000, 100, 200, 100, {"A", "B","C"});

}
void Example::update(){
	if(GetActiveWindow() == textField){ //Si el textField esta siendo usado no queremos que se mueva nada
		return;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && x != -1)
		x = 1;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x != 1)
		x = -1;
	else
		x = 0;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y != -1)
		y = 1;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y != 1)
		y = -1;
	else
		y = 0;
	shape.setOrigin(sf::Vector2<float>(shape.getOrigin().x + x*v*deltatime, shape.getOrigin().y + y*v*deltatime));
	SFMLView1.clear();
	SFMLView1.draw(shape);
	SFMLView1.display();
}
void Example::onButtonPress(HWND button){
	if(button == red)shape.setFillColor(sf::Color::Red);
	else if(button == blue)	shape.setFillColor(sf::Color::Blue);
	else if(button == green) shape.setFillColor(sf::Color::Green);
	else if(button == next) Window::manager->setWindow(new Ejemplo2());
	else if(button == textButton){
		removeComponent(textButton); //No se si hay alguna forma de cambiar texto, pero esta funciona
		textButton = generateButton(getComponentText(comboBox), 1000, 0, 200, 100);
	}
}
int main(){
	Window::manager = new WindowManager("Ejemplo", 0, 0, 1200, 1000, new Example());
}
