#include"bstreememento.h"
#include <QTextStream>
#include <QFile>
BSTreeMemento::BSTreeMemento()
{
}

void BSTreeMemento::setTraversal(const QString &traversal)
{
    this->traversal = traversal;
}

bool BSTreeMemento::writeToFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    QTextStream writer(&file);
    writer << traversal;
    writer.flush();
    file.close();
    return true;
}

bool BSTreeMemento::readFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    QTextStream reader(&file);
    traversal = reader.readAll().trimmed();
    file.close();
    return true;
}
