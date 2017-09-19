/*******************************************************************************
 * Name            : filter_manager.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation of FilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:47:02 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*****************************************************************************//**
 * Includes
 ******************************************************************************/

#include "include/filter_manager.h"
#include "iostream"
#include "GL/glui.h"
#include "pixel_buffer.h"
#include "ui_ctrl.h"
#include "blur.h"
#include "filter.h"
#include "convolution_filter.h"
#include "motion_blur.h"
#include "quantize.h"
#include "rgb_levels.h"
#include "saturation.h"
#include "sharpen.h"
#include "threshold.h"
#include "color_data.h"
#include "edge_detection.h"
#include "special_filter.h"

/*****************************************************************************//**
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*****************************************************************************//**
 * Constructors/Destructor
 ******************************************************************************/
FilterManager::FilterManager(void) :
    channel_color_red_(0.0),
    channel_color_green_(0.0),
    channel_color_blue_(0.0),
    saturation_amount_(0.0),
    threshold_amount_(0.0),
    blur_amount_(0.0),
    sharpen_amount_(0.0),
    motion_blur_amount_(0.0),
    motion_blur_direction_(UICtrl::UI_DIR_E_W),

    quantize_bins_(0) {
    blur_ = new Blur();
    edge_detection_ = new EdgeDetection();
    motion_blur_ = new MotionBlur();
    quantize_ = new Quantize();
    rgb_levels_ = new RGBLevels();
    saturation_ = new Saturation();
    sharpen_ = new Sharpen();
    special_filter_ = new SpecialFilter();
    threshold_ = new Threshold();
}

/*****************************************************************************//**
 * Member Functions
 ******************************************************************************/

void FilterManager::ApplyChannel(PixelBuffer *canvas) {
  std::cout << "Apply has been clicked for Channels with red = "
            << channel_color_red_
            << ", green = " << channel_color_green_
            << ", blue = " << channel_color_blue_ << std::endl;
    rgb_levels_->ApplyFilter
      (canvas, channel_color_red_, channel_color_green_, channel_color_blue_);

    std::cout << "Apply is finished\n";
}

void FilterManager::ApplySaturate(PixelBuffer *canvas) {
  std::cout << "Apply has been clicked for Saturate with amount = "
            << saturation_amount_ << std::endl;
    saturation_->ApplyFilter(canvas, saturation_amount_);
}

void FilterManager::ApplyBlur(PixelBuffer *canvas) {
  std::cout << "Apply has been clicked for Blur with amount = "
            << blur_amount_ << std::endl;
    blur_->ApplyFilter(canvas, blur_amount_);
}

void FilterManager::ApplySharpen(PixelBuffer *canvas) {
  std::cout << "Apply has been clicked for Sharpen with amount = "
            << sharpen_amount_ << std::endl;
    sharpen_->ApplyFilter(canvas, sharpen_amount_);
}

void FilterManager::ApplyMotionBlur(PixelBuffer *canvas) {
  std::cout << "Apply has been clicked for Sharpen with amount = "
            << motion_blur_amount_
            << " and direction " << motion_blur_direction_ << std::endl;
    motion_blur_->ApplyFilter
      (canvas, motion_blur_amount_, motion_blur_direction_);
}

void FilterManager::ApplyEdgeDetect(PixelBuffer *canvas) {
  std::cout << "Apply has been clicked for Edge Detect" << std::endl;
    edge_detection_->ApplyFilter(canvas);
}

void FilterManager::ApplyQuantize(PixelBuffer *canvas) {
  std::cout << "Apply has been clicked for Quantize with bins = "
            << quantize_bins_ << std::endl;
    quantize_->ApplyFilter(canvas, quantize_bins_);
}
void FilterManager::ApplyThreshold(PixelBuffer *canvas) {
  std::cout << "Apply Threshold has been clicked with amount ="
            << threshold_amount_ << std::endl;
    threshold_->ApplyFilter(canvas, threshold_amount_);
}
void FilterManager::ApplySpecial(PixelBuffer *canvas) {
  std::cout << "Apply has been clicked for Special" << std::endl;
    special_filter_->ApplyFilter(canvas);
}

