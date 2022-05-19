/*
 * Sprite.h
 *
 *  Created on: 18 may 2022
 */

#ifndef SPRITE_H_
#define SPRITE_H_
namespace Sprite{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//                              INICIO DE TROPAS
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	struct TroopData{
		int textureX;
		int textureY;
		int sizeX;
		int sizeY;
		int damage;
		int defense;
		int movements;
		int cost;

	};
	struct TransporterData : public TroopData{
		TransporterData(int textureX, int textureY, int sizeX, int sizeY, int damage, int defense, int movements, int cost, int capacity){
			TroopData::textureX = textureX;
			TroopData::textureY = textureY;
			TroopData::sizeX = sizeX;
			TroopData::sizeY = sizeY;
			TroopData::damage = damage;
			TroopData::defense = defense;
			TroopData::movements = movements;
			TroopData::cost = cost;
			TransporterData::capacity = capacity;
		}
		int capacity;
	};
	struct WaterTroopData : public TroopData{
		WaterTroopData(int textureX, int textureY, int sizeX, int sizeY, int damage, int defense, int movements, int cost){
			TroopData::textureX = textureX;
			TroopData::textureY = textureY;
			TroopData::sizeX = sizeX;
			TroopData::sizeY = sizeY;
			TroopData::damage = damage;
			TroopData::defense = defense;
			TroopData::movements = movements;
			TroopData::cost = cost;
		}
	};
	struct AirTroopData : public TroopData{
		AirTroopData(int textureX, int textureY, int sizeX, int sizeY, int damage, int defense, int movements, int cost){
			TroopData::textureX = textureX;
			TroopData::textureY = textureY;
			TroopData::sizeX = sizeX;
			TroopData::sizeY = sizeY;
			TroopData::damage = damage;
			TroopData::defense = defense;
			TroopData::movements = movements;
			TroopData::cost = cost;
		}
	};
	enum TroopType{
		SETTLER,
		MILITIA,
		PHALANX,
		LEGION,
		MUSKETEER,
		RIFLEMEN,
		CAVALRY,
		KNIGHT,
		CATAPULT,
		CANNON,
		CHARIOT,
		ARMOR,
		MECH_INF,
		ARTILLERY,
		FIGHTER,
		BOMBER,
		TRIREME,
		SAIL,
		FRIGATE,
		IRONCLAD,
		CRUISER,
		BATTLESHIP,
		SUBMARINE,
		CARRIER,
		TRANSPORT,
		NUCLEAR,
		DIPLOMAT,
		CARAVAN,
		NULL //Valor para tener constancia del tamaño del enum

	};
	const TroopData Troop[TroopType::NULL] = {
			(TroopData) {1,161,15,15, 0, 1, 1, 40},//Settler
			(TroopData) {17, 161, 15, 15, 1, 1, 1, 10},//Militia
			(TroopData) {33, 161, 15, 15, 1, 2, 1, 20},//Phalanx
			(TroopData) {49, 161, 15, 15, 3, 1, 1, 20},//Legion
			(TroopData) {65, 161, 15, 15, 2, 3, 1, 30},//Musketeer
			(TroopData) {81, 161, 15, 15, 3, 5, 1, 30},//Riflemen
			(TroopData) {97, 161, 15, 15, 2, 1, 2, 20},//Cavalry
			(TroopData) {113, 161, 15, 15, 4, 2, 2, 40},//Knight
			(TroopData) {129, 161, 15, 15, 6, 1, 1, 40},//Catapult
			(TroopData) {145, 161, 15, 15, 8, 1, 1, 40},//Cannon
			(TroopData) {161, 161, 15, 15, 4, 1, 2, 40},//Chariot
			(TroopData) {177, 161, 15, 15, 10, 5, 3, 80},//Armor
			(TroopData) {193, 161, 15, 15, 6, 6, 3, 50},//Mech_inf
			(TroopData) {209, 161, 15, 15, 12, 2, 2, 60},//Artillery
			(AirTroopData) {225, 161, 15, 15, 4, 2, 10, 60},//Fighter
			(AirTroopData) {241, 161, 15, 15, 12, 1, 8, 120},//Bomber
			(TransporterData) {257, 161, 15, 15, 1, 0, 3, 40, 2},//Trireme
			(TransporterData) {273, 161, 15, 15, 1, 1, 3, 40, 3},//Sail
			(TransporterData) {289, 161, 15, 15, 2, 2, 3, 40, 4},//Frigate
			(WaterTroopData) {305, 161, 15, 15, 4, 4, 4, 60},//Ironclad
			(WaterTroopData) {1, 177, 15, 15, 6, 6, 6, 80},//Cruiser
			(WaterTroopData) {17, 177, 15, 15, 18, 12, 4, 160},//Battleship
			(WaterTroopData) {33, 177, 15, 15, 8, 2, 3, 50},//Submarine
			(TransporterData) {49, 177, 15, 15, 1, 12, 5, 160, 8},//Carrier
			(TransporterData) {65, 177, 15, 15, 0, 3, 4, 50, 8},//Transport
			(TroopData) {81, 177, 15, 15, 99, 0, 16, 160},//Nuclear
			(TroopData) {97, 177, 15, 15, 0, 0, 2, 30},//Diplomat
			(TroopData) {113, 177, 15, 15, 0, 1, 1, 50} //Caravan
	};
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//                              FIN DE TROPAS
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//                              INICIO DE TERRENOS
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	class AllowedTroopTypes{
		public:
			enum {
				NONE = 0,
				GROUND = 1,
				AIR = 2,
				//GROUND + AIR = 3
				WATER = 4,
				//GROUND + WATER = 5
				//AIR + WATER = 6
				//GROUND + AIR + WATER = 7
				ALL = 8
			};
	};
	struct TerrainType{
		const int textureX;
		const int textureY;
		const int sizeX;
		const int sizeY;
		const char* file;
		int allowedTroops; //Valor de AllowedTroopTypes
	};
	class Connections {
		public:
			static const Connections
				NONE,
				UP,
				DOWN,
				LEFT,
				RIGHT;
			Connections(){

				value = 0;
			}
			virtual ~Connections(){

			}
			operator int() const {
				return x[value];
			}
			Connections operator+(Connections other) const{
				return Connections(this->value + other.value);
			}
		private:
			Connections(int value){
				this->value = value;
			}
			int value;
			static constexpr const int x[]= {0, 16, 64, 80, 128, 144, 192, 208, 32, 48, 96, 112, 160, 176, 224, 240};
	};
	enum class StackableConnections{
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		UP_RIGHT,
		UP_LEFT,
		DOWN_RIGHT,
		DOWN_LEFT
	};
	class TerrainTypes{};
	class ConnectedTerrainTypes : public TerrainTypes{};
	class NonStackableTerrainTypes : public ConnectedTerrainTypes{
		public:
			const char* file;
			int y;
			NonStackableTerrainTypes(int y, const char* file){
				this->file = file;
				this->y = y;
			};
			static NonStackableTerrainTypes
				RIVER,
				NOT_FROZEN_SEA,
				FROZEN_RIVER,
				NOT_SEA,
				MOUNTAIN,
				MOUNT,
				ICE,
				CROPS,
				FOREST,
				SWAMP,
				WATERFOREST,
				RIVER_SEA,
				BIG_CROPS;
	};
	class StackedTerrainTypes : public ConnectedTerrainTypes{
		public:
			enum{
				ROAD = 208,
				RAIL = 224
			};
	};
	class NonConnectedTerrainTypes{

	};
	class Terrain{

	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//                              FIN DE TERRENOS
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//                              INICIO DE CASILLAS
	/////////////////////////////////////////////////////////////////////////////////////////////////////

};

#endif /* SPRITE_H_ */
