#ifndef SALE_ELEMENT_H
#define SALE_ELEMENT_H

class SaleElement {
public:
    SaleElement(int typeID) : typeID_(typeID), modelID_(0), sales_(0)
    {}

    SaleElement(int typeID, int modelID, int sales);

    SaleElement(const SaleElement &element); 

    int getTypeID() const
    { return typeID_; }

    int getSales() const
    { return sales_; }

    bool operator>(const SaleElement &other) const;

    bool operator<(const SaleElement &other) const;

    bool operator==(const SaleElement &other) const;

    int getModelId() const;

private:
    int typeID_;
    int modelID_;
    int sales_;

};

SaleElement::SaleElement(const SaleElement &element) :
    typeID_(element.typeID_), modelID_(element.modelID_), sales_(element.sales_)
{}

SaleElement::SaleElement(int typeID, int modelID, int sales) :
    typeID_(typeID), modelID_(modelID), sales_(sales)
{}

bool SaleElement::operator>(const SaleElement &other) const
{
    if (this->sales_ > other.sales_)
        return true;
    else if (this->sales_ == other.sales_) {
        if (this->typeID_ > other.typeID_)
            return true;
        else if (this->typeID_ == other.typeID_) {
            if (this->modelID_ > other.modelID_)
                return true;
        }
    }
    return false;
}

bool SaleElement::operator<(const SaleElement &other) const
{
    if (this->sales_ < other.sales_)
        return true;
    else if (this->sales_ == other.sales_) {
        if (this->typeID_ < other.typeID_)
            return true;
        else if (this->typeID_ == other.typeID_) {
            if (this->modelID_ < other.modelID_)
                return true;
        }
    }
    return false;
}

bool SaleElement::operator==(const SaleElement &other) const
{
    return this->typeID_ == other.typeID_
           && this->modelID_ == other.modelID_
           && this->sales_ == other.sales_;
}

int SaleElement::getModelId() const
{
    return this->modelID_;
}

#endif /* SALE_ELEMENT_H */