#ifndef BSTREEMEMENTO_H
#define BSTREEMEMENTO_H

#include<QString>
class BSTreeMemento{
    QString traversal;
public:
    BSTreeMemento();
    void setTraversal(const QString& traversal){this->traversal = traversal;}
    QString getTraversal(){return traversal;}

    void readFromFile(const char* path);
    void writeToFile(const char* path);
};


#endif // BSTREEMEMENTO_H
