/** @file Area_espera.hh
    @brief Especificación de la clase area_espera
*/

#ifndef AREA_ESPERA_HH
#define AREA_ESPERA_HH
#include "Proceso.hh"
#ifndef NO_DIAGRAM     
#include "Cluster.hh"
#include <queue>
#endif  

using namespace std;

/** @class Area_espera
    @brief Representa un área de espera.

    Un área de espera tiene un mapa de prioridades y contenidos Prioridad_cont dónde hay una cola de procesos, el número de rechazados y el número de aceptados de cada prioridad.
*/
class Area_espera {
private:
    /** @brief Estructura de datos que se encuentra en cada prioridad y que contiene la cola de procesos, el número de aceptados y el número de rechazados de la prioridad hasta el momento */
    struct Prioridad_cont {
        /** @brief Cola de procesos ordenados por orden de inserción */
        queue<Proceso> cola_procesos;
        /** @brief Número de procesos rechazados al enviarlos al clúster de la prioridad */
        int num_rechazados;
        /** @brief Número de procesos enviados satisfactoriamente al clúster de la prioridad */
        int num_aceptados;
    };
    /** @brief  Estructura dónde para cada prioridad hay su respectiva lista de procesos */
    map<string,  Prioridad_cont> espera;

    //Consultores

    /** @brief Consulta si existe un proceso de nombre id en la cola de procesos de la prioridad apuntada por it
 
        \pre: <em>cierto</em>
        \post: Si existe se devuelve true. Sino false
        \coste constante
    */
    bool existe_proceso(int id, map<string, Prioridad_cont>::iterator it) const;
public:
    //Constructoras
    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un área de espera
      \pre <em>cierto</em>
      \post El resultado es un área de espera vacía
      \coste constante
  */  
    Area_espera();

    //Modificadores

    /** @brief Crea una prioridad vacía en el área de espera
 
        Si identificador existe, se imprime mensaje de error.
        \pre: <em>cierto</em>
        \post: prioridad añadida al área de espera.
        \coste log(n) siendo n el número de prioridades
    */
    void alta_prioridad(string prioridad);

    /** @brief Elimina una prioridad del área de espera
     *
     *  Si identificador no existe o tiene procesos pendientes, se imprime mensaje de error.
        \pre: <em>cierto</em>
        \post: prioridad eliminada del área de espera.
        \coste log(n) siendo n el número de prioridades, logarítmico
    */
    void baja_prioridad(string prioridad);

    /** @brief Añade un proceso a la cola de espera de una prioridad
     * 
     *  Si identificador no existe o tiene procesos pendientes, se imprime mensaje de error.
        \pre: <em>cierto</em>
        \post: proceso añadido a la cola de espera de la prioridad.
        \coste log(n) siendo n el número de prioridades, logarítmico
    */
    void alta_proceso_espera(Proceso proc, string prioridad);


    /** @brief Envía procesos de la sala de espera al clúster hasta que n procesos hayan sido colocados
    * 
    * Se intentan enviar los procesos al clúster por orden de prioridad y dentro de éste por antiguedad. La función finaliza cuando se han colocado, no quedan procesos pendientes o han sido rechazados. Si se rechaza vuelve al área de espera como el más reciente.
    \pre n >= 0
    \post n procesos se han colocado en el clúster
    \coste n * log(n) siendo n el número de prioridades, logarítmico * constante
    */
    void enviar_procesos_cluster(int n, Cluster& c);

    //escritura

    /** @brief Imprime los procesos pendientes de la prioridad
     *  
     * Se imprimen en orden decreciente de antiguedad desde su última alta. También escribe el número de procesos de la prioridad colocados en el clúster y el número de rechazos. Si no existe prioridad, se imprime mensaje de error.
        \pre: <em>cierto</em>
        \post: Se han impreso procesos de la prioridad pendientes, colocados y rechazados.
        \coste log(n) siendo n el número de prioridades para hacer la búsqueda, logarítmico
     */
    void imprimir_prioridad(const string& prioridad) const;
    
    /** @brief Operación de escritura
     * 
     * Se imprimen los procesos pendientes de todas las prioridades por orden creciente de prioridad. Para cada prioridad se imprime el número de procesos de la prioridad colocados en el clúster y el número de rechazados.
        \pre: <em>cierto</em>
        \post: Se han impreso los procesos de todas las prioridades pendientes, el número de colocados y rechazados.
        \coste n * log(n) siendo n el número de prioridades, logarítmico * constante
     */
    void imprimir_area_espera() const;

};

#endif