#include "Juego.h"

Juego::Juego(int width, int height)
{
	background = new Background();  
	player = new Player(10, 150);  
    enemigoFinal = new EnemigoFinal(0,0); 
    int aaancho, aalto; 
    aaancho = width/2 - enemigoFinal->getAncho();  
    aalto = height/2 -  enemigoFinal->getAlto(); 

    enemigoFinal->setX(aaancho);
    enemigoFinal->setY(aalto); 

	escopeta = new Shotgun(0, 0); 
	Random r;

	for (int i = 0; i < 9; i++)
	{
		int direccion = r.Next(1, 4); 
		int PosicionX = r.Next(0, width - 102);  
		int PosicionY = r.Next(0, height - 102); 
		enemigos.push_back(new Enemy(PosicionX, PosicionY, direccion));     
	}
}

void Juego::mostrarMenu(Graphics^ canvas)  
{
	menu = new MenuInicio(); 
	menu->mostrar(canvas);
}

void Juego::mostrar(Graphics^ canvas)
{
	
	background->mostrar(canvas);
	player->mostrar(canvas); 

	for (int i = 0; i < enemigos.size(); i++)
	{
		enemigos[i]->mostrar(canvas); 
	}
	for (int i = 0; i < balas.size(); i++)
	{
		balas[i]->mostrar(canvas);
	}

    if (enemigos.size() == 0)
    {
        enemigoFinal->mostrar(canvas);
    }

}


void Juego::mover(Graphics^ canvas)
{
    int totalEnemigos = enemigos.size();
    int totalBalas = balas.size();

    // Mover enemigos
    for (int i = 0; i < totalEnemigos; i++) {
        enemigos[i]->mover(canvas);

        if (enemigos[i]->hayColision(player)) {
            player->setX(10);
            player->setY(150);
            // lógica para disminuir vidas
        }
    }

    // Mover balas y verificar colisiones
    for (int i = totalBalas - 1; i >= 0; i--) {
        balas[i]->mover(canvas);

        // Verificar colisión de bala con enemigos
        for (int j = totalEnemigos - 1; j >= 0; j--) {
            if (balas[i]->hayColision(enemigos[j])) {
                delete balas[i];
                delete enemigos[j];

                balas.erase(balas.begin() + i);
                enemigos.erase(enemigos.begin() + j);

                // Ajustar el total después de la eliminación
                totalBalas--;
                totalEnemigos--;
                break;  // Salir del bucle `j` ya que la bala ha sido eliminada
            }
        }

        // Verificar si la bala está fuera del canvas
        if (i < totalBalas) {
            if (balas[i]->getX() < 0 ||
                balas[i]->GetXancho() > canvas->VisibleClipBounds.Width ||
                balas[i]->getY() < 0 ||
                balas[i]->GetYalto() > canvas->VisibleClipBounds.Height) {

                delete balas[i];
                balas.erase(balas.begin() + i);
                totalBalas--;
            }
        }
    }
}


void Juego::moverTeclas(Graphics^ canvas, Movimiento movimiento)
{
	player->MoverTeclar(canvas, movimiento);   

}

void Juego::mostrarShotgun(Graphics^ canvas)
{
	escopeta->setX(player->getX());    
	escopeta->setY(player->getY()+ 55);  
	escopeta->mostrar(canvas); 
}

void Juego::disparar()
{
	if (balas.size() < 3)
	{
		balas.push_back(new Bala(player->getX() + 50, player->getY() + 30, player->getMovimiento()));
	}
}

int Juego::getNumeroEnemigos()
{
    return enemigos.size();
}


