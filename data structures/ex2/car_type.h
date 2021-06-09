#ifndef CAR_TYPE_H
#define CAR_TYPE_H

class CarType {
public:
    CarType(int typeID);

    ~CarType();

private:
    int typeID_;
    int sales_;
};

#endif /* CAR_TYPE_H */
