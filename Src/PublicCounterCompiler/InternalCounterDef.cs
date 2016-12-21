// =====================================================================
// <copyright file="InternalCounterDef.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
// </copyright>
// <author>
//    AMD Developer Tools Team
// </author>
// <summary>
//      A class which contains information about an internal counter.
// </summary>
// =====================================================================
namespace PublicCounterCompiler
{
   using System;
   using System.Collections.Generic;
   using System.Text;
   
   /// <summary>
   /// Contains the name and type of an internal counter 
   /// </summary>
   public class InternalCounterDef
   {
       /// <summary>
       /// Gets or sets the name of the internal counter.
       /// </summary>
       public string Name { get; set; }

       /// <summary>
       /// Gets or sets the type of the internal counter.
       /// </summary>
       public string Type { get; set; }
   }
}
