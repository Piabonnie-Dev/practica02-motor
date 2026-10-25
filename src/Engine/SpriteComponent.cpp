#include "Engine/SpriteComponent.hpp"

// Necesitamos GameObject para acceder al objeto propietario.
#include "Engine/GameObject.hpp"

// Nos permite obtener la posicion y escala del objeto.
#include "Engine/TransformComponent.hpp"

//Constructor del componente
//Recibe una textura que fue cargada por ResourceManager
SpriteComponent::SpriteComponent(SDL_Texture* texture) : m_texture(texture){
//Verificamos que la textura exista.
    if(m_texture != nullptr){

        if(!SDL_GetTextureSize(m_texture, &m_width, &m_height))
        
        {
            SDL_Log("Error al obtener el tamanio: %s", 
            SDL_GetError());
        }

    }

}
//Permite seleccionar una region especifica de la imagen
void SpriteComponent::SetSourceRect(const SDL_FRect& rect){
   //Guardamos el rectangulo que queremos dibujar
    m_srcRect = rect;
//Activamos el uso del recorte
    m_useSrcRect = true;
}
//Desactiva el recorte para dibujar toda la imagen
void SpriteComponent::ClearSourceRect(){
    m_useSrcRect = false;
}
//Modificamos el color y la transparencia del sprite.
void SpriteComponent::SetColorMod(const SDL_FColor& color){
//Guardamos el color que se aplicara al dibujar
    m_colorMod = color;
}
//Permite voltear la imagen.
void SpriteComponent::SetFlip(SDL_FlipMode flip){
    m_flip = flip;
}
//Metodo encargado de dibujar el sprite en pantalla
void SpriteComponent::Render(SDL_Renderer* renderer){
//Si al renderer o la textura no existe,
//tons terminamos para evitar utilizar punteros nulos.
    if(renderer == nullptr || m_texture == nullptr){
        return;
    }
//Rectangulo que indica donde dibujaremos la imagen
//Inicialmente utilizamos la posicion (0,0)
//Y el tamanio original de la textura.
    SDL_FRect dstRect {
        0.0f,
        0.0f,
        m_width,
        m_height
    };
//Verificamos que el componente tenga un GameObject
    if(owner != nullptr){
//Buscamos el TransformComponent de nuestro objeto.
        auto* transform = owner->GetComponent<TransformComponent>();
    //Si existe, utilizamos su posicion y escala.
    if(transform != nullptr){

        //Posicion horizontal del objeto
        dstRect.x = transform->position.x;
//Posicion vertical del objeto
        dstRect.y = transform->position.y;

//Calculamos el ancho de la imagen
        dstRect.w = (m_useSrcRect ? m_srcRect.w : m_width) * transform->scale.x;

        //Hacemos lo mismo con el alto.
        dstRect.h = (m_useSrcRect ? m_srcRect.h : m_height)* transform->scale.y;

    }
    
    
    }

    SDL_SetTextureColorModFloat (
        m_texture,
        m_colorMod.r,
        m_colorMod.g,
        m_colorMod.b
    );


    SDL_SetTextureAlphaModFloat(
        m_texture,
        m_colorMod.a
    );
//Si el recorte esta activado, usamos m_srcRect.

    const SDL_FRect* srcRect = m_useSrcRect ? &m_srcRect : nullptr;


//Dibujamos la textura en pantalla
if(!SDL_RenderTextureRotated(
    renderer,
    m_texture,
    srcRect,
    &dstRect,
    0.0,
    nullptr,
    m_flip
))
{
    SDL_Log("Error al dibujar sprite: %s", SDL_GetError());
}

//Restauramos el color original de la textura
SDL_SetTextureColorModFloat(
    m_texture,
    1.0f,
    1.0f,
    1.0f
);
//Restauramos la transparencia original
SDL_SetTextureAlphaModFloat(m_texture, 1.0f);
}