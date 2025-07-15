#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <iomanip>

using namespace std;

// Enumeracion de Tokens
enum class TokenType{
    
    // Simbolos individuales
    NYA_OPEN, NYA_CLOSE, MEOW_OPEN, MEOW_CLOSE,
    NYEND, SPLITTY, DOTTY,
    ADDY_CHAN, SUBBY_KITTY, STARRY, SLASHY,
    LOWO, SHARPOWO, AMPY, POINU,

    // Operadores logicos
    GETS_CHAN, SAME_UWU, NOTTY_KITTY, NUSAME_OWO,
    BIGGA_CHAN, BIGGE_SAN, SMAL_CHAN, SMALE_SAN,
    AND, OR,

    // Tipos de datos
    INT, FLOAT, DOUBLE, CHAR, STRING, BOOL, NYULL,

    // Estructuras selectivas
    IFNYA, ELSUWU, ELYF, TRU, FOLS, SWITCH, CASE, DEFAULT,

    // Estructuras repetitivas
    DO, WHILE, FOR, BREAK, CONTINUE,

    // Funciones y clases
    VOID, RETURN, CLASS, STRUCT,

    // Identificadores varios
    PRINTF, SCANF, INCLUDE, NAMESPACE, NEW, DELETE,

    // Basicos
    IDENTIFIER, NUMBER, STRING_LITERAL,

    // Finales
    END_OF_FILE, UNKNOWN
};

// Estructura del Token
struct Token{
    TokenType type;
    string lexeme;
    int line;
};

//Estructura de Simbolos (para la tabla)
struct Simbolo{
    string nombre;
    string tipo;
    string valor;
    int linea;
    const void* direccion;
};

// Mapeo del keyword
unordered_map<string, TokenType> keywords = {
    // Simbolos individuales
    {"(", TokenType::NYA_OPEN},
    {")", TokenType::NYA_CLOSE},
    {"{", TokenType::MEOW_OPEN},
    {"}", TokenType::MEOW_CLOSE},
    {";", TokenType::NYEND},
    {",", TokenType::SPLITTY},
    {".", TokenType::DOTTY},
    {"+", TokenType::ADDY_CHAN},
    {"-", TokenType::SUBBY_KITTY},
    {"*", TokenType::STARRY},
    {"/", TokenType::SLASHY},
    {"_", TokenType::LOWO},
    {"#", TokenType::SHARPOWO},
    {"&", TokenType::AMPY},
    {"*&", TokenType::POINU},
    
    //  Operadores Logicos
    {"=", TokenType::GETS_CHAN},
    {"==", TokenType::SAME_UWU},
    {"!", TokenType::NOTTY_KITTY},
    {"!=", TokenType::NUSAME_OWO},
    {">", TokenType::BIGGA_CHAN},
    {">=", TokenType::BIGGE_SAN},
    {"<", TokenType::SMAL_CHAN},
    {"<=", TokenType::SMALE_SAN},
    {"&&", TokenType::AND},
    {"||", TokenType::OR},

    // Tipos de datos
    {"nyaint", TokenType::INT},
    {"purrfloat", TokenType::FLOAT},
    {"doubwu", TokenType::DOUBLE},
    {"meowchar", TokenType::CHAR},
    {"txtuwu", TokenType::STRING},
    {"boolu", TokenType::BOOL},
    {"nyull", TokenType::NYULL},

    // Selectivas
    {"ifnya", TokenType::IFNYA},
    {"elsuwu", TokenType::ELSUWU},
    {"elyf", TokenType::ELYF},
    {"yesh", TokenType::TRU},
    {"nuu", TokenType::FOLS},
    {"switchu", TokenType::SWITCH},
    {"case", TokenType::CASE},
    {"default", TokenType::DEFAULT},

    // Repetitivas
    {"wo", TokenType::DO},
    {"loopie", TokenType::WHILE},
    {"foru", TokenType::FOR},
    {"braku", TokenType::BREAK},
    {"conti", TokenType::CONTINUE},

    // Funciones y clases
    {"voido", TokenType::VOID},
    {"retu", TokenType::RETURN},
    {"clan", TokenType::CLASS},
    {"struk", TokenType::STRUCT},

    // Varios
    {"meowt", TokenType::PRINTF},
    {"mewin", TokenType::SCANF},
    {"nyaclude", TokenType::INCLUDE},
    {"nyaspace", TokenType::NAMESPACE},
    {"nuewo", TokenType::NEW},
    {"del", TokenType::DELETE},
};

