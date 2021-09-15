#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <string>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <cwchar>

//testing libraries

#include <vector>
#include <cassert>

class Automata{

    struct Node{
        Node(){
            go_back=is_error=0;
        }
        std::unordered_map<wchar_t,std::pair<Node*,int> > children;
        std::string label;
        bool is_error;
        int go_back;
    };

    public:
        Automata();
        virtual ~Automata();
        void restart();
        int next(wchar_t x); //True if successfull , False if failure
        bool in_token();//True if in reserved word
        std::string get_token_label();
        bool in_error();
        int get_go_back();
    private:
        Node * root = new Node(), * cur = root;
        int openQuotation = 0;
        wchar_t last_c = WCHAR_MAX;
        void add_to_trie(std::string token, std::string label);
        std::vector<Node*> adhoc_nodes = std::vector<Node*>(61);
        void add_adhoc_nodes();
        void all_but(std::unordered_map<wchar_t,std::pair<Node*,int> > & children,std::pair<Node *,int>to, std::unordered_set<wchar_t> but);
        void specific(std::unordered_map<wchar_t,std::pair<Node*,int> > & children,std::pair<Node *,int>to, std::vector<wchar_t> which);
        void add_range(wchar_t begin,wchar_t end,std::vector<wchar_t> & v);
        void add_to_identifier_edges(Node * node);
        std::vector<wchar_t> identifer_wchar_ts,number_wchar_ts,number_but_0_wchar_ts,hex_wchar_ts,escaped_identifier_wchar_ts={'t','b','r','n','\'','"','\\','$'};
};

#endif // AUTOMATA_H