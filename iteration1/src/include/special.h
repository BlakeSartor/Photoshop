/*******************************************************************************
 * Name            : special.h
 * Project         : BrushWork
 * Description     : Implementation of BrushWrok
 * Copyright       : Copyright 2016. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Raghav Mutneja
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION1_SRC_INCLUDE_SPECIAL_H_
#define PROJECT_ITERATION1_SRC_INCLUDE_SPECIAL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/tool.h"
#include "include/mask.h"

/*******************************************************************************
 * Class Declaration
 ******************************************************************************/

class Special : public Tool {
 public:
    Special();
    ~Special();
    void virtual SetMask();
};

#endif  // PROJECT_ITERATION1_SRC_INCLUDE_SPECIAL_H_
