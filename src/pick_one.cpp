#include "pick_one.h"

#include <iostream>
#include <unordered_map>


typedef std::unordered_map<std::string, test_fun> CASE_FUN;
typedef std::unordered_map< std::string, CASE_FUN > UNIT_CASEFUN;

// TODO: 新建MAP 与 查询指定的case， 应该分开
//       在 PUSH_CASE 中使用， 与 main 中使用该函数，含义是不一样的
using std::string;
CASE_FUN& getCaseDB(string unit_name, string case_name, test_fun f_ptr) {
	static UNIT_CASEFUN unitDB;

	auto find_unit = unitDB.find(unit_name);
	if(find_unit != unitDB.end()){
		return find_unit->second;
	}
	else{
		unitDB[unit_name][case_name] = f_ptr;
		return unitDB[unit_name];
	}
}

// Use assignment to run this function. tricky
int PUSH_CASE(std::string unit_name, std::string case_name, test_fun f_ptr)
{ 
    auto &M = getCaseDB(unit_name, case_name, f_ptr);
    M.insert(std::make_pair(case_name, f_ptr));
    return 0;
} 

using std::string;
int parse_options(string filter_str, string &unit_name, string &case_name)
{
    // use regex do valid check

    // extract component
    auto pos = filter_str.find("=");
    std::string first = filter_str.substr(0, pos);
    std::string second = filter_str.substr(pos+1);

    // unit.case
    auto dot =  second.find('.');
    unit_name = second.substr(0, dot);
    case_name = second.substr(dot+1);

    return 0;
}

int RUN_ERIC_CASE(int argc, char** argv) 
{                                       
    if(argc == 1)     
    {  
        std::cout<< "no filter\n";  
    }  
    else if(argc == 2)  
    {  
        std::string filter_str(argv[1]);
        std::string unit_name;
        std::string case_name;
        parse_options(filter_str, unit_name, case_name);  

        auto n = case_name.find('*'); 
        if( n != std::string::npos){ // multi cases
            std::string subStr = case_name.substr(0, n);
            auto &M = getCaseDB(unit_name, case_name, nullptr);
            for(auto p = M.begin(); p != M.end(); ++p){
                auto nn = p->first.find(subStr);
                if( nn != std::string::npos){
                    p->second();
                }
            }
        }
        else{ // single case
            auto &M = getCaseDB(unit_name, case_name, nullptr);
            auto p = M.find(case_name);
            if(p != M.end()){
                p->second();
            }
            else{
                std::cout<< "no case with name: " << unit_name << "." <<case_name << "\n";
            }
        }
    }

    return 0;
}                                       
