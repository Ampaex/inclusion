![imagen_proyecto](media/images/LogoProyecto.png)

***
[English]\
_Project for subject multimedia technologies and interaction._

The inclusion app pretends to be an ultralight chat application for acting as intermediary in conversations in which multiple languages are involved, our goal is providing to users an interface completely in his native language using google translate API for translating other user messages.

***
[Español]\
_Proyecto para la asignatura tecnologías multimedia e interacción._

La aplicación inclusion pretende ser una aplicación ultraligera de chat de escritorio la cual sirva como intermediaria en conversaciones en la que intervengan varios idiomas, de esta forma, el usuario final solamente ve los mensajes en su idioma nativo, traduciendo los mensajes entre usuarios con la API de Google translate.

# Capuras

## Registro en la aplicación [Inglés/Chino]
<p align="center">
  <img src="media/Captura_intro.png">
</p>


## Aplicación de chat [Inglés/Chino]
<p align="center">
  <img src="media/Captura_app.png">
</p>

# Tecnologías
* Interfaz elaborada con la librería Qt.
* API de Google Translate para traducción de mensajes.
* Programado en C++ con la tecnología de sockets para la comunicación

# A destacar
* El servidor ha sido realizado prácticamente de cero utilizando para la comunicación las librerías de sockets para C++ y un formato propio de intercambio de mensajes, esto lo hace muy eficiente.
* Usa multithreading para aprovechar al máximo el procesador del servidor.
* La aplicación en Qt tiene la posibilidad de cargar traducciones nuevas para la interfaz y añadir nuevos idiomas fácilmente en la programación.
* Tanto el servidor como el cliente no ocupan más de 1.2MB.

_Autores: Liu Yfei, Jhohan Herrera, Ernesto Aranda, Antonio Vázquez._
