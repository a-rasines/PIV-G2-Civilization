/*
 * MapWindow.cpp
 *
 *  Created on: 21 may 2022
 *      Author: algtc
 */

#include "MapWindow.h"

#include <SFML/Graphics.hpp>

#include <windef.h>
#include <cmath>
#include <cstdio>

#include "menuEjemplo.h"
#include "MapHolder.h"

float MapWindow::x;
float MapWindow::y;
int MapWindow::zoom;
using namespace std;
sf::Texture MapWindow::background;
MapWindow::MapWindow() {
	x = 0;
	y = 0;
	zoom = 5;
	lastMovement = 0;
}
void MapWindow::troopMove(TropaInst *toca, int x, int y){
	if(posibleMove(*toca,x,y)){
		toca->posicionX=x;
		toca->posicionY=y;
	}
}
void MapWindow::onClientStart(){
	for(TropaInst tr : activeTroops)
		Window::manager->sendMessage((string("1Te envio tropa:"+to_string(tr.idServidor)+string(",")+to_string(tr.idJugador)+string(",")+to_string(tr.idTropa)+
				string(",")+to_string(tr.estado)+string(",")+to_string(tr.mejorada)+string(",")+to_string(tr.posicionX)+
				string(",")+to_string(tr.posicionY)+string(",")+to_string(tr.tipo)+string(",")+to_string(tr.vida))).c_str());
	Window::manager->sendMessage("2Terminado envio de tropas");
	activeTroops.clear();
}
void MapWindow::onMessage(char* message){
	if(message[0]=='0'){
		int x,y;
		sscanf(message,"0tropa a posicion:(%i,%i)",&x,&y);
		if(activeTroops.front().idJugador!=menuEjemplo::logeado.id){
			TropaInst actual = activeTroops.front();
			troopMove(&actual, x, y);
			activeTroops.erase(activeTroops.begin());
			activeTroops.push_back(actual);
			if(activeTroops.front().idJugador!=menuEjemplo::logeado.id){
				Window::manager->sendMessage("ACK");
			}
		}
	}else if(message[0]=='1'){
		int a,b,c,d,e,f,g,h,i;
		sscanf(message,"1Te envio tropa:%i,%i,%i,%i,%i,%i,%i,%i,%i",&a,&b,&c,&d,&e,&f,&g,&h,&i);
		TropaInst t = {a,b,c,d,e,f,g,h,i};
		activeTroops.push_back(t);
		Window::manager->sendMessage("ACK");
	}else if(message[0]=='2'){
		for(TropaInst tr : activeTroops)
			Window::manager->sendMessage((string("1Te envio tropa:"+to_string(tr.idServidor)+string(",")+to_string(tr.idJugador)+string(",")+to_string(tr.idTropa)+
			string(",")+to_string(tr.estado)+string(",")+to_string(tr.mejorada)+string(",")+to_string(tr.posicionX)+
			string(",")+to_string(tr.posicionY)+string(",")+to_string(tr.tipo)+string(",")+to_string(tr.vida))).c_str());
	}
}
bool MapWindow::posibleMove(TropaInst t ,int x, int y){
	return foreground[y][x].allowedTroops->isAllowed(t.data.type);
}
void MapWindow::guardarTropas(const char* fileName){
	fstream file_out;
	file_out.open(fileName,fstream::out);
	if(!file_out.is_open()){
		cout<<"No se ha podido abrir el fichero"<< fileName<<"\n";
	}else{
		for(TropaInst tr: activeTroops){
			file_out << tr.idServidor+','+tr.idJugador+','+tr.idTropa+
					','+tr.estado+','+tr.mejorada+','+tr.posicionX+
					','+tr.posicionY+','+tr.tipo+','+tr.vida+'\n'<< endl;
			cout <<"Escritura terminada"<< endl;
		}
	}

}
void MapWindow::cargarTropas(const char* fileName){
	ifstream file;
	file.open(fileName);
	for(std::string line;getline(file,line);){
		int numeros[10];
		int index = 0;
		for(char n: line){
			if(n!=','||n!='\n'){
				int number = n-'0';
				numeros[index] = number;
			}
			index++;
		}
		TropaInst t = {numeros[0],numeros[1],numeros[2],numeros[3],numeros[4],numeros[5],numeros[6],numeros[7],numeros[8]};
		activeTroops.push_back(t);
	}
}
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
void MapWindow::start(){
	addMenuItem(Window::MenuItem{
		L"&GAME",
		{
			Window::MenuItem{L"&Tax Rate", TAX_RATE},
			Window::MenuItem{L"&Luxuries Rate", LUXURIES_RATE},
			Window::MenuItem{L"&Find City", FIND_CITY},
			Window::MenuItem{L"&Options", OPTIONS},
			Window::MenuItem{L"&Save Game", SAVE_GAME},
			Window::MenuItem{L"&REVOLUTION!", REVOLUTION},
			Window::MenuItem{},
			Window::MenuItem{L"&Retire", RETIRE},
			Window::MenuItem{L"&QUIT", QUIT}
		}
	});
	addMenuItem(Window::MenuItem{
		L"&ORDERS",
		{
			Window::MenuItem{L"&No Orders (space)", NO_ORDERS},
			Window::MenuItem{L"&Found New City (b)", FOUND_NEW_CITY},
			Window::MenuItem{L"&Build Road (r)", BUILD_ROAD},
			Window::MenuItem{L"&Change To Forest (m)", CHANGE_TO_FOREST},
			Window::MenuItem{L"&Build Fortress (f)", BUILD_FORTRESS},
			Window::MenuItem{L"&Wait (w)", WAIT},
			Window::MenuItem{L"&Sentry (s)", SENTRY},
			Window::MenuItem{L"&GoTo", GOTO},
			Window::MenuItem{L"&Pillage (P)", PILLAGE},
			Window::MenuItem{},
			Window::MenuItem{L"&Disband Unit (D)", DISBAND_UNIT}
		}
	});
	addMenuItem(Window::MenuItem{
		L"&ADVISORS",
		{
			Window::MenuItem{L"&City Status (F1)", CITY_STATUS},
			Window::MenuItem{L"&Military Advisor (F2)", MILITARY_ADVISOR},
			Window::MenuItem{L"&Intelligence Advisor (F3)", INTELLIGENCE_ADVISOR},
			Window::MenuItem{L"&Attitude Advisor (F4)", ATTITUDE_ADVISOR},
			Window::MenuItem{L"&Trade Advisor (F5)", TRADE_ADVISOR},
			Window::MenuItem{L"&Science Advisor (F6)", SCIENCE_ADVISOR},
		}
	});
	addMenuItem(Window::MenuItem{
		L"&WORLD",
		{
			Window::MenuItem{L"&Wonders of the World (F7)", WONDERS_OF_THE_WORLD},
			Window::MenuItem{L"&Top 5 Cities (F8)", TOP_5_CITIES},
			Window::MenuItem{L"&Civilization Score (F9)", CIVILIZATION_SCORE},
			Window::MenuItem{L"&World Map (F10)", WORLD_MAP},
			Window::MenuItem{L"&Demographics", DEMOGRAPHICS},
			Window::MenuItem{L"&SpaceShips", SPACESHIPS},
		}
	});
	addMenuItem(Window::MenuItem{
		L"&CIVILOPEDIA",
		{
			Window::MenuItem{L"&Complete", COMPLETE},
			Window::MenuItem{L"&Civilization Advances", CIVILIZATION_ADVANCES},
			Window::MenuItem{L"&City Improvements", CITY_IMPROVEMENTS},
			Window::MenuItem{L"&Military Units", MILITARY_UNITS},
			Window::MenuItem{L"&Terrain Types", TERRAIN_TYPES},
			Window::MenuItem{L"&Miscellaneous", MISCELLANEOUS},
		}
	});
	reposition(x, y);
	WindowManager::Dimension size = Window::manager->getWindowSize();
	mapView.create(generateView(0, 0, size.x, size.y));
	setResizable(true);
	std::string file = "resources/" + (std::string)RIVER.file;
	background.loadFromFile(file, sf::IntRect(RIVER.textureX, RIVER.textureY, RIVER.sizeX, RIVER.sizeY));
	TropaInst t1 = {0, menuEjemplo::logeado.id, 0, 1, 5, 5};
	TropaInst t2 = {0, menuEjemplo::logeado.id, 1, 16, 18,18};
	activeTroops.push_back(t1);
	activeTroops.push_back(t2);
}
float MapWindow::round(float number, int decimals){
	number *= pow(10, decimals);
	number -= remainder(number, 1) * (-(number < 0) + (number >= 0));
	return number / pow(10, decimals);

}
bool moving = false;
bool repos = false;
void MapWindow::update(){
	mapView.clear();
	for(Cell cell : activeCells){
		sf::Texture tex;
		std::string file = "resources/" + (std::string)cell.file;
		tex.loadFromFile(file, cell.texData);
		sf::RectangleShape rect;
		rect.setTexture(&background, false);
		rect.setSize(sf::Vector2f(cell.sizeX, cell.sizeY));
		rect.setPosition(sf::Vector2f(cell.posX, cell.posY));
		mapView.draw(rect);
		rect.setTexture(&tex, false);
		mapView.draw(rect);
	}
	moving = false;
	for(unsigned int i = 0; i < activeTroops.size(); i++){
		sf::Texture tex;
		TropaInst* t = &(activeTroops[i]);
		sprite::TroopData coso = sprite::Troop[t->tipo];
		tex.loadFromFile("resources/SP257.PIC_256.gif",sf::IntRect(coso.textureX,coso.textureY,coso.sizeX,coso.sizeY));
		sf::RectangleShape rect;
		rect.setTexture(&tex, false);
		rect.setSize(sf::Vector2f(coso.sizeX*zoom, coso.sizeY*zoom));
		if(t->renderingPositionX != t->posicionX || t->renderingPositionY != t->posicionY){
			moving = true;
			t->renderingPositionX = round(t->renderingPositionX + 0.2 * (t->renderingPositionX < t->posicionX) - 0.2 * (t->renderingPositionX > t->posicionX), 1);
			t->renderingPositionY = round(t->renderingPositionY + 0.2 * (t->renderingPositionY < t->posicionY) - 0.2 * (t->renderingPositionY > t->posicionY), 1);
		}
		rect.setPosition(sf::Vector2f(t->renderingPositionX*16*zoom-x, t->renderingPositionY*16*zoom-y));
		mapView.draw(rect);
	}
	if(!moving && repos){
		TropaInst troop = activeTroops.front();
		reposition((troop.posicionX-7)*16*zoom, (troop.posicionY-6)*16*zoom);
		repos = false;
	}
	mapView.display();
}

