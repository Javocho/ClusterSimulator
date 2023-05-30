/** @file  Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH
#include "Procesador.hh"
#include "Proceso.hh"
#ifndef NO_DIAGRAM      
#include "BinTree.hh"
#endif  

/** @class Cluster
    @brief Representa un clúster de procesadores.

    Un clúster tiene un árbol de nombres de procesadores y un mapa de los nombres y el procesador.
*/
class Cluster {
    private:
        /** @brief Estructura arborescente de los procesadores del clúster */
        BinTree<string> cluster_tree;
        /** @brief Estructura donde se guardan los datos de cada procesador del clúster */
        map<string, Procesador> cluster_map;

        /** @brief Operación de lectura
         * Funcion recursiva que permite la entrada inicial de los datos para configurar el cluster dejando tantos nodos en el árbol como se inserten con los repectivos nombres y una memoria para cada procesador.
         * 
         * Los nombres se colocarán en preorden dentro del árbol a y el tamaño estará dentro de cada procesador del mapa cluster_map siendo la clave el propio nombre.
            \pre <em>La entrada contiene pares de nombre sin repeticiones y tamaño de cada procesador mayor a cero </em>
            \post se han colocado los datos en el árbol a y en el mapa de procesadores del clúster
            \coste Lineal respecto al número de procesadores
        */
        void i_configurar_cluster(BinTree<string>& a);

        /** @brief Operación de lectura para modificar el árbol de procesadores del clúster
         * Función recursiva que permite la entrada de datos para modificar el cluster dejando si el procesador id no tiene procesadores auxiliares, el nuevo árbol en t a partir del nodo identificador 
            \pre <em>La entrada contiene un identifipares de nombre sin repeticiones y tamaño de cada procesador mayor a cero</em>
            \post se ha modificado el árbol del clúster desde id
            \coste Lineal respecto al número de procesadores
        */
        void i_modificar_cluster(string& id, BinTree<string>& proc);

        /** @brief Función recursiva que recorre el árbol de procesadores en preorden para consultar el mejor procesador donde enviar el proceso del área de espera al clúster siguiendo el criterio establecido.
         * 
         * El criterio es el siguiente: se elige el hueco más ajustado para la memoria del proceso, si hay dos iguales se elige el procesador con más memoria libre, si tienen la misma el que esté en un nodo más alejado de la raíz y si empatan, el que esté más a la izquierda.
            \pre <em>cierto</em>
            \post Si hay un procesador adecuado para el proceso proc, hay_adecuado es cierto e id contiene el nombre del procesador. Sino hay_adecuado es falso.
            \coste logarítmico
        */
        void i_procesador_adecuado(const Proceso &proc, string& id, int& ajustado, bool& hay_adecuado, const BinTree<string>& a, int& maxmem, int profundidad, int& mejor_prof) const;
        
    public:
        //Constructoras

        /** @brief Creadora por defecto. 
            Se ejecuta automáticamente al declarar un cluster
            \pre <em>cierto</em>
            \post El resultado es un clúster vacío
            \coste constante
        */  
        Cluster();

        //Consultores
        
        /** @brief Consulta si existe un procesador con identificador id en el clúster
            \pre <em>cierto</em>
            \post Se devuelve true si existe un procesador con identificador id en el clúster y false en caso contrario
            \coste logarítmico
        */
        bool existe_procesador(const string& id) const;

        /** @brief Devuelve el árbol del cúster
            \pre <em>cierto</em>
            \post Devuelve el árbol cluster_tree del clúster
            \coste constante
        */
        BinTree<string> get_cluster_tree() const;

        //Modificadores

        /** @brief Configura el cluster
         * 
         * Si existía un clúster anterior, deja de existir. Se garantiza que los identificadores de procesadores no se repiten.
         * 
         * Si había procesadores anteriores se elminan y en el árbol del clúster se colocan los nombres de procesador insertados
            \pre <em>cierto</em>
            \post El cluster se configura con el árbol de procesadores cluster_tree
            \coste lineal
        */
        void configurar_cluster();
        
