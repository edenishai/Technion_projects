//Part A-dry

template <class T>
std::vector slice(std::vector<T> vec,int start,int step,int stop){
    if(start<0||start>=vec.size()||stop<0||stop>vec.size()||step<=0){
        throw BadInput();
    }
    std::vector<T> new_vec();
    if(start>=stop){
        return new_vec;
    }
    for(int i=start;i<stop;i+=step){
        new_vec.push_back(vec.at(i));
        i+=step;
    }
    return new_vec;
}


//Part B

class A{
public:
    vector<shared_ptr<int>> values;
    void add(int x){
        shared_ptr<int> ptr(new int(x));
        values.push_back(ptr);
    }
};