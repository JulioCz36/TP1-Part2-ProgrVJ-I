#include "HUD.h"

HUD::HUD() {
	teclas_texture.loadFromFile("assets/controles/teclas.png");
	controles.setTexture(teclas_texture);
	controles.setPosition(600, 10);

	// Configurar texto principal
	texto.inicializar(20);
	texto.quePosicion(100, 30);
	texto.queColor(Color::Black);
	// Configurar texto de reinicio
	reinicio.inicializar(18);
	reinicio.quePosicion(700, 300);
	reinicio.queTexto("R to restart");

	// Configurar texto de reinicio
	reloj.cargar("assets/sonidos/tic-tac.wav");
	reloj.quePitch(0.28f);
	reloj.queVolumen(80);

	win.cargar("assets/sonidos/win.wav");
	win.queVolumen(60);
	over.cargar("assets/sonidos/game-over.wav");
	over.queVolumen(60);

	restart.cargar("assets/sonidos/button-R.wav");
	restart.queVolumen(40);
}

void HUD::actualizar(float deltaTime) {
	// Si el juego está en curso sonido reloj
	if (!reloj.estaReproduciendo() && !terminado && !gano) {
		reloj.play();
	}

	// Si se terminó el juego o el jugador ganó
	if (terminado || gano) {
		reloj.stop(); // Detener el sonido de reloj

		// Reproducir sonido condicion
		if (!sonidoCondicion) {
			if (terminado) over.play();
			if (gano) win.play();
			sonidoCondicion = true;
		}
		
		// Esperar 2 segundos antes de comenzar el parpadeo del mensaje de reinicio
		tiempoDesdeFin += deltaTime;
		if (tiempoDesdeFin >= 2.f) {
			tiempoParpadeo += deltaTime;

			// Alternar visibilidad del mensaje de reinicio cada 0.5 segundos
			if (tiempoParpadeo >= 0.5f) {
				mostrarReinicioAnterior = mostrarReinicio;
				mostrarReinicio = !mostrarReinicio;
				tiempoParpadeo = 0.f;

				// Reproducir sonido solo al aparecer el mensaje
				if (!mostrarReinicioAnterior && mostrarReinicio) {
					restart.play();
				}
			}
		}

		return;
	}

	// Reducir el tiempo restante mientras el juego está en curso
	tiempoRestante -= deltaTime;

	// Verificar si se acabó el tiempo
	if (tiempoRestante <= 0.f) {
		tiempoRestante = 0.f;
		terminado = true;
	}
}
void HUD::dibujar(RenderWindow& w) {
	if (!terminado && !gano) {
		w.draw(controles);
	}

	// Dibujar texto principal 
	texto.dibujar(w);

	// Dibujar mensaje de reinicio si corresponde
	if ((terminado || gano) && mostrarReinicio) {
		reinicio.dibujar(w);
	}
}

void HUD::actualizarTexto() {
	// Configurar mensaje final según el estado del juego
	if (gano) {
		texto.queColor(Color(0, 173, 17));
		texto.quePosicion(400, 200);
		texto.queSize(60);
		texto.queTexto("¡ You win !");
	}
	else if (terminado) {
		texto.queColor(Color(170, 0, 20));
		texto.quePosicion(400, 200);
		texto.queSize(60);
		texto.queTexto("Game Over");
	}
	else {
		// Mostrar tiempo restante
		texto.queColor(Color::Black);
		texto.quePosicion(100, 30);
		texto.queSize(20);
		texto.queTexto("Tiempo: " + to_string((int)tiempoRestante));
	}
}


void HUD::esIncorrecto() {
	// Penalizar tiempo y el juego sigue activo
	if (!terminado) {
		tiempoRestante -= 10.f;
		if (tiempoRestante < 0.f) tiempoRestante = 0.f;
	}
}
void HUD::elGano() {
	// Establecer que el jugador ganó
	gano = true;
}

bool HUD::seTermino(){
	// Indicar si se terminó el juego
	return terminado;
}
