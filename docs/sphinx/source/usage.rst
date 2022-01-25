.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
.. GPU Performance API Usage

.. highlight:: c++

Usage
-----

This page provides an overview of the GPUPerfAPI library. Please refer to
:ref:`the API Reference Page <gpa_api_reference>` for more information.

Loading the GPUPerfAPI Library
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

GPUPerfAPI binary releases include separate library files for each
supported API. The following table shows the name of the library files
for each API

.. csv-table::
    :header: "API", "Library Names"
    :widths: 45, 55

    "Vulkan", "| 64-bit Windows: GPUPerfAPIVK-x64.dll
    | 32-bit Windows: GPUPerfAPIVK.dll
    | 64-bit Linux: libGPUPerfAPIVK.so
    | 32-bit Linux: libGPUPerfAPIVK32.so"
    "DirectX 12", "| 64-bit Windows: GPUPerfAPIDX12-x64.dll
    | 32-bit Windows: GPUPerfAPIDX12.dll"
    "DirectX 11", "| 64-bit Windows: GPUPerfAPIDX11-x64.dll
    | 32-bit Windows: GPUPerfAPIDX11.dll"
    "OpenGL", "| 64-bit Windows: GPUPerfAPIGL-x64.dll
    | 32-bit Windows: GPUPerfAPIGL.dll
    | 64-bit Linux: libGPUPerfAPIGL.so
    | 32-bit Linux: libGPUPerfAPIGL32.so"
    "OpenCL", "| 64-bit Windows: GPUPerfAPICL-x64.dll
    | 32-bit Windows: GPUPerfAPICL.dll"

To use the GPUPerfAPI library:

* Include the header file gpu_performance_api/gpu_perf_api.h. For Vulkan, include gpu_performance_api/gpu_perf_api_vk.h.
* Declare a variable of type GpaGetFuncTablePtrType
* Load the GPUPerfAPI library

  * On Windows, use ``LoadLibrary`` on the GPUPerfAPI DLL for your chosen API (see
    above table)
  * On Linux, use ``dlopen`` on the GPUPerfAPI shared library for your chosen API
    (see above table)

* Get the address of the ``GpaGetFuncTable`` function

  * On Windows, use ``GetProcAddres``
  * On Linux, use ``dlsym``

* Call GpaGetFuncTable to get a table of function pointers for each API.

All of the above can be simplified using the gpu_perf_api_interface_loader.h C++ header
file. This header file simplifies the loading and initialization of the GPA
entrypoints. The following code shows how to use this header file to load and
initialize the DirectX 12 version of GPA:

.. _gpa_load_and_init_sample:

.. code-block:: c++

    #include "gpu_performance_api/gpu_perf_api_interface_loader.h"

    #ifdef __cplusplus
    GpaApiManager* GpaApiManager::gpa_api_manager_ = nullptr;
    #endif
    GpaFuncTableInfo* gpa_function_table_info = nullptr;
    GpaFunctionTable* gpa_function_table      = nullptr;

    bool InitializeGpa()
    {
        bool ret_val = false;

        if (kGpaStatusOk == GpaApiManager::Instance()->LoadApi(kGpaApiDirectx12))
        {
            gpa_function_table = GpaApiManager::Instance()->GetFunctionTable(kGpaApiDirectx12);

            if (nullptr != gpa_function_table)
            {
                ret_val = kGpaStatusOk == gpa_function_table->GpaInitialize(kGpaInitializeDefaultBit);
            }
        }

        return ret_val;
    }

Registering a Logging Callback
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

An entrypoint is available for registering a callback function which GPUPerfAPI
will use to report back additional information about errors and general API
usage. It is recommended that all GPUPerfAPI clients register a logging
callback for error messages at a minimum. Any time a GPUPerfAPI function
returns an error, it will output a log message with more information about the
condition that caused the error.

In order to use this feature, you must define a static function with the
following signature:

.. code-block:: c++

    void MyLoggingFunction(GpaLoggingType message_type, const char* message)

The function is registered using the GpaRegisterLoggingCallback entrypoint.

