.. Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
.. GPU Performance Counters

.. _gpa_counters:

Performance Counters
####################

The performance counters exposed through GPU Performance API are organized into
groups to help provide clarity and organization to all the available data.
Below is a collective list of counters from all the supported hardware
generations. Some of the counters may not be available depending on the
hardware being profiled. To view which GPUs belong to which hardware
generations, the best reference is the `gs_cardInfo array in the
common-src-DeviceInfo
<https://github.com/GPUOpen-Tools/common-src-DeviceInfo/blob/master/DeviceInfoUtils.cpp#L19>`_
repository on GitHub. You can see how the various cards map to hardware
generations by looking at the `GDT_HW_GENERATION enum
<https://github.com/GPUOpen-Tools/common-src-DeviceInfo/blob/master/DeviceInfo.h#L59>`_

For Graphics workloads, it is recommended that you initially profile with
counters from the Timing group to determine whether the profiled calls are
worth optimizing (based on GPUTime value), and which parts of the pipeline are
performing the most work. Note that because the GPU is highly parallelized,
various parts of the pipeline can be active at the same time; thus, the "Busy"
counters probably will sum over 100 percent. After identifying one or more
stages to investigate further, enable the corresponding counter groups for more
information on the stage and whether or not potential optimizations exist.

Counters Exposed for Graphics Performance Analysis
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

The following tables show the set of counters exposed for analysis of GPU
Graphics workloads, as well the family of GPUs and APUs on which each counter
is available:

.. include:: graphics_counter_tables_gfx10.rst
.. include:: graphics_counter_tables_gfx9.rst
.. include:: graphics_counter_tables_gfx8.rst

Counters Exposed for Compute Performance Analysis
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

The following tables show the set of counters exposed for analysis of GPU
Compute workloads, as well the family of GPUs and APUs on which each counter
is available:

.. include:: compute_counter_tables_gfx10.rst
.. include:: compute_counter_tables_gfx9.rst
.. include:: compute_counter_tables_gfx8.rst