void MapWindow::onClose(){
	guardarTropas("resources/troopSave.dat");
}

void MapWindow::reposition(int x, int y){
	this->x=x;
	this->y=y;
	WindowManager::Dimension size = Window::manager->getWindowSize();
	activeCells.clear();
	y = -y;
	for(TerrainType row[100] : foreground){
		y += row[0].sizeY * zoom;
		if(y >= size.y + row[0].sizeY * zoom)break;
		else if(y<0)continue;
		int cx = -x;
		for(TerrainType cell : row){
			cx += cell.sizeX * zoom;
			if(cx >= size.x + cell.sizeX * zoom)break;
			else if(cx<0)continue;
			activeCells.push_back((Cell){
				cx-cell.sizeX*zoom,
				y-cell.sizeY*zoom,
				cell.sizeX * zoom,
				cell.sizeY * zoom,
				cell.file,
				sf::IntRect(
						cell.textureX,
						cell.textureY,
						cell.sizeX,
						cell.sizeY
					)
				}
			);
		}
	}
}
void MapWindow::onResize(int newWidth, int newHeight){
	reposition(x, y);
}
void MapWindow::onKeyDown(int keycode){
	if(activeTroops.front().idJugador==menuEjemplo::logeado.id && !moving && (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left))){
		TropaInst troop = activeTroops.front();
		troopMove(&troop,
			troop.posicionX + (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
			troop.posicionY + (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		);
		const char* messagea = (string("0tropa a posicion:(")+to_string(troop.posicionX)+string(",")+to_string(troop.posicionY)+string(")")).c_str();
		cout << "Movimiento: " << messagea << "\n";
		Window::manager->sendMessage(messagea);
		activeTroops.erase(activeTroops.begin());
		activeTroops.push_back(troop);
		repos = true;
	}
}
void MapWindow::onMenu(UINT_PTR menuId){
}
MapWindow::~MapWindow() {}

/*int main(){
	Window::manager = new WindowManager("Civilization", 1200, 1000, new MapWindow());
}
*/