        /** @brief Modifica el cluster
         * 
         * Si p no es un identificador de procesador, tiene procesos en ejecución o tiene procesadores auxiliares, se imprime un mensaje de error. Se garantiza que no habrá repetición de identificadores de procesadores.
            \pre <em>La entrada contiene pares de nombre sin repeticiones y tamaño de cada procesador </em>
            \post el nuevo árbol se coloca en el lugar del nodo del procesador con identificador id
            \coste lineal
        */

        void modificar_cluster(string& id);

        /** @brief Añade un proceso al procesador id
            \pre <em>cierto</em>
            \post El proceso se añade al mapa de procesos del procesador id
            \coste logarítmico
        */  
        void alta_proceso_procesador(const string& id, const Proceso& proc);

        /** @brief Elimina un proceso id_proceso del procesador id_procesador.  Si no existe el procesador o el proceso no está en el procesador, se imprime un mensaje de error.
            \pre <em>cierto</em>
            \post El proceso se elimina del mapa de procesos del procesador id_procesador
            \coste logarítmico
        */  
        void baja_proceso_procesador(const string& id_procesador, int id_proceso);

        /** @brief Avanza el tiempo
         * 
         * El parámetro implicito "time" de los procesadores avanza "t" y se ejecutan los procesos con un tiempo de ejecución menor a time
            \pre t > 0 
            \post El tiempo ha avanzado en t unidades
            \coste lineal respecto al número de procesadores
        */
        void avanzar_tiempo(int time);

        /** @brief Compacta la memoria del procesador
         * 
         * Compacta la memoria del procesador con identificador id moviendo los procesos al principio de la memoria del procesador, sin dejar huecos respetando el orden inicial.
            \pre <em>cierto</em>
            \post Se ha compactado la memoria del procesador
            \coste logarítmico
        */
        void compactar_memoria_procesador(const string& id);
    

        /** @brief Compacta la memoria del cluster
         * 
         * Compacta la memoria de todos los procesadores del cluster moviendo los procesos al principio de la memoria del procesador, sin dejar huecos respetando el orden inicial.
            \pre <em>cierto</em>
            \post Se ha compactado la memoria de los procesadores del cluster
            \coste llogarítmico * n siendo n el número de procesadores
        */
        void compactar_memoria_cluster();

        /** @brief Función que recorre el árbol cluster_tree de procesadores en preorden para decidir el mejor procesador para enviar el proceso del área de espera al clúster siguiendo el criterio establecido a través de la inmersión.
         * 
            \pre <em>cierto</em>
            \post Si hay un procesador adecuado para el proceso proc, hay_adecuado es cierto e id contiene el nombre del procesador. Sino hay_adecuado es falso.
            \coste lineal respecto a la llamada a función logarítmica
        */
        void procesador_adecuado(const Proceso& proc, string& id, bool& hay_adecuado) const;

        /** @brief Si se ha podido encontrar un procesador adecuado en el clúster para el proceso proc, se envía y se devuelve true. Sino se devuelve false.
         * 
            \pre <em>cierto</em>
            \post Si hay un procesador adecuado, se envía el proceso y devuelve true. Sino devuelve false
            \coste logarítmico
        */
        bool proceso_enviado(const Proceso& Proc, bool& colocado);
      

        //escritura

        /** @brief Imprime los procesadores del cluster
         * 
         * Escribe los procesadores por orden de identificador. Para cada uno se escriben sus procesos por orden de posición de memoria y los datos de cada proceso.
            \pre <em>cierto</em>
            \post Se han impreso los procesadores del cluster
            \coste lineal respecto al número de procesadores
        */
        void imprimir_procesadores_cluster() const;
        

        /** @brief Imprime los procesos del procesador y en cada uno, el tiempo para acabe de ejecutarse. 
            \pre <em>cierto</em>
            \post Se han impreso el procesador
            \coste logarítmico (al usar find)
        */
        void imprimir_procesador(const string& id) const;

        /** @brief Imprime la estructura del cluster.
         * 
            \pre <em>cierto</em>
            \post Se ha impreso la estructura del cluster
            \coste logarítmico (al usar find)
        */
        static void imprimir_estructura_cluster(const BinTree<string>& a);

};

#endif