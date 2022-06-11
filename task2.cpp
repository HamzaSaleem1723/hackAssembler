#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <cstring>
#include <map>

using namespace std;

string Result = "";                                     // Global Variable to Hold the End Result

string ignore_comments(string s)                        // Function for Removing Comments
{
    string str = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (!isspace(s[i]))
        {
            if (s[i] == '/' and s[i + 1] == '/')
            {
                return str;
            }
            else
            {
                str.push_back(s[i]);
            }
        }
    }
    return str;
}

string decimal_to_binary(string c)                      // Function to convert decimal values into binary
{
    int a = 0;
    string w = "";
    for (int i = 1; i < c.length(); i++)
    {
        w.push_back(c[i]);
    }
    stringstream ss1(w);
    ss1 >> a;   
    string temp, binary_number = "";
    char b[1000];
    temp = itoa(a, b, 2);
    for (int i = 0; i < 16 - temp.length(); i++)
    {
        binary_number.push_back('0');
    }
    binary_number.append(temp);
    return binary_number;
}

string C_instruction_binary(string str)                // Function to generate C-instruction Binary    
{
    map<string, string> map_comp0;
    map<string, string> map_comp1;
    map<string, string> map_dest;
    map<string, string> map_jump;
    string c_in;
    string comp = "";
    string jump = "";
    string dest = "";
    bool check = false;
    bool jump_1 = false;
    map_comp0.insert(make_pair("0", "101010"));         // Map for computation
    map_comp0.insert(make_pair("1", "111111"));
    map_comp0.insert(make_pair("-1", "111010"));
    map_comp0.insert(make_pair("D", "001100"));
    map_comp0.insert(make_pair("A", "110000"));
    map_comp0.insert(make_pair("!D", "001101"));
    map_comp0.insert(make_pair("!A", "110001"));
    map_comp0.insert(make_pair("-D", "001111"));
    map_comp0.insert(make_pair("-A", "110011"));
    map_comp0.insert(make_pair("D+1", "011111"));
    map_comp0.insert(make_pair("A+1", "110111"));
    map_comp0.insert(make_pair("D-1", "001110"));
    map_comp0.insert(make_pair("A-1", "110010"));
    map_comp0.insert(make_pair("D+A", "000010"));
    map_comp0.insert(make_pair("D-A", "010011"));
    map_comp0.insert(make_pair("A-D", "000111"));
    map_comp0.insert(make_pair("D&A", "000000"));
    map_comp0.insert(make_pair("D|A", "010101"));

    map_comp1.insert(make_pair("M", "110000"));
    map_comp1.insert(make_pair("!M", "110001"));
    map_comp1.insert(make_pair("-M", "110011"));
    map_comp1.insert(make_pair("M+1", "110111"));
    map_comp1.insert(make_pair("M-1", "110010"));
    map_comp1.insert(make_pair("D+M", "000010"));
    map_comp1.insert(make_pair("D-M", "010011"));
    map_comp1.insert(make_pair("M-D", "000111"));
    map_comp1.insert(make_pair("D&M", "000000"));
    map_comp1.insert(make_pair("D|M", "010101"));

    map_dest.insert(make_pair("0", "000"));                         // Map for destination
    map_dest.insert(make_pair("M", "001"));
    map_dest.insert(make_pair("D", "010"));
    map_dest.insert(make_pair("MD", "011"));
    map_dest.insert(make_pair("A", "100"));
    map_dest.insert(make_pair("AM", "101"));
    map_dest.insert(make_pair("AD", "110"));
    map_dest.insert(make_pair("AMD", "111"));

    map_jump.insert(make_pair("0", "000"));                        // Map for jump
    map_jump.insert(make_pair("JGT", "001"));
    map_jump.insert(make_pair("JEQ", "010"));
    map_jump.insert(make_pair("JGE", "011"));
    map_jump.insert(make_pair("JLT", "100"));
    map_jump.insert(make_pair("JNE", "101"));
    map_jump.insert(make_pair("JLE", "110"));
    map_jump.insert(make_pair("JMP", "111"));

    Result.append("111");
    for (int i = 0; i < str.length(); i++)                     // computation
    {  
        if (str[i] == '=')
        {
            for (int j = ++i; j < str.length(); j++)
            {
                comp.push_back(str[j]);
            }
            break;
        }
        else if (str[i] == ';')
        {
            for (int j = 0; j < i; j++)
            {
                comp.push_back(str[j]);
            }
            break;
        }
    }
    for (int i = 0; i < comp.length(); i++)
    {
        if (comp[i] == 'M')
        {
            check = true;
        }
    }
    if (check)
    {
        Result.push_back('1');
        Result.append(map_comp1.find(comp)->second);
    }
    else
    {
        Result.push_back('0');
        Result.append(map_comp0.find(comp)->second);
    }
    
    for (int i = 0; i < str.length(); i++)              // destination
    {
        if (str[i] == '=')
        {
            
            for (int j = 0; j < i; j++)
            {
               
                dest.push_back(str[j]);
                
            }

            Result.append(map_dest.find(dest)->second);
        }
        else if (str[i] == ';')
        {
            Result.append("000");
            break;
        }
    }
                                             
    for (int i = 0; i < str.length(); i++)           // jump;
    {
        if (str[i] == ';')
        {
            jump_1 = true;
            for (int j = ++i; j < str.length(); j++)
            {
                
                jump.push_back(str[j]);
                
            }

            Result.append(map_jump.find(jump)->second);
        }
    }
    if (!jump_1)
    {
        Result.append("000");
    }
    
    c_in = Result;
    Result = "";
    return c_in;
}
int main()
{
    string input_file;
    string output_file = "";
    cout << "Enter the Name of the File: " << "\n"; 
    cin >> input_file;
    ifstream my_read_file(input_file);
    for(int i=0;i!=input_file.length();i++){
        if(input_file[i]=='.'){
            break;
        }
        else{
            output_file.push_back(input_file[i]);
        }

    }

    map<string, string> Map_for_var;
    map<string, string>::iterator y;
    map<string, string> Map_for_predefined;
    map<string, string>::iterator x;
    Map_for_predefined.insert(make_pair("@SCREEN", "@16384"));
    Map_for_predefined.insert(make_pair("@KBD", "@24576"));
    Map_for_predefined.insert(make_pair("@SP", "@0"));
    Map_for_predefined.insert(make_pair("@LCL", "@1"));
    Map_for_predefined.insert(make_pair("@ARG", "@2"));
    Map_for_predefined.insert(make_pair("@THIS", "@3"));
    Map_for_predefined.insert(make_pair("@THAT", "@4"));
    Map_for_predefined.insert(make_pair("@R0", "@0"));
    Map_for_predefined.insert(make_pair("@R1", "@1"));
    Map_for_predefined.insert(make_pair("@R2", "@2"));
    Map_for_predefined.insert(make_pair("@R3", "@3"));
    Map_for_predefined.insert(make_pair("@R4", "@4"));
    Map_for_predefined.insert(make_pair("@R5", "@5"));
    Map_for_predefined.insert(make_pair("@R6", "@6"));
    Map_for_predefined.insert(make_pair("@R7", "@7"));
    Map_for_predefined.insert(make_pair("@R8", "@8"));
    Map_for_predefined.insert(make_pair("@R9", "@9"));
    Map_for_predefined.insert(make_pair("@R10", "@10"));
    Map_for_predefined.insert(make_pair("@R11", "@11"));
    Map_for_predefined.insert(make_pair("@12", "@12"));
    Map_for_predefined.insert(make_pair("@R13", "@13"));
    Map_for_predefined.insert(make_pair("@R14", "@14"));
    Map_for_predefined.insert(make_pair("@R15", "@15"));
    int line = 0;
    while (!my_read_file.eof())
    {
        string str;
        string w = "";
        string co = "";
        getline(my_read_file, str);
        str = ignore_comments(str);
        if (str == "")
            continue;
        if (str[0] != '(')
        {
            line++;
            
        }
        if (str[0] == '(')                                          // Handling labels
        {
            for (int i = 0; i < str.length(); i++)
            {
                w.push_back('@');
                co.push_back('@');
                for (int j = 1; j < str.length() - 1; j++)
                {
                    w.push_back(str[j]);
                }
                co.append(to_string(line));
                Map_for_predefined.insert(make_pair(w, co));
                break;
            }
        }
    }
    my_read_file.close();

    ifstream my_read_file_1(input_file);
    ofstream my_write_file("symbol.txt");

    int var = 16;
    string var_1 = "";
    while (!my_read_file_1.eof())
    {
        string str;
        getline(my_read_file_1, str);
        
        str = ignore_comments(str);
        if (str == "")
            continue;       
        if (str[0] == '(')
            continue;
        if (str[0] == '@')                                      // Handling Variables
        {   
            if (str[1] == '0' or str[1] == '1' or str[1] == '2' or str[1] == '3' or str[1] == '4' or str[1] == '5' or str[1] == '6' or str[1] == '7' or str[1] == '8' or str[1] == '9')
            {
                my_write_file << str << "\n";
                continue;
            }
            x = Map_for_predefined.find(str);
            if (x == Map_for_predefined.end())
            {
                
                y = Map_for_var.find(str);
                if (y == Map_for_var.end())
                {
                    
                    var_1.push_back('@');
                    var_1.append(to_string(var));
                    
                    Map_for_var.insert(make_pair(str, var_1));
                    str = var_1;
                    var++;
                    var_1 = "";
                }
                else
                {
                    
                    str = Map_for_var.find(str)->second;
                }
                my_write_file << str << "\n";
            }
            else
            {
                
                str = Map_for_predefined.find(str)->second;
                my_write_file << str << "\n";
            }
        }
        else
        {

            my_write_file << str << "\n";
        }
    }
    
    my_read_file_1.close();
    my_write_file.close();

    ifstream my_read_file_2("symbol.txt");
    ofstream my_write_file_2(output_file.append(".hack"));

    while (!my_read_file_2.eof())
    {
        string str;
        getline(my_read_file_2, str);
        str = ignore_comments(str);
        if (str == "")
            continue;
        

        else if (str[0] == '@')
        {
            
            my_write_file_2 << decimal_to_binary(str) << "\n";
        }
        else
        {
            str = C_instruction_binary(str);
            my_write_file_2 << str << "\n";
        }
    }
    my_read_file_2.close();
    my_write_file_2.close();
    remove("symbol.txt");
    return 0;
}