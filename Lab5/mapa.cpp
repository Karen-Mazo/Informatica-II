#include "mapa.h"
#include "galletapeque.h"
#include "galletagrande.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>

Mapa::Mapa() {
    bloqueSize = 20;
    galletaSize = 6;
    posGalletasGrandes = {{3,1},{3,19},{17,1},{17,19}};
    cargarMapa();
    cargarGalletas();
    numColumnas = mapa[0].size() - 1;
    numFilas = mapa.size() - 1;
    //cargarGalletaGrande();
}

int Mapa::getBloqueSize() const{return bloqueSize;}
int Mapa::getNumColumnas() const {return numColumnas;}
int Mapa::getNumFilas() const {return numFilas;}
QVector<QVector<int>> Mapa::getMapa() const{return mapa;}

void Mapa::cargarMapa(){
    mapa = {
        {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1},
        {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,0, 1},
        {1,0,1,1,1, 0,1,1,1,0, 1,0,1,1,1, 0,1,1,1,0, 1},
        {1,2,1,1,1, 0,1,1,1,0, 1,0,1,1,1, 0,1,1,1,2, 1},
        {1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1},
        {1,0,1,1,1, 0,1,0,1,1, 1,1,1,0,1, 0,1,1,1,0, 1},
        {1,0,0,0,0, 0,1,0,0,0, 1,0,0,0,1, 0,0,0,0,0, 1},
        {1,1,1,1,1, 0,1,1,1,2, 1,2,1,1,1, 0,1,1,1,1, 1},
        {2,2,2,2,1, 0,1,2,2,2, 2,2,2,2,1, 0,1,2,2,2, 2},
        {1,1,1,1,1, 0,1,2,1,1, 2,1,1,2,1, 0,1,1,1,1, 1},
        {2,2,2,2,2, 0,2,2,1,2, 2,2,1,2,2, 0,2,2,2,2, 2},
        {1,1,1,1,1, 0,1,2,1,2, 2,2,1,2,1, 0,1,1,1,1, 1},
        {2,2,2,2,1, 0,1,2,1,1, 1,1,1,2,1, 0,1,2,2,2, 2},
        {2,2,2,2,1, 0,1,2,2,2, 2,2,2,2,1, 0,1,2,2,2, 2},
        {1,1,1,1,1, 0,2,2,1,1, 1,1,1,2,2, 0,1,1,1,1, 1},
        {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,0, 1},
        {1,0,1,1,1, 0,1,1,1,0, 1,0,1,1,1, 0,1,1,1,0, 1},
        {1,2,0,0,1, 0,0,0,0,0, 2,0,0,0,0, 0,1,0,0,2, 1},
        {1,1,2,0,1, 0,1,0,1,1, 1,1,1,0,1, 0,1,0,2,1, 1},
        {1,0,0,0,0, 0,1,0,0,0, 1,0,0,0,1, 0,0,0,0,0, 1},
        {1,0,1,1,1, 1,1,1,1,0, 1,0,1,1,1, 1,1,1,1,0, 1},
        {1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1},
        {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1}
    };

}

void Mapa::cargarGalletas(){
    for (int i = 0; i < (int)mapa.size(); i++){
        for(int j = 0; j < (int)mapa[i].size(); j++){
            if(mapa[i][j] == 0){
                galletaPeque* galleta = new galletaPeque(i, j);
                galletasPeque.append(galleta);
            }
        }
    }
    for (const auto& pos : posGalletasGrandes){
        galletaGrande* galletaG = new galletaGrande(pos[0],pos[1]);
        galletasGrandes.append(galletaG);
    }
}

void Mapa::dibujar(QGraphicsScene *scene){
    QGraphicsRectItem* pared;
    QGraphicsEllipseItem* galletaPeque;
    QGraphicsEllipseItem* galletaGrande;
    QBrush brushPared(Qt::blue);
    QBrush brushGalleta(Qt::yellow);
    for(int i = 0; i < (int)mapa.size(); i++){
        for(int j = 0; j < (int)mapa[i].size(); j++){
            if(mapa[i][j] == 1){
                pared = scene->addRect(j * bloqueSize, i * bloqueSize, bloqueSize, bloqueSize);
                pared->setBrush(brushPared);
                pared->setPen(Qt::NoPen);
                //pared->setBrush(Qt::NoBrush); // para las paredes invisibles opcionales
                pared->setData(0,"pared");
            }
            else if(mapa[i][j] == 0){
                galletaPeque = scene->addEllipse(j * bloqueSize + 7, i * bloqueSize + 7, galletaSize, galletaSize);
                galletaPeque->setBrush(brushGalleta);
                galletaPeque->setData(0,"galletaPeque");
            }
        }
    }
    for (auto pos : posGalletasGrandes){
        galletaGrande = scene->addEllipse(pos[1] * bloqueSize + 4, pos[0] * bloqueSize + 4, (galletaSize * 2) + 1, (galletaSize * 2) + 1);
        galletaGrande->setBrush(brushGalleta);
        galletaGrande->setData(0,"galletaGrande");
    }
}


