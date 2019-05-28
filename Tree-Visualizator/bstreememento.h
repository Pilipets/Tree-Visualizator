#ifndef BSTREEMEMENTO_H
#define BSTREEMEMENTO_H

#include<QString>
#include<QFile>

class BSTreeMemento{
    QString traversal;
public:
    BSTreeMemento(){};
    void setTraversal(const QString& traversal);
    QString getTraversal();

    void readFromFile(const char* path);
    void writeToFile(QFile &file);
};


#endif // BSTREEMEMENTO_H
