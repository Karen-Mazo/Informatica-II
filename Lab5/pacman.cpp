#include "pacman.h"
#include "mapa.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>

pacMan::pacMan(QObject* parent)
    : QObject(parent), mapa(new Mapa()), sprite(new QTimer()), vidas(3), puntaje(0), velocidad(2), direccionActual(4),posicion(200, 340),posicionInicial(200, 340)
{
    connect(sprite, SIGNAL(timeout()), this, SLOT(cambiarSprite()));
    sprite->start(500);
    filas = 0;
    columnas = 83;
    pixmap = new QPixmap(":/sprites/pacman.png");
    ancho = 44;
    alto = 85;
}

QPoint pacMan::getPosicion() const{return posicion;}
int pacMan::getVidas() const{return vidas;}
int pacMan::getPuntaje() const {return puntaje;}
int pacMan::getMapX() const {
    return posicion.x() / mapa->getBloqueSize();
}
int pacMan::getMapY() const {
    return posicion.y() / mapa->getBloqueSize();
}
int pacMan::getMapXRightSide() const {
    return (posicion.x() + 17) / mapa->getBloqueSize();
}
int pacMan::getMapYRightSide() const {
    return (posicion.y() + 17) / mapa->getBloqueSize();
}


/*bool pacMan::colisionPared(){
    bool colisiona = false;
    if(mapa->getMapa()[getMapY()][getMapX()] == 1
        || mapa->getMapa()[getMapYRightSide()][getMapX()] == 1
        || mapa->getMapa()[getMapY()][getMapXRightSide()] == 1
        || mapa->getMapa()[getMapYRightSide()][getMapXRightSide()] == 1){colisiona = true;}
    return colisiona;
}
*/

void pacMan::moverArriba(){
    int siguienteFila = (posicion.y() - velocidad) / mapa->getBloqueSize();
    int columnaIzquierda = posicion.x() / mapa->getBloqueSize();
    int columnaDerecha = (posicion.x() + boundingRect().width() - 1) / mapa->getBloqueSize();
    qDebug() << "Mover Arriba:";
    qDebug() << "Posición actual: x =" << posicion.x() << "y =" << posicion.y();
    qDebug() << "Siguiente fila:" << siguienteFila << "Columnas: izquierda =" << columnaIzquierda << "derecha =" << columnaDerecha;
    qDebug() << "Valores en el mapa: izquierda =" << mapa->getMapa()[siguienteFila][columnaIzquierda]
             << "derecha =" << mapa->getMapa()[siguienteFila][columnaDerecha];
    if (siguienteFila >= 0 && mapa->getMapa()[siguienteFila][columnaIzquierda] != 1 &&
        mapa->getMapa()[siguienteFila][columnaDerecha] != 1) {
        posicion.ry() -= velocidad;
        direccionActual = 0;
    }
}

void pacMan::moverAbajo() {
    int siguienteFila = (posicion.y() + boundingRect().height() + velocidad - 1) / mapa->getBloqueSize();
    int columnaIzquierda = posicion.x() / mapa->getBloqueSize();
    int columnaDerecha = (posicion.x() + boundingRect().width() - 1) / mapa->getBloqueSize();
    qDebug() << "Mover Abajo:";
    qDebug() << "Posición actual: x =" << posicion.x() << "y =" << posicion.y();
    qDebug() << "Siguiente fila:" << siguienteFila << "Columnas: izquierda =" << columnaIzquierda << "derecha =" << columnaDerecha;
    qDebug() << "Valores en el mapa: izquierda =" << mapa->getMapa()[siguienteFila][columnaIzquierda]
             << "derecha =" << mapa->getMapa()[siguienteFila][columnaDerecha];
    if (siguienteFila < mapa->getNumFilas() && mapa->getMapa()[siguienteFila][columnaIzquierda] != 1 &&
        mapa->getMapa()[siguienteFila][columnaDerecha] != 1) {
        posicion.ry() += velocidad;
        direccionActual = 2;
    }
}

void pacMan::moverIzquierda() {
    int siguienteColumna = (posicion.x() - velocidad) / mapa->getBloqueSize();
    int filaSuperior = posicion.y() / mapa->getBloqueSize();
    int filaInferior = (posicion.y() + boundingRect().height() - 1) / mapa->getBloqueSize();
    qDebug() << "Mover Izquierda:";
    qDebug() << "Posición actual: x =" << posicion.x() << "y =" << posicion.y();
    qDebug() << "Fila superior:" << filaSuperior << "Fila inferior:" << filaInferior << "Siguiente columna:" << siguienteColumna;
    qDebug() << "Valores en el mapa: superior =" << mapa->getMapa()[filaSuperior][siguienteColumna]
             << "inferior =" << mapa->getMapa()[filaInferior][siguienteColumna];
    if (siguienteColumna >= 0 && mapa->getMapa()[filaSuperior][siguienteColumna] != 1 &&
        mapa->getMapa()[filaInferior][siguienteColumna] != 1) {
        posicion.rx() -= velocidad;
        direccionActual = 3;
    }
}

void pacMan::moverDerecha() {
    int siguienteColumna = (posicion.x() + boundingRect().width() + velocidad - 1) / mapa->getBloqueSize();
    int filaSuperior = posicion.y() / mapa->getBloqueSize();
    int filaInferior = (posicion.y() + boundingRect().height() - 1) / mapa->getBloqueSize();
    qDebug() << "Mover Derecha:";
    qDebug() << "Posición actual: x =" << posicion.x() << "y =" << posicion.y();
    qDebug() << "Fila superior:" << filaSuperior << "Fila inferior:" << filaInferior << "Siguiente columna:" << siguienteColumna;
    qDebug() << "Valores en el mapa: superior =" << mapa->getMapa()[filaSuperior][siguienteColumna]
             << "inferior =" << mapa->getMapa()[filaInferior][siguienteColumna];
    if (siguienteColumna < mapa->getNumColumnas() && mapa->getMapa()[filaSuperior][siguienteColumna] != 1 &&
        mapa->getMapa()[filaInferior][siguienteColumna] != 1) {
        posicion.rx() += velocidad;
        direccionActual = 1;
    }
}