void FilterManager::InitGlui(const GLUI *const glui,
                             void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *filter_panel = new GLUI_Panel(const_cast<GLUI*>(glui), "Filters");
  {
    GLUI_Panel *blur_panel = new GLUI_Panel(filter_panel, "Blur");
    {
      GLUI_Spinner * blur_amount = new GLUI_Spinner(blur_panel, "Amount:",
                                                    &blur_amount_);
      blur_amount->set_int_limits(0, 20);
      blur_amount->set_int_val(5);

      new GLUI_Button(blur_panel, "Apply",
                      UICtrl::UI_APPLY_BLUR, s_gluicallback);
    }

    GLUI_Panel *motion_blur_panel = new GLUI_Panel(filter_panel, "MotionBlur");
    {
      GLUI_Spinner*motion_blur_amount = new GLUI_Spinner(motion_blur_panel,
                                                         "Amount:",
                                                         &motion_blur_amount_);
      motion_blur_amount->set_int_limits(0, 100);
      motion_blur_amount->set_int_val(5);

      motion_blur_direction_ = UICtrl::UI_DIR_E_W;
      GLUI_RadioGroup *dir_blur = new GLUI_RadioGroup(
          motion_blur_panel,
          reinterpret_cast<int*>(&motion_blur_direction_));
      new GLUI_RadioButton(dir_blur, "North/South");
      new GLUI_RadioButton(dir_blur, "East/West");
      new GLUI_RadioButton(dir_blur, "NorthEast/SouthWest");
      new GLUI_RadioButton(dir_blur, "NorthWest/SouthEast");

      new GLUI_Button(motion_blur_panel, "Apply",
                      UICtrl::UI_APPLY_MOTION_BLUR, s_gluicallback);
    }
    GLUI_Panel *sharpen_panel = new GLUI_Panel(filter_panel, "Sharpen");
    {
      GLUI_Spinner * sharp_amount = new GLUI_Spinner(sharpen_panel,
                                                     "Amount:",
                                                     &sharpen_amount_);
      sharp_amount->set_int_limits(0, 100);
      sharp_amount->set_int_val(5);

      new GLUI_Button(sharpen_panel, "Apply",
                      UICtrl::UI_APPLY_SHARP, s_gluicallback);
    }
    GLUI_Panel *edge_det_panel = new GLUI_Panel(filter_panel, "Edge Detect");

    {
      new GLUI_Button(edge_det_panel, "Apply",
                      UICtrl::UI_APPLY_EDGE, s_gluicallback);
    }
    GLUI_Panel *thres_panel = new GLUI_Panel(filter_panel, "Threshold");
    {
      GLUI_Spinner *threshold_amount = new GLUI_Spinner(thres_panel,
                                                        "Level:",
                                                        &threshold_amount_);
      threshold_amount->set_float_limits(0, 1);
      threshold_amount->set_float_val(0.5);

      new GLUI_Button(thres_panel, "Apply",
                      UICtrl::UI_APPLY_THRESHOLD, s_gluicallback);
    }

    new GLUI_Column(filter_panel, true);

    GLUI_Panel *satur_panel = new GLUI_Panel(filter_panel, "Saturation");
    {
      GLUI_Spinner * saturation_amount = new GLUI_Spinner(satur_panel,
                                                          "Amount:",
                                                          &saturation_amount_);
      saturation_amount->set_float_limits(-10, 10);
      saturation_amount->set_float_val(1);

      new GLUI_Button(satur_panel, "Apply",
                      UICtrl::UI_APPLY_SATURATE,
                      s_gluicallback);
    }

    GLUI_Panel *channel_panel = new GLUI_Panel(filter_panel, "Channels");
    {
      GLUI_Spinner *channel_red = new GLUI_Spinner(channel_panel, "Red:",
                                                   &channel_color_red_);
      GLUI_Spinner *channel_green = new GLUI_Spinner(channel_panel,
                                                     "Green:",
                                                     &channel_color_green_);
      GLUI_Spinner *channel_blue = new GLUI_Spinner(channel_panel,
                                                    "Blue:",
                                                    &channel_color_blue_);

      channel_red->set_float_limits(0, 10);
      channel_red->set_float_val(1);
      channel_green->set_float_limits(0, 10);
      channel_green->set_float_val(1);
      channel_blue->set_float_limits(0, 10);
      channel_blue->set_float_val(1);

      new GLUI_Button(channel_panel, "Apply",
                      UICtrl::UI_APPLY_CHANNEL,
                      s_gluicallback);
    }

    GLUI_Panel *quant_panel = new GLUI_Panel(filter_panel, "Quantize");
    {
      GLUI_Spinner * quantize_bins = new GLUI_Spinner(quant_panel, "Bins:",
                                                      &quantize_bins_);
      quantize_bins->set_int_limits(2, 256);
      quantize_bins->set_int_val(8);
      quantize_bins->set_speed(0.1);

      new GLUI_Button(quant_panel, "Apply",
                      UICtrl::UI_APPLY_QUANTIZE,
                      s_gluicallback);
    }

    /*! YOUR SPECIAL FILTER PANEL */
    GLUI_Panel *specialFilterPanel = new GLUI_Panel(filter_panel,
                                                    "Special Filter");
    {
      new GLUI_Button(specialFilterPanel,
                      "Apply",
                      UICtrl::UI_APPLY_SPECIAL_FILTER,
                      s_gluicallback);
    }
  }
} /* FilterManager::InitGlui() */

}  /* namespace image_tools */
