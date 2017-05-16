#ifndef DESERIALIZABLE_H
#define DESERIALIZABLE_H

#include <QJsonObject>

class Deserializable
{
public:
    Deserializable();
    ~Deserializable();
    virtual void deserialize_from_json(const QJsonObject&) = 0;
};

#endif // DESERIALIZABLE_H
