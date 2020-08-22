#ifndef __PYNUMPYENGINE_H__
#define __PYNUMPYENGINE_H__

#include <PyBaseEngine.h>
#include<numpy/arrayobject.h>

namespace HUI{
    class PyNumpyEngine: public HUI::PyBaseEngine{
    public:
        /**
         * Return true (nonzero) when the Python interpreter 
         * has been initialized, false (zero) if not.
        */
        int init_python(wchar_t * python_dir=NULL){   
            int return_res = PyBaseEngine::init_python(python_dir);
            import_array();		/* load numpy api */
            return return_res;
        }
    };
};
#endif
