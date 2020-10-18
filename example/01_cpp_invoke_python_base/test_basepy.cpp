#include <PyBaseEngine.h>

//  g++ -o test_basepy test_basepy.cpp -I /home/hui/ide/miniconda3/envs/torch101/include/python3.7m/ -I . -L /home/hui/ide/miniconda3/envs/torch101/lib/ -lpython3.7m -std=c++11

class DealBmpAPI{
    HUI::PyBaseEngine* pyengine;
    PyObject* module_obj;
    PyObject* func_print_hello;
    PyObject* func_print_str;
    
public:
    DealBmpAPI(HUI::PyBaseEngine* pyengine){
        pyengine = pyengine;
        module_obj = pyengine->import_module("deal_bmp");
        func_print_hello =  NULL;
        func_print_str = NULL;
    }
    
    void print_hello(){
        if(!func_print_hello){
            func_print_hello = pyengine->get_func(module_obj, "print_hello");
        }
        PyEval_CallObject(func_print_hello, NULL);
    }
    
    void print_str(const char* str){
        if(!func_print_str){
            func_print_str = pyengine->get_func(module_obj, "print_str");
        }
        PyObject* args = Py_BuildValue("(s)", str);
        PyEval_CallObject(func_print_str, args);
    }
};

int main(){
    HUI::PyBaseEngine* pyengine = new HUI::PyBaseEngine();
    pyengine->init_python();
    pyengine->insert_python_path(0, "./");
    
    DealBmpAPI deal_bmp(pyengine);
    deal_bmp.print_hello();
    deal_bmp.print_str("world");
    
    delete pyengine;
    return 0;
}