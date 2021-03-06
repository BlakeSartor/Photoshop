/*******************************************************************************
 * Name            : motion_blur.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/15/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_MOTION_BLUR_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_MOTION_BLUR_H_

/****************************************************************************
includes
****************************************************************************/

#include "filter.h"
#include "convolution_filter.h"
#include "pixel_buffer.h"
#include "color_data.h"
#include "ui_ctrl.h"

/****************************************************************************
class definitions
****************************************************************************/

class MotionBlur : public ConvolutionFilter {
 public:
    MotionBlur();
    ~MotionBlur();
    void SetMask();
    void SetMask(int size,
      enum image_tools::UICtrl::MotionBlurDirection direction);
 protected:
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_MOTION_BLUR_H_
