#include "Partida.h"

Partida::Partida(){
	fondoTextura.loadFromFile("assets/mundo/mundo_fondo.png");
	fondo.setTexture(fondoTextura);
	colision.cargar("assets/sonidos/punch.wav");

	//creo jugador
	jugador = new Personaje(Vector2f(400, 520), gravedad);

	//creo los bloques y le asigno su numero
	for (int i = 0; i < 10; ++i) {
		int numero = std::rand() % 999 + 1;
		valores[i] = numero;

		int x = 35 + i * (45 + 35);
		Vector2f pos(x, 400.f);
		bloques[i] = new Bloque(pos, numero);

	}

	//ordeno su valor de la forma OrdenamientoBurbuja
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (valores[j] > valores[j + 1]) {
				auxiliar = valores[j];

				valores[j] = valores[j + 1];

				valores[j + 1] = auxiliar;
			}
		}
	}
}
Partida::~Partida() {
	delete jugador;
	for (int i = 0; i < 10; ++i) {
		delete bloques[i];
	}
}

void Partida::actualizar(Juego& j){
	float deltaTime = reloj.verReinicio();

	hud.actualizar(deltaTime);
	hud.actualizarTexto();
	if (!hud.seTermino() && indiceObjetivo < 10) {

		jugador->actualizar(deltaTime);

		JugadorYBoque();
	}
	for (int i = 0; i < 10; ++i) {
		bloques[i]->actualizar(deltaTime);
	}

	if (hud.seTermino() || indiceObjetivo == 10) {
		ordenarBloques();

	}

}
void Partida::dibujar(RenderWindow& w){
	w.draw(fondo);
	hud.dibujar(w);

	jugador->dibujar(w);
	for (int i = 0; i < 10; ++i) {
		bloques[i]->dibujar(w);
	}

}
void Partida::procesoEventos(Juego& j, Event& event){
	jugador->manejarEventos(event);
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::R && (hud.seTermino() || indiceObjetivo == 10)) {
		j.reiniciar();
	}
}

void Partida::JugadorYBoque(){
	hayColisionConAlguno = false;
	for (int i = 0; i < 10; ++i) {

		if (jugador->verBounds().intersects(bloques[i]->verBounds())) {
			hayColisionConAlguno = true;

			colision.play();

			colisionInferiorJugadorBloque(bloques[i]);

			// Saltear bloques ya marcados como correctos
			if (bloques[i]->fueCorrecto()) {
				break;
			}

			if (!colisionandoConBloque) {
				if (indiceObjetivo < 10) {
					if (bloques[i]->verNumero() == valores[indiceObjetivo]) {
						indiceObjetivo++;
						bloques[i]->esCorrecto();

						if (indiceObjetivo == 10) {
							hud.elGano();
							ordenarBloques();
						}
					}
					else {
						hud.esIncorrecto();
					}
				}
			}
			break;
		}
	}

	colisionandoConBloque = hayColisionConAlguno;
}
void Partida::colisionInferiorJugadorBloque(Bloque* bloque){
	// controlar choque con la parte inferior del bloque
	FloatRect jugadorBounds = jugador->verBounds();
	FloatRect bloqueBounds = bloque->verBounds();

	if (jugador->verVelocidadY() < 0 &&
		jugadorBounds.top > bloqueBounds.top + bloqueBounds.height - 10) {
		jugador->queVelocidadY(0);
		jugador->quePos({
			jugador->verPos().x,
			bloqueBounds.top + bloqueBounds.height + jugadorBounds.height / 2
			});
	}
}
void Partida::ordenarBloques() {
	// Reordena los bloques según el array de valores ordenados
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (bloques[j]->verNumero() == valores[i]) {
				float x = 35 + i * (45 + 35);
				bloques[j]->quePos(Vector2f(x, 400.f));
				break;
			}
		}
	}
}

