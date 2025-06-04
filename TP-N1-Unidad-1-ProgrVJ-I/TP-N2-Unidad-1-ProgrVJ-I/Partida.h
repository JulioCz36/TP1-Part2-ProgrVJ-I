#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Personaje.h"
#include "Bloque.h"
#include "HUD.h"
#include "Reloj.h"
#include "Escenas.h"

using namespace sf;
using namespace std;

class Partida : public Escena {
	Texture fondoTextura;	// Textura de fondo
	Sprite fondo;             // Sprite que representa el fondo visual
	
	Reloj reloj;			// Cronómetro para manejar el tiempo de partida
	Audio colision;     // Sonido de colisión entre el jugador y bloques

	HUD hud;	 // Interfaz de usuario

	Personaje* jugador = nullptr; // Puntero al jugador
	float gravedad = 787.5f;	//	gravedad aplicada al jugador

	Bloque* bloques[10];          // Arreglo de punteros a bloques
	bool colisionandoConBloque = false;  // Si el jugador está colisionando actualmente
	bool hayColisionConAlguno = false;   // Si hay colisión con un bloque

	int valores[10];              // Valores asigado a cada bloque
	int auxiliar = 0;             // Variable auxiliar para ordenar el arreglo valor
	int indiceObjetivo = 0;       // Índice del bloque objetivo correcto
public:
	Partida();
	~Partida();

	// actualización de la escena.
	void actualizar(Juego& j) override;
	// Dibuja elementos visibles en pantalla.
	void dibujar(RenderWindow& w) override;

	// Procesa la entrada del jugador y eventos del sistema.
	void procesoEventos(Juego& j, Event& event) override;


	// Maneja la interacción entre el jugador y todos los bloques.
	void JugadorYBoque();

	// Lógica para cuando el jugador colisiona por debajo con un bloque.
	void colisionInferiorJugadorBloque(Bloque* bloque);

	// Ordena los bloques por su valor numerico.
	void ordenarBloques();
};

