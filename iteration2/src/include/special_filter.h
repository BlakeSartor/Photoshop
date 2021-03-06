/*******************************************************************************
 * Name            : special_filter.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/20/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_SPECIAL_FILTER_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_SPECIAL_FILTER_H_

/****************************************************************************
includes
****************************************************************************/

#include "include/filter.h"
#include "include/convolution_filter.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/****************************************************************************
class definitions
****************************************************************************/

class SpecialFilter : public ConvolutionFilter {
 public:
    SpecialFilter();
    ~SpecialFilter();
    void SetMask();
    void SetMask(int size);
    // void ApplyFilter(image_tools::PixelBuffer *canvas);
 protected:
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_SPECIAL_FILTER_H_
