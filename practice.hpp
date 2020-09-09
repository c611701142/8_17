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
public:
    //StringSet() = default;
    StringSet() {
        bc_ = {{kEmptyBase, 1}}; // set root element
    }
    
private:
    //配列がその要素を含むようにサイズを変更する必要がある
    void w_base(int index,int val){
        if(index > bc_.size()){
            bc_.resize(index);
        }

        bc_[index].base = val;

    }

    //base[index]にvalを格納する
     //valは設定する値
     //index > DA_SIZEの時のDA_SIZEをindexまで拡張する
    void w_check(int index,int val){
        if(index > bc_.size()){
            bc_.resize(index);
        }

        bc_[index].check = val;
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
    }// control reaches end of non-void function
public:
     void modify(int index,std::vector<uint8_t> row,int b){
        const std::string str;
        int q = 0;
        for(uint8_t c : str) {//各文字に１　数字を割り当て
            //M-1新しいbase[index]の決定
            int old_base = bc_[index].base;//退避しておく
            //bc_[index].base = w_check(index,x_check(b));//新しいbase値を設定　ここエラー
            w_check(index,x_check(b));//新しいbase値を設定
            //M-2遷移の移動
            int old_t = old_base + c;
            int t =  bc_[index].base + c;
            w_base(t,bc_[old_t].base);//古い遷移先のbase値をコピー
            if(bc_[old_t].base > 0){
                if(bc_[q].check == old_t){//手順M-3
                    w_check(q,t);//新しい遷移先の遷移先を再定義
                }
            } 

        }
        
    }
    

    //キー追加時に衝突が起こった場合、ノードの移動によって衝突を回避し、
    //キーの残りの文字列を追加する
    void insert(int index,int pos){
        const std::string str;
        std::vector<uint8_t> row;
        uint8_t c;
        if(bc_[index].base >= 0){//遷移している
            //衝突が起こったときの処理 I-1
            for(uint8_t c : str) {//各文字に１　数字を割り当て
                int t = bc_[index].base + c;
                if(bc_[t].check > 0){
                    row = getlabel(index);//変数Rにセット
                    modify(index,row,c);//ノードの移動処理
                //}
                //遷移先の定義 I-2
                int t = bc_[index].base + c;
                w_check(t,index);//遷移を定義
                pos++;
                //残りの文字列の追加 I-3
                //a_posとは何か？
                int new_base = x_check(c);//新しいbase値を定義
                t = bc_[index].base + c;
                //bc_[t].check = w_check(t,index);
                w_check(t,index);
                pos++;
                }
                else if(bc_[t].check < 0){//葉ノード
                w_base(t,-1);
                }
            }
        }
    }

    //葉ノードindexを削除することで実現
    //検索成功時に呼び出す
    void delete_sucsess(int index){
        w_base(index,0);
        w_check(index,0); 
    }

    // 文字列を追加するための関数
    int trie_search(const std::string str) {
        //D-1初期化
        int index = 1;//現在のindex番号
        int pos = 1;//キーの文字位置を示す
        //D-3終了判定
        //std::cout << str << std::endl;
        if(bc_[index].base >= 0){//遷移している
            //D-2
            for(uint8_t c : str) {//各文字に１　数字を割り当て
                int t = forward(index,c);
                /*
                std::cout << "-----------------------------" << std::endl;
                std::cout << str << std::endl;
                std::cout << t << std::endl;
                std::cout << c << std::endl;
                */
                if(t == 0){//探索失敗
                    //この時にinsertを呼び出すことで、追加アルゴリズムが実現(2.2.2.)
                    insert(index,pos);
                    return 0;
                    exit(0);
                }
                else if(t != 0){
                    t = index;
                    pos++;//次の文字を探索するためインクリメント
                }
            
            }
        }
        else if(bc_[index].base < 0 ){//indexは葉ノードとなり、検索成功
            delete_sucsess(index);
            return index;
        }
    }

//単語
    bool contains(const std::string& key) const {
        int node = 1; // root
        for (uint8_t c : key) {
            std::cout << key  << std::endl;
            int next_node = bc_[node].base + c;
            if (bc_[next_node].check != node) {
                return false;
            }
            node = next_node;
        }
        // '\0'
        int next_node = bc_[node].base + kLeafChar;
        return bc_[next_node].check == node;
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
            return ;
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
    

   

};

}