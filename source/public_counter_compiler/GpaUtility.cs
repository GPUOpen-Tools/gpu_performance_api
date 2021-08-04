// =====================================================================
// <copyright file="GpaUtility.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2019-2020 Advanced Micro Devices, Inc. All rights reserved.
// </copyright>
// <author>
//    AMD Developer Tools Team
// </author>
// <summary>
//      GPA Utility class
// </summary>
// =====================================================================

using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.IO;

public static class GpaUtility
{
    public static string ToCamelCase(this string singleWord)
    {
        if (!String.IsNullOrEmpty(singleWord))
        {
            return singleWord[0].ToString().ToUpper() + singleWord.Substring(1).ToLower();
        }

        return singleWord;
    }

    public static string ToCamelCase(this string wordsWithSeparator, char separator)
    {
        if (String.IsNullOrEmpty(wordsWithSeparator))
        {
            return wordsWithSeparator;
        }

        string[] splitStrings = wordsWithSeparator.Split(separator);
        string camelCaseString = string.Empty;
        foreach (string s in splitStrings)
        {
            camelCaseString += s.ToCamelCase();
        }

        return camelCaseString;
    }
}
