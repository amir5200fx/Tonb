//
// Created by amir on 9/1/25.
//
#include <model/mesh_2d.hxx>

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLabel label("Hello, Tonb World!");
    label.resize(300, 100);
    label.show();

    return QApplication::exec();
}