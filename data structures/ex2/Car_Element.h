#ifndef CAR_ELEMENT_H
#define CAR_ELEMENT_H

class CarElement {
public:

    explicit CarElement(int typeID, int sales = 0);

    bool operator<(const CarElement& element) const;

    bool operator>(const CarElement& element) const;

    bool operator==(const CarElement& element) const;

    int getSales();

    int getTypeId();

    ~CarElement() = default;

    void flatDelete();

private:
    int typeID_;
    int sales_;
};

#endif /* CAR_ELEMENT_H */
