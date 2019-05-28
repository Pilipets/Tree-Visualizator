#ifndef TREEFACTORY_H
#define TREEFACTORY_H

class TreeFactory{
    static TreeFactory *factory;
public:

    void operator::new(size_t) override;

};

#endif // TREEFACTORY_H
