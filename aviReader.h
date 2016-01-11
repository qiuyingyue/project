#ifndef aviReader_h
#define aviReader_h
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/videostab/videostab.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "cv.h"
extern int videotext;
using namespace std;
void initAvi(char *videofile);
void videoTexInit();
void genMytex(int texw, int texh);
#endif /* aviReader_h */
