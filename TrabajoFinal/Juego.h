#pragma once
#include "MenuInicio.h"
#include "Background.h"
#include "Player.h" 
#include "Enemy.h"
#include "Shotgun.h"
#include "Bala.h"
#include "EnemigoFinal.h"
#include <vector>

class Juego
{
private:
	Background* background;
	MenuInicio* menu;   
	Player* player;
	Shotgun* escopeta;
	EnemigoFinal* enemigoFinal;  
	vector <Bala*> balas;
	vector <Enemy*> enemigos; 

public:
	Juego(int width, int height);
	void mostrarMenu(Graphics^ canvas);
	void mostrar(Graphics^ canvas); 
	void mover(Graphics^ canvas);
	void moverTeclas(Graphics^ canvas, Movimiento movimiento);
	void mostrarShotgun(Graphics^ canvas); 
	void disparar();
	int getNumeroEnemigos();

};

