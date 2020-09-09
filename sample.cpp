//#include <iostream>

class object{
public:
  virtual ~ object() {}   
};

class Vector : public object{
    object** data_;
    int capacity_;//格納可能な最大要素数
    int size_;//格納されている要素数

public:
Vector() : data_(0),capacity_(0),size_(0) {}
~Vector()
{   for(int i = 0;i<size_;++i){
        delete data_[i];
    }
    delete[] data_;
}

void add(object* item){//格納領域が不足するなら、領域の再割り当てを行う
    if(size_ == capacity_){
        capacity_ += 10;
        object** tmp = new object*[capacity_];
        for(int i = 0; i < size_; ++i){
            tmp[i] = data_[i];
        }
        delete[] data_;
        data_ = tmp;
    }
    data_[size_ ++] = item;
}
 //index番目の要素を返す
 object* at(int index){
     if(index < 0 || index >= size_){
         return 0;
     }
     return data_[index];

     //格納されている要素を返す
 }


};

int main() {//コマンドライン引数の使用 argcは引数の個数　argvは配列へのポインタ
 
}
