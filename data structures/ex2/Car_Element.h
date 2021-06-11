#ifndef CAR_ELEMENT_H
#define CAR_ELEMENT_H

class CarElement {
public:

    explicit CarElement(int typeID, int sales = 0);

    bool operator<(CarElement& element);

    bool operator==(CarElement& element);

    int getSales();

    int getTypeId();

    ~CarElement() = default;

private:
    int typeID_;
    int sales_;
};

#endif /* CAR_ELEMENT_H */