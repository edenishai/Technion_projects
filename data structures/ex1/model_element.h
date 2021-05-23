#ifndef MODEL_ELEMENT_H
#define MODEL_ELEMENT_H

const int SELL_POINTS = 10;
const int COMPLAINT_POINTS = 100;

class ModelElement {
public:
    ModelElement();

    ModelElement(int typeID, int modelID, int grade = 0);

    ModelElement(const ModelElement& other) = default;

    ~ModelElement() = default;

    bool operator>(const ModelElement &other) const;

    bool operator<(const ModelElement &other) const;

    bool operator==(const ModelElement &other) const;

    int getTypeId() const;

    int getGrade() const;

    int getModel() const;

    ModelElement *clone();

    void reciveComplaint(int months);

private:
    int typeID_;
    int modelID_;
    int grade_;
};

#endif /* MODEL_ELEMENT_H */
