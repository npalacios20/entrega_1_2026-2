INSTRUCTIVO DEL JUEGO TRIUMPH
1. PRESENTACIÓN
Triumph es un juego de cartas dinámico para 2 o más jugadores, donde se compite por acumular la mayor cantidad de puntos a lo largo de varias rondas. 
Cada carta tiene un color y un valor numérico, y las reglas de comparación las define el jugador que inicia cada ronda.

3. ELEMENTOS DEL JUEGO

🃏 Cartas: Cada carta tiene un color y un valor (número entero).
👤 Jugadores	Mínimo 2 participantes: Cada uno cuenta con un numero de jugador asignado y una puntuación acumulada.
🔄 Rondas:	El juego se desarrolla por rondas, en cada ronda se define un ganador parcial.
🏆 Puntuación:	Se suman puntos por ronda ganada; al final se declara el ganador del Juego.
💾 Partida guardada:	El progreso se puede guardar en archivo para retomar en otro momento.

4. INICIAR EL JUEGO
   
Ejecuta el programa en C++.
Aparecerá el menú principal con estas opciones:

=== MENÚ PRINCIPAL - TRIUMPH ===
1. Iniciar partida nueva
2. Cargar partida guardada
3. Salir
   
Para partida nueva:
Ingresa la cantidad de jugadores (mínimo 2).
El juego reparte las cartas de forma equilibrada.

Para retomar partida:
Selecciona la opción 2.
El programa buscará el archivo guardado y cargará los nombres, puntuaciones y cartas pendientes.

5. DESARROLLO DE UNA RONDA
   
Paso 1: Definición del color y la regla
El jugador 1 de la ronda lanza su carta primero.
El color de su carta se convierte en el color base de la ronda.
El mismo jugador indica la regla de comparación:
+ → Gana quien tenga el valor MAYOR del mismo color
- → Gana quien tenga el valor MENOR del mismo color
  
Paso 2: Jugada de los demás participantes
En orden, cada jugador lanza su carta.
✅ Válido: si la carta es del mismo color que el color base.
❌ Inválido: si no tiene cartas del color requerido → queda fuera de la competencia de esa ronda.

Paso 3: Determinación del ganador de la ronda
Se comparan los valores de las cartas válidas según la regla (+ o -).
El ganador de la ronda recibe los puntos correspondientes.
El programa muestra: 
* Cartas jugadas por cada participante
* Quién ganó la ronda
* Puntuación actualizada de todos

Paso 4: Continuación
El turno pasa automáticamente al siguiente jugador como iniciador de la ronda siguiente.
El proceso se repite hasta que se decida finalizar la partida.

5. GUARDAR Y RETOMAR LA PARTIDA
Al finalizar cada ronda o al terminar el juego, el programa preguntará:
¿Deseas guardar la partida antes de salir? (s/n):
Si respondes s:
Se guarda el estado completo: nombres, puntuaciones, cartas restantes y ronda en curso.
Se mostrará en pantalla la ruta exacta donde quedó almacenado el archivo.
Para continuar después:
Selecciona "Cargar partida guardada" en el menú.
El sistema recupera todo desde la misma ruta.

7. FINALIZACIÓN Y GANADOR
Cuando decidas terminar la partida, se suman todos los puntos acumulados.
Se declara el Ganador del Juego al jugador con la puntuación más alta.
En caso de empate, se indica expresamente en pantalla.
Puedes guardar el resultado final antes de cerrar el programa.

9. REGLAS IMPORTANTES
* No se puede jugar con menos de 2 jugadores.
* Solo las cartas del color base participan para ganar la ronda.
* La regla + y - la define quien inicia la ronda.
* Cada jugador lanza su carta y el turno pasa automáticamente al siguiente.
* Los puntos se acumulan ronda tras ronda.
* Si no hay cartas del color requerido, el jugador no compite en esa ronda.
* Al ingresar -1, el jugador confirma que pasa esta ronda y no compite por puntos en ella.
  
