#include <PyNumpyEngine.h>

typedef unsigned char uint8;
typedef unsigned int uint;

class AIAPI{
	HUI::PyBaseEngine* pyengine;
	PyObject* module_obj;
	PyObject* func_init_shibie_model;
	PyObject* func_jiance;
	PyObject* func_shibie;
	PyObject* func_finish;

public:
	AIAPI(HUI::PyBaseEngine* pyengine){
		this->pyengine = pyengine;
		module_obj = pyengine->import_module("ai_api");
		func_init_shibie_model = NULL;
		func_jiance = NULL;
		func_shibie = NULL;
		func_finish = NULL;
	}
    
	int init_shibie_model(){
		if(!func_init_shibie_model)
			func_init_shibie_model = pyengine->get_func(module_obj, "init_shibie_model");
		PyEval_CallObject(func_init_shibie_model, NULL);
        return true;
	}

	int jiance(uint8* rgb_data, uint rgb_w, uint rgb_h, uint rgb_c, const char* rgb_file,
            uint8* xray_data, uint xray_w, uint xray_h, uint xray_c, const char* xray_file,
            uint8* radar_data, uint radar_w, uint radar_h, uint radar_c, const char* radar_file
            ){
		if(!func_jiance)
			func_jiance = pyengine->get_func(module_obj, "jiance");
		PyObject* rgb_array = build_array(rgb_data, rgb_w, rgb_h, rgb_c);
        PyObject* xray_array = build_array(xray_data, xray_w, xray_h, xray_c);
        PyObject* radar_array = build_array(radar_data, radar_w, radar_h, radar_c);
        
        PyObject* args = PyTuple_New(6);
        PyTuple_SetItem(args, 0, rgb_array);
        PyTuple_SetItem(args, 1, Py_BuildValue("s", rgb_file));
        PyTuple_SetItem(args, 2, xray_array);
        PyTuple_SetItem(args, 3, Py_BuildValue("s", rgb_file));
        PyTuple_SetItem(args, 4, radar_array);
        PyTuple_SetItem(args, 5, Py_BuildValue("s", radar_file));
		PyEval_CallObject(func_jiance, args);
        return true;
	}

	int shibie(uint8* rgb_data, uint rgb_w, uint rgb_h, uint rgb_c, const char* rgb_file,
            uint8* xray_data, uint xray_w, uint xray_h, uint xray_c, const char* xray_file){
		if(!func_shibie)
			func_shibie = pyengine->get_func(module_obj, "shibie");

		PyObject* rgb_array = build_array(rgb_data, rgb_w, rgb_h, rgb_c);
        PyObject* xray_array = build_array(xray_data, xray_w, xray_h, xray_c);
        
        PyObject* args = PyTuple_New(4);
        PyTuple_SetItem(args, 0, rgb_array);
        PyTuple_SetItem(args, 1, Py_BuildValue("s", rgb_file));
        PyTuple_SetItem(args, 2, xray_array);
        PyTuple_SetItem(args, 3, Py_BuildValue("s", rgb_file));
		PyEval_CallObject(func_jiance, args);
        return true;
	}

   /*
   * rgb_file/xray_file/xray_file 检测识别结果文件， fusion结果会插入到该文件
   * datatype: 雷达的状态 0：左条带 1：右条带 2：聚束
   */
   int fuse_result(const char* rgb_file, const char* xray_file, const char* radar_file, uint8 datatype){
       
   }

   /**
   * rgb_file/xray_file/radar_file： 可见光/红外/雷达的检测和识别的结果
   * cal_type: 0: 目标检测 1：目标识别 2：目标检测+目标识别
   */
   	int jiance_and_shibie(uint8* rgb_data, uint rgb_w, uint rgb_h, uint rgb_c, const char* rgb_file,
            uint8* xray_data, uint xray_w, uint xray_h, uint xray_c, const char* xray_file,
            uint8* radar_data, uint radar_w, uint radar_h, uint radar_c, const char* radar_file,
            uint8 cal_type
            ){
        
    }
    
	int finish(){
		if(!func_finish)
			func_finish = pyengine->get_func(module_obj, "finish");
		PyEval_CallObject(func_finish, NULL);
        return true;
	}

protected:
    PyObject* build_array(uint8* data, uint w, uint h, uint c){
        npy_intp dims[] = {h, w, c};
        PyObject* array = PyArray_SimpleNewFromData(3, dims, NPY_UINT8, data);
        return array;
    }
};
