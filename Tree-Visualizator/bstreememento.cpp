#include"bstreememento.h"
#include <QTextStream>
BSTreeMemento::BSTreeMemento()
{
}

void BSTreeMemento::setTraversal(const QString &traversal)
{
    this->traversal = traversal;
}

QString BSTreeMemento::getTraversal()
{
    return traversal;
}

void BSTreeMemento::writeToFile(QFile &file)
{
    QTextStream writer(&file);
    writer << traversal;
    writer.flush();
}
