// =====================================================================
// <copyright file="PublicCounterDef.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
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
   using System.Text;

   /// <summary>
   /// Contains information about a public counter definition
   /// </summary>
   public class PublicCounterDef
   {
      /// <summary>
      /// stores the maximum name length
      /// </summary>
      private static int maxNameLen = 0;

      /// <summary>
      /// stores the maximum description length
      /// </summary>
      private static int maxDescLen = 0;

      /// <summary>
      /// stores the max type length
      /// </summary>
      private static int maxTypeLen = 0;

      /// <summary>
      /// stores the max usage length
      /// </summary>
      private static int maxUsageLen = 0;

      /// <summary>
      /// stores the max counter list size.
      /// </summary>
      private static int maxCounterCount = 0;

      /// <summary>
      /// stores the max equation length
      /// </summary>
      private static int maxCompLen = 0;

      /// <summary>
      /// The name of the counter.
      /// </summary>
      private string name = string.Empty;

      /// <summary>
      /// The counter description.
      /// </summary>
      private string desc = string.Empty;

      /// <summary>
      /// The counter type. datatype?
      /// </summary>
      private string type = string.Empty;

      /// <summary>
      /// The counter usage.
      /// </summary>
      private string usage = string.Empty;

      /// <summary>
      /// The list of internal counters.
      /// </summary>
      private List<int> counters = new List<int>();

      /// <summary>
      /// The counter computation equation.
      /// </summary>
      private string comp = string.Empty;
      
      /// <summary>
      /// Gets or sets the name of the counter.
      /// </summary>
      public string Name
      {
         get
         {
            return this.name;
         }

         set
         {
            this.name = value;
            if (this.name.Length > maxNameLen)
            {
               maxNameLen = this.name.Length;
            }
         }
      }

      /// <summary>
      /// Gets or sets the counter description.
      /// </summary>
      public string Desc
      {
         get
         {
            return this.desc;
         }

         set
         {
            this.desc = value;
            if (this.desc.Length > maxDescLen)
            {
               maxDescLen = this.desc.Length;
            }
         }
      }

      /// <summary>
      /// Gets or sets the counter type.
      /// </summary>
      public string Type
      {
         get
         {
            return this.type;
         }

         set
         {
            this.type = value;
            if (this.type.Length > maxTypeLen)
            {
               maxTypeLen = this.type.Length;
            }
         }
      }

      /// <summary>
      /// Gets or sets usage information.
      /// </summary>
      public string Usage
      {
         get
         {
            return this.usage;
         }

         set
         {
            this.usage = value;
            if (this.usage.Length > maxUsageLen)
            {
               maxUsageLen = this.usage.Length;
            }
         }
      }

      /// <summary>
      /// Gets or sets the equation from which the counter should be computed.
      /// </summary>
      public string Comp
      {
         get
         {
            return this.comp;
         }

         set
         {
            this.comp = value;
            if (this.comp.Length > maxCompLen)
            {
               maxCompLen = this.comp.Length;
            }
         }
      }

      /// <summary>
      /// Gets or sets the 
      /// </summary>
      public string CounterType { get; set; }

      /// <summary>
      /// Adds a counter the list of required internal counters for this public counter.
      /// </summary>
      /// <param name="counterIndex">The index of the internal counter to add.</param>
      public void AddCounter(int counterIndex)
      {
         this.counters.Add(counterIndex);
         if (this.counters.Count > maxCounterCount)
         {
            maxCounterCount = this.counters.Count;
         }
      }

      /// <summary>
      /// Gets a required counter based on the index from the computation equation.
      /// </summary>
      /// <param name="index">the index of the counter to get.</param>
      /// <returns>The 'global' index of the internal counter.</returns>
      public int GetCounter(int index)
      {
         return this.counters[index];
      }

      /// <summary>
      /// Get the nubmer of internal counters used in this public counter.
      /// </summary>
      /// <returns>The number of counters used.</returns>
      public int GetCounterCount()
      {
         return this.counters.Count;
      }

      /// <summary>
      /// Clears the list of internal counters used.
      /// </summary>
      public void ClearCounters()
      {
         this.counters.Clear();
      }

      /// <summary>
      /// Checks to see if a 'global' index is available in the counters list.
      /// </summary>
      /// <param name="counterIndex">The 'global' index to find.</param>
      /// <returns>True if the index is in the </returns>
      public bool CounterDefined(int counterIndex)
      {
         return this.counters.Contains(counterIndex);
      }

      /// <summary>
      /// Gets the list of internal counters.
      /// </summary>
      /// <returns>List of internal counters.</returns>
      public List<int> GetCounters()
      {
         return this.counters;
      }
   }
}

