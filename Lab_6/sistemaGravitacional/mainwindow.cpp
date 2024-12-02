#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->eliminarUltimo,&QPushButton::clicked,this,&MainWindow::eliminarUltimoCuerpo);
    connect(ui->iniciarSimulacion, &QPushButton::clicked, this, &MainWindow::iniciarSimulacion);
    connect(ui->annadirCuerpo, &QPushButton::clicked, this, &MainWindow::annadirCuerpo);
    connect(ui->sistema1, &QPushButton::clicked, this, &MainWindow::sistemaUno);
    connect(ui->sistema2, &QPushButton::clicked, this, &MainWindow::sistemaDos);
    connect(ui->reiniciar, &QPushButton::clicked, this, &MainWindow::reiniciarSimulacion);

    showMaximized();

    scene = new QGraphicsScene(-300, -400, 600, 800);
    ui->graphicsView->setScene(scene);

    timer = new QTimer(this);
    timertwo = new QTimer(this);

    numSimulacion = 0;
    timertwo->start(0.1);

    ui->posX->setRange(-1e20, 1e20);
    ui->posY->setRange(-1e20, 1e20);
    ui->Masa->setRange(-1e20, 1e20);
    ui->Radio->setRange(-1e20, 1e20);
    ui->velX->setRange(-1e20, 1e20);
    ui->velY->setRange(-1e20, 1e20);

    connect(timer, SIGNAL(timeout()), this, SLOT(actualizar()));
    connect(timertwo, SIGNAL(timeout()), this, SLOT(estadoBotones()));

    estado = false;

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);




}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete timertwo;
    delete scene;
}

void MainWindow::iniciarSimulacion()
{
    estado = true;
}

void MainWindow::annadirCuerpo()
{
    numSimulacion = 3;
    timer->start(33);

    float posX = ui->posX->value();
    float posY = ui->posY->value();;
    float masa = ui->Masa->value();
    float radio = ui->Radio->value();
    float velX = ui->velX->value();
    float velY = ui->velY->value();

    sistema.append(new Cuerpo(posX,posY,masa,radio,velX,velY));
    scene->addItem(sistema.last());


}

void MainWindow::actualizar()
{
    float masa, posx, posy;
    if(estado){
        for (int r=0 ; r<11; r++)
        {
            for (int j=0 ; j < sistema.length(); j++)
            {
                int nombre = j + 1;
                float posX = sistema[j]->getPosX();
                float posY = sistema[j]->getPosY();
                float masa = sistema[j]->getMasa();
                float radio = sistema[j]->getRadio();
                float velX = sistema[j]->getVelocidadX();
                float velY = sistema[j]->getVelocidadY();
                escribirArchivo(nombre, posX, posY, masa, radio, velX, velY, false);
                for (int i=0; i < sistema.length(); i++){
                    if (sistema[i] != sistema[j]){
                        masa = sistema[i]->getMasa();
                        posx = sistema[i]->getPosX();
                        posy = sistema[i]->getPosY();
                        sistema[j]->aceleracion(masa, posx, posy);
                    }

                }
                sistema[j]->velocidad();
                sistema[j]->posicion();
                sistema[j]->setAceleracionX(0);
                sistema[j]->setAceleracionY(0);
            }
        }
        escribirArchivo(0, 0, 0, 0, 0, 0, 0, true);
    }
}


void MainWindow::escribirArchivo(int nombre, float posX, float posY, float masa, float radio, float velX, float velY, bool saltoLinea) {
    QString archivo = QCoreApplication::applicationDirPath() + "/../../../sistemaGravitacional/Sistema.csv";
    qDebug() << "Ruta del archivo CSV:" << archivo;

    QFile file(archivo);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Error al abrir el archivo:" << file.errorString();
        return;
    }

    QTextStream stream(&file);

    if (file.size() == 0) {
        QString encabezado = "Cuerpo;Posicion inicial X;Posicion inicial Y;Masa;Radio;Velocidad X inicial;Velocidad Y inicial";
        stream << encabezado << "\n";
    }

    if(saltoLinea){
        stream << "\n";
    }
    else{
        stream << nombre << ";"
               << posX << ";"
               << posY << ";"
               << masa << ";"
               << radio << ";"
               << velX << ";"
               << velY << "\n";
    }
    file.close();
    qDebug() << "Archivo escrito con exito";
}

void MainWindow::reiniciarSimulacion()
{
    Cuerpo* elementoActual;
    for (QList<Cuerpo*>::iterator it = sistema.begin(); it != sistema.end(); ++it) {
        elementoActual = *it;
        scene->removeItem(*it);
    }
    sistema.clear();
    estado = false;
}

void MainWindow::eliminarUltimoCuerpo()
{
    if (!sistema.isEmpty())
    {
        scene->removeItem(sistema.last());
        delete sistema.last();
        sistema.removeLast();
    }
}

void MainWindow::sistemaUno()
{
    numSimulacion = 1;
    timer->start(33);
    sistema.append(new Cuerpo(0, -7000, 70, 120, 2, 0));
    scene->addItem(sistema.last());

    sistema.append(new Cuerpo(0, 0, 70000, 300, 0, 0));
    scene->addItem(sistema.last());

    sistema.append(new Cuerpo(4000, 5000, 25, 100, -1.6, 1.2));
    scene->addItem(sistema.last());

}

void MainWindow::sistemaDos()
{
    numSimulacion = 2;
    timer->start(33);
    sistema.append(new Cuerpo(0, 0, 50000, 200, 0, 0));
    scene->addItem(sistema.last());

    sistema.append(new Cuerpo(-5000, 0, 70, 70, 0, -2));
    scene->addItem(sistema.last());

    sistema.append(new Cuerpo(5000, 0, 70, 70, 0, 2));
    scene->addItem(sistema.last());

    sistema.append(new Cuerpo(0, -5000, 70, 70, 2, 0));
    scene->addItem(sistema.last());

    sistema.append(new Cuerpo(0, 5000, 70, 70, -2, 0));
    scene->addItem(sistema.last());
}

void MainWindow::estadoBotones()
{
    if (sistema.isEmpty() || sistema.size() == 0){
        ui->iniciarSimulacion->setEnabled(false);
        ui->eliminarUltimo->setEnabled(false);
    }
    else{
        ui->iniciarSimulacion->setEnabled(true);
        ui->eliminarUltimo->setEnabled(true);
    }


}
