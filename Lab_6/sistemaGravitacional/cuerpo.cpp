#include "cuerpo.h"


Cuerpo::Cuerpo()
{
    posX = 0;
    posY = 0;
    velocidadX = 0;
    velocidadY = 0;
    aceleracionX = 0;
    aceleracionY = 0;
    radio = 0;
    masa = 0;

    escenaY = 20;
    escenaX = 10;
    G  = 9.81;
    DeltaT = 1;

    setPos(0,0);
}

Cuerpo::Cuerpo(float posX, float posY, float masa, float radio, float velocidadX, float velocidadY)
{
    this->posX = posX;
    this->posY = posY;
    this->velocidadX = velocidadX;
    this->velocidadY = velocidadY;
    this->aceleracionX = 0;
    this->aceleracionY = 0;
    this->radio = radio;
    this->masa = masa;

    escenaY = 20*1.2;
    escenaX = 20*1.2;
    G  = 1;
    DeltaT = 1;

    setPos((posX/escenaX), (-posY/escenaY));

}

float Cuerpo::getPosX() const{return posX;}
float Cuerpo::getPosY() const{return posY;}
float Cuerpo::getVelocidadX() const{return velocidadX;}
float Cuerpo::getVelocidadY() const{return velocidadY;}
float Cuerpo::getAceleracionX() const{return aceleracionX;}
float Cuerpo::getAceleracionY() const{return aceleracionY;}
float Cuerpo::getRadio() const{return radio;}
float Cuerpo::getMasa() const{return masa;}

void Cuerpo::setPosX(float val){posX = val;}
void Cuerpo::setPosY(float val){posY = val;}
void Cuerpo::setVelocidadX(float val){velocidadX = val;}
void Cuerpo::setVelocidadY(float val){velocidadY = val;}
void Cuerpo::setAceleracionX(float val){aceleracionX = val;}
void Cuerpo::setAceleracionY(float val){aceleracionY = val;}
void Cuerpo::setRadio(float val){radio = val;}
void Cuerpo::setMasa(float val){masa = val;}

QRectF Cuerpo::boundingRect() const
{
    return QRect(-radio/escenaX, -radio/escenaX, (radio/escenaX)*2, (radio/escenaX)*2);
}

void Cuerpo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect());
}

void Cuerpo::aceleracion(float masa2, float posX2, float posY2)
{

    float r = 0;
    float alpha = 0;

    r = sqrt(pow((posX2 - posX), 2) + pow((posY2 - posY), 2));

    if (posX2 != posX){
        alpha = atan2((posY2 - posY),(posX2 - posX));
    }
    else{
        alpha = 0;
    }

    aceleracionX += (G * masa2 * cos(alpha)) / pow(r, 2);
    aceleracionY += (G * masa2 * sin(alpha)) / pow(r, 2);
}

void Cuerpo::velocidad()
{
    velocidadX = velocidadX + (aceleracionX * DeltaT);
    velocidadY = velocidadY + (aceleracionY * DeltaT);
}

void Cuerpo::posicion()
{
    posX = posX + (velocidadX * DeltaT) + (0.5 * aceleracionX * pow(DeltaT, 2));
    posY = posY + (velocidadY * DeltaT) + (0.5 * aceleracionY * pow(DeltaT, 2));

    setPos((posX/escenaX), (-posY/escenaY));
}



