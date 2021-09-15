#include "automata.h"

Automata::Automata(){    

    for(auto & adhoc_node : adhoc_nodes)
        adhoc_node = new Node();

    add_range('1','9',identifer_wchar_ts);

    number_but_0_wchar_ts = identifer_wchar_ts;

    identifer_wchar_ts.push_back('0');

    hex_wchar_ts = number_wchar_ts = identifer_wchar_ts;

    add_range('a','z',identifer_wchar_ts);
    add_range('A','Z',identifer_wchar_ts);
    
    identifer_wchar_ts.push_back('_');

    add_range('A','F',hex_wchar_ts);
    add_range('a','f',hex_wchar_ts);


    add_adhoc_nodes();
    
    std::ifstream in("reserved.in");
    std::string label;
    std::string line,token;
    while(std::getline(in,line)){
        std::stringstream line_stream(line);
        line_stream >> label >> token;
        add_to_trie(token,label);
    }

    add_to_identifier_edges(root);

}
void Automata::add_adhoc_nodes(){
    //0
    auto & root_children = root->children;
    //part 1
    root_children['"']={adhoc_nodes[16],0};
    root_children['#']={adhoc_nodes[0],0};
    root_children['/']={adhoc_nodes[2],0};
    root_children['`']={adhoc_nodes[30],0};
    root_children['\'']={adhoc_nodes[8],0};
    //part 2
    root_children['0']={adhoc_nodes[33],0};
    root_children['.']={adhoc_nodes[58],0};
    specific(root_children,{adhoc_nodes[47],0},number_but_0_wchar_ts);
    //std::vector<wchar_t> letters;
    //specific(root_children,{adhoc_nodes[29],0},letters);
    //root_children['_']={adhoc_nodes[29],0};
    //0
    auto & _0_ch = adhoc_nodes[0]->children;
    _0_ch['!']={adhoc_nodes[1],0};
    //1
    adhoc_nodes[1]->label="ShebangLine";
    auto & _1_ch = adhoc_nodes[1]->children;
    all_but(_1_ch,{adhoc_nodes[1],0},{'\r','\n'});
    //2
    auto & _2_ch = adhoc_nodes[2]->children;
    _2_ch['/']={adhoc_nodes[3],0};
    _2_ch['*']={adhoc_nodes[4],1};
    //3
    adhoc_nodes[3]->label="LineComment";
    auto & _3_ch = adhoc_nodes[3]->children;
    all_but(_3_ch,{adhoc_nodes[3],0},{'\r','\n'});
    //4
    auto & _4_ch = adhoc_nodes[4]->children;
    _4_ch['*']={adhoc_nodes[5],0};
    _4_ch['/']={adhoc_nodes[7],0};
    all_but(_4_ch,{adhoc_nodes[4],0},{'*','/'});
    //5
    auto & _5_ch = adhoc_nodes[5]->children;
    _5_ch['/']={adhoc_nodes[6],-1};
    all_but(_5_ch,{adhoc_nodes[4],0},{'/'});
    //6
    adhoc_nodes[6]->label="DelimitedComment";
    auto & _6_ch = adhoc_nodes[6]->children;
    _6_ch['/']={adhoc_nodes[2],0};
    _6_ch['*']={adhoc_nodes[5],0};
    all_but(_6_ch,{adhoc_nodes[4],0},{'/','*'});
    //7
    auto & _7_ch = adhoc_nodes[7]->children;
    _7_ch['*']={adhoc_nodes[4],1};
    all_but(_7_ch,{adhoc_nodes[4],0},{'*'});
    //8
    auto & _8_ch = adhoc_nodes[8]->children;
    _8_ch['\\']={adhoc_nodes[9],0};
    all_but(_8_ch,{adhoc_nodes[14],0},{'\r','\n','\'','\\'});
    //9
    auto & _9_ch = adhoc_nodes[9]->children;
    _9_ch['u']={adhoc_nodes[10],0};
    specific(_9_ch,{adhoc_nodes[14],0},{'t','b','r','n','\'','"','\\','$'});
    //10
    auto & _10_ch = adhoc_nodes[10]->children;
    std::vector<wchar_t> v_09_AF_af;
    add_range('0','9',v_09_AF_af);
    add_range('A','F',v_09_AF_af);
    add_range('a','f',v_09_AF_af);
    specific(_10_ch,{adhoc_nodes[11],0},v_09_AF_af);
    //11
    auto & _11_ch = adhoc_nodes[11]->children;
    specific(_11_ch,{adhoc_nodes[12],0},v_09_AF_af);
    //12
    auto & _12_ch = adhoc_nodes[12]->children;
    specific(_12_ch,{adhoc_nodes[13],0},v_09_AF_af);
    //13
    auto & _13_ch = adhoc_nodes[13]->children;
    specific(_13_ch,{adhoc_nodes[14],0},v_09_AF_af);
    //14
    auto & _14_ch = adhoc_nodes[14]->children;
    _14_ch['\'']={adhoc_nodes[15],0};
    //15
    adhoc_nodes[15]->label="CharacterLiteral";
    //16
    auto & _16_ch = adhoc_nodes[16]->children;
    _16_ch['"']={adhoc_nodes[19],0};
    _16_ch['\\']={adhoc_nodes[20],0};
    all_but(_16_ch,{adhoc_nodes[17],0},{'"','\\'});
    //17
    auto & _17_ch = adhoc_nodes[17]->children;
    _17_ch['"']={adhoc_nodes[18],0};
    _17_ch['\\']={adhoc_nodes[20],0};
    _17_ch['\n']={adhoc_nodes[57],0};
    all_but(_17_ch,{adhoc_nodes[17],0},{'"','\\','\n'});
    //18
    adhoc_nodes[18]->label="lineStringLiteral";
    //19
    adhoc_nodes[19]->label="lineStringLiteral";
    auto & _19_ch = adhoc_nodes[19]->children;
    _19_ch['"']={adhoc_nodes[25],0};
    //20
    auto & _20_ch = adhoc_nodes[20]->children;
    _20_ch['u']={adhoc_nodes[21],0};
    specific(_20_ch,{adhoc_nodes[17],0},escaped_identifier_wchar_ts);
    //21
    auto & _21_ch = adhoc_nodes[21]->children;
    specific(_21_ch,{adhoc_nodes[22],0},v_09_AF_af);
    //22
    auto & _22_ch = adhoc_nodes[22]->children;
    specific(_22_ch,{adhoc_nodes[23],0},v_09_AF_af);
    //23
    auto & _23_ch = adhoc_nodes[23]->children;
    specific(_23_ch,{adhoc_nodes[24],0},v_09_AF_af);
    //24
    auto & _24_ch = adhoc_nodes[24]->children;
    specific(_24_ch,{adhoc_nodes[17],0},v_09_AF_af);
    //25
    auto & _25_ch = adhoc_nodes[25]->children;
    _25_ch['"']={adhoc_nodes[26],0};
    all_but(_25_ch,{adhoc_nodes[25],0},{'"'});
    //26
    auto & _26_ch = adhoc_nodes[26]->children;
    _26_ch['"']={adhoc_nodes[27],0};
    all_but(_26_ch,{adhoc_nodes[25],0},{'"'});
    //27
    auto & _27_ch = adhoc_nodes[27]->children;
    _27_ch['"']={adhoc_nodes[28],0};
    all_but(_27_ch,{adhoc_nodes[25],0},{'"'});
    //28
    adhoc_nodes[28]->label="multiLineStringLiteral";
    auto & _28_ch = adhoc_nodes[28]->children;
    _28_ch['"']={adhoc_nodes[28],0};
    //all_but(_28_ch,{adhoc_nodes[25],0},{'"'}); X
    //29
        //Pendant because it's for Identifier
    adhoc_nodes[29]->label="Identifier";
    auto & _29_ch = adhoc_nodes[29]->children;
    specific(_29_ch,{adhoc_nodes[29],0},identifer_wchar_ts);
    //30
    auto & _30_ch = adhoc_nodes[30]->children;
    all_but(_30_ch,{adhoc_nodes[31],0},{'\r','\n','`'});
    //31
    auto & _31_ch = adhoc_nodes[31]->children;
    _31_ch['`']={adhoc_nodes[32],0};
    all_but(_31_ch,{adhoc_nodes[31],0},{'\r','\n','`'});
    //32
    adhoc_nodes[32]->label="Identifier";
    //part 2
    //33
    adhoc_nodes[33]->label="IntegerLiteral";
    auto & _33_ch = adhoc_nodes[33]->children;
    _33_ch['F']={adhoc_nodes[46],0};
    _33_ch['f']={adhoc_nodes[46],0};
    _33_ch['.']={adhoc_nodes[42],0};
    _33_ch['E']={adhoc_nodes[43],0};
    _33_ch['e']={adhoc_nodes[43],0};
    _33_ch['_']={adhoc_nodes[45],0};
    _33_ch['L']={adhoc_nodes[54],0};
    _33_ch['b']={adhoc_nodes[34],0};
    _33_ch['B']={adhoc_nodes[34],0};
    _33_ch['x']={adhoc_nodes[38],0};
    _33_ch['X']={adhoc_nodes[38],0};
    _33_ch['u']={adhoc_nodes[55],0};
    _33_ch['U']={adhoc_nodes[55],0};
    specific(_33_ch,{adhoc_nodes[44],0},number_wchar_ts);
    //34
    auto & _34_ch = adhoc_nodes[34]->children;
    _34_ch['0']={adhoc_nodes[35],0};
    _34_ch['1']={adhoc_nodes[35],0};
    //35
    adhoc_nodes[35]->label = "BinLiteral";
    auto & _35_ch = adhoc_nodes[35]->children;
    _35_ch['L']={adhoc_nodes[54],0};
    _35_ch['_']={adhoc_nodes[37],0};
    _35_ch['0']={adhoc_nodes[36],0};
    _35_ch['1']={adhoc_nodes[36],0};
    _35_ch['U']={adhoc_nodes[55],0};
    _35_ch['u']={adhoc_nodes[55],0};
    //36
    adhoc_nodes[36]->label = "BinLiteral";
    auto & _36_ch = adhoc_nodes[36]->children;
    _36_ch['_']={adhoc_nodes[37],0};
    _36_ch['L']={adhoc_nodes[54],0};
    _36_ch['0']={adhoc_nodes[36],0};
    _36_ch['1']={adhoc_nodes[36],0};
    _36_ch['U']={adhoc_nodes[55],0};
    _36_ch['u']={adhoc_nodes[55],0};
    //37
    auto & _37_ch = adhoc_nodes[37]->children;
    _37_ch['_']={adhoc_nodes[37],0};
    _37_ch['0']={adhoc_nodes[36],0};
    _37_ch['1']={adhoc_nodes[36],0};
    //38
    auto & _38_ch = adhoc_nodes[38]->children;
    specific(_38_ch,{adhoc_nodes[39],0},hex_wchar_ts);
    //39
    adhoc_nodes[39]->label = "HexLiteral";
    auto & _39_ch = adhoc_nodes[39]->children;
    _39_ch['_']={adhoc_nodes[41],0};
    _39_ch['L']={adhoc_nodes[54],0};
    _39_ch['U']={adhoc_nodes[55],0};
    _39_ch['u']={adhoc_nodes[55],0};
    specific(_39_ch,{adhoc_nodes[40],0},hex_wchar_ts);
    //40
    adhoc_nodes[40]->label = "HexLiteral";
    auto & _40_ch = adhoc_nodes[40]->children;
    _40_ch['_']={adhoc_nodes[41],0};
    _40_ch['U']={adhoc_nodes[55],0};
    _40_ch['u']={adhoc_nodes[55],0};
    _40_ch['L']={adhoc_nodes[54],0};
    specific(_40_ch,{adhoc_nodes[40],0},hex_wchar_ts);
    //41
    auto & _41_ch = adhoc_nodes[41]->children;
    _41_ch['_']={adhoc_nodes[41],0};
    specific(_41_ch,{adhoc_nodes[40],0},hex_wchar_ts);
    //42
    auto & _42_ch = adhoc_nodes[42]->children;
    _42_ch['.']={adhoc_nodes[59],0};
    specific(_42_ch,{adhoc_nodes[49],0},number_wchar_ts);
    //43
    auto & _43_ch = adhoc_nodes[43]->children;
    _43_ch['+']={adhoc_nodes[51],0};
    _43_ch['-']={adhoc_nodes[51],0};
    specific(_43_ch,{adhoc_nodes[50],0},number_wchar_ts);
    //44
    auto & _44_ch = adhoc_nodes[44]->children;
    _44_ch['_']={adhoc_nodes[45],0};
    _44_ch['e']={adhoc_nodes[43],0};
    _44_ch['E']={adhoc_nodes[43],0};
    _44_ch['f']={adhoc_nodes[46],0};
    _44_ch['F']={adhoc_nodes[46],0};
    _44_ch['.']={adhoc_nodes[42],0};
    specific(_44_ch,{adhoc_nodes[44],0},number_wchar_ts);
    //45
    auto & _45_ch = adhoc_nodes[45]->children;
    _45_ch['_']={adhoc_nodes[45],0};
    specific(_45_ch,{adhoc_nodes[44],0},number_wchar_ts);
    //46
    adhoc_nodes[46]->label = "FloatLiteral";
    //47
    adhoc_nodes[47]->label = "IntegerLiteral";
    auto & _47_ch = adhoc_nodes[47]->children;
    _47_ch['E']={adhoc_nodes[43],0};
    _47_ch['e']={adhoc_nodes[43],0};
    _47_ch['_']={adhoc_nodes[48],0};
    _47_ch['.']={adhoc_nodes[42],0};
    _47_ch['F']={adhoc_nodes[46],0};
    _47_ch['f']={adhoc_nodes[46],0};
    _47_ch['L']={adhoc_nodes[54],0};
    _47_ch['U']={adhoc_nodes[55],0};
    _47_ch['u']={adhoc_nodes[55],0};
    specific(_47_ch,{adhoc_nodes[47],0},number_wchar_ts);
    //48
    auto & _48_ch = adhoc_nodes[48]->children;
    _48_ch['_']={adhoc_nodes[48],0};
    specific(_48_ch,{adhoc_nodes[47],0},number_wchar_ts);
    //49
    adhoc_nodes[49]->label = "DoubleLiteral";
    auto & _49_ch = adhoc_nodes[49]->children;
    _49_ch['_']={adhoc_nodes[52],0};
    _49_ch['F']={adhoc_nodes[46],0};
    _49_ch['f']={adhoc_nodes[46],0};
    _49_ch['E']={adhoc_nodes[43],0};
    _49_ch['e']={adhoc_nodes[43],0};
    specific(_49_ch,{adhoc_nodes[49],0},number_wchar_ts);
    //50
    adhoc_nodes[50]->label = "DoubleLiteral";
    auto & _50_ch = adhoc_nodes[50]->children;
    _50_ch['_']={adhoc_nodes[53],0};
    _50_ch['F']={adhoc_nodes[46],0};
    _50_ch['f']={adhoc_nodes[46],0};
    specific(_50_ch,{adhoc_nodes[50],0},number_wchar_ts);
    //51
    auto & _51_ch = adhoc_nodes[51]->children;
    specific(_51_ch,{adhoc_nodes[50],0},number_wchar_ts);
    //52
    auto & _52_ch = adhoc_nodes[52]->children;
    _52_ch['_']={adhoc_nodes[52],0};
    specific(_52_ch,{adhoc_nodes[49],0},number_wchar_ts);
    //53
    auto & _53_ch = adhoc_nodes[53]->children;
    _53_ch['_']={adhoc_nodes[53],0};
    specific(_53_ch,{adhoc_nodes[50],0},number_wchar_ts);
    //54
    adhoc_nodes[54]->label = "LongLiteral";
    //55
    adhoc_nodes[55]->label = "UnsignedLiteral";
    auto & _55_ch = adhoc_nodes[55]->children;
    _55_ch['L']={adhoc_nodes[56],0};
    //56
    adhoc_nodes[56]->label = "UnsignedLiteral";
    //57
    adhoc_nodes[57]->is_error = true;
    //58
    adhoc_nodes[58]->label= "DOT";
    auto & _58_ch = adhoc_nodes[58]->children;
    specific(_58_ch,{adhoc_nodes[49],0},number_wchar_ts);
    //59
    adhoc_nodes[59]->label = "IntegerLiteral";
    adhoc_nodes[59]->go_back = 2;
    auto & _59_ch = adhoc_nodes[59]->children;
    _59_ch['.'] = {adhoc_nodes[60],0};
    //60
    adhoc_nodes[60]->label = "IntegerLiteral";
    adhoc_nodes[60]->go_back = 3;
}
void Automata::all_but(std::unordered_map<wchar_t,std::pair<Node*,int> > & children,std::pair<Node *,int>to, std::unordered_set<wchar_t> but){
    //dangerous!!
    for(wchar_t c = 0 ;; c++){
        if(but.find(c)==but.end())
            children[c]=to;
        if(c==last_c)
            break;
    }
}
void Automata::specific(std::unordered_map<wchar_t,std::pair<Node*,int> > & children,std::pair<Node *,int>to, std::vector<wchar_t> which){
    for(auto c : which)
        children[c]=to;
}
void Automata::add_range(wchar_t begin,wchar_t end,std::vector<wchar_t> & v){
    if(begin<=end)
        for(;;begin++){
            v.push_back(begin);
            if(begin==end)
                break;
        }
}
Automata::~Automata(){

}
int Automata::get_go_back(){
    return cur->go_back;
}
int Automata::next(wchar_t x){
    auto & children = cur->children;
    auto next = children.find(x);
    if(next!=children.end()){
        openQuotation+=next->second.second;
        cur = next->second.first;
        //patch begin
        /*std::cout << "x: " << x << " ";
        std::cout << "20?: " << (cur==adhoc_nodes[19]) << " ";
        std::cout << "26?: " << (cur==adhoc_nodes[25]) << "\n";*/
        //std::cout << "state label: " << cur->label << " openQuotation: " << openQuotation << "\n";
        //std::cout << "6?: " << (cur == adhoc_nodes[5]) << " " << "7?: " << (cur==adhoc_nodes[6])  << "\n";
        if(cur->label=="DelimitedComment" && openQuotation==0)
            return 2; //inmmediate
        return 1; //later
        //patch end
    }
    return 0;
}
bool Automata::in_error(){
    return cur->is_error;
}
bool Automata::in_token(){
    return !cur->label.empty() && openQuotation==0;
}
std::string Automata::get_token_label(){
    return cur->label;
}
void Automata::add_to_trie(std::string token, std::string label){
    Node * cur = root;
    for(wchar_t c: token){
        auto & children = cur->children;
        auto next = children.find(c);
        if(next==children.end())
            next = children.insert({c,{new Node(),0}}).first;
        cur = next->second.first;
    }
    cur->label = label;
    //cur-> = ;
}
void Automata::restart(){
    cur = root;
    openQuotation=0;
}
void Automata::add_to_identifier_edges(Node * node){
    auto & children =  node->children;
    for(wchar_t c:identifer_wchar_ts){
        if(!isdigit(c)||node!=root){
            auto it = children.find(c);
            if(it==children.end())
                //add edge from node to identifier through c
                children[c]={adhoc_nodes[29],0};
            else{
                //add that this node is identifier
                if(it->second.first->label.empty())
                    it->second.first->label="Identifier";
                add_to_identifier_edges(it->second.first);
            }
        }
    }
}


// int main(){
//     std::cout << "main begin\n";
//     Automata reserved_automata = Automata();
//     std::vector<std::string> words = {
//         "++"
//         ,"+"
//         ,"..."
//         ,"va"
//         ,"*="
//         ,"//efd kdljf fdfs"
//         ,"/*jflkj*/"
//         ,"/*df/*fjldkj*/fd*/"
//         ,"\"j fjlj lkjf\""
//         ,"="
//         ,"`j fllk fjdk`"
//         ,"_4343"
//         ,"hello"
//         ,"bye"
//     };
//     for(auto word : words){
//         reserved_automata.restart();
//         for(auto c:word){
//             assert(reserved_automata.next(c));
//         }
//         assert(reserved_automata.in_token());
//         auto info = reserved_automata.get_token_label_and_();
//         std::cout << "word: " << word << " label: " << info.first <<  " ?: " << info.second << "\n";
//     }
//     std::cout << "main end\n";
// }