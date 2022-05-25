#include "OrgChart.hpp"
#include <string>
#include <iostream>

using namespace std;

namespace ariel{
    OrgChart::Iterator::Iterator(){
        this->ptr = NULL;
        this->order = "";
    }
    OrgChart::Iterator::Iterator(const OrgChart &o, const string& order){
        this->ptr = o.root;
        this->order = order;
        if(order == "level"){
            queue<struct Tree*> temp;
            if(!this->ptr->data.empty()){
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
            if(!this->ptr->data.empty()){
                temp.push(this->ptr);
            }
            while (!temp.empty())
            {
                struct Tree* curr = temp.front();
                temp.pop();
                if(!curr->children.empty() && curr->children.at(0)!=NULL){
                    for(int i=(int)curr->children.size()-1; i>=0; i--){
                        uint pos = unsigned (i);
                        temp.push(curr->children.at(pos));
                    }
                }
                this->s.push(curr);
            } 
        }
        else{
            if(!this->ptr->data.empty()){
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
    
    bool OrgChart::Iterator::operator==(const Iterator &other) const{
        if(this->order == "level" || this->order == "pre"){
            if(this->q.empty() && other.q.empty()){
                return true;
            }
            return(this->q.front() == other.q.front());
        }
        if(this->s.empty() && other.s.empty()){
            return true;
        }
        if(other.s.empty()){
            return false;
        }
        return(this->s.top() == other.s.top());
    }
    
    bool OrgChart::Iterator::operator!=(const Iterator &other) const{
        return !(*this == other);
    }

    OrgChart::Iterator& OrgChart::Iterator::operator=(const Iterator &other){
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
        return &(this->get_node()->data);
    }

    struct Tree* OrgChart::Iterator::get_node(){
        if(this->order == "level" || this->order == "pre"){
            return(this->q.front());
        }
            return(this->s.top());
    }
    
    OrgChart::OrgChart(){
        this->root = new struct Tree;
        (*this->root).data = "";
        (*this->root).children.push_back(NULL);
    }

    OrgChart& OrgChart::add_root(const string &s){
        if(s.empty()){
            throw("can't enter empty string");
        }
        (*this->root).data = s;
        return *this;
    }

    OrgChart& OrgChart::add_sub(const string &sup, const string &inf){
        if(inf.empty()){
            throw("can't enter empty string");
        }
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
        throw("first argument doesn't exist");
        return *this;
    }
    OrgChart::Iterator OrgChart::begin() const{
        return begin_level_order();
    }
    OrgChart::Iterator OrgChart::end() const{
        return end_level_order();
    }
    OrgChart::Iterator OrgChart::begin_level_order() const{
        if(this->root->data.empty()){
            throw("chart is empty!");
        }
        return Iterator(*this, "level");
    }
    OrgChart::Iterator OrgChart::end_level_order() const{
        if(this->root->data.empty()){
            throw("chart is empty!");
        }
        Iterator end;
        return end;
    }
    OrgChart::Iterator OrgChart::begin_reverse_order(){
        if(this->root->data.empty()){
            throw("chart is empty!");
        }
        return Iterator(*this, "reverse");
    }
    OrgChart::Iterator OrgChart::reverse_order(){
        if(this->root->data.empty()){
            throw("chart is empty!");
        }
        Iterator end;
        return end;
    }
    OrgChart::Iterator OrgChart::begin_preorder(){
        if(this->root->data.empty()){
            throw("chart is empty!");
        }
        return Iterator(*this, "pre");
    }
    OrgChart::Iterator OrgChart::end_preorder(){
        if(this->root->data.empty()){
            throw("chart is empty!");
        }
        Iterator end;
        return end;
    }
    std::ostream& operator<<(std::ostream& output, const OrgChart& other){
        string res;
        for(auto it = other.begin(); it != other.end(); ++it){
            res += *it;
            res += " ";
        }
        return output<<res;
    }
}