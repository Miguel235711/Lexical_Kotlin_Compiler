#include "regexer.h"

Regexer::Regexer(){

}
Regexer::~Regexer(){

}
std::string Regexer::get_token_label(const std::string & token){
    for(auto regex: regexes){
        if(std::regex_match(token,regex.first))
            return regex.second;
    }
    return "";
}


int main(){
    auto regexer = Regexer();
    std::cout << regexer.BinLiteral << "\n";
    std::cout << regexer.IntegerLiteral << "\n";
    std::cout << regexer.HexLiteral << "\n";
    std::cout << regexer.DoubleLiteral << "\n";
    std::cout << regexer.FloatLiteral << "\n";
    std::cout << regexer.IntegerLiteral << "\n";
}

/*int main(){
    auto regexer = Regexer();
    std::cout<<regexer.get_token_label("9.3f")<<"\n";
    std::cout<<regex_match("343f",regexes[6].first)<<"\n";
    std::cout<<regex_match("34.31",regexes[5].first)<<"\n";
    std::cout<<regex_match("0",regexes[1].first)<<"\n";
    std::cout<<regex_match("03",regexes[1].first)<<"\n"; // 0
    std::cout<<regex_match("34",regexes[1].first)<<"\n";
    std::cout<<regex_match("0b100",regexes[0].first)<<"\n";
    std::cout<<regex_match("0b0",regexes[0].first)<<"\n";
    std::cout<<regex_match("0b",regexes[0].first)<<"\n"; //0
    std::cout<<regex_match("0b0__1",regexes[0].first)<<"\n";
}*/