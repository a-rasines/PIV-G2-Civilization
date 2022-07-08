/*
 * MapWindow.h
 *
 *  Created on: 21 may 2022
 *      Author: algtc
 */

#ifndef MAPWINDOW_H_
#define MAPWINDOW_H_
#include "WindowObjects/Window.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include "Sprite.h"
#include "tropa.h"
#include"Ejemplo2.h"
class MapWindow : public Window{
public:
	enum MenuOption{
		TAX_RATE,
		LUXURIES_RATE,
		FIND_CITY,
		OPTIONS,
		SAVE_GAME,
		REVOLUTION,
		RETIRE,
		QUIT,

		NO_ORDERS,
		FOUND_NEW_CITY,
		BUILD_ROAD,
		CHANGE_TO_FOREST,
		BUILD_FORTRESS,
		WAIT,
		SENTRY,
		GOTO,
		PILLAGE,
		DISBAND_UNIT,

		CITY_STATUS,
		MILITARY_ADVISOR,
		INTELLIGENCE_ADVISOR,
		ATTITUDE_ADVISOR,
		TRADE_ADVISOR,
		SCIENCE_ADVISOR,

		WONDERS_OF_THE_WORLD,
		TOP_5_CITIES,
		CIVILIZATION_SCORE,
		WORLD_MAP,
		DEMOGRAPHICS,
		SPACESHIPS,

		COMPLETE,
		CIVILIZATION_ADVANCES,
		CITY_IMPROVEMENTS,
		MILITARY_UNITS,
		TERRAIN_TYPES,
		MISCELLANEOUS
	};
	struct TropaInst : public Tropa{
		TropaInst(int serverId, int userId, int troopId, int type, int posX, int posY){
			this->idServidor = serverId;
			this->idJugador = userId;
			this->idTropa = troopId;
			this->data = sprite::Troop[type];
			this->estado = 0;
			this->mejorada = 0;
			this->posicionX = posX;
			this->posicionY = posY;
			this->renderingPositionX = posX;
			this->renderingPositionY = posY;
			this->tipo = type;
			this->vida = data.defense;
		};
		TropaInst(int serverId, int userId, int troopId,int estado,int mejora, int posX, int posY, int type, int vida){
					this->idServidor = serverId;
					this->idJugador = userId;
					this->idTropa = troopId;
					this->data = sprite::Troop[type];
					this->estado = estado;
					this->mejorada = mejora;
					this->posicionX = posX;
					this->posicionY = posY;
					this->renderingPositionX = posX;
					this->renderingPositionY = posY;
					this->tipo = type;
					this->vida = vida;
				};
		bool operator == (Tropa t){
			return idTropa==t.idTropa && idJugador == t.idJugador;
		}
		void keyPress(int keycode, MapWindow *mw);
		sprite::TroopData data;
		float renderingPositionX;
		float renderingPositionY;
	};
	void cargarTropas(const char* fichero);
	void guardarTropas(const char* fichero);
	void onClientStart();
	MapWindow();
	void troopMove(TropaInst *t, int x, int y);
	bool posibleMove(TropaInst t,int x, int y);
	void start(); //Esta funcion se llama al cambiar de pantalla
	void update();//Esta funcion se llama cada vez que de una vuelta al bucle
	void onClose();
	void onButtonPress(HWND button){};//Esta funcion se llama cuando un boton sea pulsado
	void reposition(int x, int y);//Se llama para mover el mapa
	void onResize(int newWidth, int newHeight);//Esta funcion se llama cuando la ventana cambia de tamaño
	void onKeyDown(int keycode);//Esta función se llama cuando una tecla es pulsada
	void onMessage(char * message);
	void onMenu(UINT_PTR menuId);
	struct Cell{
		int posX;
		int posY;
		int sizeX;
		int sizeY;
		std::string file;
		sf::IntRect texData;

	};
	virtual ~MapWindow();
	static int zoom;
private:
	float round(float number, int decimals);
	sf::RenderWindow mapView;
	static float x;
	static float y;
	std::vector<Cell> activeCells;
	std::vector<TropaInst> activeTroops;
	static sf::Texture background;
	int lastMovement;
	bool moving = false;
	bool repos = true;
};

#endif /* MAPWINDOW_H_ */