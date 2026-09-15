#pragma once // es una directiva de preprocesador que asegura que el archivo de encabezado se incluya solo una vez en un archivo de origen durante la compilación.

#include <SDL3/SDL.h> // incluye la biblioteca SDL3 para el desarrollo de aplicaciones multimedia.

class GameObject; // Declaracion de la clase GameObject anticipada, utilizado para avisarle al pinche compilador que existe una clase GameObject, sin necesidad de incluir su definición completa en este archivo de encabezado.
// pej GameObject* obj;

class Component 
{

    public: 

    //Puntero de vuelta al padre
    GameObject *owner{nullptr}; //Creamos un puntero sin inicializar llamado owner que apunta a un objeto de tipo GameObject, estableciendo su valor incial en nullptr (nulo).

    //destructor virtual

    virtual ~Component() = default;  //Garantiza limpieza correcta, la sintaxis "= default" indica que se utilizará la implementación predeterminada del destructor.
    //Y lo hace mas eficiente que abrir corchetes y definirlo como vacio {}. 

    //Metodos virtuales del ciclo de vida
    virtual void Init(){} // se utiliza para incializar los recursos especificos de cada entidad, como cargar texturas, sonidos, etc. Se llama una vez al inicio del juego o cuando se crea el objeto.
    virtual void Update(float dt){} //Maneja la logica del juego basada en el tiempo. El parametro dt (delta time)
    virtual void Render(SDL_Renderer *renderer){} // Se encarga de la representacion grafica. Recibe el puntero renderer al renderer de SDL, para dibujar el objeto en la pantalla. Se llama cada frame para renderizar el objeto en la pantalla.

    

};