The function registered will receive callbacks for message types registered.
The message type is passed into the logging function so that different message
types can be handled differently if desired. For instance, errors could be
output to ``stderr`` or be used to raise an assert, while messages and trace
information could be output to an application's or tool's normal log file. A
tool may also want to prefix log messages with a string representation of the
log type before writing the message. The messages passed into the logging
function will not have a newline at the end, allowing for more flexible
handling of the message.

Initializing and Destroying a GPUPerfAPI Instance
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

GPUPerfAPI must be initialized before the rendering context or device is
created, so that the driver can be prepared for accessing hardware data.
In the case of DirectX 12 or Vulkan, initialization must be done before
a queue is created. Once you are done using GPUPerfAPI, you should
destroy the GPUPerfAPI instance. In the case of DirectX 12, destruction
must be done before the device is destroyed.

The following methods can be used to initialize and destroy GPUPerfAPI:

.. csv-table::
    :header: "GPA Initialization/Destruction Method", "Brief Description"
    :widths: 45, 55

    "GpaInitialize", "Initializes the driver so that counters are exposed."
    "GpaDestroy", "Undoes any initialization to ensure proper behavior in applications that are not being profiled."

An example of the code used to initialize a GPUPerfAPI instance can be seen
above in :ref:`the GpaInterfaceLoader sample code <gpa_load_and_init_sample>`

Opening and Closing a Context
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

After initializing a GPUPerfAPI instance and after the necessary API-specific
construct has been created, a context can be opened using the GpaOpenContext
function. Once a context is open, you can query the available performance
counters and create and begin a session. After you are done using GPUPerfAPI,
you should close the context.

The following methods can be used to open and close contexts:

.. csv-table::
    :header: "Context Handling Method", "Brief Description"
    :widths: 45, 55

    "GpaOpenContext", "Opens the counters in the specified context for reading."
    "GpaCloseContext", "Closes the counters in the specified context."

When calling GpaOpenContext, the type of the supplied ``context`` is
different depending on which API is being used. See the table below for the
required type which should be passed to GpaOpenContext:

.. csv-table::
    :header: "API", "GpaOpenContext ``context`` Parameter Type"
    :widths: 45, 55

    "Vulkan", "| ``GpaVkContextOpenInfo*``
    | (defined in gpu_perf_api_vk.h)"
    "DirectX 12", "| ``ID3D12Device*``"
    "DirectX 11", "| ``ID3D11Device*``"
    "OpenGL", "| Windows: ``HGLRC``
    | Linux: ``GLXContext``"
    "OpenCL", "| ``cl_command_queue*``"

Querying a Context and Counters
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

After creating a context, you can use the returned GpaContextId to query
information about the context and the performance counters exposed by the
context.

The following methods can be used to query information about the context:

.. csv-table::
    :header: "Context Query Method", "Brief Description"
    :widths: 45, 55

    "GpaGetSupportedSampleTypes", "Gets a mask of the sample types supported by the specified context."
    "GpaGetDeviceAndRevisionId", "Gets the GPU device and revision id associated with the specified context."
    "GpaGetDeviceName", "Gets the device name of the GPU associated with the specified context."
    "GpaGetDeviceGeneration", "Gets the device generation of the GPU associated with the specified context."

The following methods can be used to query information about performance counters:

.. csv-table::
    :header: "Counter Query Method", "Brief Description"
    :widths: 45, 55

    "GpaGetNumCounters", "Gets the number of counters available."
    "GpaGetCounterName", "Gets the name of the specified counter."
    "GpaGetCounterIndex", "Gets index of a counter given its name (case insensitive)."
    "GpaGetCounterGroup", "Gets the group of the specified counter."
    "GpaGetCounterDescription", "Gets the description of the specified counter."
    "GpaGetCounterDataType", "Gets the data type of the specified counter."
    "GpaGetCounterUsageType", "Gets the usage type of the specified counter."
    "GpaGetCounterUuid", "Gets the UUID of the specified counter."
    "GpaGetCounterSampleType", "Gets the supported sample type of the specified counter."
    "GpaGetDataTypeAsStr", "Gets a string with the name of the specified counter data type."
    "GpaGetUsageTypeAsStr", "Gets a string with the name of the specified counter usage type."

Creating and Using a Session
@@@@@@@@@@@@@@@@@@@@@@@@@@@@

