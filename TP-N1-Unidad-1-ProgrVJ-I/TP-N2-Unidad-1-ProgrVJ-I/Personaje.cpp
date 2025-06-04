#include "Personaje.h"
Personaje::Personaje(Vector2f pos, float gravedadMundo) : Objeto("assets/personaje/personaje_sheet.png", pos, { 64, 64 }, 2.5f), gravedad(gravedadMundo) {

    backGround.Add("idle", { 0, 1, 2, 3, 4,5,6,7 }, 8, true);
    backGround.Add("walk", { 8, 9, 10, 11, 12,13,14,15 }, 8, true);
    backGround.Add("run", { 16, 17, 18, 19, 20,21,22,23 }, 8, true);
    backGround.Add("jump", { 24,25 }, 8, true);
    backGround.Add("fall", { 26,27 }, 8, true);
    backGround.Add("land", { 28,29}, 8, true);


    running.cargar("assets/sonidos/running.wav");
    running.quePitch(0.6f);
    walk.cargar("assets/sonidos/running.wav");
    walk.quePitch(0.52f);
    jump.cargar("assets/sonidos/jump.wav");
    land.cargar("assets/sonidos/land.wav");
}

void Personaje::actualizar(float deltaTime) {
    Objeto::actualizar(deltaTime);
    mover(deltaTime);
    verificarLimitesPantalla();
    aplicarGravedad(deltaTime);
     if (estaQuieto() && !enElAire) {
         backGround.Play("idle");
     }
}
void Personaje::manejarEventos(Event& e) {
    if (e.type == Event::KeyPressed && (e.key.code == saltar1 || e.key.code == saltar2) && !enElAire) {
        velocidadY = -velocidadSalto;
        enElAire = true;
    }
}


void Personaje::mover(float deltaTime) {
    float desplazamiento = velocidad * deltaTime;
    bool corriendo = false;
    bool caminando = false;

    if (Keyboard::isKeyPressed(der)) {
        backGround.FlipX(false);
        backGround.move(desplazamiento, 0);
        if (!enElAire) {
            backGround.Play("walk");
            caminando = true;
        }
    }
    if (Keyboard::isKeyPressed(izq)) {
        backGround.FlipX(true);
        backGround.move(-desplazamiento, 0);
        if (!enElAire) {
            backGround.Play("walk");
            caminando = true;
        }
    }
    if (Keyboard::isKeyPressed(der) && Keyboard::isKeyPressed(correr)) {
        backGround.FlipX(false);
        backGround.move(desplazamiento * 1.5f, 0);
        if (!enElAire) {
            backGround.Play("run");
            corriendo = true;
        }
    }
    if (Keyboard::isKeyPressed(izq) && Keyboard::isKeyPressed(correr)) {
        backGround.FlipX(true);
        backGround.move(-desplazamiento * 1.5f, 0);
        if (!enElAire) {
            backGround.Play("run");
            corriendo = true;
        }
    }

    // Control del sonido de correr
    if (corriendo) {
        if (!running.estaReproduciendo()) running.play();
    }
    else {
        running.stop();
    }

    // Control del sonido de caminar
    if (caminando && !corriendo) {
        if (!walk.estaReproduciendo()) walk.play();
    }
    else {
        walk.stop();
    }
}
void Personaje::aplicarGravedad(float deltaTime) {
    //gravedad
    velocidadY += gravedad * deltaTime;

    // Mover en Y
    backGround.move(0, velocidadY * deltaTime);

    // Aterrizaje
    if (backGround.getPosition().y >= 520) {
        backGround.setPosition(backGround.getPosition().x, 520);
        velocidadY = 0;
        enElAire = false;
    }
}
void Personaje::animacion(float deltaTime) {
    if (enElAire) {
        if (velocidadY < 0 && !saltoIniciado) {
            backGround.Play("jump");
            saltoIniciado = true;
            caidaIniciada = false;
            jump.play();
        }
        else if (velocidadY > 0 && !caidaIniciada) {
            backGround.Play("fall");
            caidaIniciada = true;
        }
    }
    else {
        // Si acaba de aterrizar
        if (saltoIniciado || caidaIniciada) {
            saltoIniciado = false;
            caidaIniciada = false;
            backGround.Play("land");
            land.play();
        }
    }
}

bool Personaje::estaQuieto() {
    return !(Keyboard::isKeyPressed(der) ||Keyboard::isKeyPressed(izq));
}
void Personaje::verificarLimitesPantalla() {
    FloatRect bounds = backGround.getGlobalBounds();
    Vector2f pos = backGround.getPosition();

    float margenIzquierdo = 55.f;
    float margenDerecho = 55.f;

    float izquierdaReal = pos.x - bounds.width / 2 + margenIzquierdo;
    float derechaReal = pos.x + bounds.width / 2 - margenDerecho;

    if (izquierdaReal  < 0) {
        backGround.setPosition(bounds.width / 2 - margenIzquierdo, pos.y);
    }
    if (derechaReal > 800) {
        backGround.setPosition(800 - bounds.width / 2 + margenDerecho, pos.y);
    }
}


FloatRect Personaje::verBounds() { 
    if (enElAire) {
        return ajustarHitbox(backGround.getGlobalBounds(), 33, 45, 70, 70);
    }
    else {
        return ajustarHitbox(backGround.getGlobalBounds(), 43, 40, 70, 70);
    }
}



