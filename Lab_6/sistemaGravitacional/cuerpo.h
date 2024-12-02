#ifndef CUERPO_H
#define CUERPO_H

#include <QGraphicsItem>
#include <QPainter>
#include <cmath>
#include <qcolor.h>
#include<stdlib.h>

class Cuerpo : public QGraphicsItem
{
private:
    float G, posX, posY, velocidadX, velocidadY, aceleracionX, aceleracionY, radio, masa;
    int escenaY, escenaX,DeltaT;

public:
    Cuerpo();
    Cuerpo(float posX, float posY, float masa, float radio, float velociadX, float velocidadY);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    float getPosX() const;
    float getPosY() const;
    float getVelocidadX() const;
    float getVelocidadY() const;
    float getAceleracionX() const;
    float getAceleracionY() const;
    float getRadio() const;
    float getMasa() const;
    bool getCentro() const;
    float getPosAnteriorX() const;
    float getPosAnteriorY() const;

    void setPosX(float val);
    void setPosY(float val);
    void setVelocidadX(float val);
    void setVelocidadY(float val);
    void setAceleracionX(float val);
    void setAceleracionY(float val);
    void setRadio(float val);
    void setMasa(float val);

    void aceleracion(float masa2, float posX2, float posY2);
    void velocidad();
    void posicion();

};

#endif // CUERPO_H
