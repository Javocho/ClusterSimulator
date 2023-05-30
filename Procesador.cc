#include "Procesador.hh"

//constructoras

Procesador::Procesador() {
}

Procesador::Procesador(int mem) {
    mem_libre = mem;
    memtotal = mem;
    huecos.insert(make_pair(mem, 0));
}

//Consultoras

int Procesador::get_mem_libre() const {
    return mem_libre;
}

bool Procesador::existe_proceso(int id) const {
    return posicion.find(id) != posicion.end();
}

bool Procesador::hay_procesos() const {
    if (procesos.empty()) return false;
    return true;
}

//Modificadores

void Procesador::alta_proceso(const Proceso& proc) {
    if (mem_libre < proc.get_mem()) cout << "error: no cabe proceso" << endl;
    else if (posicion.find(proc.get_id()) != posicion.end()) cout << "error: ya existe proceso" << endl;
    else {
        set<pair<int, int>, ComparePairs>::iterator it = huecos.begin();
        it = huecos.lower_bound(make_pair(proc.get_mem(), 0));
        if (it == huecos.end()) cout << "error: no cabe proceso" << endl;
        else if (it != huecos.end()) {
            int mem_aux = it->first;
            int pos_aux = it->second;
            huecos.erase(it);
            if (mem_aux > proc.get_mem()) {
                huecos.insert(make_pair(mem_aux - proc.get_mem(), pos_aux + proc.get_mem())); //se inserta hueco del tamaño de la memoria restante del hueco escogido para del proceso que comienza donde acaba el proceso
                posicion.insert(make_pair(proc.get_id(), pos_aux));
            }
            else posicion.insert(make_pair(proc.get_id(), pos_aux));
            mem_libre -= proc.get_mem();
            procesos.insert(make_pair(pos_aux, proc));
        }
    }
}

void Procesador::baja_proceso(int id) {
    map<int,int>::iterator it = posicion.find(id);
    if (it == posicion.end()) cout << "error: no existe proceso" << endl;
    map<int, Proceso>::iterator it2 = procesos.find(it->second);
    int pos = it->second;
    int pos_final = it->second;
    int espacio_que_añadir = it2->second.get_mem();
    int peso_hueco;
    int pos_hueco;
    bool anterior = hay_hueco_arriba(pos, peso_hueco, pos_hueco);
    if (anterior) {
        espacio_que_añadir += peso_hueco;
        pos_final = pos_hueco;
    }
    peso_hueco = 0;
    bool posterior = hay_hueco_abajo(pos, peso_hueco, pos_hueco);
    if (posterior) {
        espacio_que_añadir += peso_hueco;
    }
    if (espacio_que_añadir  != 0) huecos.insert(make_pair(espacio_que_añadir, pos_final));
    mem_libre += it2->second.get_mem();
    posicion.erase(it);
    procesos.erase(it2);
}

void Procesador::avanzar_tiempo(int time) {
    if (not procesos.empty()) {
        map<int, Proceso>::iterator it = procesos.begin();
        while (it != procesos.end()) {
            int id = it->second.get_id();
            it->second.set_time(it->second.get_time() - time);
            if (it->second.get_time() <= 0) {
                ++it;
                baja_proceso(id);
            }
            else ++it;
        }
    }
}

void Procesador::compactar_memoria() {
    if (not procesos.empty()) {
        map<int, Proceso>::iterator it = procesos.begin();
        map<int, int>::iterator it2;
        int pos = 0;
        int pes = 0;
        huecos.clear(); //vacío el set de huecos
        while (it != procesos.end()) {
            pes = it->second.get_mem();
            if (it->first != pos) { //recoloco procesos
                it2 = posicion.find(it->second.get_id());
                it2->second = pos;
                Proceso aux = it->second;
                it = procesos.erase(it);
                procesos.insert(make_pair(pos, aux));
            }
            else ++it;
            pos += pes;
        }
        --it;
        int poshueco = it->first + it->second.get_mem();
        if (poshueco != memtotal) {
            huecos.insert(make_pair(mem_libre, poshueco)); //coloco el hueco restante al final
        }
    }
}

//escritura

void Procesador::imprimir() const {
    map<int, Proceso>::const_iterator it = procesos.begin();
    while (it != procesos.end()) {
        cout << it->first << ' ' << it->second.get_id() << " " << it->second.get_mem() << " " << it->second.get_time() << endl;
        ++it;
    }
}

//funciones auxiliares

bool Procesador::hay_hueco_arriba(int pos, int& peso_hueco, int& pos_hueco) {
    map<int, Proceso>::iterator it = procesos.find(pos);
    if (it != procesos.begin()) {
        --it;
        int pos_nueva = it->first;
        int peso_nuevo = it->second.get_mem();
        if (peso_nuevo + pos_nueva == pos) return false; //proceso seguido del anterior (no hay hueco)
        else {
            peso_hueco = pos - (pos_nueva + peso_nuevo);  //posición inicial proceso - posición final proceso anterior será el tamaño del hueco
            pos_hueco = pos_nueva + peso_nuevo;
            set<pair<int, int>, ComparePairs>::iterator it2 = huecos.find(make_pair(peso_hueco, pos_hueco));
            huecos.erase(it2); //elimina hueco superior al proceso
            return true;
        }
    }

    else {
        if (it->first == 0) return false;
        else { //no empieza en cero y es el primer proceso quiere decir que hay hueco arriba del proceso
            peso_hueco = it->first;
            pos_hueco = 0;
            set<pair<int, int>, ComparePairs>::iterator it2 = huecos.find(make_pair(peso_hueco, pos_hueco));
            huecos.erase(it2);
            return true;
        }
    }
    peso_hueco = it->first;
 }

 bool Procesador::hay_hueco_abajo(int pos, int& peso_hueco, int& pos_hueco) {
    map<int, Proceso>::iterator it = procesos.find(pos);
    int peso = it->second.get_mem();
    ++it;
    if (it != procesos.end()) {
        if (pos + peso == it->first) return false; //si posición final del proceso es igual a la posición inicial del siguiente proceso quiere decir que no hay hueco debajo 
        else {
            peso_hueco = it->first - (pos + peso); //posición inicial siguiente proceso - posición final proceso será el tamaño del hueco
            pos_hueco = pos + peso;
            set<pair<int, int>, ComparePairs>::iterator it2 = huecos.find(make_pair(peso_hueco, pos_hueco));
            huecos.erase(it2);
            return true;
        } 
    }
    else {
        if (pos + peso == memtotal) return false;
        else { //si posición final del proceso es distinta a la memoria total quiere decir que hay hueco abajo 
            pos_hueco = pos + peso;
            peso_hueco = memtotal - pos_hueco;
            set<pair<int, int>, ComparePairs>::iterator it2 = huecos.find(make_pair(peso_hueco, pos_hueco)); 
            huecos.erase(it2);
            return true;
        }
    }
 }

int Procesador::hueco_ajustado(int mem) const {
    if (mem > mem_libre) return 0;
    set<pair<int, int>, ComparePairs>::const_iterator it = huecos.lower_bound(make_pair(mem, 0)); //menor hueco mayor o igual que mem, sino huecos.end()
    if (it == huecos.end()) return 0;
    return it->first;
}