// Nombres para los .txt
unordered_map<TokenType, string> tokenNames = {
    {TokenType::NYA_OPEN, "NYA_OPEN"},
    {TokenType::NYA_CLOSE, "NYA_CLOSE"},
    {TokenType::MEOW_OPEN, "MEOW_OPEN"},
    {TokenType::MEOW_CLOSE, "MEOW_CLOSE"},
    {TokenType::NYEND, "NYEND"},
    {TokenType::SPLITTY, "SPLITTY"},
    {TokenType::DOTTY, "DOTTY"},
    {TokenType::ADDY_CHAN, "ADDY_CHAN"},
    {TokenType::SUBBY_KITTY, "SUBBY_KITTY"},
    {TokenType::STARRY, "STARRY"},
    {TokenType::SLASHY, "SLASHY"},
    {TokenType::LOWO, "LOWO"},
    {TokenType::SHARPOWO, "SHARPOWO"},
    {TokenType::AMPY, "AMPY"},
    {TokenType::POINU, "POINU"},

    {TokenType::GETS_CHAN, "GETS_CHAN"},
    {TokenType::SAME_UWU, "SAME_UWU"},
    {TokenType::NOTTY_KITTY, "NOTTY_KITTY"},
    {TokenType::NUSAME_OWO, "NUSAME_OWO"},
    {TokenType::BIGGA_CHAN, "BIGGA_CHAN"},
    {TokenType::BIGGE_SAN, "BIGGE_SAN"},
    {TokenType::SMAL_CHAN, "SMAL_CHAN"},
    {TokenType::SMALE_SAN, "SMALE_SAN"},
    {TokenType::AND, "AND"},
    {TokenType::OR, "OR"},

    {TokenType::INT, "INT"},
    {TokenType::FLOAT, "FLOAT"},
    {TokenType::DOUBLE, "DOUBLE"},
    {TokenType::CHAR, "CHAR"},
    {TokenType::STRING, "STRING"},
    {TokenType::BOOL, "BOOL"},
    {TokenType::NYULL, "NYULL"},

    {TokenType::IFNYA, "IFNYA"},
    {TokenType::ELSUWU, "ELSUWU"},
    {TokenType::ELYF, "ELYF"},
    {TokenType::TRU, "TRU"},
    {TokenType::FOLS, "FOLS"},
    {TokenType::SWITCH, "SWITCH"},
    {TokenType::CASE, "CASE"},
    {TokenType::DEFAULT, "DEFAULT"},

    {TokenType::DO, "DO"},
    {TokenType::WHILE, "WHILE"},
    {TokenType::FOR, "FOR"},
    {TokenType::BREAK, "BREAK"},
    {TokenType::CONTINUE, "CONTINUE"},

    {TokenType::VOID, "VOID"},
    {TokenType::RETURN, "RETURN"},
    {TokenType::CLASS, "CLASS"},
    {TokenType::STRUCT, "STRUCT"},

    {TokenType::PRINTF, "PRINTF"},
    {TokenType::SCANF, "SCANF"},
    {TokenType::INCLUDE, "INCLUDE"},
    {TokenType::NAMESPACE, "NAMESPACE"},
    {TokenType::NEW, "NEW"},
    {TokenType::DELETE, "DELETE"},

    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::NUMBER, "NUMBER"},
    {TokenType::STRING_LITERAL, "STRING_LITERAL"},
    {TokenType::END_OF_FILE, "EOF"},
    {TokenType::UNKNOWN, "UNKNOWN"}
};

