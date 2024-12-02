#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "cuerpo.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void escribirArchivo(int nombre, float posX, float posY, float masa, float radio, float velX, float velY, bool saltoLinea);

private:
    Ui::MainWindow *ui;
    QList <Cuerpo*> sistema;
    QGraphicsScene *scene;
    QTimer *timer;
    QTimer *timertwo;
    bool estado;
    int numSimulacion;

private slots:
    void iniciarSimulacion();
    void annadirCuerpo();
    void actualizar();
    void reiniciarSimulacion();
    void eliminarUltimoCuerpo();
    void sistemaUno();
    void sistemaDos();
    void estadoBotones();
};

#endif // MAINWINDOW_H
