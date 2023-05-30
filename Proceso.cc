#include "Proceso.hh"

Proceso::Proceso() {
    id = 0;
    mem = 0;
    time = 0;
}

Proceso::Proceso(int id, int mem, int time) {
    this->id = id;
    this->mem = mem;
    this->time = time;
}

//Consultoras

int Proceso::get_id() const {
    return id;
}

int Proceso::get_mem() const {
    return mem;
}

int Proceso::get_time() const {
    return time;
}

//Modificadoras

void Proceso::set_time(int time) {
    this->time = time;
}
