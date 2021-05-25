#ifndef MODEL_ELEMENT_H
#define MODEL_ELEMENT_H

const int SELL_POINTS = 10;
const int COMPLAINT_POINTS = 100;

class ModelElement {
public:
    ModelElement(int typeID = 0, int modelID = 0, int grade = 0);

    ModelElement(const ModelElement& other) :
        typeID_(other.typeID_), modelID_(other.modelID_), grade_(other.grade_)
    {}

    ~ModelElement() = default;

    bool operator>(const ModelElement &other) const;

    bool operator<(const ModelElement &other) const;

    bool operator==(const ModelElement &other) const;

    int getTypeId() const;

    int getGrade() const;

    int getModel() const;

    ModelElement *clone();

    void reciveComplaint(int months);

    void flatDelete();


private:
    int typeID_;
    int modelID_;
    int grade_;
};

#endif /* MODEL_ELEMENT_H */
