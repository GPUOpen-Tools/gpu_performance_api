/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2014-2018 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 **********************************************************************************************************************/
/**
 **********************************************************************************************************************
 * @file  vk_internal_ext_helper.h
 * @brief Helper header for unpublished extensions.
 **********************************************************************************************************************
 */

#ifndef VK_INTERNAL_EXT_HELPER_H_
#define VK_INTERNAL_EXT_HELPER_H_

#define VK_EXTENSION_ENUM_BASE_VALUE        1000000000ull
#define VK_EXTENSION_ENUM_RANGE_SIZE        1000ull

#define VK_EXTENSION_ENUM(extnr, type, offset) \
    ((type)(VK_EXTENSION_ENUM_BASE_VALUE + (((extnr)-1) * VK_EXTENSION_ENUM_RANGE_SIZE) + (offset)))

#define VK_EXTENSION_BIT(type, bit) \
    ((type)(1 << (bit)))

#endif /* VK_INTERNAL_EXT_HELPER_H_ */
