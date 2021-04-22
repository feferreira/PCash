#ifndef CORRETORA_H
#define CORRETORA_H
#include "data.h"
#include <map>

class PgConnection;
class QString;

class Corretora : public Data
{

public:
    bool getListaCorretora();
    std::map<QString,int> listaCorretora;

};

#endif // CORRETORA_H
