/**
 * @mainpage Práctica PRO2. Simulador de un cluster de procesadores multiproceso.
 * 
    @file program.cc
    @brief Programa principal de la práctica <em>Simulador de un cluster de procesadores multiproceso</em>.
*/

// para que el diagrama modular quede bien se han escrito includes redundantes;
// en los ficheros .hh de la documentación de las clases ocurre lo mismo.
#include "Proceso.hh"
#include "Cluster.hh"
#include "Procesador.hh"
#include "Area_espera.hh"
#ifndef NO_DIAGRAM 
#include <iostream>
#include "BinTree.hh"
#endif

using namespace std;

int main() {
    string comando, prioridad;
    Cluster c;
    c.configurar_cluster();
    Area_espera a;
    int n;
    cin >> n;
    for (int i = 0; i  < n; ++i) {
        cin >> prioridad;
        a.alta_prioridad(prioridad);
    }
    while (comando != "fin") {
        if (comando == "cc" or comando == "configurar_cluster") {
            cout << '#' << comando << endl;
            c.configurar_cluster();
        }
        else if (comando == "mc" or comando == "modificar_cluster") {
            string idprocesador;
            cin >> idprocesador;
            cout << '#' << comando << ' ' << idprocesador << endl;
            c.modificar_cluster(idprocesador);
        }
        //problemitas con modificar_cluster, si no está, entrada pasa a ser comandos creo
        else if (comando == "epc" or comando == "enviar_procesos_cluster") {
            int n;
            cin >> n;
            cout << '#' << comando << ' ' << n << endl;
            a.enviar_procesos_cluster(n, c);
        }
        else if (comando == "at" or comando == "avanzar_tiempo") {
            int t;
            cin >> t;
            cout << '#' << comando << ' ' << t << endl;
            c.avanzar_tiempo(t);
        }
        else if (comando == "ipc" or comando == "imprimir_procesadores_cluster") {
            cout << '#' << comando << endl;
            c.imprimir_procesadores_cluster();
        }
        else if (comando == "iec" or comando == "imprimir_estructura_cluster") {
            cout << '#' << comando << endl;
            c.imprimir_estructura_cluster(c.get_cluster_tree());
            cout << endl;
        }
        else if (comando == "cmp" or comando == "compactar_memoria_procesador") {
            string idprocesador;
            cin >> idprocesador;
            cout << '#' << comando << ' ' << idprocesador << endl;
            c.compactar_memoria_procesador(idprocesador);
        }
        else if (comando == "cmc" or comando == "compactar_memoria_cluster") {
            cout << '#' << comando << endl;
            c.compactar_memoria_cluster();
        }
        else if (comando == "ap" or comando == "alta_prioridad") {
            cin >> prioridad;
            cout << '#' << comando << ' ' << prioridad << endl;
            a.alta_prioridad(prioridad);
        }
        else if (comando == "bp" or comando == "baja_prioridad") {
            cin >> prioridad;
            cout << '#' << comando << ' ' << prioridad << endl;
            a.baja_prioridad(prioridad);
        }
        else if (comando == "ape" or comando == "alta_proceso_espera") {
            int identif, tiempo, mem;
            cin >> prioridad;
            cin >> identif >> mem >> tiempo;
            cout << '#' << comando << ' ' << prioridad << ' ' << identif << endl;
            Proceso proc(identif, mem, tiempo);
            a.alta_proceso_espera(proc, prioridad);
        }
        else if (comando == "ipri" or comando == "imprimir_prioridad") {
            cin >> prioridad;
            cout << '#' << comando << ' ' << prioridad << endl;
            a.imprimir_prioridad(prioridad);
        }
        else if (comando == "iae" or comando == "imprimir_area_espera") {
            cout << '#' << comando << endl;
            a.imprimir_area_espera();
        }
        else if (comando == "app" or comando == "alta_proceso_procesador") {
            int idproceso, mem, tiempo;
            string idprocesador;
            cin >> idprocesador;
            cin >> idproceso >> mem >> tiempo;
            cout << '#' << comando << ' ' << idprocesador << ' ' << idproceso << endl;;
            Proceso proc(idproceso, mem, tiempo);
            c.alta_proceso_procesador(idprocesador, proc);
        }
        else if (comando == "bpp" or comando == "baja_proceso_procesador") {
            int id_proceso;
            string idprocesador;
            cin >> idprocesador;
            cin >> id_proceso;
            cout << '#' << comando << ' ' << idprocesador << ' ' << id_proceso << endl;
            c.baja_proceso_procesador(idprocesador, id_proceso);
        }
        else if (comando == "ipro" or comando == "imprimir_procesador") {
            string idprocesador;
            cin >> idprocesador;
            cout << '#' << comando << ' ' << idprocesador << endl;
            c.imprimir_procesador(idprocesador);
        }
        cin >> comando;
    }
}
