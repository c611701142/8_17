#include <string>
#include <vector>
#include <unordered_map>
//unordered_map クラスは O(1) で、さらに高速である。
//要素を順序付けできないという欠点がある
//#include <map>
//map は 二分木 を使っているために、キーから要素を取り出す処理時間が O(log N) で、そこそこ高速である。
//#include <set>
#include <string_view>//ヘッダでは、所有権を持たず文字列を参照する文字列クラスを定義する。
#include <cassert>
//assertを使用するため　

namespace b3prac {

class StringSet {
public:
    static constexpr uint8_t kLeafChar = '\0';
    static constexpr uint8_t MaxUint8_t = 0xFF;
    static constexpr int kEmptyCheck = 0xFFFFFFFF;
    static constexpr int kEmptyBase = 0xFFFFFFFF;//4294967295 int型の最大値 16^8-1
    static constexpr int kFailedIndex = 0;
private:
    struct Unit {
        int base,check;
        Unit() : base(kEmptyBase), check(kEmptyCheck) {}
        Unit(int b, int c) : base(b),check(c) {}
    };
    std::vector<Unit> bc_;
    //bc_ = {kEmptyBase, 0}; // set root element
public:
    //StringSet() = default;
    StringSet() {
        bc_ = {{kEmptyBase, 0}}; // set root element
    }
    // 文字列を追加するための関数
    void insert(const std::string str) {
        int node = 0;
        int n = 0;
        for(uint8_t c : str) {//各文字に１　数字を割り当て
           
        }
    }

private:
    //base[index]にvalを格納する
     //valは設定する値
     //index > DA_SIZEの時のDA_SIZEをindexまで拡張する
    void w_check(int index,int val){
        bc_[index].check = val;
        if(index > bc_.size()){
            bc_.resize(index);
        }
     }

    //9/4
    //新しいbase値の決定
     int x_check(int a){
        //D-1　初期化
        int q = 1;bool flag = true;
        uint8_t c;
        //D-3  終了判定
        if(q <= bc_.size() ){
            flag = true;
        }
        else if(q > bc_.size()){
            flag = false;
        }
        //D-2 インデックス検索  flag = trueで入る
        if(flag == true){
            if(bc_[q + c].check == 0){
                return q;
            }
            else{
                q++;  
            }
        }
        else if(flag == false){
            return q;
            exit(0);
        }
    }

    void w_base(int index,int val){
        bc_[index].base = val;
        if(index > bc_.size()){
            bc_.resize(index);
        }


    }

public:
    //キー追加時に衝突が起こった場合、ノードの移動によって衝突を回避し、
    //キーの残りの文字列を追加する
    void insert2(int index,int pos){
        std::string str;
        std::vector<uint8_t> row;
        uint8_t c;
        std::vector<uint8_t> a;
        //衝突が起こったときの処理 I-1
        //for(uint8_t c : str) {//各文字に１　数字を割り当て
            int idx = bc_[index].base + c;
            if(bc_[idx].check > 0){
                row = getlabel(index);//変数Rにセット
            //}
        //遷移先の定義 I-2
        int t = bc_[index].base + c;
        //bc_[index].check = w_check(t,index);遷移を定義？
        pos++;
        //残りの文字列の追加 I-3
        //a_posとは何か？
        int new_base = x_check(a[pos]);//新しいbase値を定義
        t = bc_[index].base + a[pos];
        bc_[t].check = index;
        pos++;

        //まだ追記あり　２３２２
        }
    }

    void modify(int index,std::vector<uint8_t> row,int b){
        uint8_t c;
        int q = 0;
        //M-1新しいbase[index]の決定
        int old_base = bc_[index].base;//退避しておく
        //bc_[index].base = w_check(index,b);//新しいbase値を設定
        //M-2遷移の移動
        int old_t = old_base + c;
        int t =  bc_[index].base + c;
        w_base(t,bc_[old_t].base);
        if(bc_[old_t].base > 0){
            if(bc_[q].check == old_t){
                //bc_[q].check = w_check(q,t);
            }
        } //新しい遷移先の遷移先の再定義が必要になる M-3
         //check[q] = old_base　になるすべてのq にたいしてw_check(q,t)により、checkを再定義
        
    }
    
