//
//  main.cpp
//  20166052_20166024
//
//  Created by toka magdy ragab  on 12/15/18.
//  Copyright © 2018 toka magdy ragab . All rights reserved.
//

#include <iostream>
#include <vector>
#include<cstdlib>
#include<ctime>
#include<limits>

using namespace std;

const int SKIPLIST_MAX_LEVELS = 16;
const float probability = 0.5;

struct node
{
    int value;
    vector<node*> next;
    
    node (int v, int level)
    {
        value = v;
        for (int i = 0; i < level; i++)
            next.emplace_back(nullptr);
    }
};

class skiplist
{
    node* head;
    int value;
    int level;

    int randomLevel()
    {
        srand(time(0));
        int lvl = 1;
        while ((((double)rand()/RAND_MAX)) < probability && (abs(lvl) < SKIPLIST_MAX_LEVELS))
            lvl++;
        return abs(lvl);
    }
    
public:
    skiplist()
    {
        head = new node(value, SKIPLIST_MAX_LEVELS);
        level = 0;
    }
    
    string toString()
    {
        string s = "", t = "";
        node* temp = head->next[0];
        while (temp != nullptr)
        {
            int num = temp->value;
            while (num != 0)
            {
                int n = num % 10;
                t += n+48;
                num /= 10;
            }
            
            for (int i = t.length()-1; i >=0 ; i--)
                s += t[i];
            s += "/";
            t = "";
            temp = temp->next[0];
        }
        return s;
    }
    
    void insert(int v)
    {
        if (find(v))
            return;
        vector<node*> update(head->next);
        node* temp = head;
        for (int i = level; i >= 0; i--)
        {
            while (temp->next[i] != nullptr && temp->next[i]->value < v)
                temp = temp->next[i];
            update[i] = temp;
        }
        temp = temp->next[0];
            
        int lvl = randomLevel();
        if (lvl > level)
        {
                for (int i = level + 1; i < lvl; ++i)
                    update[i] = head;
            level = lvl;
        }
        
        temp = new node(v, lvl);
        
        for (int i = 0; i < lvl; i++)
        {
            temp->next[i] = update[i]->next[i];
            update[i]->next[i] = temp;
        }
    }
    
    void remove(int v)
    {
        node* temp = head;
        vector<node*> update(head->next);
        for (int i = level; i >= 0; i--)
        {
            while (temp->next[i] != nullptr && temp->next[i]->value < v)
                temp = temp->next[i];
            
            update[i] = temp;
        }
        
        temp = temp->next[0];
        
        if (v == temp->value)
        {
            for (int i = 0; i <= level; i++)
            {
                if (update[i]->next[i] != temp)
                    break;
                update[i]->next[i] = temp->next[i];
            }
            delete temp;
            while (level > 0 && head->next[level] == NULL)
                level--;
        }
    }
    
    bool find(int v)
    {
        node* temp = head;
        for (int i = level; i >= 0; i--)
            while (temp->next[i] != nullptr && temp->next[i]->value < v)
                temp = temp->next[i];
        
        temp = temp->next[0];
       
        if (temp != nullptr && v == temp->value)
            return true;
        return false;
    }
    
    int size()
    {
        int size = 0;
        node* temp = head;
        while (temp->next[0] != nullptr)
        {
            temp = temp->next[0];
            size++;
        }
        return size;
    }
    
    ~skiplist()
    {
        delete head;
    }
    
};


int main(int argc, const char * argv[])
{
    skiplist s;
    s.insert(96);
    s.insert(16);
    s.insert(2);
    s.insert(10);
    s.insert(31);
    s.insert(15);
    s.insert(71);
    
    
    cout << "the list's size: " << s.size() << endl;
    cout << "the list: " << s.toString() << endl;
    
    if (s.find(10))
        cout << "10 fouund" << endl;

    cout << "removing 31" << endl;
    s.remove(31);
    
    cout << "the list's size: " << s.size() << endl;
    cout << "the list: " << s.toString() << endl;
    
    return 0;
}
