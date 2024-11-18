#ifndef PACMAN_H
#define PACMAN_H


#include <QObject>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsItem>
#include <QPoint>

class Mapa;

class pacMan: public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit pacMan(QObject* parent = nullptr);
    QPoint getPosicion() const;
    int getVidas() const;
    int getPuntaje() const;
    int getMapX() const;
    int getMapY() const;
    int getMapXRightSide() const;
    int getMapYRightSide() const;
    bool caminoValido(int direccion);
    bool estaEnModoComer();
    bool colisionPared();
    void moverArriba();
    void moverAbajo();
    void moverIzquierda();
    void moverDerecha();
    void verificarColision();
    void moverEnDireccionActual();
    void keyPressEvent(QKeyEvent* event);
    void teletransportar();
    void perderVida();
    void aumentarPuntos();
    void colisionFantasma();
    void reiniciar();
    void cambiarSprite();
    void activarComerFantasma();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

signals:
    void puntajeCambiado(int puntaje);
    void vidaCambio(int vidas);
    void juegoTerminado();

private:
    QPoint posicion;
    QPoint posicionInicial;
    QTimer* sprite;
    Mapa* mapa;
    QPixmap* pixmap;
    int vidas, puntaje, velocidad,direccionActual,direccionDeseada;
    int columnas, filas, ancho, alto;
    bool comerFantasma;




};

#endif // PACMAN_H
