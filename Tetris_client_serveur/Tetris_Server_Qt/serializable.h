#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>

class Serializable
{
public:
    Serializable();
    ~Serializable();
    virtual QJsonObject serialize_to_json() = 0;
};

#endif // SERIALIZABLE_H
