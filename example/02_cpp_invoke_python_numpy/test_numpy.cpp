#include <PyNumpyEngine.h>


// g++ -o test_numpy test_numpy.cpp -I /home/hui/ide/miniconda3/envs/torch101/include/python3.7m/ -I .  -I /home/hui/ide/miniconda3/envs/torch101/lib/python3.7/site-packages/numpy/core/include/ -L /home/hui/ide/miniconda3/envs/torch101/lib/ -lpython3.7m -std=c++11

class DealBmpAPI{
    HUI::PyBaseEngine* pyengine;
    PyObject* module_obj;
    PyObject* func_print_img;
    
public:
    DealBmpAPI(HUI::PyBaseEngine* pyengine){
        pyengine = pyengine;
        module_obj = pyengine->import_module("python_numpy");
        func_print_img =  NULL;
    }
    
    ~DealBmpAPI(){
        printf("del ref %ld %ld\n", func_print_img->ob_refcnt, module_obj->ob_refcnt);
        // Py_DECREF(func_print_img);  // this brother can not delete, or will get segment error
        // printf("del ref %ld %ld\n", func_print_img->ob_refcnt, module_obj->ob_refcnt);
	Py_DECREF(module_obj);
        printf("del ref %ld %ld\n", func_print_img->ob_refcnt, module_obj->ob_refcnt);
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
        printf("ref: %ld %ld %ld %ld %ld\n", pRet1->ob_refcnt, input->ob_refcnt, args->ob_refcnt, func_print_img->ob_refcnt, module_obj->ob_refcnt);
        Py_DECREF(pRet1);  // return None, need dec, we guess the None is static and global, like Constant pool
	Py_DECREF(args);   // decref of args(a tuple), it will decref all items in it, so we do not need decref input
        printf("ref: %ld %ld %ld %ld %ld\n", pRet1->ob_refcnt, input->ob_refcnt, args->ob_refcnt, func_print_img->ob_refcnt, module_obj->ob_refcnt);
    }
};

int main(){
    HUI::PyNumpyEngine* pyengine = new HUI::PyNumpyEngine();
    pyengine->init_python();
    pyengine->insert_python_path(0, "./");
    
    DealBmpAPI deal_bmp(pyengine);
    unsigned char array[1000*1000];
    int k = 0;
    int sum = 0;
    for(int i = 0; i < 1000; i++)
	for(int j = 0; j < 1000; j++){
		array[k] = ((i % 256) * (j %256) % 256);
		sum += array[k];
		k++;
	}
	
    for(int i = 0; i < 6; i++){
	printf("[cpp] %d %d\n", i, sum);
    	deal_bmp.print_img(array, 1000, 1000, 1);
    }
 
    delete pyengine;
    return 0;
}