    //葉ノードindexを削除することで実現
    //検索成功時に呼び出す
    void delete_sucsess(int index){
        w_base(index,0);
        w_check(index,0); 
    }
//単語
    bool contains(const std::string& key) const {
        int node = 0; // root
        //std::cout << "--------------contains---------------" << std::endl;
        //std::cout << "key : " << key << std::endl;
        for (uint8_t c : key) {//一文字ずつループを回す
            //std::cout << "uint8_t : " << c << std::endl;
            //std::cout << "node  : " << node << std::endl;
            int next_node = forward(node, c);
           // std::cout << "check : " << bc_[next_node].check << std::endl;
            if (next_node == kFailedIndex) {
                //std::cout << "-------Fauiled value check------------" << std::endl;
                //std::cout << key << std::endl;
                int tmp_base = 0;
                for(uint8_t a : key) {
                    //std::cout << "c: " << a << ", " << int(a) << std::endl;
                    //std::cout << "node : " << tmp_base << std::endl;
                    //std::cout << "base : " << bc_[tmp_base].base << std::endl;
                    int tmp_next = bc_[tmp_base].base + a;
                    //std::cout << "tmp_next : " << tmp_next << std::endl;
                    //std::cout << "check : " << bc_[tmp_next].check << std::endl;
                    if(tmp_base != bc_[tmp_next].check) {
                        break;
                    }
                    tmp_base = tmp_next;
                }
                return false;//このif文に入るとFailedになる
            }
            node = next_node;
        }
        // '\0'
        int next_node = forward(node, kLeafChar);
        return next_node != kFailedIndex;
    }
private:
    int find_base(const std::unordered_map<uint8_t, int>& row) const {
        for (int base = 0; true; ++base) {
            bool found = true;
            for (auto p : row) {
                uint8_t c = p.first;
                int index = base + c;
                //std::cout << "index : " << index << std::endl;
                if (index < bc_.size() and bc_[index].check != kEmptyCheck) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return base;
            }
        }
        std::cout << "DA_SIZE() : " << bc_.size() << std::endl;
        return bc_.size();
    }

    void expand(int index) {
        if (index < bc_.size()){
            return;
            //std::cout << "index : " << index << std::endl;
        }
        //std::cout << "index : " << index << std::endl;
        bc_.resize(index+1);
        //std::cout << "index : " << index << std::endl;
    }

     //ノードindexからでる遷移ラベルを要素とする集合Rを返す
    std::vector<uint8_t> getlabel(int r) {
        std::vector<uint8_t> row;
        int count = 0;
        //std::cout << "base : " << bc_[r].base << std::endl;
        if(bc_[r].base == kEmptyBase) {
            return row;
        }
        for(int i = 1; i < MaxUint8_t; i++) {
            uint8_t c = i;
            int idx = bc_[r].base + c;
            if(r == bc_[idx].check) {
                if (bc_.size() > idx) {
                    //row[c] = 0;
                    row.emplace_back();
                    row[count] = c;
                    count++;
                }
            }
        }

        if (r != 0) {
            int idx = bc_[r].base + kLeafChar;
            if(r == bc_[idx].check) {
                if (bc_.size() > idx) {
                    row.emplace_back();
                    row[kLeafChar] = 0;
                }
            }
        }

        return row;
    }
    //8.30~黒田記述 
    //transitionを確認するための関数
    int forward(int r,uint8_t c)const{
        int t = bc_[r].base + c;
        if(0 < t && t < bc_.size() + 1){
            if(bc_[t].check == r){
                return t;
            }
        }
        else{
            return kFailedIndex;//遷移失敗0を変えす
        }
        return t;//警告けすため　
    }// control reaches end of non-void function

   

};

}