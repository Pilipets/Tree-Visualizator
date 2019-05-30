#ifndef BSTREEMEMENTO_H
#define BSTREEMEMENTO_H

#include<QString>
#include<QFile>

class BSTreeMemento{
    QString traversal;
public:
    BSTreeMemento();
    void setTraversal(const QString& traversal);
    QString getTraversal() const {return traversal;}
    bool writeToFile(const QString &fileName);
    bool readFromFile(const QString &fileName);
};


#endif // BSTREEMEMENTO_H
