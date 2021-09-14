#ifndef REGEXER_H
#define REGEXER_H

#include <regex>
#include <iostream>

class Regexer{

    public:
        Regexer();
        virtual ~Regexer();
        void restart();
        std::string get_token_label(const std::string & token);
        std::string DecDigitNoZero = "[1-9]";
        std::string DecDigit = "[0-9]";
        std::string DecDigitOrSeparator = "[0-9_]";
        std::string DecDigits="("+DecDigit+DecDigitOrSeparator+"*)?"+DecDigit;
        std::string DoubleExponent = "[eE][\\+-]?("+DecDigits+")";
        std::string DoubleLiteral = "("+DecDigits+")?\\.("+DecDigits+")("+DoubleExponent+")?|("+DecDigits+")("+DoubleExponent+")"; //((#(#|_)*)?#)?\.((#(#|_)*)?#)(ES?((#(#|_)*)?#))?|((#(#|_)*)?#)(ES?((#(#|_)*)?#))
        //((#(#|_)*)?#)?P(#(#|_)*)?#(ES?(#(#|_)*)?#)?|((#(#|_)*)?#)(ES?(#(#|_)*)?#)->//(((#|0)(#|_|0)*)?(#|0))?P((#|0)(#|_|0)*)?(#|0)(ES?((#|0)(#|_|0)*)?(#|0))?|(((#|0)(#|_|0)*)?(#|0))(ES?((#|0)(#|_|0)*)?(#|0))
        std::string FloatLiteral = "(("+DoubleLiteral+")|"+"("+DecDigits+"))[fF]";
        std::string IntegerLiteral = "("+DecDigitNoZero+DecDigitOrSeparator+"*)?"+DecDigit;// ([1-9][0-9_]*)?[0-9] -> ("&*)?# -> (#(_|0|#))
        std::string HexDigit = "[0-9A-Fa-f]";
        std::string HexDigitOrSeparator = "[0-9A-Fa-f_]";
        std::string HexLiteral = "0[xX]("+HexDigit+HexDigitOrSeparator+"*)?"+HexDigit;//0[xX]([0-9A-Fa-f][0-9A-Fa-f_]*)?[0-9A-Fa-f]->0>(<(<|_)*)?<
        std::string BinDigit = "[01]";
        std::string BinDigitOrSeparator = "[01_]";
        std::string BinLiteral = "0[bB]("+BinDigit+BinDigitOrSeparator+"*)?"+BinDigit; //0(b|B)((0|1)(0|1|_)*)?(0|1) -> 0$(!%*)?!
        std::string UnsignedLiteral = "("+IntegerLiteral+"|"+HexLiteral+BinLiteral+")[uU]L?";
        std::string LongLiteral = "("+IntegerLiteral+"|"+HexLiteral+BinLiteral+")L";
        ///double,int and float -> 
        // ((((#|0)(#|_|0)*)?(#|0))?P((#|0)(#|_|0)*)?(#|0)(ES?((#|0)(#|_|0)*)?(#|0))?|(((#|0)(#|_|0)*)?(#|0))(ES?((#|0)(#|_|0)*)?(#|0)))F?
        // |(#(#|_|0)*)?(#|0)
        // |((#|0)(#|_|0)*)?(#|0)F
    private:
        
        std::vector<std::pair<std::regex,std::string>> regexes = {
            {std::regex(BinLiteral),"BinLiteral"} 
            ,{std::regex(IntegerLiteral),"IntegerLiteral"}
            ,{std::regex(HexLiteral),"HexLiteral"}
            ,{std::regex(UnsignedLiteral),"UnsignedLiteral"}
            ,{std::regex(LongLiteral),"LongLiteral"}
            ,{std::regex(DoubleLiteral),"DoubleLiteral"}
            ,{std::regex(FloatLiteral),"FloatLiteral"}
        };
        
};

#endif // REGEXER_H