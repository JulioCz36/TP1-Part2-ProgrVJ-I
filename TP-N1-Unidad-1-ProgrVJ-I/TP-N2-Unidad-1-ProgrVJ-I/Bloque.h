#pragma once
#include "Afichmation.h"
#include <SFML/Graphics.hpp>
#include "Texto.h"
#include "Objeto.h"
using namespace sf;

class Bloque : public Objeto {
private:
    Texto numero;  // muestra el número del bloque.

    // Variables para la animación de rebote
    bool esElCorrecto = false;     // detecta que el número es el correcto.
    bool fueElCorrecto = false;    // detecta que ya fueCorrecto y no restar tiempo.
    float tiempoAnim = 0.f;        // Tiempo acumulado desde que empezó la animación.
    float duracionAnim = 0.4f;     // Duración total de la animación.
    float alturaRebote = -10.f;    // Altura del rebote .
    Vector2f posicionOriginal;     // Posición inicial del bloque.

public:

    Bloque(Vector2f pos, int num);

    // Dibuja el bloque y su número en la ventana.
    void dibujar(RenderWindow& w) override;


    // Animación de rebote si el bloque es el correcto.
    void animacion(float deltaTime) override;

    // Marca al bloque como correcto.
    void esCorrecto();

    // Devuelve true si el bloque ya fue marcado y evitar restar tiempo.
    bool fueCorrecto();

    // Devuelve el número que contiene el bloque.
    int verNumero();

    // Cambia la posición del bloque en pantalla.
    void quePos(Vector2f pos);
};


