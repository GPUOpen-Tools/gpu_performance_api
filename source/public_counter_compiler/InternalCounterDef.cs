// =====================================================================
// <copyright file="InternalCounterDef.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2020 Advanced Micro Devices, Inc. All rights reserved.
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
    public class InternalCounterDef : IEquatable<InternalCounterDef>
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public InternalCounterDef(int index, string name, string datatype, bool asicSpecific)
        {
            this.index = index;
            this.name = name;
            this.datatype = datatype;
            isAsicSpecific = asicSpecific;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public InternalCounterDef(InternalCounterDef other)
        {
            index = other.index;
            name = other.name;
            datatype = other.datatype;
            isAsicSpecific = other.isAsicSpecific;
        }

        /// <summary>
        /// Index of the internal counter.
        /// </summary>
        public int index { get; }

        /// <summary>
        /// Gets the name of the internal counter.
        /// </summary>
        public string name { get; }

        /// <summary>
        /// Gets the type of the internal counter.
        /// </summary>
        public string datatype { get; }

        /// <summary>
        /// Flag that indicates whether the internal counter is ASIC specific
        /// </summary>
        public bool isAsicSpecific { get; }

        /// <summary>
        /// ToString() representation of the internal counter.
        /// </summary>
        override public string ToString()
        {
            return name;
        }

        /// <summary>
        /// Equality operator
        /// </summary>
        public bool Equals(InternalCounterDef other)
        {
            return name == other.name;
        }
    }
}
