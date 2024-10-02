class LRUCache {
public:
    struct ListNode {
       //int val;
       pair<int,int> kv_pair;
       ListNode *next;
       ListNode *prev;
       ListNode() : kv_pair(0,0), next(nullptr), prev(nullptr) {}
       ListNode(int x,int y) : kv_pair(x,y), next(nullptr), prev(nullptr) {}
       ListNode(int x, int y, ListNode *next, ListNode *prev) : kv_pair(x,y), next(next), prev(prev) {}
    };
    ListNode* cache_head=nullptr;
    ListNode* cache_tail=nullptr;
    int capacity=0;
    int used_node=0;
    unordered_map <int,int> key_map;

    LRUCache(int capacity) {
        this->capacity=capacity;
        this->cache_head=nullptr;
        this->cache_tail=nullptr;
    }
    
    int get(int key) {
        //使用c++ std::unordered_map查找
        auto it=key_map.find(key);
        if(it==key_map.end())
            return -1;
        else{ //need update the position in LRU cache
            ListNode* cur=cache_head;
            while(cur){
                if(cur->kv_pair.first == key){
                    if(cur==cache_head){
                        break;
                    } else if(cur==cache_tail){
                        cache_tail=cur->prev;
                        cache_tail->next=nullptr;
                        cur->next=cache_head;
                        cur->prev=nullptr;
                        cache_head->prev=cur;
                        cache_head=cur;
                    } else {
                        cur->next->prev=cur->prev;
                        cur->prev->next=cur->next;
                        cur->next=cache_head;
                        cur->prev=nullptr;
                        cache_head->prev=cur;
                        cache_head=cur;
                    }
                    break;
                } else {
                    cur=cur->next;
                }
            }
            return it->second;
        }
    }
    
    void put(int key, int value) {
        auto it=key_map.find(key);
        if(it != key_map.end()){ //key exist, DO update 
        
            //cout<<"01 key exist="<<key<<" ,value="<<value<<endl;        
            ListNode* cur=cache_head; 
            while(cur){
                if(cur->kv_pair.first == key){
                    //cout<<"02 key exist="<<key<<" ,value="<<value<<endl;
                    //update the exist kv pair in std::unodered_map and ListNode.
                    key_map[key]=value;
                    //this->key_map.erase(key);
                    //this->key_map.insert(make_pair(key,value));
                    //cur->kv_pair.second=value;

                    if(cur==cache_head){
                        break;
                    } else if(cur==cache_tail){
                        cache_tail=cur->prev;
                        cache_tail->next=nullptr;
                        cur->next=cache_head;
                        cur->prev=nullptr;
                        cache_head->prev=cur;
                        cache_head=cur;
                        break;
                    } else {
                        cur->next->prev=cur->prev;
                        cur->prev->next=cur->next;
                        cur->next=cache_head;
                        cur->prev=nullptr;
                        cache_head->prev=cur;
                        cache_head=cur; //new edit
                        break;
                    }
                } else {
                    cur=cur->next;
                }
            }
        } else { //key not exist, DO insert & delete
            //LRU not full
            if(is_empty()){
                cout<<"key not exist,LRU empty"<<endl;
                //insert
                ListNode* new_node=new ListNode(key, value, nullptr, nullptr);
                this->cache_head=new_node;
                this->cache_tail=new_node;
                this->used_node++;
                key_map[key]=value;
            } else if(!is_full()){
                cout<<"key not exist,LRU not full"<<endl;
                //insert
                ListNode* new_node=new ListNode(key, value, cache_head, nullptr);
                this->cache_head->prev=new_node;
                this->cache_head=new_node;
                this->used_node++;
                key_map[key]=value;
            } else { //LRU full
                cout<<"key not exist,LRU full"<<endl;
                //insert
                ListNode* new_node=new ListNode(key, value, cache_head, nullptr);
                this->cache_head->prev=new_node;
                this->cache_head=new_node;
                //delete
                ListNode* temp=cache_tail;
                cache_tail=cache_tail->prev;
                cache_tail->next=nullptr;
                
                key_map.erase(temp->kv_pair.first);
                key_map[key]=value;
                
                delete temp;
            }
        }
        print_LRU();
    }

    bool is_full(){
        if(this->used_node < this->capacity)
            return false;
        else
            return true;
    }
    bool is_empty(){
        if(this->used_node==0)
            return true;
        else
            return false;
    }
    void print_LRU(){
        ListNode* cur=cache_head;
        cout<<"# of node="<<used_node<<", LRU list:";
        while(cur){
            cout<<" "<<cur->kv_pair.first;
            cur=cur->next;
        }
        cout<<endl;
    }
    
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
