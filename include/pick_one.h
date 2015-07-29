#include <string>
#include <functional>


typedef std::function<void(void)> test_fun;
int PUSH_CASE(std::string unit_name, std::string case_name, test_fun f_ptr);
int RUN_ERIC_CASE(int argc, char** argv);

#define MAKE_NAME_IMPL(unit_name,case_name,idx) \
	_##unit_name##_##case_name##_##idx

#define MAKE_NAME(unit_name,case_name,idx) \
	MAKE_NAME_IMPL(unit_name,case_name,idx)

#define MAKE_FUNCTION(v1,v2) \
	MAKE_NAME(v1,v2, __LINE__)


//generate the function
#define ERIC_TEST(test_unit, test_case) \
	static void MAKE_FUNCTION(test_unit, test_case)(void); \
    static int MAKE_NAME(test_unit,test_case_,__LINE__ )= \
    PUSH_CASE(#test_unit,#test_case,MAKE_FUNCTION(test_unit,test_case)); \
    static void MAKE_FUNCTION(test_unit, test_case)(void) 