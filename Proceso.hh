/** @file Proceso.hh
    @brief Especificación de la clase Proceso
*/

#ifndef PROCESO_HH
#define PROCESO_HH

#ifndef NO_DIAGRAM        
#endif

using namespace std;


/** @class Proceso
    @brief Representa un proceso  

    Representa un proceso con un identificador, la cantidad de memoria estimada que va a necesitar para ejecutarse y el tiempo estimado de ejecución.
    Puede ir a un clúster directamente o a sala de espera con un string de prioridad.
*/
class Proceso {
    private:
        /** @brief Identificador del proceso */
        int id;
        /** @brief Memoria del proceso */
        int mem;
        /** @brief Tiempo necesario para ejecutar el proceso */
        int time;
    public:
        //Constructoras 

        /** @brief Creadora por defecto. 

        Se ejecuta automáticamente al declarar un proceso.
        \pre <em>cierto</em>
        \post El resultado es un proceso vacío
        \coste constante
    */   
    Proceso();

    /** @brief Creadora con valores concretos. 

    \pre id > 0, mem > 0, time > 0
    \post El resultado es un proceso con identificador "id", memoria "mem" y tiempo "time"
    \coste constante
    */   
    Proceso(int id, int mem, int time);

    //Consultoras

    /** @brief Consultora del identificador
        \pre <em>cierto</em>
        \post El resultado es el identificador del atributo privado
        \coste constante
    */
    int get_id() const;

    /** @brief Consultora de la memoria
        \pre <em>cierto</em>
        \post El resultado es la memoria del atributo privado
        \coste constante
    */
    int get_mem() const;

    /** @brief Consultora del tiempo
        \pre <em>cierto</em>
        \post El resultado es el tiempo del atributo privado
        \coste constante
    */
    int get_time() const;

    //Modificadoras

    /** @brief Modificadora del tiempo
        \pre <em>cierto</em>
        \post El atributo privado de la clase time, pasa a ser el parámetro de la función time
        \coste constante
    */
    void set_time(int time);
};

#endif