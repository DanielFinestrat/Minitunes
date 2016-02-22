# Minitunes

Programa en C++ que permite crear una biblioteca de música online, manejar playlists y reproducirlas en streaming usando mplayer. 

___
Imprescindible tener mplayer instalado. Si usas Ubuntu puedes instalarlo de la siguietne manera:

```sudo apt-get install mplayer```
___
Para acceder rapido a sus funciones podemos ejecutarlo siguiendo la siguiente sintaxis 

```Syntax: ./minitunes [-d] [-i jsonfilename].```

[-d] cargará la collection y playlist almacenada en el fichero minitunes.dat y [-i jsonfilename] analizará el json que introduzcas.
___
Para usar la importación de previews desde iTunes usar un wget de la sigueinte manera:

```wget itunes.apple.com/search?term="[TERMINO DE BUSQUEDA]" -q -O [NOMBRE DEL FICHERO]```

Por ejemplo: 

```wget itunes.apple.com/search?term="Ninja Sex Party" -q -O NinjaSexParty.txt```
___


[Daniel Finestrat Martínez 2014.](https://garagefruit.com)