//Lexer (Analizador lexico)
class Lexer{
    string entrada;
    vector<Token> tokens;
    int inicio = 0, ValorActual = 0, line = 1;

    public:
        Lexer(const string& src) : entrada(src){}

        vector<Token>scanTokens(){ 
            while(!esFinal()){
                inicio = ValorActual;

                scanToken();
            }

            tokens.push_back({TokenType::END_OF_FILE, "", line});
            
            return tokens;
        }

    private:

    //Metodos de ayuda
        bool esFinal(){
            return ValorActual >= (int)entrada.length();
        }

        char avanza(){
            return entrada[ValorActual++];
        }

        bool esIgual(char expected){
            if(esFinal() || entrada[ValorActual] != expected) return false;
           
            ValorActual++;

            return true;
        }

        char next(){
            return esFinal() ? '\0' : entrada[ValorActual];
        }

    //Metodo que añade un token a al vector token
        void addToken(TokenType type){
            string text = entrada.substr(inicio, ValorActual - inicio);

            tokens.push_back({type, text, line});
        }

    //Metodo que escanea 
        void scanToken(){
            char c = avanza();

            switch(c){
                case '(': addToken(TokenType::NYA_OPEN); break;
                case ')': addToken(TokenType::NYA_CLOSE); break;
                case '{': addToken(TokenType::MEOW_OPEN); break;
                case '}': addToken(TokenType::MEOW_CLOSE); break;
                case ';': addToken(TokenType::NYEND); break;
                case ',': addToken(TokenType::SPLITTY); break;
                case '.': addToken(TokenType::DOTTY); break;
                case '+': addToken(TokenType::ADDY_CHAN); break;
                case '-': addToken(TokenType::SUBBY_KITTY); break;
                case '*': addToken(TokenType::STARRY); break;
                case '/': addToken(TokenType::SLASHY); break;
                case '#': addToken(TokenType::SHARPOWO); break;
                
                case '&': addToken(esIgual('&') ? TokenType::AND : TokenType::AMPY); break;
                case '|': addToken(esIgual('|') ? TokenType::OR : TokenType::UNKNOWN); break;
                
                case '=': addToken(esIgual('=') ? TokenType::SAME_UWU : TokenType::GETS_CHAN); break;
                case '!': addToken(esIgual('=') ? TokenType::NUSAME_OWO : TokenType::NOTTY_KITTY); break;
                case '>': addToken(esIgual('=') ? TokenType::BIGGE_SAN : TokenType::BIGGA_CHAN); break;
                case '<': addToken(esIgual('=') ? TokenType::SMALE_SAN : TokenType::SMAL_CHAN); break;
                
                case '"': cadenaTexto(); break;
                case '\n': line++; break;
                case ' ': 
                case '\r':
                case '\t':break;

                default:
                    if(isdigit(c)){numero();}
                    else if(isalpha(c) || c == '_'){identificador();}
                    else{addToken(TokenType::UNKNOWN);}
            }
        }

        void identificador(){
            while(isalnum(next()) || next() == '_') avanza();

            string text = entrada.substr(inicio, ValorActual - inicio);
            auto it = keywords.find(text);

            addToken(it != keywords.end() ? it -> second : TokenType::IDENTIFIER);
        }

        void numero(){
            while(isdigit(next())) avanza();

            if(next()=='.' && isdigit(entrada[ValorActual+1])){
                avanza();

                while (isdigit(next())) avanza();
            }

            addToken(TokenType::NUMBER);
        }

        void cadenaTexto(){
            while (next() != '"' && !esFinal()){
                if (next() == '\n') line++;

                avanza();
            }

            if(esFinal()) return;

            avanza();

            addToken(TokenType::STRING_LITERAL);
        }
};


//Parser (Analizador Sintactico)
class Parser{
    vector<Token> tokens;
    vector<string> errores;
    int current = 0;

    public:
        Parser(const vector<Token>& t) : tokens(t) {}

