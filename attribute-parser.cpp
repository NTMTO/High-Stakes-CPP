#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

void progress_cursor(string& s, int new_start){
    s = s.substr(new_start);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int num_lines;
    int num_qs;
    unordered_map<string, string> prop_map;
    
    //Gaurd against invalid
    if (!(cin >> num_lines >> num_qs)){
        cout << "Input invalid, must begin with 2 whitespace seperated integers.";
        return 1;
    }

    //cin >> num_lines >> num_qs; This is not needed and is actually bad. C++ extracts the input into the variables in the above statement. Different than C#!
    
    string temp_line;
    string tag = "";
    
    //Process lines
    for (int i = 0; i < num_lines; i++){
        getline(cin, temp_line);
        if (temp_line.empty() || temp_line == ""){ continue; }
        if (temp_line.find("<") == string::npos){
            cout << "Input body malformed. Must include opening carat(<). This line will be skipped.";
            continue;
        }
        
        //First collect tag, accounting for compound tags with "."
        
        int tag_start_idx = temp_line.find("<") + 1;
        //Beginning tags are followed by a space, ending are followed by ">"
        int tag_last_idx = temp_line.find_first_of(" ,>");
        
        //Existing compound tag ending
        if (temp_line.find("/") != string::npos //Ending
            && tag.find_last_of(".") != string::npos //Compound
            && tag != ""){ //Not empty
                tag = tag.substr(0, tag.find_last_of("."));
        }
        //Existing single tag ending
        if (temp_line.find("//") != string::npos //Ending
            && tag.find_last_of(".") == string::npos //Single
            && tag != ""){ //Not empty
                tag = "";
            }
        if (tag != ""){
            tag += ".";
        }
        tag += temp_line.substr(tag_start_idx, tag_last_idx);
        
        
        //Implement cursor to collect properties
        progress_cursor(temp_line, tag_last_idx);
        
        //Begin parsing properties
        if (temp_line.find("=") == string::npos) {
            cout << "The tag \"" << tag << "\" has no properties. Moving on.";
            continue;
        }
        while (temp_line.find("=") != string::npos){
            string prop_name = "";
            string prop_val = "";
            //Might be extra whitespace
            progress_cursor(temp_line, temp_line.find_first_not_of(" "));
            
            prop_name = temp_line.substr(0, temp_line.find_first_of(" ,="));
            
            if (temp_line.find("\"") == string::npos){
                cout << "Property value malformed. Must begin with \". This line will be skipped.";
                break;
            }
            progress_cursor(temp_line, temp_line.find("\"") + 1);
            prop_val = temp_line.substr(0, temp_line.find_last_not_of(" ,\",>"));
            prop_map[tag + "~" + prop_name] = prop_val;
            if (temp_line.find(" ") != string::npos){
                progress_cursor(temp_line, temp_line.find(" "))
            }
        }
        
    }
    
    
    return 0;
}








