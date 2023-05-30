#include "Area_espera.hh"
#include "Cluster.hh"
#include "Area_espera.hh"

Area_espera::Area_espera() {
    map<string,  Prioridad_cont>::iterator it = espera.begin();
    while (it != espera.end()) {
        it->second.num_rechazados = 0;
        it->second.num_aceptados = 0;
        ++it;
    }
}

bool Area_espera::existe_proceso(int id, map<string, Prioridad_cont>::iterator it) const {
    bool existe = false;
    queue<Proceso> aux = it->second.cola_procesos;
    while (not aux.empty() and not existe) {
        Proceso proc = aux.front();
        if (proc.get_id() == id) existe = true;
        aux.pop();
    }
    return existe;
}

void Area_espera::alta_prioridad(string prioridad) {
    if (espera.find(prioridad) != espera.end()) cout << "error: ya existe prioridad" << endl;
    else {
        Prioridad_cont aux;
        aux.num_aceptados = 0;
        aux.num_rechazados = 0;
        espera.insert(make_pair(prioridad, aux));
    }
}

void Area_espera::baja_prioridad(string prioridad) {
    map<string, Prioridad_cont >::iterator it = espera.find(prioridad);
    if (it == espera.end()) cout << "error: no existe prioridad" << endl;
    else if (not it->second.cola_procesos.empty()) cout << "error: prioridad con procesos" << endl;
    else espera.erase(it);
}

void Area_espera::alta_proceso_espera(Proceso proc, string prioridad) {
    const map<string, Prioridad_cont>::iterator& it = espera.find(prioridad);
    if (it == espera.end()) cout << "error: no existe prioridad" << endl;
    else if (existe_proceso(proc.get_id(), it)) cout << "error: ya existe proceso" << endl;
    else it->second.cola_procesos.push(proc);
}

void Area_espera::enviar_procesos_cluster(int n, Cluster& c) {
    //que pasa si hueco que le va mejor ese procesador ya tiene proceso con nombre
    map<string, Prioridad_cont>::iterator it = espera.begin();
    int n_colocados = 0;
    queue<Proceso> aux;
    while (n_colocados < n and it != espera.end()) {
        if (it->second.cola_procesos.empty()) { //si no quedan procesos en la prioridad y ha habido procesos rechazados se vuelven a insertar en la cola 
            it->second.cola_procesos = aux;
            ++it;
            while (not aux.empty()) aux.pop();
        }
        else {
            bool colocado;
            c.proceso_enviado(it->second.cola_procesos.front(), colocado);
            if (colocado) {
                it->second.cola_procesos.pop();
                ++n_colocados;
                it->second.num_aceptados++;
            }
            else {
                Proceso proc = it->second.cola_procesos.front();
                it->second.cola_procesos.pop();
                aux.push(proc);
                it->second.num_rechazados++;
            }
        }
    }
    if (not aux.empty()) { //si no quedan procesos en la prioridad, no quedan prioridades y ha habido procesos rechazados se vuelven a insertar en la cola 
        if (it == espera.end()) --it;
        it->second.cola_procesos = aux;
    }
}

//escritura

void Area_espera::imprimir_prioridad(const string& prioridad) const {
    map<string, Prioridad_cont>::const_iterator it = espera.find(prioridad);
    if (it == espera.end()) {
        cout << "error: no existe prioridad" << endl;
    }
    else {
        queue<Proceso> aux = it->second.cola_procesos;
        while (not aux.empty()) {
            Proceso proc = aux.front();
            cout << proc.get_id() << ' ' << proc.get_mem() << ' ' << proc.get_time() << endl;
            aux.pop();
        }
        cout << it->second.num_aceptados << ' ' << it->second.num_rechazados << endl;
    }                                                                                                                           
}

void Area_espera::imprimir_area_espera() const {
    map<string, Prioridad_cont>::const_iterator it = espera.begin();
    while (it != espera.end()) {
        cout << it->first << endl;
        imprimir_prioridad(it->first);
        ++it;
    }
}
