#ifndef RESERVED_AUTOMATA_H
#define RESERVED_AUTOMATA_H

#include <string>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>

//testing libraries

#include <vector>
#include <cassert>

class Reserved_Automata{

    struct Node{
        Node(){}
        std::unordered_map<char,Node*> children;
        std::string label;
        bool is_isolated;
    };

    public:
        Reserved_Automata();
        virtual ~Reserved_Automata();
        void restart();
        bool next(char x); //True if successfull , False if failure
        bool in_reserved_word(); //True if in reserved word
        std::pair<std::string,int> get_reserved_word_label_and_is_isolated();
    private:
        Node * root = new Node(), * cur = root;
        void add_to_trie(std::string token, std::string label, bool is_isolated);
};

#endif // RESERVED_AUTOMATA_H