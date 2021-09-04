//#define DEV_MODE
#include "xhfr.hpp"
#include "app_code/App.hpp"

int main(int argc, char* argv[]) {

        App app;

        int w = 1280, h = 720;
        float s = 1.4;
        w *= s;
        h *= s;
        app.init(argc, argv, "luapad", w, h);


        //PHYSFS_mount("test.7z","/res/",0);
        //PHYSFS_mount("./","/", 0);
        //PHYSFS_setWriteDir("./");



        /*
         * {
            //temp I HOPE
            PHYSFS_mount("compressed.zip","/",0);
        }*/




        xhfr::main();

        xhfr::shutdown();

}

