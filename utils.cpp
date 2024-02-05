#include "./header.h"


//converts to BIG text
//string as value because it might be modified
std::string big_text(const std::string& input, const bool& have_lines){
    static int char_ctr; //counter of characters 
    static int t_cols = std::stoi(exec("stty size | awk '{print $2}'"));

    if(!input.length()){
        char_ctr = 0;
        return "\n";
    }

    //TOP BIG LETTERS (match the bottom)
    const std::vector<std::string> top_big = {
        "▄▀█", "█▄▄", "█▀▀", "█▀▄", "█▀▀", "█▀▀", "█▀▀", "█ █", "█", "  █", "█▄▀", "█  ", 
        "█▀▄▀█", "█▄ █", "█▀█", "█▀█", "█▀█", "█▀█", "█▀", "▀█▀", "█ █", "█ █", "█ █ █", 
        "▀▄▀", "█▄█", "▀█", 
        
        "█▀█", "▄█", "▀█", "▀▀█", "█ █", "█▀", "█▄▄", "▀▀█", "▄▀▀▄", "█▀█"
    };

    //BOTTOM BIG LETTERS (match the top)
    //a - z and 0 -9 
    const std::vector<std::string> bottom_big = {
        "█▀█", "█▄█", "█▄▄", "█▄▀", "██▄", "█▀ ", "█▄█", "█▀█", "█", "█▄█", "█ █", "█▄▄", 
        "█ ▀ █", "█ ▀█", "█▄█", "█▀▀", "▀▀█", "█▀▄", "▄█", " █ ", "█▄█", "▀▄▀", "▀▄▀▄▀", 
        "█ █", " █ ", "█▄", 
        
        "█▄█", " █", "█▄", "▄▄█", "▀▀█", "▄█", "█▄█", "  █", "▀██▀", "▀▀█"
    };

    //outputs
    std::string top_line ="";
    std::string top; 
    std::string bottom;
    std::string bottom_line ="";


    for(const char c: input){
        switch(tolower(c)){
            case 'a' ... 'z': 
                //appends the big version strings of each
                top += top_big[(int)tolower(c)-97];
                bottom += bottom_big[(int)tolower(c)-97];
                char_ctr++;
                break;
            case '0' ... '9':
                //decimal - 48 + 26
                top+= top_big[(int)c-22];
                bottom+= bottom_big[(int)c-22];
                char_ctr++;
                break;

            //special characters
            case '.':  top += ' '; bottom += "▄"; break;
            case '\'': top += "▀"; bottom += ' '; break;
            case '-': top += "▄▄"; bottom += "  "; break;
            case ' ':  top += ' '; bottom += ' '; break;
            case '!': top += "█"; bottom += "▄"; break;
            case '?': top += "▀█"; bottom += " ▄"; break;
            default: continue; //skips any and all other characters
        }
        //adds separator
        char_ctr +=3; //3 chars + space 
        top += ' ';
        bottom += ' ';
    }
    
    //adds the lines
    if(have_lines){
        for(size_t i=0; i<char_ctr-1; i++){
            top_line += "▀";
            bottom_line += "▄";
        }
        top_line += N;
        bottom_line += N;
    }

    top.resize(top.size() - 1);
    bottom.resize(bottom.size() - 1);

    if(char_ctr > t_cols){
        char_ctr = 0;
        return "\n";
    }


    //returns the fat string
    return top_line + top + N + bottom + N + bottom_line;
};

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
};

// if string is an int
bool is_int(const char* string, int start_i=0) {
    do {
        if(!isdigit(string[start_i])) {
            return false;
        }
        start_i++;
    } while(string[start_i] != '\0');
    return true;
}

//prints the help page erf
void help(const std::string& path) {
    std::system(("echo -e \"OVERVIEW:\n" + 
    big_text("massive text", 1) + 
    N + 
    big_text("...ginormous even", 0) +
    "\"").c_str());
    std::ifstream docs(std::string(path) + "commands.txt");
    std::string line;
    while (getline(docs, line)){
        std::system(("echo -e \"" + line + "\"").c_str());
    }
}

template<typename T>
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}