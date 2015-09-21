#ifndef __DEFINES_H__
#define __DEFINES_H__

enum Directions {
	SOUTH_EAST = 0,
	SOUTH = 1,
	SOUTH_WEST = 2,
	WEST = 3,
	NORTH_WEST = 4,
	NORTH = 5,
	NORTH_EAST = 6,
	EAST = 7
};

//Archivo Configuracion
#define CONFIG_FILE_PATH "configuracion.yaml"
#define CONFIG_FILE_PATH_DEFAULT  "configuracionDefault.yaml"

//Pantalla Default
#define ANCHO_DEFAULT  640
#define ALTO_DEFAULT  480

//Configuracion Default
#define VELOCIDAD_PERSONAJE_DEFAULT 1
#define MARGEN_SCROLL_DEFAULT  0
#define VELOCIDAD_SCROLL_DEFAULT  0

//Escenario Default
#define ESCENARIO_DEFAULT_NOMBRE  "escenario_default"
#define ESCENARIO_DEFAULT_SIZE_X  10
#define ESCENARIO_DEFAULT_SIZE_Y  10

//Tipo Entidad Default
#define ENTIDAD_DEFAULT_NOMBRE  "entidad_default"
#define ENTIDAD_DEFAULT_IMAGEN  "resources//undefined.png"	// PONER IMG DEFAULT. TIENE Q EXISTIR
#define ENTIDAD_DEFAULT_POSX  1
#define ENTIDAD_DEFAULT_POSY  1
#define ENTIDAD_DEFAULT_ANCHO_BASE  0.5
#define ENTIDAD_DEFAULT_ALTO_BASE  0.5
#define ENTIDAD_DEFAULT_PIXEL_REF_X  30
#define ENTIDAD_DEFAULT_PIXEL_REF_Y  30
#define ENTIDAD_DEFAULT_ALTO_SPRITE  32
#define ENTIDAD_DEFAULT_ANCHO_SPRITE  64
#define ENTIDAD_DEFAULT_CANTIDAD_SPRITES  1
#define ENTIDAD_DEFAULT_FPS  0
#define ENTIDAD_DEFAULT_DELAY  0

//Protagonista Default
#define PROTAGONISTA_DEFAULT_NOMBRE "protagonista_default"
#define PROTAGONISTA_DEFAULT_IMAGEN "resources//mago.png"	// PONER IMG DEFAULT. TIENE Q EXISTIR
#define PROTAGONISTA_DEFAULT_POSX 1
#define PROTAGONISTA_DEFAULT_POSY 1
#define PROTAGONISTA_DEFAULT_ANCHO_BASE  0.5
#define PROTAGONISTA_DEFAULT_ALTO_BASE  0.5
#define PROTAGONISTA_DEFAULT_PIXEL_REF_X  30
#define PROTAGONISTA_DEFAULT_PIXEL_REF_Y  30
#define PROTAGONISTA_DEFAULT_FPS  0
#define PROTAGONISTA_DEFAULT_DELAY  0
#define PROTAGONISTA_DEFAULT_ANCHO_SPRITE  60
#define PROTAGONISTA_DEFAULT_ALTO_SPRITE  60
#define PROTAGONISTA_DEFAULT_CANTIDAD_SPRITES  5

//Terreno Default
#define TERRENO_DEFAULT_NOMBRE "terreno_default"
#define TERRENO_DEFAULT_IMAGEN "resources//pasto.png"	// PONER IMG DEFAULT. TIENE Q EXISTIR
#define TERRENO_DEFAULT_ANCHO_BASE  1
#define TERRENO_DEFAULT_ALTO_BASE  1
#define TERRENO_DEFAULT_PIXEL_REF_X  32
#define TERRENO_DEFAULT_PIXEL_REF_Y  0
#define TERRENO_DEFAULT_FPS  0
#define TERRENO_DEFAULT_DELAY  0
#define TERRENO_DEFAULT_ANCHO_SPRITE  64
#define TERRENO_DEFAULT_ALTO_SPRITE  32
#define TERRENO_DEFAULT_CANTIDAD_SPRITES  1

//Log Level
#define LOG_LEVEL_OFF  0
#define LOG_LEVEL_ERROR  1
#define LOG_LEVEL_WARNING  2
#define LOG_LEVEL_INFORMATION  3

//Tile
#define TILE_WIDTH_DEFAULT  64
#define TILE_HEIGHT_DEFAULT  32
#endif
