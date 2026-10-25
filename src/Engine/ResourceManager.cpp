
#include <Engine/ResourceManager.hpp>
//Constructor que recibe el renderer de SDL3.
//Guardamos el puntero para poder crear texturas despues.
ResourceManager::ResourceManager(SDL_Renderer* renderer) : m_renderer(renderer){

}
//Destructor de nuestro administrador.
//Antes de destruirse, libera las texturas almacenadas.
ResourceManager::~ResourceManager(){
    Clear();
}

//Busca una textura en la cache y la carga si todavia no existe.
SDL_Texture* ResourceManager::GetTexture(const std::string& filepath){

    //Buscamos la ruta dentro del mapa de texturas
    auto it = m_textures.find(filepath);

//end() representa la posicion posterior al ultimo elemento.
//Si find() devuelve otra posicion, encontro la textura.
    if(it != m_textures.end()){
        SDL_Log("[ResourceManager] Reutilizando: %s",
        filepath.c_str());

        //get() devuelve el puntero SDL_Texture*.
        //La propiedad sigue perteneciendo al unique_ptr
        return it->second.get();
    }
//Antes de cargar, verificamos que exista un renderer.
    if(m_renderer == nullptr){
        SDL_Log("[ResourceManager] Error: renderer nulo");
        return nullptr;
    }


//Cargamos la imagen desde el disco a la RAM.
//IMG_Load devuelve un puntero a SDL_Surface.
    SDL_Surface* surface = IMG_Load(filepath.c_str());

//Verificamos que la superficie se haya encontrado correctamente
    if (surface == nullptr){
        SDL_Log("[ResourceManager] Error al cargar %s: %s",
        filepath.c_str(), SDL_GetError());

        return nullptr;
    }

//Guardamos el ancho y alto antes de liberar la superficie.
    int width = surface->w;
    int height = surface->h;


//Creamos una textura a partir de la superficie.
SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

//La superficie ya no es necesaria despues de crear la textura,
//Asi que liberamos su memoria de inmediato.
SDL_DestroySurface(surface);
//Verificamos que la textura se haya encontrado correctamente.
if(texture == nullptr){
    SDL_Log("[ResourceManager] Error al crear textura %s: %s",
    filepath.c_str(), SDL_GetError());

return nullptr;
}
//Guardamos la textura en la cache.
auto result = m_textures.emplace(
    filepath, 
    TexturePtr(texture)

);

//Mostramos la informacion sobre el recurso cargado
SDL_Log("[ResourceManager] Textura cargada: %s (%dx%d)",
filepath.c_str(), width, height);

//Devolvemos el puntero de la textura almacenada
return result.first->second.get();

}
//Comprueba si una textura ya existe dentro de la cache
bool ResourceManager::HasTexture(const std::string& filepath) const{

    //Retorna true si encuentra la ruta.
    //Retorna false si no existe
return m_textures.find(filepath) != m_textures.end();

}
//Elimina una textura especificada de la cache
bool ResourceManager::UnloadTexture(const std::string& filepath){
//Buscamos la textura que queremos eliminar
    auto it = m_textures.find(filepath);
//Si no existe, no podemos eliminarla.
    if(it == m_textures.end()){
        return false;
    }
//erase elimina el elemento del mapa.
    m_textures.erase(it);

    SDL_Log("[ResourceManager] Textura eliminada: %s",
    filepath.c_str());

    return true;
}
// Libera todas las texturas almacenadas.
void ResourceManager::Clear()
{
    // Guardamos la cantidad antes de limpiar.
    std::size_t count = m_textures.size();

    // clear elimina todos los elementos del mapa.
    // Cada TexturePtr llama a su TextureDeleter.
    m_textures.clear();

    SDL_Log("[ResourceManager] Cache limpiada: %zu texturas.",
            count);
}


