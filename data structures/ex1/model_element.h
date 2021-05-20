#ifndef MODEL_ELEMENT_H
#define MODEL_ELEMENT_H

class ModelElement {
public:
    ModelElement(int typeID, int modelID);

    bool operator>(const ModelElement &other) const;

    bool operator<(const ModelElement &other) const;

    bool operator==(const ModelElement &other) const;

private:
    int typeID_;
    int modelID_;
    int sales_;
    int grade_;
};

ModelElement::ModelElement(int typeID, int modelID) :
        typeID_(typeID), modelID_(modelID), sales_(0), grade_(0)
{}

bool ModelElement::operator>(const ModelElement &other) const
{
    if (this->grade_ > other.grade_)
        return true;
    else if (this->grade_ == other.grade_) {
        if (this->typeID_ > other.typeID_)
            return true;
        else if (this->typeID_ == other.typeID_) {
            if (this->modelID_ > other.modelID_)
                return true;
        }
    }
    return false;
}

bool ModelElement::operator<(const ModelElement &other) const
{
    if (this->grade_ < other.grade_)
        return true;
    else if (this->grade_ == other.grade_) {
        if (this->typeID_ < other.typeID_)
            return true;
        else if (this->typeID_ == other.typeID_) {
            if (this->modelID_ < other.modelID_)
                return true;
        }
    }
    return false;
}

bool ModelElement::operator==(const ModelElement &other) const
{
    if (this->typeID_ == other.typeID_
        && this->modelID_ == other.modelID_
        && this->sales_ == other.sales_
        && this->grade_ == other.grade_) {
        return true;
    } else
        return false;
}

#endif /* MODEL_ELEMENT_H */