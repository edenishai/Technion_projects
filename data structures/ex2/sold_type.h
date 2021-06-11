#ifndef SOLD_TYPE_H
#define SOLD_TYPE_H

//different >, < operator than car_type

class SoldType {
public:
    SoldType(int typeID);

    ~SoldType();

private:
    int typeID_;
    int sales_;
};

#endif /* SOLD_TYPE_H */