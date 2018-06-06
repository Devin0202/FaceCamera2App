#pragma once

/*******************************************************************************************
*
* Copyright 2018, HiScene
*
* This file is HiScene's property. It contains HiScene's proprietary and confidential
* information and trade secret. The information and code contained in this file is only
* intended for authorized HiScene employees and customers.
*
* DO NOT DISTRIBUTE, DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT PROPER AUTHORIZATION FROM
* HISCENE.
*
* If you are not an intended recipient of this file, you must not copy, distribute, modify,
* or take any action in reliance on it. If you have received this file in error, please
* immediately notify HiScene, and permanently delete the original and any copy of it and
* any printout thereof.
*
******************************************************************************************/

#include <cstdlib>
#include <cstdint>

/// supported image types
/// current version only support NV12 & NV21
typedef enum
{
    HIGES_IMAGE_TYPE_8UC1 = 0, // gray image, 8 unsigned char channel 1
    HIGES_IMAGE_TYPE_8UC3 = 1, // bgr image, 8 unsigned char channel 3
    HIGES_IMAGE_TYPE_NV12 = 2, // yuv NV12 color image
    HIGES_IMAGE_TYPE_NV21 = 3  // yuv NV21 color image
} HiGesImageType;

/// a type representing an image object. data is not managed - user manages data.
typedef struct
{
    HiGesImageType  type;       // image type
    int             width;      // number of columns in pixels : only support 720p image (1280x720) at present.
    int             height;     // number of rows in pixels
    unsigned char*  data;       // point to the first pixel in first row
    int             stride;     // bytes between each two neighboring row heads, no padding allowed in this version (== width)
    uint32_t        timestamp;  // the timestamp of the frame when captured in milliseconds (ms).
} HiGesImage;

/// representing a rectangle in the image, unit in pixels.
typedef struct
{
    int     x;          // horizontal coordinate of the top left corner
    int     y;          // vertical coordinate of the top left corner
    int     width;      // length in horizontal direction.
    int     height;     // length in vertical direction.
} HiGesRect;

/// HiGes bool type
typedef enum
{
    HIGES_FALSE = 0,
    HIGES_TRUE  = 1
} HiGesBool;

/// possible trace patterns
/// all the trace patterns are defined as follows:
///   1. user wears the camera.
///   2. trace pattern is viewed from the perspective of user.
///   3. not all patterns are supported at current version (-1 to 8 are supported)
typedef enum
{
    HIGES_TRACE_PATTERN_ERROR              = -1,   // error
    HIGES_TRACE_PATTERN_NONE               = 0,    // no trace
    HIGES_TRACE_PATTERN_LEFT               = 1,    // moving left
    HIGES_TRACE_PATTERN_RIGHT              = 2,    // moving right
    HIGES_TRACE_PATTERN_LEFT_FAST          = 3,    // moving left fast
    HIGES_TRACE_PATTERN_RIGHT_FAST         = 4,    // moving right fast
    HIGES_TRACE_PATTERN_PALM2FIST          = 5,    // palm to fist
    HIGES_TRACE_PATTERN_FIST2PALM          = 6,    // fist to palm
    HIGES_TRACE_PATTERN_EXPAND             = 7,    // expand
    HIGES_TRACE_PATTERN_COLLAPSE           = 8,    // collapse
} HiGesTracePattern;

typedef enum
{
    HIGES_LOGMODE_NOMODE       = 0,
    HIGES_LOGMODE_DEBUG        = 1,
    HIGES_LOGMODE_ERROR        = 2
} HiGesLogMode;

typedef enum
{
    HIGES_HAND_NONE    = 0,      // no hand
    HIGES_HAND_PALM    = 1,
    HIGES_HAND_FIST    = 2,
    HIGES_HAND_MULTI   = 3
} HiGesHandType;

typedef struct {
} HiGesOptions;

/// a type representing the processing result of higes.
typedef struct
{
    size_t                 handBBoxesCount;            // [input, output] how many bboxes in the buffer. The algorithm will at most fill this many items in headBBoxes.
    HiGesRect*             handBBoxes;                 // [output] buffer pointer holds output for bboxes.
    HiGesHandType          handType;                   // [output] in this frame, which one (palm/fist) is tracked
    HiGesTracePattern      tracePattern;               // [output] in this frame, the pattern of trace
} HiGesResult;

/// a type representing the processing result of higes.
typedef struct
{
    int w[10];
    int h[10];
    int l[10];
    int t[10];

    int ws;
    int hs;
    int ls;
    int ts;
} cReturn;