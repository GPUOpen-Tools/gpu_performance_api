// =====================================================================
// <copyright file="PublicCounterDef.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2020 Advanced Micro Devices, Inc. All rights reserved.
// </copyright>
// <author>
//    AMD Developer Tools Team
// </author>
// <summary>
//      A class which contains information about a public counter.
// </summary>
// =====================================================================
namespace PublicCounterCompiler
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Security.Cryptography;
    using System.Text;

    /// <summary>
    /// Maps block instance counters to their counter index
    /// </summary>
    class DerivedCounterRegisterMap
    {
        /// <summary>
        /// Adds a counter the list of block instance counters.
        /// </summary>
        /// <param name="counterName">The name of the counter.</param>
        public void AddCounter(string counterName)
        {
            registerMap[counterName] = globalRegisterIndex;
            ++globalRegisterIndex;
        }

        /// <summary>
        /// Gets the counter index for a block instance counter.
        /// </summary>
        /// <param name="counterName">The name of the counter.</param>
        /// <returns>Index of counter, or -1 if not found</returns>
        public int GetCounterIndex(string counterName)
        {
            try
            {
                if (!registerMap.ContainsKey(counterName))
                    return -1;
                return registerMap[counterName];
            }
            catch
            {
                return -1;
            }
        }

        /// <summary>
        /// Gets all the counter indices for the indicated block instance counter template.
        /// </summary>
        /// <param name="counterName">The base name of the counter.</param>
        /// <returns>Ordered list of indices</returns>
        public List<int> GetAllCounterIndices(string counterNameBase)
        {
            List<int> indices = new List<int>();

            int baseCounterIndex = 0;

            while (true)
            {
                string counterName = counterNameBase.Replace("*", baseCounterIndex.ToString());

                int registerIndex = GetCounterIndex(counterName);

                if (registerIndex < 0)
                    break;

                indices.Add(registerIndex);

                ++baseCounterIndex;
            }

            return indices;
        }

        /// <summary>
        /// Global register index of the block instance counter within this counter.
        /// </summary>
        private int globalRegisterIndex = 0;

        /// <summary>
        /// Map of block instance counters and indices.
        /// </summary>
        private Dictionary<string, int> registerMap = new Dictionary<string, int>();
    }

    /// <summary>
    /// Contains information about a public counter definition
    /// </summary>
    public class DerivedCounterDef
    {
        /// <summary>
        /// MD5 hash function used by reproducible counter GUID generation based on the
        /// counter name and description
        /// </summary>
        MD5 md5Hash = MD5.Create();

        /// <summary>
        /// Map of name referenced counters to their index
        /// </summary>
        private DerivedCounterRegisterMap counterRegisterMap = new DerivedCounterRegisterMap();

        /// <summary>
        /// Block instance register base name and the range of counter indices it covers.
        /// </summary>
        private class RegisterBaseNameRange
        {
            public string registerBaseName;
            public int startIndex;
            public int endIndex;
        }

        /// <summary>
        /// List of block instance register base names and the ranges of counter indices they cover.
        /// </summary>
        List<RegisterBaseNameRange> registerBaseNameRanges = new List<RegisterBaseNameRange>();

        /// <summary>
        /// Adds a block instance register to the register map.
        /// </summary>
        /// <param name="registerCounterName">Name of the block instance register.</param>
        public void AddRegisterCounter(string registerCounterName)
        {
            counterRegisterMap.AddCounter(registerCounterName);
        }

        /// <summary>
        /// Returns the ending index of the last register counter.
        /// </summary>
        /// <returns>On success, the ending index of the last register counter.  Otherwise, -1.</returns>
        private int GetLastRegisterCounterEndingIndex()
        {
            if (registerBaseNameRanges.Count == 0)
            {
                return -1;
            }

            return registerBaseNameRanges[registerBaseNameRanges.Count - 1].endIndex;
        }

        /// <summary>
        /// Records a block instance register base name and its reference range.
        /// </summary>
        /// <param name="registerCounterBaseName">Base name of the block instance register.</param>
        /// <param name="startIndex">Starting index of the register.</param>
        /// <param name="endIndex">Ending index of the register.</param>
        public void AddRegisterCounterBaseNameRange(string registerCounterBaseName, int startIndex, int endIndex)
        {
            int offset = GetLastRegisterCounterEndingIndex();

            if (offset >= 0)
            {
                ++offset;
            }
            else
            {
                offset = 0;
            }

            RegisterBaseNameRange range = new RegisterBaseNameRange();

            range.registerBaseName = registerCounterBaseName;
            range.startIndex = startIndex + offset;
            range.endIndex = endIndex + offset;

            registerBaseNameRanges.Add(range);
        }

        /// <summary>
        /// Determine the block instance register base name by counter index.
        /// </summary>
        /// <param name="index">Counter index to lookup the block instance register base name for.</param>
        /// <param name="startIndex">Returned start index of the register.</param>
        /// <param name="endIndex">Returned end index of the register.</param>
        /// <returns>On success, the block instance register base name, and the start end end indices.  Otherwise, an empty string.</returns>
        public string GetRegisterCounterBaseNameForIndex(int index, out int startIndex, out int endIndex)
        {
            startIndex = -1;
            endIndex = -1;

            foreach (var register in registerBaseNameRanges)
            {
                if (index >= register.startIndex && index <= register.endIndex)
                {
                    startIndex = register.startIndex;
                    endIndex = register.endIndex;
                    return register.registerBaseName;
                }
            }

            Debug.Assert(false);
            return string.Empty;
        }

        /// <summary>
        /// Retrieves the index of a block instance register.
        /// </summary>
        /// <param name="counterName">Name of the block instance register.</param>
        /// <returns>Index of the block instance register</returns>
        public int GetRegisterCounterIndex(string counterName)
        {
            return counterRegisterMap.GetCounterIndex(counterName);
        }

        /// <summary>
        /// Retrieves all of the indices based on the wild-carded base block instance register template name.
        /// </summary>
        /// <param name="baseCounterName">Wild-cared template name of the block instance register.</param>
        /// <returns>True if the index is in the </returns>
        public List<int> GetAllRegisterCounterIndices(string baseCounterName)
        {
            return counterRegisterMap.GetAllCounterIndices(baseCounterName);
        }

        /// <summary>
        /// Structure for a hardware counter
        /// </summary>
        public class HardwareCounterDef : IEquatable<HardwareCounterDef>
        {
            /// <summary>
            /// Constructor
            /// </summary>
            public HardwareCounterDef(string counterName, int counterId)
            {
                Name = counterName;
                Id = counterId;
                Referenced = false;
            }

            /// <summary>
            /// ToString() conversion for a hardware counter definition
            /// </summary>
            override public string ToString()
            {
                return Id.ToString();
            }

            /// <summary>
            /// Equality operator
            /// </summary>
            public bool Equals(HardwareCounterDef other)
            {
                return Id == other.Id;
            }

            /// <summary>
            /// Hardware counter name
            /// </summary>
            public string Name
            {
                get;
            }

            /// <summary>
            /// Hardware counter id
            /// </summary>
            public int Id
            {
                get;
            }

            /// <summary>
            /// Whether the hardware counter has been referenced
            /// </summary>
            public bool Referenced
            {
                get;
                set;
            }
        };

        /// <summary>
        /// The list of internal counters.
        /// </summary>
        private List<HardwareCounterDef> _counters = new List<HardwareCounterDef>();

        /// <summary>
        /// Gets or sets the name of the counter.
        /// </summary>
        public string Name
        {
            get;
            set;
        }

        public bool ValidName()
        {
            return !string.IsNullOrEmpty(Name);
        }

        /// <summary>
        /// Gets or sets the counter group (aka category).
        /// </summary>
        public string Group
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the counter description.
        /// </summary>
        public string Desc
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the counter type.
        /// </summary>
        public string Type
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets usage information.
        /// </summary>
        public string Usage
        {
            get;
            set;
        }

        public bool ValidUsage()
        {
            return !string.IsNullOrEmpty(Usage);
        }

        /// <summary>
        /// Gets or sets the equation from which the counter should be computed.
        /// </summary>
        public string Comp
        {
            get;
            set;
        }

        public bool ValidEquation()
        {
            return !string.IsNullOrEmpty(Comp);
        }

        /// <summary>
        /// Gets or sets the readable comp for readable debugging, output, validation
        /// </summary>
        public string CompReadable
        {
            get;
            set;
        }

        /// <summary>
        /// Adds a counter the list of required internal counters for this public counter.
        /// </summary>
        /// <param name="counterIndex">The index of the internal counter to add.</param>
        public void AddCounter(string counterName, int counterIndex)
        {
            this._counters.Add(new HardwareCounterDef(counterName, counterIndex));
        }

        /// <summary>
        /// Gets a required counter based on the index from the computation equation.
        /// </summary>
        /// <param name="index">the index of the counter to get.</param>
        /// <returns>The 'global' index of the internal counter.</returns>
        public HardwareCounterDef GetCounter(int index)
        {
            return this._counters[index];
        }

        /// <summary>
        /// Get the number of internal counters used in this public counter.
        /// </summary>
        /// <returns>The number of counters used.</returns>
        public int GetCounterCount()
        {
            return this._counters.Count;
        }

        /// <summary>
        /// Clears the list of internal counters used.
        /// </summary>
        public void ClearCounters()
        {
            this._counters.Clear();
        }

        /// <summary>
        /// Checks to see if a 'global' index is available in the counters list.
        /// </summary>
        /// <param name="counterIndex">The 'global' index to find.</param>
        /// <returns>True if the index is in the </returns>
        public bool CounterDefined(int counterIndex)
        {
            return this._counters.Contains(new HardwareCounterDef(string.Empty, counterIndex));
        }

        /// <summary>
        /// Gets the list of internal counters.
        /// </summary>
        /// <returns>List of internal counters.</returns>
        public List<HardwareCounterDef> GetCounters()
        {
            return this._counters;
        }

        /// <summary>
        /// Generates a Guid for the counter using an MD5 hash of the counter name and description.
        /// </summary>
        /// <returns>Guid for the counter.</returns>
        public Guid GuidHash
        {
            get
            {
                byte[] data = md5Hash.ComputeHash(Encoding.UTF8.GetBytes(Name + Desc));

                StringBuilder sBuilder = new StringBuilder();

                for (int i = 0; i < data.Length; i++)
                {
                    sBuilder.Append(data[i].ToString("x2"));
                }

                Guid guid = new Guid(sBuilder.ToString());
                return guid;
            }
        }

    }
}

