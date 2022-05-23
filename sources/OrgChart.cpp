#include "OrgChart.hpp"
#include <string>
#include <iostream>

using namespace std;

namespace ariel{
    OrgChart::Iterator::Iterator(){
        this->ptr = NULL;
        this->order = "";
    }
    OrgChart::Iterator::Iterator(const OrgChart &o, string order){
        this->ptr = o.root;
        this->order = order;
        if(order == "level"){
            queue<struct Tree*> temp;
            if(this->ptr->data!= ""){
                temp.push(this->ptr);
            }
            while (!temp.empty())
            {
                struct Tree* curr = temp.front();
                temp.pop();
                if(curr->children.at(0)!=NULL){
                    for(unsigned int i=0; i<curr->children.size(); i++){
                        temp.push(curr->children.at(i));
                    }
                }
                this->q.push(curr);
            }    
        }
        else if(order == "reverse"){
            queue<struct Tree*> temp;
            if(this->ptr->data!= ""){
                temp.push(this->ptr);
            }
            while (!temp.empty())
            {
                struct Tree* curr = temp.front();
                temp.pop();
                if(curr->children.at(0)!=NULL){
                    for(unsigned int i=curr->children.size()-1; i>=0; i--){
                        temp.push(curr->children.at(i));
                    }
                }
                this->s.push(curr);
            } 
        }
        else{
            if(this->ptr->data != ""){
                preorder(this->ptr);
            }
        }
    }

    void OrgChart::Iterator::preorder(struct Tree* node){
        if(node == NULL){
            return;
        }
        this->q.push(node);
        for(unsigned int i=0; i < node->children.size(); i++){
            preorder(node->children.at(i));
        }
    }
    
    OrgChart::Iterator& OrgChart::Iterator::operator++(){
        if(this->order == "level" || this->order == "pre"){
            this->q.pop();
        }
        else{
            this->s.pop();
        }
        return *this;
    }
    
    string OrgChart::Iterator::operator*(){
        return this->get_node()->data;
    }
    
    bool OrgChart::Iterator::operator==(Iterator other){
        if(this->order == "level" || this->order == "pre"){
            if(this->q.empty() && other.q.empty()){
                return true;
            }
            return(this->q.front() == other.q.front());
        }
        else{
            if(this->s.empty() && other.s.empty()){
                return true;
            }
            return(this->s.top() == other.s.top());
        }
    }
    
    bool OrgChart::Iterator::operator!=(Iterator other){
        return !(*this == other);
    }

    OrgChart::Iterator& OrgChart::Iterator::operator=(Iterator &other){
        if(this == &other){//a=a
            return(*this); 
        }
        this->ptr = other.ptr;
        this->order = other.order;
        this->q = other.q;
        this->s = other.s;
        return *this;
    }

    string* OrgChart::Iterator::operator->(){
        return &this->get_node()->data;
    }

    struct Tree* OrgChart::Iterator::get_node(){
        if(this->order == "level" || this->order == "pre"){
            return(this->q.front());
        }
        else{
            return(this->s.top());
        }
    }
    
    OrgChart::OrgChart(){
        this->root = new struct Tree;
        (*this->root).data = "";
        (*this->root).children.push_back(NULL);
    }

    OrgChart& OrgChart::add_root(string s){
        (*this->root).data = s;
        return *this;
    }

    OrgChart& OrgChart::add_sub(string sup, string inf){
        for(auto it = this->begin_level_order(); it != this->end_level_order(); ++it){
            if(*it == sup){
                struct Tree *curr = new struct Tree;
                curr->data = inf;
                curr->children.push_back(NULL);
                if(it.get_node()->children[0] == NULL){
                    it.get_node()->children[0] = curr;
                }else{
                    it.get_node()->children.push_back(curr);
                }
                return *this;
            }
        }
        throw("%s doesn't exist", sup);
        return *this;
    }
    OrgChart::Iterator OrgChart::begin() const{
        return begin_level_order();
    }
    OrgChart::Iterator OrgChart::end() const{
        return end_level_order();
    }
    OrgChart::Iterator OrgChart::begin_level_order() const{
        return Iterator(*this, "level");
    }
    OrgChart::Iterator OrgChart::end_level_order() const{
        Iterator end;
        return end;
    }
    OrgChart::Iterator OrgChart::begin_reverse_order(){
        return Iterator(*this, "reverse");
    }
    OrgChart::Iterator OrgChart::reverse_order(){
        Iterator end;
        return end;
    }
    OrgChart::Iterator OrgChart::begin_preorder(){
        return Iterator(*this, "pre");
    }
    OrgChart::Iterator OrgChart::end_preorder(){
        Iterator end;
        return end;
    }
    std::ostream& operator<<(std::ostream& output, const OrgChart& other){
        string res;
        for(auto it = other.begin(); it != other.end(); ++it){
            res += *it;
        }
        return output<<res;
    }
}