        void parse(){
            programa();
        }

        vector<string> getErrores(){
            return errores;
        }

    private:
        void programa(){
            int noAvanceCount = 0;
            const int MAX_REINTENTOS = 5;

            while (!esFinal()){
                int prev = current;
                int prevErrors = errores.size();

                if(esTipoRetorno() && siguienteEsFuncion()){
                    definicionFuncion();
                }
                else if(esDeclaracion()){
                    declaracion();
                }
                else{
                    sentencia();
                }

                if(current == prev){
                    if(prevErrors == (int)errores.size()){
                        cout<<"\nValidacion completada: no se encontraron errores sintacticos.\n";
                        return;
                    } else {
                        noAvanceCount++;
                        if (noAvanceCount >= MAX_REINTENTOS) {
                            cout << "\nParser detenido por bucle: errores no recuperables detectados.\n";

                            return;
                        }

                        sincronizar();
                    }
                }
                else{
                    noAvanceCount = 0; // Reiniciar si hubo progreso
                }
            }
        }

        void primario(){
            if(coincide(TokenType::NUMBER) || coincide(TokenType::STRING_LITERAL) || coincide(TokenType::TRU) || coincide(TokenType::FOLS)){
                avanzar();

                return;
            }
            
            if(coincide(TokenType::IDENTIFIER)){
                avanzar();

                if(coincide(TokenType::NYA_OPEN)){
                    avanzar();

                    while(!coincide(TokenType::NYA_CLOSE) && !esFinal()){
                        expresion();

                        if(coincide(TokenType::SPLITTY)) avanzar();
                    }

                    if(coincide(TokenType::NYA_CLOSE)) avanzar();
                    else error("Se esperaba ')' despues de los argumentos");
                }
                return;
            }
            
            if(coincide(TokenType::NYA_OPEN)){
                avanzar(); expresion();

                if(coincide(TokenType::NYA_CLOSE)) avanzar();
                else error("Se esperaba ')' despues de la expresion");

                return;
            }

            // Error unico y sincronizacion
            error("Expresion invalida");

            sincronizar();
        }

        bool esDeclaracion(){
            if(esFinal()) return false;

            TokenType t = tokens[current].type;
            
            return t == TokenType::INT || t == TokenType::FLOAT || t == TokenType::DOUBLE || t == TokenType::CHAR || t == TokenType::STRING || t == TokenType::BOOL;
        }

        void declaracion(){
            // Consumir tipo
            avanzar();

            // Identificador obligatorio
            if(!coincide(TokenType::IDENTIFIER)){
                error("Se esperaba un identificador");

                sincronizar();

                return;
            }

            avanzar();

            // Opcional: asignacion
            if(coincide(TokenType::GETS_CHAN)){
                avanzar();
                expresion();
            }

            // Fin de declaracion
            if(!coincide(TokenType::NYEND)){
                error("Se esperaba ';' al final de la declaracion");

                sincronizar();
            }
            else{
                avanzar();
            }
        }

        void sentencia(){
            if(esFinal()) return;

            switch(tokens[current].type){
                case TokenType::PRINTF: sentenciaPrint(); break;
                case TokenType::IFNYA: sentenciaIf(); break;
                case TokenType::MEOW_OPEN: bloque(); break;
                case TokenType::WHILE: sentenciaWhile(); break;
                case TokenType::FOR: sentenciaFor(); break;
                case TokenType::DO: sentenciaDoWhile(); break;
                case TokenType::RETURN: sentenciaReturn(); break;
                default: sentenciaExpresion();
            }
        }

        void sentenciaPrint(){
            avanzar(); // Consumir 'meowt'

            if(coincide(TokenType::NYA_OPEN)){
                avanzar();

                // Argumentos de printf
                while(!coincide(TokenType::NYA_CLOSE) && !esFinal()){
                    expresion();

                    if (coincide(TokenType::SPLITTY)){
                        avanzar();
                    }
                }

                if(!coincide(TokenType::NYA_CLOSE)){
                    error("Se esperaba ')' despues de los argumentos de meowt");
                }
                else{
                    avanzar();
                }
            }
            if(!coincide(TokenType::NYEND)){
                error("Se esperaba ';' despues de meowt");

                sincronizar();
            }
            else{
                avanzar();
            }
        }