After creating a context, a session can be created. A session is the
container for enabling counters, sampling GPU workloads and storing results.

The following methods can be used to manage sessions:

.. csv-table::
    :header: "Session Handling Method", "Brief Description"
    :widths: 45, 55

    "GpaCreateSession", "Creates a session."
    "GpaDeleteSession", "Deletes a session object."
    "GpaBeginSession", "Begins sampling with the currently enabled set of counters."
    "GpaEndSession", "Ends sampling with the currently enabled set of counters."

Enabling Counters on a Session
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

After creating a session but before sampling on that session, counters should
be enabled. This must be done after GpaCreateSession is called, but before
GpaBeginSession is called.

The following methods can be used to enable/disable counters on a session:

.. csv-table::
    :header: "Counter Enable/Disable Method", "Brief Description"
    :widths: 45, 55

    "GpaEnableCounter", "Enables a specified counter."
    "GpaDisableCounter", "Disables a specified counter."
    "GpaEnableCounterByName", "Enables a specified counter using the counter name (case insensitive)."
    "GpaDisableCounterByName", "Disables a specified counter using the counter name (case insensitive)."
    "GpaEnableAllCounters", "Enables all counters."
    "GpaDisableAllCounters", "Disables all counters."

Querying Enabled Counters and Counter Scheduling
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

A session can be also queried for information about which counters are enabled
as well as information on the number of passes required for the current set of
enabled counters.

The following methods can be used to query enabled counters and counter
scheduling on a session:

.. csv-table::
    :header: "Counter Scheduling Query Method", "Brief Description"
    :widths: 45, 55

    "GpaGetPassCount", "Gets the number of passes required for the currently enabled set of counters."
    "GpaGetNumEnabledCounters", "Gets the number of enabled counters."
    "GpaGetEnabledIndex", "Gets the counter index for an enabled counter."
    "GpaIsCounterEnabled", "Checks whether or not a counter is enabled."

Creating and Managing Samples
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

After counters are enabled on a session and the session has been started, GPA
command lists and samples can be created. A sample is the GPU workload for
which performance counters are to be collected. All enabled counters will be
collected for each sample. For DirectX 12 and Vulkan, :ref:`samples can start
on one command list and end on another<specific_usage_multiple_command_lists>`.
There is also :ref:`special handling <specific_usage_bundles>` needed for
DirectX 12 bundles and Vulkan secondary command buffers.

The following methods can be used to create and manage samples on a session:

.. csv-table::
    :header: "Sample Handling Method", "Brief Description"
    :widths: 45, 55

    "GpaBeginCommandList", "Begins command list for sampling."
    "GpaEndCommandList", "Ends command list for sampling."
    "GpaBeginSample", "Begins a sample in a command list."
    "GpaEndSample", "Ends a sample in a command list."
    "GpaContinueSampleOnCommandList", "Continues a primary command list sample on another primary command list."
    "GpaCopySecondarySamples", "Copies a set of samples from a secondary command list back to the primary command list that executed the secondary command list."
    "GpaGetSampleCount", "Returns the number of samples created for the specified session."

Querying Results
@@@@@@@@@@@@@@@@

Once sampling is complete and the session has been ended, the sample results
can be read. For DirectX 12 and Vulkan, the command list or command buffer
which contains the samples must have been fully executed before results will be
available.

The following methods can be used to check if results are available and to read
the results for samples:

.. csv-table::
    :header: "Results Querying Method", "Brief Description"
    :widths: 45, 55

    "GpaIsPassComplete", "Checks whether or not a pass has finished."
    "GpaIsSessionComplete", "Checks if results for all samples within a session are available."
    "GpaGetSampleResultSize", "Gets the result size for a given sample."
    "GpaGetSampleResult", "Gets the result data for a given sample."

Displaying Status/Error
@@@@@@@@@@@@@@@@@@@@@@@

All GPUPerfAPI functions return a GpaStatus code to indicate success or
failure. A simple string representation of the status or error codes can be
retrieved using the following method:

.. csv-table::
    :header: "Status/Error Helper Method", "Brief Description"
    :widths: 45, 55

    "GpaGetStatusAsStr", "Gets a string representation of a GpaStatus value."

