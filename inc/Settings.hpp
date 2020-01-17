namespace TstBits {
    typedef unsigned short ushort;
    struct Settings {
        ushort  GL_VERSION_MAJOR    = 1;
        ushort  GL_VERSION_MINOR    = 1;
        ushort  FRAMERATE_LIMIT     = 0;
        ushort  SCREEN_WIDTH        = 800;
        ushort  SCREEN_HEIGHT       = 480;
        ushort  DEPTH_BITS          = 24;
        bool    FULLSCREEN          = false;
        bool    GL_CORE_PROFILE     = false;
        bool    VERTICAL_SYNC       = true;
        bool    SRGB_MODE           = true;
    };
}