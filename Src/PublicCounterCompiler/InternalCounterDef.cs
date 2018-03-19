// =====================================================================
// <copyright file="InternalCounterDef.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2017 Advanced Micro Devices, Inc. All rights reserved.
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
            Index = index;
            Name = name;
            Datatype = datatype;
            IsAsicSpecific = asicSpecific;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public InternalCounterDef(InternalCounterDef other)
        {
            Index = other.Index;
            Name = other.Name;
            Datatype = other.Datatype;
            IsAsicSpecific = other.IsAsicSpecific;
        }

        /// <summary>
        /// Index of the internal counter.
        /// </summary>
        public int Index { get; }

        /// <summary>
        /// Gets the name of the internal counter.
        /// </summary>
        public string Name { get; }

        /// <summary>
        /// Gets the type of the internal counter.
        /// </summary>
        public string Datatype { get; }

        /// <summary>
        /// Flag that indicates whether the internal counter is ASIC specific
        /// </summary>
        public bool IsAsicSpecific { get; }

        /// <summary>
        /// ToString() representation of the internal counter.
        /// </summary>
        override public string ToString()
        {
            return Name;
        }

        /// <summary>
        /// Equality operator
        /// </summary>
        public bool Equals(InternalCounterDef other)
        {
            return Name == other.Name;
        }
    }
}
