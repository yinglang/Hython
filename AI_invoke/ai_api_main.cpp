#include <ai_api.h>

int main(){
    // Must Be HUI::PyNumpyEngine,  can not be PyBaseEngine
    HUI::PyNumpyEngine* pyengine = new HUI::PyNumpyEngine();
    pyengine->init_python();
    pyengine->insert_python_path(0, "./");
    
    AIAPI aiapi(pyengine);

    aiapi.init_shibie_model();

    unsigned char data[48] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4,
                   2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5,
                   3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6,
                   4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7};

    aiapi.jiance(data, 4, 4, 3, "rgb.json", 
            data, 4, 4, 3, "xray.json",
            data, 4, 4, 3, "radar.json");

    aiapi.shibie(data, 4, 4, 3, "shibie_rgb.json", 
        data, 4, 4, 3, "shibie_xray.json");

    aiapi.finish();
    delete pyengine;
    return 0;
}