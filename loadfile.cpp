#include <turbojpeg.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "loadfile.h"
#define _throw(action, message) {\
    printf("ERROR in line %d while %s:\n%s\n", __LINE__, action, message); \
    retval = -1;  goto bailout; \
}
#define __throwtj(action)  _throw(action,tjGetErrorStr2(tjInstance))
#define _throwunix(action)  _throw(action, strerror(errno))
const char *subsampName[TJ_NUMSAMP] = {
    "4:4:4", "4:2:2", "4:2:0", "Grayscale", "4:4:0", "4:1:1"
};

const char *colorspaceName[TJ_NUMCS] = {
    "RGB", "YCbCr", "GRAY", "CMYK", "YCCK"
};

//JPEGIMAGE BEGIN
void jpegImage::releaseBuf()
{
    if (d_buf)
        tjFree(d_buf);
}
int jpegImage::loadJpegFile(const char * filename)
{
    int retval = 0;
    FILE *jpegFile = NULL;
    int size;
    int jpegSize;
    tjhandle tjInstance = NULL;
    int width, height;
    int flags = 0;
    int pixelFormat = TJPF_BGRX;
    unsigned char * imgBuf = NULL, *jpegBuf = NULL;

    if (( jpegFile = fopen(filename,"rb")) == NULL)
        _throwunix("open file");
    if (fseek(jpegFile,0,SEEK_END) < 0 || ((size = ftell(jpegFile)) < 0) ||
            fseek(jpegFile,0,SEEK_SET) <0)
        _throwunix("determining input file size");
    jpegSize = size;
    jpegBuf = (unsigned char *) tjAlloc(jpegSize);
    fread(jpegBuf,jpegSize,1,jpegFile);
    tjInstance = tjInitDecompress();
    int inSubsamp,inColorspace;
    tjDecompressHeader3(tjInstance,jpegBuf,jpegSize,&width,&height,
            &inSubsamp,&inColorspace);
    //printf("Input Image: %d x %d pixels, %s subsampling , %s colorspace\n",
     //       width,height,subsampName[inSubsamp],colorspaceName[inColorspace]); 

    imgBuf = (unsigned char *) tjAlloc(width * height * tjPixelSize[pixelFormat]);
    if (tjDecompress2(tjInstance,jpegBuf,jpegSize,imgBuf,width,0,height,
            pixelFormat,flags) < 0)
        __throwtj("decompressing JPEG image");
    d_width = width;
    d_height = height;
    d_buf = imgBuf;
    tjFree(jpegBuf); jpegBuf = NULL;
    tjDestroy(tjInstance); tjInstance = NULL;
bailout:
  //if (imgBuf) tjFree(imgBuf);
  if (tjInstance) tjDestroy(tjInstance);
  if (jpegBuf) tjFree(jpegBuf);
  if (jpegFile) fclose(jpegFile);
  return retval;
}
jpegImage::~jpegImage()
{
    releaseBuf();
}
jpegImage& jpegImage::operator=(const jpegImage& s)
{
    return *this;
}
jpegImage::jpegImage(const jpegImage& s)
{
}
jpegImage::jpegImage(const char * filename)
{
    d_width = 0;
    d_height = 0;
    d_format = TJPF_BGRX;
    d_type = 0;
    d_buf =NULL;
    loadJpegFile(filename);
}
//JPEGIMAGE END