void pacMan::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_W:
        direccionDeseada = 0;
        break;
    case Qt::Key_S:
        direccionDeseada = 2;
        break;
    case Qt::Key_A:
        direccionDeseada = 3;
        break;
    case Qt::Key_D:
        direccionDeseada = 1;
        break;
    default:
        break;
    }
}

bool pacMan::caminoValido(int direccion){
    int filaSuperior = posicion.y() / mapa->getBloqueSize();
    int filaInferior = (posicion.y() + boundingRect().height() - 1) / mapa->getBloqueSize();
    int columnaIzquierda = posicion.x() / mapa->getBloqueSize();
    int columnaDerecha = (posicion.x() + boundingRect().width() - 1) / mapa->getBloqueSize();

    switch (direccion) {
    case 0:
        filaSuperior--;
        break;
    case 1:
        columnaDerecha++;
        break;
    case 2:
        filaInferior++;
        break;
    case 3:
        columnaIzquierda--;
        break;
    default:
        break;
    }
    if (filaSuperior >= 0 && filaInferior < mapa->getNumFilas() &&
        columnaIzquierda >= 0 && columnaDerecha < mapa->getNumColumnas()) {
        return mapa->getMapa()[filaSuperior][columnaIzquierda] != 1 &&
               mapa->getMapa()[filaSuperior][columnaDerecha] != 1 &&
               mapa->getMapa()[filaInferior][columnaIzquierda] != 1 &&
               mapa->getMapa()[filaInferior][columnaDerecha] != 1;
    }
    return false;
}

void pacMan::teletransportar(){
    int fila = posicion.y() / mapa->getBloqueSize();
    int columna = posicion.x() / mapa->getBloqueSize();
    if(fila == 10 && columna == 0 && direccionActual == 3){
        posicion.setX((mapa->getNumColumnas() - 1) * mapa->getBloqueSize());
        direccionActual = 3;
    } else if (fila == 10 && columna == mapa->getNumColumnas() - 1 && direccionActual == 1){
        posicion.setX(0);
        direccionActual = 1;
    }
}

void pacMan::colisionFantasma(){
    perderVida();
    if(vidas > 0){
        this->setVisible(false);
        this->setPos(posicionInicial);
        this->setVisible(true);
    }
    else if(vidas == 0 || puntaje >= 1840){
        qDebug() << "Fin del juego";
        emit juegoTerminado();
    }

}
void pacMan::moverEnDireccionActual(){
    if(caminoValido(direccionDeseada)){
        direccionActual = direccionDeseada;
    }
    switch (direccionActual) {
    case 0:
        moverArriba();
        break;
    case 1:
        moverDerecha();
        break;
    case 2:
        moverAbajo();
        break;
    case 3:
        moverIzquierda();
        break;
    default:
        break;
    }
    teletransportar();
    QList<QGraphicsItem*> colisiones = collidingItems();

    for (QGraphicsItem* item : colisiones) {
        if (item->data(0).toString() == "galletaPeque") {
            if(item->data(1).toBool() == false){
                item->setOpacity(0); // se hacen visibles las pareced
                item->setData(1,true);
                qDebug() << "Colision con galleta pequeña";
                aumentarPuntos();
                break;
            }
        }
        else if(item->data(0).toString() == "galletaGrande"){
            if(item->data(1).toBool() == false){
                item->setOpacity(0); // se hacen visibles las pareced
                item->setData(1,true);
                qDebug() << "Colision con galleta Grande";
                aumentarPuntos();
                break;
            }
        }
        else if(item->data(0).toString() == "fantasma"){
            if(item->data(1).toBool() == false){
                qDebug() << "Colision con fantasma";
                aumentarPuntos();
                colisionFantasma();
                break;
            }
        }
    }
}


QRectF pacMan::boundingRect() const {
    return QRectF(0, 0, 17, 17);
}

void pacMan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());
}


/*QRectF pacMan::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void pacMan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,0,ancho, alto);
}*/

void pacMan::cambiarSprite()
{
    columnas += 44;
    if(columnas>=435){
        columnas = 83;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}
void pacMan::perderVida(){
    if (vidas > 0){
        vidas--;
        emit vidaCambio(vidas);
    }
}

void pacMan::activarComerFantasma(){
    comerFantasma = true;
    QTimer::singleShot(5000, this, [this](){
        comerFantasma = false;
    });
}

bool pacMan::estaEnModoComer(){
    return comerFantasma;
}

void pacMan::aumentarPuntos(){
    QList<QGraphicsItem*> colisiones = collidingItems();

    for (QGraphicsItem* item : colisiones) {
        if (item->data(0).toString() == "galletaPeque") {
            puntaje += 10;
            emit puntajeCambiado(puntaje);
            break;
        }
        else if(item->data(0).toString() == "galletaGrande"){
            puntaje += 25;
            emit puntajeCambiado(puntaje);
            break;
        }
        else if(item->data(0).toString() == "fantasma"){
            puntaje += 200;
            emit puntajeCambiado(puntaje);
            break;
        }
    }
}

void pacMan::reiniciar(){
    vidas = 3;
    puntaje = 0;
    setPos(200,340);
    emit puntajeCambiado(puntaje);
    emit vidaCambio(vidas);
}
