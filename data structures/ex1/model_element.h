#ifndef MODEL_ELEMENT_H
#define MODEL_ELEMENT_H

class ModelElement {
public:
    ModelElement(int typeID, int modelID);
    
private:
    int typeID_;
    int modelID_;
    int sales_;
    int grade_;
};

ModelElement::ModelElement(int typeID, int modelID):
    typeID_(typeID), modelID_(modelID), sales_(0), grade_(0) {}

#endif /* MODEL_ELEMENT_H */