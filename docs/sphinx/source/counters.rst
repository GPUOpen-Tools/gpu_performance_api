.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
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
<https://github.com/GPUOpen-Tools/common_src_device_info/blob/master/DeviceInfo.cpp#L10>`_
repository on GitHub. You can see how the various cards map to hardware
generations by looking at the `GDT_HW_GENERATION enum
<https://github.com/GPUOpen-Tools/common_src_device_info/blob/master/DeviceInfo.h#L67>`_

For Graphics workloads, it is recommended that you initially profile with
counters from the Timing group to determine whether the profiled calls are
worth optimizing (based on GPUTime value), and which parts of the pipeline are
performing the most work. Note that because the GPU is highly parallelized,
various parts of the pipeline can be active at the same time; thus, the "Busy"
counters probably will sum over 100 percent. After identifying one or more
stages to investigate further, enable the corresponding counter groups for more
information on the stage and whether or not potential optimizations exist.

Pipeline-Based Counter Groups
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

On Vega, RDNA, and RDNA2 hardware, certain use cases allow the driver to make
optimizations by combining two shader stages together. For example, in a Vertex
+ Geometry + Pixel Shader pipeline (VS-GS-PS), the Vertex and Geometry Shaders
get combined and GPUPerfAPI exposes them in the "VertexGeometry" group
(counters with the "VsGs" prefix). In pipelines that use tessellation, the
Vertex and Hull Shaders are combined and exposed as the "PreTessellation" group
(with "PreTess" prefix), and the Domain and Geometry Shaders (if GS is used)
are combined into the the "PostTessellation" group (with "PostTess" prefix).
Pixel Shaders and Compute Shaders are always exposed as their respective types.
The table below may help to visualize the mapping between the API-level shaders
(across the top), and which prefixes to look for in the GPUPerfAPI counters.

.. csv-table::
    :header: "Pipeline", "Vertex", "Hull", "Domain", "Geometry", "Pixel", "Compute"
    :widths: auto

    "VS-PS",          "VsGs",    "",        "",         "",         "PS", ""
    "VS-GS-PS",       "VsGs",    "",        "",         "VsGs",     "PS", ""
    "VS-HS-DS-PS",    "PreTess", "PreTess", "PostTess", "PostTess", "PS", ""
    "VS-HS-DS-GS-PS", "PreTess", "PreTess", "PostTess", "PostTess", "PS", ""
    "CS",             "",        "",        "",         "",         "",   "CS"

A Note About Third-Party Applications
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Several third-party applications (such as RenderDoc and Microsoft PIX)
integrate GPUPerfAPI as part of their profiling feature set. These applications
may choose to expose only a subset of the counters supported by GPUPerfAPI,
especially in cases where the counters do not support the design goals of the
application. Specifically, it is known that the counters reporting a percentage
are not exposed. This is due to the way that these tools collect and report
aggregate performance counter values for groups of draw calls. For instance, if
a set of draw calls is grouped together by a User Marker, a tool may report
performance counter values for the User Marker by simply summing up the counter
values for the individual draw calls. While this may be valid for many counters,
it does not work well for percentage-based counters. Even if the tools were to
perform a simple average of the percent values, it still may not provide an
accurate reflection of the actual performance. For most of the percentage-based
counters, GPUPerfAPI also exposes counters representing the components used to
calculate the percentage. One example of this is the cache hit counters -- these
are exposed both as a cache hit percentage and as individual counters
representing the number of cache requests, the number of hits and the number of
misses. Please reference the Usage column of the tables below to know which
counters will not be exposed by these applications.

Counters Exposed for Graphics Performance Analysis
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

The following tables show the set of counters exposed for analysis of GPU
Graphics workloads, as well the family of GPUs and APUs on which each counter
is available:

.. include:: graphics_counter_tables_gfx103.rst
.. include:: graphics_counter_tables_gfx10.rst
.. include:: graphics_counter_tables_gfx9.rst
.. include:: graphics_counter_tables_gfx8.rst

Counters Exposed for Compute Performance Analysis
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

The following tables show the set of counters exposed for analysis of GPU
Compute workloads, as well the family of GPUs and APUs on which each counter
is available:

.. include:: compute_counter_tables_gfx103.rst
.. include:: compute_counter_tables_gfx10.rst
.. include:: compute_counter_tables_gfx9.rst
.. include:: compute_counter_tables_gfx8.rst

