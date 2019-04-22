#ifndef LOADFILE_H
#define LOADFILE_H
class jpegImage
{
    private:
    int d_width;
    int d_height;
    int d_format;
    int d_type;
    unsigned char * d_buf;
    public:
        //constructor
        jpegImage(const char * filename);
        jpegImage(const jpegImage& s);
        jpegImage& operator=(const jpegImage& s);
        ~jpegImage();
    public:
        //maniulator
        int loadJpegFile(const char * filename);
        void releaseBuf();
        //accessor
        int getWidth() { return d_width; }
        int getHeight() { return d_height; }
        int getType() { return d_type;}
        int getFormat() { return d_format;}
        unsigned char *  getBuf() { return d_buf;}
};
#endif

