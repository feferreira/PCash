#ifndef PROVENTOS_H
#define PROVENTOS_H
#include "data.h"
#include <map>

class QString;

class Proventos : public Data
{
public:
    bool getListaTipoProvento();
    std::map<QString,int> listaTipoProvento;
    bool insertProvento(QString data, QString papel, unsigned int valor, unsigned int corretora, unsigned int tipo);
    bool removeProvento(int proventoId);
};

#endif // PROVENTOS_H
