//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Declaration of API-specific imlpementation functions
//==============================================================================

#ifndef _GPA_VERSION_H_
#define _GPA_VERSION_H_

#define GPA_MAJOR_VERSION 2
#define GPA_MINOR_VERSION 20
#define GPA_BUILD_NUMBER 0
#define GPA_UPDATE_VERSION 0

#define GPA_STR_VALUE(s) #s
#define GPA_VERSION_STRING(s) GPA_STR_VALUE(s)

#define GPA_MAJOR_VERSION_STR GPA_VERSION_STRING(GPA_MAJOR_VERSION)
#define GPA_MINOR_VERSION_STR GPA_VERSION_STRING(GPA_MINOR_VERSION)
#define GPA_BUILD_NUMBER_STR GPA_VERSION_STRING(GPA_BUILD_NUMBER)
#define GPA_UPDATE_VERSION_STR GPA_VERSION_STRING(GPA_UPDATE_VERSION)

#define GPA_COPYRIGHT_CURRENT_YEAR 2016

#define GPA_COPYRIGHT_STR "Copyright (c) 2010-" GPA_VERSION_STRING(GPA_COPYRIGHT_CURRENT_YEAR) " Advanced Micro Devices, Inc. All rights reserved."

#endif // _GPA_VERSION_H_