Multi-pass Counter Collection
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Collection of some individual counters and some combinations of counters will
require more than one pass. After enabling counters, you can query the number
of passes required. If the number of passes is greater than one, you will need
to execute an identical GPU workload once for each pass. For DirectX 12 and
Vulkan, this typically means recording the same command list or command buffer
more than once, calling GpaBeginCommandList on each command list for each
pass, and beginning and ending samples for the same workloads within the
command lists. For other graphics and compute APIs, this means making the same
draw calls or dispatching the same kernels in the same sequence multiple times.
The same sample id must be found in every pass, and that sample id must be used
for the same workload within each pass. If it is impossible or impractical to
repeat the operations to be profiled, select a counter set requiring only a
single pass. For sets requiring more than one pass, results are available only
after all passes are complete.

Specific Usage Note for Vulkan
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

In order to enable counter collection in the Vulkan driver, several Vulkan
extensions are required. The application being profiled with GPUPerfAPI will
need to request those extensions as part of the Vulkan instance and device
initialization. GPUPerfAPI simplifies this by defining three macros in the
gpu_performance_api/gpu_perf_api_vk.h header file: ``AMD_GPA_REQUIRED_INSTANCE_EXTENSION_NAME_LIST``
for the required instance extensions,
``AMD_GPA_REQUIRED_DEVICE_EXTENSION_NAME_LIST`` for the required device
extensions and ``AMD_GPA_OPTIONAL_DEVICE_EXTENSION_NAME_LIST`` for optional,
but recommended, device extensions. The extensions defined in
``AMD_GPA_REQUIRED_INSTANCE_EXTENSION_NAME_LIST`` should be included in the
``VkInstanceCreateInfo`` structure that is passed to the ``vkCreateInstance``
function. Similarly, the extensions defined in
``AMD_GPA_REQUIRED_DEVICE_EXTENSION_NAME_LIST`` and
``AMD_GPA_OPTIONAL_DEVICE_EXTENSION_NAME_LIST`` should be included in the
``VkDeviceCreateInfo`` structure that is passed to ``VkCreateDevice`` function.

.. _specific_usage_bundles:

Specific Usage Note for Bundles (DirectX 12) and Secondary Command Buffers (Vulkan)
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

While samples within a Bundle or Secondary Command Buffer (both referred to
here as "secondary command lists") are supported by GPUPerfAPI, they require
special handling. Both the primary and secondary command list must be started
using GpaBeginCommandList. Samples can be created on both types of command
lists; however, the samples on the secondary command list must be copied back
to the primary command list. This is done using the GpaCopySecondarySamples
function. Once samples are copied back to the primary command list, results
will be available after the primary command list has been executed. Bundles or
secondary command buffers must be re-recorded for each counter pass. This also
means that extra GpaCommandListId instances must be created (one per pass for
each bundle or secondary command buffer) in order to support copying the
results from the bundles or secondary command buffers after execution.

.. _specific_usage_multiple_command_lists:

Specific Usage Note for Samples that Start and End on Different Command Lists
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

For DirectX 12 and Vulkan, GPUPerfAPI supports starting a sample on one command
list and ending it on another. For this to work properly, the command lists
must be executed in the correct order by the application -- the command list
which ends the sample must be executed after the command list which begins the
sample. Both the command list where the sample starts and the command list
where the sample ends must be started using GpaBeginCommandList. After the
sample has been started on the first command list using GpaBeginSample, it can
be continued on another command list by calling
GpaContinueSampleOnCommandList. After it has been continued, the sample can be
ended using GpaEndSample and specifying the second command list.

Deploying GPUPerfAPI
@@@@@@@@@@@@@@@@@@@@

To deploy an application that uses GPUPerfAPI, simply make sure that the
necessary GPUPerfAPI library is available and can be loaded using the normal
library search mechanism for the host operating system (i.e. in the PATH on
Windows and LD_LIBRARY_PATH on Linux).

When deploying the DirectX 11 version on Windows, you will also need to deploy
GPUPerfAPIDXGetAMDDeviceInfo.dll or GPUPerfAPIDXGetAMDDeviceInfo-x64.dll, if you
need to support systems with multiple AMD GPUs.  This library is used by GPA to
determine which GPU is being used for rendering at runtime.  For single-GPU
systems, this library is not required.
