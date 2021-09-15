#include "automata.h"

#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <fstream>
#include <cstring>

std::string cases_path = "./cases/";

int main(){
    DIR *dir;
    dirent * ent;

    auto cases_path_c_str = cases_path.c_str();

    auto automata = Automata(); //remember to have it restarted each time it opens a new file

    if((dir=opendir(cases_path_c_str))!=NULL){
        while((ent=readdir(dir))!=NULL){
            //std::cout << "*** filename: " << ent->d_name << "\n";
            if(strcmp(ent->d_name,".")&&strcmp(ent->d_name,"..")){
                char path[512];
                sprintf(path,"%s%s",cases_path_c_str,ent->d_name);
                std::cout << path << "\n";
                auto in_stream = std::wifstream(path);
                if(!in_stream.is_open()){
                    std::cout << "error opening file " << path << "\n";
                    return EXIT_FAILURE;
                }
                //analysis logic: TODO
                wchar_t c;
                std::string token;
                int next_status;
                auto handle_char = [&](wchar_t c){
                    if(!(next_status=automata.next(c))){
                        if(automata.in_token()){
                            //token found
                            //continue with c by going back X+1 char determined by state and pop from token X char
                            int go_back = automata.get_go_back();
                            for(int i = 0; i <= go_back; i++)
                                in_stream.unget();
                            while(go_back--)
                                token.pop_back();
                            std::cout << token << " " << automata.get_token_label() << "\n";
                        }else{
                            //check if it is space token to ignore it,otherwise print that the token cannot be recognized
                            if(!isspace(c)||!token.empty()){
                                //std::cout << "token: " << token << " c: " << c << "\n"; 
                                if(token.empty())
                                    token.push_back(c);
                                std::cout << token << " is not a valid token\n";
                                return EXIT_FAILURE;
                            }
                            //ignore space
                        }
                        automata.restart();
                        token="";
                    }else if(automata.in_error()){
                        token.push_back(c);
                        std::cout << token << " is not a valid token\n";
                        return EXIT_FAILURE;
                    }else{
                        token.push_back(c);
                        if(next_status==2){
                            //inmmediate
                            //token found
                            std::cout << token << " " << automata.get_token_label() << "\n";
                            automata.restart();
                            token="";
                        }
                    }
                    return EXIT_SUCCESS;
                };
                while(in_stream.get(c)){
                    //std::cout << "is c == \\: " << (c=='\\') << "\n";
                    //std::cout << "c: " << c << 'é' << "\n";
                    if(handle_char(c)==EXIT_FAILURE)
                        return  EXIT_FAILURE;
                }
                handle_char('\n'); //for last token
                in_stream.close();
                //return 0;
            }
        }
    }else{
        std::cout << "error getting directory\n";
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}