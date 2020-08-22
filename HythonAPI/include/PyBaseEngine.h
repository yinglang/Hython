#ifndef __PYENGINE_H__
#define __PYENGINE_H__

#include  <Python.h>
#include <string>

namespace HUI{
    // 如果value不为true，则打印错误信息，同时结束程序
    void pyassert(bool value, const char* error_string){
        if(!value){
            fprintf(stderr, "%s\n", error_string);
            exit(-1);
        }
    }

    class PyBaseEngine{
        bool finished;
    public:
        PyBaseEngine(){
            finished = false;
        }
        
        /**
         * Return true (nonzero) when the Python interpreter 
         * has been initialized, false (zero) if not.
        */
        int init_python(wchar_t * python_dir=NULL){   
            if(python_dir)
                Py_SetProgramName(python_dir);  /* optional but recommended */
            
            Py_Initialize();
            int return_res = Py_IsInitialized();
            pyassert(return_res, "python initialize failed.");
            finished = false;
            return return_res;
        }

        /*
            normal finish_python() are called in deconstructor, 
            should not called by user.
        */
        void finish_python(){
            Py_Finalize();
            finished = true;
        }

        ~PyBaseEngine(){
            if(!finished) finish_python();
        }

        void run(const char* python_stmt){
            PyRun_SimpleString(python_stmt);
        }

        PyObject* import_module(const char* module_name){
            PyObject* module_obj = PyImport_ImportModule(module_name);
            pyassert(module_obj != NULL, 
                (std::string(module_name) + " not found or got error while import " + std::string(module_name)).c_str());
            return module_obj;
        }
        
        PyObject* get_func(PyObject* module_obj, const char* func_name){
            PyObject * func_obj = PyObject_GetAttrString(module_obj, func_name);
            pyassert(func_obj != NULL, 
                (std::string(func_name) + "not found or got error while call it.").c_str());
            return func_obj;
        }

        // void call_func(PyObject* module_obj, const char* func_name){
        //     PyObject * func_obj = PyObject_GetAttrString(module_obj, func_name);
        //     pyassert(func_obj != NULL, 
        //         (std::string(func_name) + "not found or got error while call it.").c_str());
        //     PyEval_CallObject(func_obj, NULL);
        // }

        ////////////////// middle low-level API ///////////////////////////////

        /**
         * excute path cmd:
         *  import sys
         *  sys.path.insert(idx, "'" + c_str + "'")
        */
        void insert_python_path(int idx, const char* c_str){
            run("import sys");
            std::string insert_stmt = std::string("sys.path.insert(") + std::to_string(idx) +
            std::string(", '") + c_str + std::string("')");
            run(insert_stmt.c_str());
        }
    };
};

#endif

