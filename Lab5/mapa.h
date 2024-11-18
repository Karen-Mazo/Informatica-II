#ifndef MAPA_H
#define MAPA_H

#include <QVector>
#include <QPoint>
#include <QGraphicsScene>
#include <QGraphicsItem>

class galletaPeque;
class galletaGrande;
class Mapa
{
public:
    Mapa();
    int getBloqueSize() const;
    int getNumFilas() const;
    int getNumColumnas() const;
    QVector<QVector<int>> getMapa() const;
    void cargarMapa();
    void cargarGalletas();
    //void cargarGalletaGrande();
    void dibujar(QGraphicsScene *scene);
    bool verificarPared(int x, int y);


private:
    QVector<QVector<int>> mapa;
    QVector<galletaPeque*> galletasPeque;
    QVector<galletaGrande*> galletasGrandes;
    QVector<QVector<int>> posGalletasGrandes;
    QPoint inicioPacman;
    QVector<QPoint> inicioFantasmas;
    int bloqueSize;
    int galletaSize;
    int numFilas;
    int numColumnas;


};

#endif // MAPA_H
