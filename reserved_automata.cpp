#include "reserved_automata.h"

Reserved_Automata::Reserved_Automata(){
    std::ifstream in("reserved.in");
    std::string line,label,token;
    int is_isolated;
    while(std::getline(in,line)){
        std::stringstream line_stream(line);
        line_stream >> label >> token >> is_isolated;
        add_to_trie(token,label,is_isolated);
    }
}
Reserved_Automata::~Reserved_Automata(){

}
bool Reserved_Automata::next(char x){
    auto & children = cur->children;
    auto next = children.find(x);
    if(next!=children.end()){
        cur = next->second;
        return true;
    }
    return false;
}
bool Reserved_Automata::in_reserved_word(){
    return !cur->label.empty();
}
std::pair<std::string,int> Reserved_Automata::get_reserved_word_label_and_is_isolated(){
    return std::make_pair(cur->label,cur->is_isolated);
}
void Reserved_Automata::add_to_trie(std::string token, std::string label, bool is_isolated){
    Node * cur = root;
    for(char c: token){
        auto & children = cur->children;
        auto next = children.find(c);
        if(next==children.end())
            next = children.insert({c,new Node()}).first;
        cur = next->second;
    }
    cur->label = label;
    cur->is_isolated = is_isolated;
}
void Reserved_Automata::restart(){
    cur = root;
}


int main(){
    Reserved_Automata reserved_automata = Reserved_Automata();
    std::vector<std::string> words = {"++","+","...","val","*="};
    for(auto word : words){
        reserved_automata.restart();
        for(auto c:word){
            assert(reserved_automata.next(c));
        }
        assert(reserved_automata.in_reserved_word());
        auto info = reserved_automata.get_reserved_word_label_and_is_isolated();
        std::cout << "word: " << word << " label: " << info.first <<  " is_isolated?: " << info.second << "\n";
    }
}