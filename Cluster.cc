#include "Cluster.hh"

using namespace std;

Cluster::Cluster() {
    cluster_tree = BinTree<string>();
    cluster_map = map<string, Procesador>();
}

//consultores

bool Cluster::existe_procesador(const string& id) const {
    map<string, Procesador>::const_iterator it = cluster_map.find(id);
    return it != cluster_map.end();
}

BinTree<string> Cluster::get_cluster_tree() const {
    return cluster_tree;
}

//modificadores

void Cluster::i_configurar_cluster(BinTree<string>& a) {
    string s;
    int tam;
    BinTree<string> al, ar;
    cin >> s;
    if (s != "*") {
        cin >> tam;
        Procesador p(tam);
        i_configurar_cluster(al);
        i_configurar_cluster(ar);
        BinTree<string> b(s, al, ar);
        cluster_map.insert(make_pair(s, p));
        a = b;
    }
}

void Cluster::configurar_cluster() {
    cluster_map.clear();
    i_configurar_cluster(cluster_tree);
}

void Cluster::i_modificar_cluster(string& identificador, BinTree<string>& t) {
    if (not t.empty()) {
        if (t.value() != identificador) {
            BinTree<string> l = t.left();
            BinTree<string> r = t.right();

            i_modificar_cluster(identificador, l);
            i_modificar_cluster(identificador, r);

            t = BinTree<string>(t.value(), l, r);
        }

        else if (t.left().empty() and t.right().empty()) {
            map<string, Procesador>::iterator it = cluster_map.find(identificador);
            cluster_map.erase(it);

            i_configurar_cluster(t);
        }

        else {
            BinTree<string> l = t.left();
            BinTree<string> r = t.right();

            i_modificar_cluster(identificador, l);
            i_modificar_cluster(identificador, r);

            t = BinTree<string>(t.value(), l, r);

            //por si no se puede hacer modificar_cluster pero queremos descartar entrada de árbol para que no lo trate como comandos
            cout << "error: procesador con auxiliares" << endl;
        }
    }
}

void Cluster::modificar_cluster(string &identificador)
{
    map<string, Procesador>::iterator it = cluster_map.find(identificador);

    if (it == cluster_map.end())
    {
        cout << "error: no existe procesador" << endl;
    }

    else if (it->second.hay_procesos() != 0)
    {
        cout << "error: procesador con procesos" << endl;
    }

    else
    {
        i_modificar_cluster(identificador, cluster_tree);
    }
}

void Cluster::alta_proceso_procesador(const string& id, const Proceso& proc) {
    if (not existe_procesador(id)) cout << "error: no existe procesador" << endl;
    else {
        map<string, Procesador>::iterator it = cluster_map.find(id);
        if (it->second.existe_proceso(proc.get_id())) cout << "error: ya existe proceso" << endl;
        else if (it->second.get_mem_libre() < proc.get_mem()) cout << "error: no cabe proceso" << endl;
        else {
            it->second.alta_proceso(proc);
        }
    }
}

void Cluster::baja_proceso_procesador(const string& id_procesador, int id_proceso) {
    if (not existe_procesador(id_procesador)) cout << "error: no existe procesador" << endl;
    else {
        map<string, Procesador>::iterator it = cluster_map.find(id_procesador);
        map<int, Proceso>::iterator it2;
        if (not it->second.existe_proceso(id_proceso)) cout << "error: no existe proceso" << endl;
        else it->second.baja_proceso(id_proceso);
    }
}

void Cluster::avanzar_tiempo(int time) {
    for (map<string, Procesador>::iterator it = cluster_map.begin(); it != cluster_map.end(); ++it) {
        it->second.avanzar_tiempo(time);
    }
}

void Cluster::compactar_memoria_procesador(const string& id) {
    if (not existe_procesador(id)) cout << "error: no existe procesador" << endl;
    else {
        map<string, Procesador>::iterator it = cluster_map.find(id);
        it->second.compactar_memoria();
    }
}

void Cluster::compactar_memoria_cluster() {
    map<string, Procesador>::iterator it = cluster_map.begin();
    while (it != cluster_map.end()) {
        it->second.compactar_memoria();
        ++it;
    }
}

void Cluster::procesador_adecuado(const Proceso& proc, string& id, bool& hay_adecuado) const {
    int profundidad = 0;
    int mejor_prof = 0;
    int ajustado = -1;
    int maxmem = 0;
    hay_adecuado = false;
    i_procesador_adecuado(proc, id, ajustado, hay_adecuado, cluster_tree, maxmem, profundidad, mejor_prof);
}

void Cluster::i_procesador_adecuado(const Proceso &proc, string& id, int& ajustado, bool& hay_adecuado, const BinTree<string>& a, int& maxmem, int profundidad, int& mejor_prof) const {
    map<string, Procesador>::const_iterator it = cluster_map.find(a.value());
    int hueco = 0;
    if (it != cluster_map.end())
        hueco = it->second.hueco_ajustado(proc.get_mem());
    if (!it->second.existe_proceso(proc.get_id()))
    {
        if (hueco != 0)
        { 
            if (hueco < ajustado or ajustado == -1)
            {
                ajustado = hueco;
                maxmem = it->second.get_mem_libre();
                mejor_prof = profundidad;
                id = it->first;
                hay_adecuado = true;
            }
            else if (hueco == ajustado)
            {
                if (it->second.get_mem_libre() > maxmem)
                {
                    maxmem = it->second.get_mem_libre();
                    mejor_prof = profundidad;
                    id = it->first;
                    hay_adecuado = true;
                }
                else if (it->second.get_mem_libre() == maxmem)
                {
                    if (profundidad < mejor_prof)
                    {
                        mejor_prof = profundidad;
                        id = it->first;
                        hay_adecuado = true;
                    }
                }
            }
        }
    }

    profundidad += 1;
    if (not a.left().empty())
    {
        i_procesador_adecuado(proc, id, ajustado, hay_adecuado, a.left(), maxmem, profundidad, mejor_prof);
    }

    if (not a.right().empty())
    {
        i_procesador_adecuado(proc, id, ajustado, hay_adecuado, a.right(), maxmem, profundidad, mejor_prof);
    }
}


bool Cluster::proceso_enviado(const Proceso& proc, bool& colocado) {
    string id;
    procesador_adecuado(proc, id, colocado);
    if (not colocado) return false;
    map<string, Procesador>::iterator it = cluster_map.find(id);
    it->second.alta_proceso(proc);
    return true;
}

//escritura

void Cluster::imprimir_procesadores_cluster() const {
    for (map<string, Procesador>::const_iterator it = cluster_map.begin(); it != cluster_map.end(); ++it) {
        cout << it->first << endl;
        it->second.imprimir();
    }
}

void Cluster::imprimir_procesador(const string& id) const {
    map<string, Procesador>::const_iterator it = cluster_map.find(id);
    if (it == cluster_map.end()) cout << "error: no existe procesador" << endl;
    else it->second.imprimir();
}

void Cluster::imprimir_estructura_cluster(const BinTree<string>& a) {
    if (not a.empty()) {
        cout << '(';
        cout << a.value();
        imprimir_estructura_cluster(a.left());
        imprimir_estructura_cluster(a.right());
        cout << ')';
    }
    else cout << " ";
}

