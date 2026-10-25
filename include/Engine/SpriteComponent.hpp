#pragma once
#include <SDL3/SDL.h>
#include "Engine/Component.hpp"


//Componente encargado de dibujar una textura en pantalla.
class SpriteComponent : public Component {
    private:
//Puntero a la textura que queremos pintar
    SDL_Texture* m_texture{ nullptr};

    //Ancho y Alto originales de la textura
    //Los obtenemos en el constructor
    float m_width{0.0f};
    float m_height{0.0f};


    //Rectangulo que indica que parte de la imagen dibujar
    //Por ejemplo, podemos seleccionar un sprite de una hoja.
    SDL_FRect m_srcRect{0.0f, 0.0f, 0.0f, 0.0f};

bool m_useSrcRect {false};

//Color y transparencia aplicados al dibujar.
//Los valores van de 0.0f a 1.0f.
//(1,1,1,1) mantiene el color y la opacidad original.
SDL_FColor m_colorMod {1.0f, 1.0f, 1.0f, 1.0f};

//Indica si queremos voltear la imagen
//SDL_FLIP_NONE significa que no se voltean.
SDL_FlipMode m_flip{SDL_FLIP_NONE};

public:
//Constructor que recibe la textura que dibujaremso
explicit SpriteComponent(SDL_Texture* texture);

//Permite seleccionar una region de la imagen
void SetSourceRect(const SDL_FRect& rect);

//Desactiva el recorte y utiliza la imagen completa.

void ClearSourceRect();

//Permite modificar el color y la transparencia.
void SetColorMod(const SDL_FColor& color);

//Permite voltear la textura horizontal o verticalmente

void SetFlip(SDL_FlipMode flip);

//Metodo heredado de component
//Dibujara la textura utilizando el renderer de SDL3.

void Render(SDL_Renderer* renderer) override;
};