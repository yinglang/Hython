#include <PyNumpyEngine.h>

// g++ -o test_numpy test_numpy.cpp -I /home/hui/ide/miniconda3/envs/torch101/include/python3.7m/ -I .  -I /home/hui/ide/miniconda3/envs/torch101/lib/python3.7/site-packages/numpy/core/include/ -L /home/hui/ide/miniconda3/envs/torch101/lib/ -lpython3.7m -std=c++11

class DealBmpAPI{
    HUI::PyBaseEngine* pyengine;
    PyObject* module_obj;
    PyObject* func_print_img;
    
public:
    DealBmpAPI(HUI::PyBaseEngine* pyengine){
        pyengine = pyengine;
        module_obj = pyengine->import_module("deal_bmp");
        func_print_img =  NULL;
    }
    
    void print_img(unsigned char* array, unsigned int h, unsigned int w, unsigned int c){
        if(!func_print_img){
            func_print_img= pyengine->get_func(module_obj, "print_img");
        }
        
        PyObject* args = PyTuple_New(1);
        /// turn cpp array to numpy PyObject
        npy_intp dims[] = {h, w, c};
        PyObject* input = PyArray_SimpleNewFromData(3, dims, NPY_UINT8, array); // 输入的array可以是一维flatten的指针
        PyTuple_SetItem(args, 0, input);
        PyObject* pRet1 = PyEval_CallObject(func_print_img, args);
    }
};

int main(){
    HUI::PyNumpyEngine* pyengine = new HUI::PyNumpyEngine();
    pyengine->init_python();
    pyengine->insert_python_path(0, "./");
    
    DealBmpAPI deal_bmp(pyengine);
    unsigned char array[48] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4,
                   2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5,
                   3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6,
                   4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7};
    deal_bmp.print_img(array, 4, 4, 3);
    
    delete pyengine;
    return 0;
}