#include <memory>

#include <string>
#include <unordered_map> // Contenedor que guarda elementos mediante una clave y un valor. Lo utilizaremos como cache para almacenar las rutas de las imagenes.
#include <cstddef> // Degine std::size_t, un tipo para representar cantidades y tamanios.
#include <SDL3_image/SDL_image.h> 
#include <SDL3/SDL.h>


//Estructura encargada de liberar correctamente una textura
struct TextureDeleter{
//Este operador permite usar la estructura como una funcion
//Recibe el puntero de la textura que debe destruirse.
void operator()(SDL_Texture* texture) const noexcept{
if(texture) //Comprobamos que la textura no sea nula.
{
//SDL necesita su propio funcion para liberar texturas.
    SDL_DestroyTexture(texture);
}

}



};

//TexturePtr sera un unique_ptr que utilizara TextureDeleter
//Para liberar automaticamente las texturas.
using TexturePtr = std::unique_ptr<SDL_Texture, TextureDeleter>;

class ResourceManager //Clase encargada de administrar las texturas del videojuego.
{

    private:
    //Puntero al renderer de SDL3
    //Lo necesito para crear las texturas
    SDL_Renderer* m_renderer{nullptr};

    //Cache de Texturas
    
    std::unordered_map<std::string, TexturePtr> m_textures;


    public:
    //Constructor por defecto
//Permite crear el administrador sin pasarle un renderer.
    ResourceManager() = default;
//Constructor que recibe un renderer
//explicit evita conversiones implicitas no deseadas.
    explicit ResourceManager(SDL_Renderer* renderer);


    //Destructor de la clase.

    ~ResourceManager();

    //Cada textura debe tener un unico propietario
    ResourceManager(const ResourceManager&) = delete;
//Tambien prohibimos copiar mediante asignacion.
   ResourceManager& operator=(const ResourceManager&) = delete;

   //Permitimos mover el administrador y transferir sus recursos.
   ResourceManager(ResourceManager&&) noexcept = default;
//Permitimos la asignacion por movimiento
   ResourceManager& operator=(  ResourceManager&&) noexcept = default;

//Guarda el renderer que utilizara el administrador
void SetRenderer(SDL_Renderer* renderer){
    m_renderer = renderer;
}

//Devuelve el renderer almacenado
SDL_Renderer* GetRenderer() const{
    return m_renderer;
} 

//Busca una textura en el cache, si ya existe, devuelve la textura
//almacenada. Si no existe, intentara cargarla desde el archivo.
SDL_Texture* GetTexture(const std::string& filepath);

//Comprueba si una textura ya se encuentra en la cache
bool HasTexture(const std::string& filepath) const;
//Devuelve cuantas texturas distintas tenemos guardadas.
std::size_t GetTextureCount() const{
    return m_textures.size();
}

//Elimina una textura especificada de la cache
//Devuelve true si logro eliminarla
bool UnloadTexture(const std::string& filepath);
//Vacia toda la acache y libera sus texturas.
void Clear();

};