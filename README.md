# Minitunes

Programa en C++ que permite crear una biblioteca de música online, manejar playlists y reproducirlas en streaming usando mplayer. 

__
Imprescindible tener mplayer instalado. Si usas Ubuntu puedes instalarlo de la siguietne manera:

sudo apt-get install mplayer
__
__
Para acceder rapido a sus funciones podemos ejecutarlo siguiendo la siguiente sintaxis 

Syntax: ./minitunes [-d] [-i jsonfilename]. 

-d cargará la collection y playlist almacenada en elfichero minitunes.dat y -i analizará el json que introduzcas.
__
__
Para usar la importación de previews desde iTunes usar un wget de la sigueinte manera:

wget itunes.apple.com/search?term="[TERMINO DE BUSQUEDA]" -q -O [NOMBRE DEL FICHERO]

Por ejemplo: 

wget itunes.apple.com/search?term="Ninja Sex Party" -q -O NinjaSexParty.txt
__


Daniel Finestrat Martínez 2014.