**Taller 3 (redes y conectividad con grafos)** 

  Integrantes:
+ Edurado Erices
+ Cristian Nuñez

Este taller se realizó en Visual Studio Code en C++ (los siguientes comandos se ingresan por consola)...  
+ para compilar el main: **g++ -o main main.cpp**  
+ para ejecutar el codigo: **./main.exe**  

El código se raelizó a base de 2 clases; Nodo y Grafo, donde el Nodo posee como atributos id, nombre, tipo y un vector con las conexiones (pair<Nodo*,pair<velocidad,distancia>>), El Grafo posee solo un vector de Nodos o vertices del Grafo.    
Al iniciar el programa, se presenta un menú con las siguientes opciones:
1.  Mostrar Nodos
2.  Mostrar conexiones
3.  Buscar camino mas corto
4.  Salir

Cada opción tiene las siguientes funciones:  
1.  Mostrar los atributos de cada nodo o vértices del grafo
2.  Mostrar cada vértice del grafo y las aristas o conexiones de cada nodo
3.  Se ingresa la id del cliente emisor, se ingresa la id del cliente receptor y el peso del archivo a enviar y a partir de estos datos se muestra por pantalla en detalle la ruta del archivo, los segundos de demora y la efectividad del envío.
4.  No se muestra mas el menú y se finaliza la ejecución.

el objeto de este taller fue realizar un algoritmo de búsqueda del camino más corto desde un vértice hasta otro vértice del grafo. El algoritmo utilizado, es una adaptación del algoritmo de Bellman-Ford, donde además de reconocer el camino más corto, se muestra la trayectoria que se realizó para terminar el recorrido y el peso de cada arista recorrida.
