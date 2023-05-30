/** @file  Procesador.hh
    @brief Especificación de la clase Procesador
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH
#include "Proceso.hh"
#ifndef NO_DIAGRAM       
#include <set>
#include <map>
#include <string>
#include <iostream>
#endif

using namespace std;


/** @class Procesador
    @brief Representa un procesador  

    Un procesador tiene una memoria, un identificador, un entero que indica la memoria que no está ocupada, un mapa de nombre de procesos y sus respectivas posiciones, otro mapa de posiciones de procesos y los respectivos procesos y un set de pares de tamaño de huecos y sus posiciones siendo un hueco, un lugar libre sin procesos.
*/
class Procesador {
    private:
        /** @brief Algoritmo de ordenación para explicitar cómo se ordena la estructura de los huecos */
        struct ComparePairs {
            bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) const {
                if (p1.first == p2.first) {
                    return p1.second < p2.second;
                }
                return p1.first < p2.first;
            }
        };
        
        /** @brief Memoria libre del procesador */
        int mem_libre;
        /** @brief Memoria total del procesador */
        int memtotal;
        /** @brief Estructura dónde para cada nombre de proceso tiene asignada la posición donde se encuentra */
        map<int, int> posicion; //nombre, posición
        /** @brief Estructura dónde para cada posición de los procesos se encuentran los datos del proceso en cuestión */
        map<int, Proceso> procesos; //posicion, proceso
        /** @brief Estructura para consultar los huecos de memoria libre del procesador dónde para cada hueco se asigna su tamaño y su posición */
        set<pair<int, int>, ComparePairs> huecos; //pair<tamaño, posición>

        //métodos privados

        /** @brief Consulta si hay un hueco encima del proceso que hay en la posición pos y se guarda la posición y el peso del hueco en los respectivos parámetros. Se elimina el hueco de arriba.
            \pre <em>cierto</em>
            \post Devuelve cierto si existe un hueco arriba de la posición pos, guardo la posición del hueco y el tamaño en peso_hueco, pos_hueco y lo elimina
            \coste log(n) siendo n el número de huecos
        */  
        bool hay_hueco_arriba(int pos, int& peso_hueco, int& pos_hueco);

        /** @brief Consulta si hay un hueco debajo del proceso que hay en la posición pos y se guarda la posición y el peso del hueco en los respectivos parámetros. Se elimina el hueco de arriba.
            \pre <em>cierto</em>
            \post Devuelve cierto si existe un hueco debajo de la posición pos, guardo la posición del hueco y el tamaño en peso_hueco, pos_hueco y lo elimina
            \coste log(n) siendo n el número de huecos
        */  
        bool hay_hueco_abajo(int pos, int& peso_hueco, int& pos_hueco);
    public:
        //Constructores

        /** @brief Creadora por defecto. 
            Se ejecuta automáticamente al declarar un procesador
            \pre <em>cierto</em>
            \post El resultado es un procesador vacío
            \coste constante
        */  
       
        Procesador();
        /** @brief Creadora con memoria concreta. 
            \pre id > 0, mem > 0
            \post El resultado es un procesador con identificador "id", memoria "mem" y sin procesos 
            \coste constante
        */  
        Procesador(int mem);

        //Consultores

        /** @brief Devuelve la memoria del procesador
            \pre <em>cierto</em>
            \post El resultado es la memoria del procesador
            \coste constante
        */  
        int get_mem_libre() const;

        /** @brief Devuelve si existe el proceso id. 
            \pre <em>cierto</em>
            \post Devuelve cierto si existe el proceso id
            \coste log(n) siendo n el número de procesos
        */  
        bool existe_proceso(int id) const;

        /** @brief Comprueba si hay procesos en el procesador.
            \pre <em>cierto</em>
            \post Devuelve cierto si hay procesos
            \coste constante
        */
        bool hay_procesos() const;

        //Modificadores

        /** @brief Añade un proceso al procesador
            \pre <em>cierto</em>
            \post El proceso se añade a los mapas de procesos del procesador
            \coste log(n) siendo n el número de huecos
        */  
        void alta_proceso(const Proceso& proc);

        /** @brief Elimina un proceso del procesador
            \pre <em>cierto</em>
            \post El proceso de nombre 'id' se elimina los mapas de procesos del procesador
            \coste log(n) siendo n el número de huecos
        */  
        void baja_proceso(int id);

        /** @brief Compacta la memoria del procesador
         * 
         * Compacta la memoria del procesador moviendo los procesos al principio de la memoria del procesador, sin dejar huecos respetando el orden inicial.
            \pre <em>cierto</em>
            \post Se ha compactado la memoria del procesador
            \coste lineal
        */
        void compactar_memoria();

        /** @brief Avanza el tiempo
         * Avanza el tiempo de cada proceso eliminando los procesos que tienen un tiempo de ejecución menor a time. 
            \pre <em>cierto</em>
            \post Se ha compactado avanzado el tiempo de cada proceso del procesador y se han descartado los procesos ya ejecutados
            \coste lineal
        */
        void avanzar_tiempo(int time);

        /** @brief Consulta y devuelve el hueco dentro del procesador para colocar un proceso de tamaño mem
            \pre <em>cierto</em>
            \post Se ha devuelto el hueco de medida más ajustada
            \coste log(n) siendo n el número de huecos
        */
        int hueco_ajustado(int mem) const;
        
       //escritura
       
        /** @brief Operación de escritura 
         * Imprime el procesador
            \pre <em>cierto</em>
            \post Se han impreso los procesos del procesador y el tiempo para que acabe de ejecutarse cada uno
            \coste lineal
        */
        void imprimir() const;
};

#endif


