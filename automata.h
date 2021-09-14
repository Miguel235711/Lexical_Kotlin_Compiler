#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <string>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>

//testing libraries

#include <vector>
#include <cassert>

class Automata{

    struct Node{
        Node(){
            go_back=is_error=0;
        }
        std::unordered_map<char,std::pair<Node*,int> > children;
        std::string label;
        bool is_error;
        int go_back;
    };

    public:
        Automata();
        virtual ~Automata();
        void restart();
        int next(char x); //True if successfull , False if failure
        bool in_token();//True if in reserved word
        std::string get_token_label();
        bool in_error();
        int get_go_back();
    private:
        Node * root = new Node(), * cur = root;
        int openQuotation = 0;
        char last_c = char(255);
        void add_to_trie(std::string token, std::string label);
        std::vector<Node*> adhoc_nodes = std::vector<Node*>(61);
        void add_adhoc_nodes();
        void all_but(std::unordered_map<char,std::pair<Node*,int> > & children,std::pair<Node *,int>to, std::unordered_set<char> but);
        void specific(std::unordered_map<char,std::pair<Node*,int> > & children,std::pair<Node *,int>to, std::vector<char> which);
        void add_range(char begin,char end,std::vector<char> & v);
        void add_to_identifier_edges(Node * node);
        std::vector<char> identifer_chars,number_chars,number_but_0_chars,hex_chars,escaped_identifier_chars={'t','b','r','n','\'','"','\\','$'};
};

#endif // AUTOMATA_H