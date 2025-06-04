#include "Bloque.h"
Bloque::Bloque(Vector2f pos, int num) :  Objeto("assets/mundo/bloque_sheet.png", pos, { 45, 45 }), posicionOriginal(pos){
    backGround.Add("off", { 1 }, 8, true);
    backGround.Add("on", { 0 }, 8, true);
    backGround.Play("off");

    numero.inicializar(13);
    numero.queTexto(to_string(num));
    numero.queColor(Color(170, 0, 20));
    numero.quePosicion(backGround.getPosition().x, backGround.getPosition().y + 5);

};

void Bloque::dibujar(RenderWindow& w) {
    w.draw(backGround);
    numero.dibujar(w);
}
void Bloque::animacion(float deltaTime) {
    if (esElCorrecto) {
        numero.queColor(Color(50, 150, 75));
        backGround.Play("on");
        tiempoAnim += deltaTime;

        float progreso = tiempoAnim / duracionAnim;

        // Rebote simple: sube y luego baja
        float offsetY = 0.f;
        if (progreso < 0.5f) {
            offsetY = alturaRebote * (progreso / 0.5f); // sube
        }
        else if (progreso < 1.f) {
            offsetY = alturaRebote * (1 - (progreso - 0.5f) / 0.5f); // baja
        }
        else {
            esElCorrecto = false;
            offsetY = 0.f;
            tiempoAnim = 0.f;
            

        }

        Vector2f nuevaPos = posicionOriginal + Vector2f(0.f, offsetY);
        backGround.setPosition(nuevaPos);
        numero.quePosicion(nuevaPos.x, nuevaPos.y + 5);
    }
}
void Bloque::esCorrecto() {
    esElCorrecto = true;
    fueElCorrecto = true;
}
bool Bloque::fueCorrecto() {
    return fueElCorrecto;
}

int Bloque::verNumero() { return stoi(numero.verString()); }


void Bloque::quePos(Vector2f pos) {
    Objeto::quePos(pos);
    numero.quePosicion(backGround.getPosition().x, backGround.getPosition().y + 5);
}   