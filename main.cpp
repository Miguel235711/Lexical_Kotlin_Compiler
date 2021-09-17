#include "automata.h"

#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <fstream>
#include <cstring>
#include <functional>
#include <unordered_set>

std::string cases_path = "./cases/";


std::string get_char_error_msg(int row,int col,wchar_t c,const std::string & path){
    return path+":"+std::to_string(row)+":"+std::to_string(col)+": error: ";
}

void print_error(int row,int col,wchar_t c,std::string & path,std::string & token,std::function<void(std::string)> & out){
    token.push_back(c);
    out(get_char_error_msg(row,col,token.back(),path)+token+" is not a valid token\n");
}

std::unordered_set<std::string> to_ignore_tokens = {"DelimitedComment","LineComment"};

void handle_found_token(const std::string & token,Automata & automata,std::function<void(std::string)> & out,std::vector<std::pair<std::string,std::string> > & tokens){
    auto label = automata.get_token_label();
    if(to_ignore_tokens.find(label)==to_ignore_tokens.end()){
        out(token+" "+(label)+"\n");
        tokens.push_back({token,label});
    }
}

int analyze_file(std::string path,Automata automata,std::function<void(std::string)> & out,std::vector<std::pair<std::string,std::string> > & tokens){
    out(path+"\n");
    auto in_stream = std::wifstream(path);
    if(!in_stream.is_open()){
        out("error opening file "+path+"\n");
        return EXIT_FAILURE;
    }
    //analysis logic: TODO
    wchar_t c;
    std::string token;
    int next_status,row=1,col=0;
    auto handle_char = [&](wchar_t c){
        if(c=='\n'||c=='\r'){
            row++;
            col=0;
        }else
            col++;
        if(!(next_status=automata.next(c))){
            if(automata.in_token()){
                //token found
                //continue with c by going back X+1 char determined by state and pop from token X char
                int go_back = automata.get_go_back();
                for(int i = 0; i <= go_back; i++)
                    in_stream.unget();
                while(go_back--)
                    token.pop_back();
                handle_found_token(token,automata,out,tokens);
            }else{
                //check if it is space token to ignore it,otherwise print that the token cannot be recognized
                if(!isspace(c)||!token.empty()){
                    //std::cout << "token: " << token << " c: " << c << "\n"; 
                    //if(token.empty())
                    print_error(row,col,c,path,token,out);
                    return EXIT_FAILURE;
                }/*else if(isspace(c))
                    //NL WS
                    if(c=='\n' || c=='\r')
                        std::cout << "NL\n";*/
                //ignore space
            }
            automata.restart();
            token="";
        }else if(automata.in_error()){
            print_error(row,col,c,path,token,out);
            return EXIT_FAILURE;
        }else{
            token.push_back(c);
            if(next_status==2){
                //inmmediate
                //token found
                handle_found_token(token,automata,out,tokens);
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
            return EXIT_FAILURE;
    }
    handle_char('\n'); //for last token
    if(token!=""){
        //error 
        print_error(row-1,col,c,path,token,out);
        return EXIT_FAILURE;
    }
    in_stream.close();
    return EXIT_SUCCESS;
    //return 0;
}

bool testing = false;

int main(int argc,char ** argv){

    std::vector<std::string> filenames; 

    std::string out_file_name;

    for(int i = 1 ; i < argc; i ++){
        auto str_n = strlen(argv[i]);
        if(out_file_name.empty() && str_n>3 && argv[i][0]=='-'&&argv[i][1]=='f'&&argv[i][2]=='='){
            out_file_name = &argv[i][3];
        }else{
            //filename
            filenames.push_back(argv[i]);
        }
    }

    // std::cout << out_file_name << "\n";
    //std::cout << filenames.size() << "\n";
    DIR *dir;
    dirent * ent;

    auto cases_path_c_str = cases_path.c_str();

    auto automata = Automata(); //remember to have it restarted each time it opens a new file

    auto f_out_stdout = [&](const std::string & x){
        std::cout << x;
    };
    std::ofstream out;
    if(!out_file_name.empty())
        out.open(out_file_name);
    auto f_out_custom_file = [&](const std::string & x){
        out << x;
    };

    std::function<void(std::string)> f_out;
    if(out_file_name.empty())
        f_out = f_out_stdout;
    else
        f_out = f_out_custom_file;

    if(testing){
        if((dir=opendir(cases_path_c_str))!=NULL){
            while((ent=readdir(dir))!=NULL){
                //std::cout << "*** filename: " << ent->d_name << "\n";
                if(strcmp(ent->d_name,".")&&strcmp(ent->d_name,"..")){
                    char path[1024];
                    sprintf(path,"%s%s",cases_path_c_str,ent->d_name);
                    std::vector<std::pair<std::string,std::string> > tokens;
                    if(analyze_file(std::string(path),automata,f_out,tokens)==EXIT_FAILURE)
                        return EXIT_FAILURE;
                }
            }
        }else{
            std::cout << "error getting testing directory\n";
            return EXIT_FAILURE;
        }
    }else{
        for(auto file_name : filenames){
            std::vector<std::pair<std::string,std::string> > tokens;
            if(analyze_file(file_name,automata,f_out,tokens)==EXIT_FAILURE)
                return EXIT_FAILURE;
        }
    }
    out.close();
    
    return EXIT_SUCCESS;
}