        void sentenciaIf(){
            avanzar(); // Consumir 'ifnya'

            if(!coincide(TokenType::NYA_OPEN)){
                error("Se esperaba '(' despues de ifnya");
            }
            else{
                avanzar();
            }

            expresion();

            if(!coincide(TokenType::NYA_CLOSE)){
                error("Se esperaba ')' despues de la condicion");
            }
            else{
                avanzar();
            }

            sentencia();

            if(coincide(TokenType::ELSUWU)){
                avanzar();
                sentencia();
            }
        }

        void sentenciaWhile(){
            avanzar(); // Consumir 'loopie'

            if(!coincide(TokenType::NYA_OPEN)){
                error("Se esperaba '(' despues de loopie");
            }
            else{
                avanzar();
            }

            expresion();

            if(!coincide(TokenType::NYA_CLOSE)){
                error("Se esperaba ')' despues de la condicion");
            }
            else{
                avanzar();
            }

            sentencia();
        }

        void sentenciaDoWhile(){
            avanzar(); // Consumir 'wo'
            sentencia();
            
            if(!coincide(TokenType::WHILE)){
                error("Se esperaba 'loopie' despues del bloque wo");
            }
            else{
                avanzar();
            }
            
            if(!coincide(TokenType::NYA_OPEN)){
                error("Se esperaba '(' despues de loopie");
            }
            else{
                avanzar();
            }
            
            expresion();
            
            if(!coincide(TokenType::NYA_CLOSE)){
                error("Se esperaba ')' despues de la condicion");
            }
            else{
                avanzar();
            }
            
            if(!coincide(TokenType::NYEND)){
                error("Se esperaba ';' al final de wo-lopie");
            }
            else{
                avanzar();
            }
        }

        void sentenciaFor(){
            avanzar(); // Consumir 'foru'

            if (!coincide(TokenType::NYA_OPEN)) {
                error("Se esperaba '(' despues de foru");
            }
            else{
                avanzar();
            }

            // Inicializacion
            if (esDeclaracion()){
                declaracion();
            }
            else if(!coincide(TokenType::NYEND)){
                sentenciaExpresion();
            }
            else{
                avanzar(); // Saltar ';' si no hay inicializacion
            }

            // Condicion
            if(!coincide(TokenType::NYEND)){
                expresion();
            }

            if(!coincide(TokenType::NYEND)){
                error("Se esperaba ';' despues de la condicion");
                
                sincronizar();
            }
            else{
                avanzar();
            }

            // Incremento
            if(!coincide(TokenType::NYA_CLOSE)){
                expresion();
            }

            if(!coincide(TokenType::NYA_CLOSE)){
                error("Se esperaba ')' despues de la clausula foru");
                
                sincronizar();
            }
            else{
                avanzar();
            }

            sentencia();
        }

        void sentenciaReturn(){
            avanzar(); // Consumir 'retu'

            if(!coincide(TokenType::NYEND)){
                expresion();
            }
            
            if(!coincide(TokenType::NYEND)){
                error("Se esperaba ';' despues de retu");
                
                sincronizar();
            }
            else{
                avanzar();
            }
        }

        void sentenciaExpresion(){
            expresion();
            if(!coincide(TokenType::NYEND)){
                error("Se esperaba ';' despues de la expresion");
                
                sincronizar();
            }
            else{
                avanzar();
            }
        }

        void bloque(){
            avanzar(); // Consumir '{'

            while(!coincide(TokenType::MEOW_CLOSE) && !esFinal()){
                if(esDeclaracion()){
                    declaracion();
                }
                else{
                    sentencia();
                }
            }

            if(coincide(TokenType::MEOW_CLOSE)){
                avanzar();
            }
            else{
                error("Se esperaba '}' para cerrar el bloque");
            }
        }

        void expresion(){
            if(coincide(TokenType::IDENTIFIER) && (int)tokens.size() > current+1 && tokens[current+1].type == TokenType::GETS_CHAN){
                avanzar(); // IDENTIFIER
                avanzar(); // =
                expresion();
            }
            else{
                expresionLogica();
            }
        }

        void expresionLogica(){
            expresionIgualdad();

            while(coincide(TokenType::OR) || coincide(TokenType::AND)){
                avanzar();
                expresionIgualdad();
            }
        }

        void expresionIgualdad(){
            expresionComparacion();

            while(coincide(TokenType::SAME_UWU) || coincide(TokenType::NUSAME_OWO)){
                avanzar();
                expresionComparacion();
            }
        }

        void expresionComparacion(){
            termino();

            while(coincide(TokenType::BIGGA_CHAN) || coincide(TokenType::BIGGE_SAN) || coincide(TokenType::SMAL_CHAN) || coincide(TokenType::SMALE_SAN)){
                avanzar();
                termino();
            }
        }

        void termino(){
            factor();

            while(coincide(TokenType::ADDY_CHAN) || coincide(TokenType::SUBBY_KITTY)){
                avanzar();
                factor();
            }
        }

        void factor(){
            unario();

            while(coincide(TokenType::STARRY) || coincide(TokenType::SLASHY)){
                avanzar();
                unario();
            }
        }

        void unario(){
            if(coincide(TokenType::NOTTY_KITTY) || coincide(TokenType::SUBBY_KITTY)){
                avanzar();
                unario();
            }
            else{
                primario();
            }
        }

        bool esTipoRetorno(){
            if(esFinal()) return false;
            
            TokenType t = tokens[current].type;
            
            return t == TokenType::INT || t == TokenType::FLOAT || t == TokenType::DOUBLE || t == TokenType::CHAR || t == TokenType::STRING || t == TokenType::BOOL || t == TokenType::VOID;
        }

        bool siguienteEsFuncion(){
            if(current + 2 >= (int)tokens.size()) return false;
            
            return tokens[current+1].type == TokenType::IDENTIFIER && tokens[current+2].type == TokenType::NYA_OPEN;
        }

        void definicionFuncion(){
            avanzar();
            avanzar();
            
            // Consumir '('
            if(!coincide(TokenType::NYA_OPEN)){
                error("Se esperaba '(' despues del nombre de la funcion");
                
                sincronizar();
                
                return;
            }
            avanzar();
            
            // Manejar parametros (si existen)
            if(!coincide(TokenType::NYA_CLOSE)){
                while(!coincide(TokenType::NYA_CLOSE) && !esFinal()){
                    avanzar();
                }
            }
            
            // Consumir ')'
            if(coincide(TokenType::NYA_CLOSE)){
                avanzar();
            }
            else{
                error("Se esperaba ')' despues de los parametros");
            }
            
            // Parsear el cuerpo de la funcion
            if(coincide(TokenType::MEOW_OPEN)){
                bloque();
            }
            else{
                error("Se esperaba '{' para el cuerpo de la funcion");
            }
        }

        bool coincide(TokenType tipo){
            return !esFinal() && tokens[current].type == tipo;
        }

        Token avanzar(){
            return esFinal() ? tokens[current] : tokens[++current-1];
        }

        bool esFinal(){
            return current >= (int)tokens.size() || tokens[current].type == TokenType::END_OF_FILE;
        }

        void error(const string& mensaje){
            int linea = esFinal() ? tokens.back().line : tokens[current].line;

            errores.push_back("Linea " + to_string(linea) + ": " + mensaje);
        }

        void sincronizar(){
            while(!esFinal()){
                if(previo().type == TokenType::NYEND) return;

                switch(tokens[current].type){
                    case TokenType::NYEND: return;
                    default: avanzar();}
            }
        }

        Token previo(){
            return current == 0 ? tokens[0] : tokens[current-1];
        }
};


int main(){
    string filename;

    cout<<"Ingrese el nombre del archivo fuente NekoLang: "; cin>>filename;

    ifstream file(filename);

    if(!file.is_open()){
        cout<<"No se encontro el archivo.\n";

        return 0;
    }

    stringstream buffer;

    buffer<<file.rdbuf();
    file.close();

    // Lexer
    Lexer lexer(buffer.str());
    vector<Token> tokens = lexer.scanTokens();

    // Tabla de Tokens
    ofstream tokns("tokens.txt");
    
    if(tokns.is_open()){
        tokns<<left<<setw(10)<<"Linea"<<setw(20)<<"Tipo"<<setw(30)<<"Lexema"<<"\n";
        tokns<<string(40,'-')<<"\n";
            
        for(const auto& token : tokens){
            tokns<<left<<setw(10)<<token.line<<setw(20)<<tokenNames[token.type]<<setw(30)<<token.lexeme<<"\n";
        }

        tokns.close();

        cout<<"\nArchivo 'tokens.txt' ha sido generado.\n";
    }
    else{
        cout<<"Error al crear tokens.txt\n";
    }

    // Tabla de Simbolos
    ofstream symbol("simbolos.txt");

    if(symbol.is_open()){
        symbol<<left<<setw(15)<<"Nombre"<<setw(15)<<"Tipo"<<setw(15)<<"Valor"<<setw(10)<<"Linea"<<setw(15)<<"Direccion"<<"\n";
        symbol<<string(70,'-')<<"\n";

        for(size_t i = 0; (i+3) < tokens.size(); i++){
            Token t_tipo = tokens[i];
            Token t_id = tokens[i+1];
            Token t_op = tokens[i+2];
            Token t_val = tokens[i+3];

            if((t_tipo.type == TokenType::INT || t_tipo.type == TokenType::FLOAT || t_tipo.type == TokenType::DOUBLE || t_tipo.type == TokenType::CHAR || t_tipo.type == TokenType::STRING || t_tipo.type == TokenType::BOOL) && t_id.type==TokenType::IDENTIFIER && t_op.type == TokenType::GETS_CHAN && (t_val.type == TokenType::NUMBER || t_val.type == TokenType::STRING_LITERAL || t_val.type == TokenType::TRU || t_val.type == TokenType::FOLS)){
                symbol<<left<<setw(15)<<t_id.lexeme<<setw(15) <<t_tipo.lexeme<<setw(15)<<t_val.lexeme<<setw(10)<<t_id.line<<setw(15)<<(void*)t_val.lexeme.c_str()<<"\n";
            }
        }

        symbol.close();

        cout<<"\nArchivo 'simbolos.txt' ha sido generado.\n";
    }
    else{
        cout<<"Error al crear tokens.txt\n";
    }

    // Parser
    Parser parser(tokens);
    parser.parse();

    // Tabla de Errores
    ofstream parsr("errores.txt");
    vector<string> errores = parser.getErrores();

    if(parsr.is_open()){
        if(errores.empty()){
            parsr << "No se encontraron errores sintacticos.\n";
        }
        else{
            parsr<<left<<setw(10)<<"Linea"<<setw(40)<<"Descripcion"<<"\n";
            parsr<<string(50, '-')<<"\n";
            
            for(const auto& error : errores){
                size_t pos = error.find(':');

                if(pos != string::npos){
                    string linea = error.substr(6, pos - 6); // "Linea X"
                    string desc = error.substr(pos + 2); // Descripción

                    parsr<<left<<setw(10)<<linea<<setw(40)<<desc<<"\n";
                }
                else{
                    parsr<<error<<"\n";
                }
            }
        }

        parsr.close();

        cout<<"\nArchivo 'errores.txt' ha sido generado.\n";
    }
    else{
        cout<<"Error al crear errores.txt\n";
    }

    return 0;
}
