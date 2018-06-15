.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
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
    | 32-bit Windows: GPUPerfAPICL.dll
    | 64-bit Linux: libGPUPerfAPICL.so
    | 32-bit Linux: libGPUPerfAPICL32.so"
    "ROCm/HSA", "| 64-bit Linux: libGPUPerfAPIHSA.so"

To use the GPUPerfAPI library:

* Include the header file GPUPerfAPI.h. For Vulkan, include GPUPerfAPI-VK.h.
* Declare a variable of type GPA_GetFuncTablePtrType
* Load the GPUPerfAPI library

  * On Windows, use ``LoadLibrary`` on the GPUPerfAPI DLL for your chosen API (see
    above table)
  * On Linux, use ``dlopen`` on the GPUPerfAPI shared library for your chosen API
    (see above table)

* Get the address of the ``GPA_GetFuncTable`` function

  * On Windows, use ``GetProcAddres``
  * On Linux, use ``dlsym``

* Call GPA_GetFuncTable to get a table of function pointers for each API.

All of the above can be simplified using the GPAInterfaceLoader.h C++ header
file. This header file simplifies the loading and initialization of the GPA
entrypoints. The following code shows how to use this header file to load and
initialize the DirectX 12 version of GPA:

.. _gpa_load_and_init_sample:

.. code-block:: c++

    #include "GPAInterfaceLoader.h"

    GPAApiManager* GPAApiManager::m_pGpaApiManager = nullptr;

    GPAFunctionTable* pGpaFunctionTable = nullptr;

    bool InitializeGPA()
    {
        bool retVal = false;

        if (GPA_STATUS_OK == GPAApiManager::Instance()->LoadApi(GPA_API_DIRECTX_12))
        {
            pGpaFunctionTable = GPAApiManager::Instance()->GetFunctionTable(GPA_API_DIRECTX_12);

            if (nullptr != pGpaFunctionTable)
            {
                retVal = GPA_STATUS_OK == pGpaFunctionTable->GPA_Initialize(GPA_INITIALIZE_DEFAULT_BIT);
            }
        }

        return retVal;
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

    void MyLoggingFunction(GPA_Logging_Type messageType, const char* message)

The function is registered using the GPA_RegisterLoggingCallback entrypoint.

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
a queue is created. For HSA/ROCm, this function must be called before the
first call to ``hsa_init``. Once you are done using GPUPerfAPI, you should
destroy the GPUPerfAPI instance. In the case of DirectX 12, destruction
must be done before the device is destroyed.

The following methods can be used to initialize and destroy GPUPerfAPI:

.. csv-table::
    :header: "GPA Initialization/Destruction Method", "Brief Description"
    :widths: 45, 55

    "GPA_Initialize", "Initializes the driver so that counters are exposed."
    "GPA_Destroy", "Undoes any initialization to ensure proper behavior in applications that are not being profiled."

An example of the code used to initialize a GPUPerfAPI instance can be seen
above in :ref:`the GPAInterfaceLoader sample code <gpa_load_and_init_sample>`

Opening and Closing a Context
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

After initializing a GPUPerfAPI instance and after the necessary API-specific
construct has been created, a context can be opened using the GPA_OpenContext
function. Once a context is open, you can query the available performance
counters and create and begin a session. After you are done using GPUPerfAPI,
you should close the context.

The following methods can be used to open and close contexts:

.. csv-table::
    :header: "Context Handling Method", "Brief Description"
    :widths: 45, 55

    "GPA_OpenContext", "Opens the counters in the specified context for reading."
    "GPA_CloseContext", "Closes the counters in the specified context."

When calling GPA_OpenContext, the type of the supplied ``pContext`` is
different depending on which API is being used. See the table below for the
required type which should be passed to GPA_OpenContext:

.. csv-table::
    :header: "API", "GPA_OpenContext ``pContext`` Parameter Type"
    :widths: 45, 55

    "Vulkan", "| ``GPA_vkContextOpenInfo*``
    | (defined in GPUPerfAPI-Vk.h)"
    "DirectX 12", "| ``ID3D12Device*``"
    "DirectX 11", "| ``ID3D11Device*``"
    "OpenGL", "| Windows: ``HGLRC``
    | Linux: ``GLXContext``"
    "OpenCL", "| ``cl_command_queue*``"
    "ROCm/HSA", "| ``hsa_queue_t*``"

Querying a Context and Counters
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

After creating a context, you can use the returned GPA_ContextId to query
information about the context and the performance counters exposed by the
context.

The following methods can be used to query information about the context:

.. csv-table::
    :header: "Context Query Method", "Brief Description"
    :widths: 45, 55

    "GPA_GetSupportedSampleTypes", "Gets a mask of the sample types supported by the specified context."
    "GPA_GetDeviceAndRevisionId", "Gets the GPU device and revision id associated with the specified context."
    "GPA_GetDeviceName", "Gets the device name of the GPU associated with the specified context."

The following methods can be used to query information about performance counters:

.. csv-table::
    :header: "Counter Query Method", "Brief Description"
    :widths: 45, 55

    "GPA_GetNumCounters", "Gets the number of counters available."
    "GPA_GetCounterName", "Gets the name of the specified counter."
    "GPA_GetCounterIndex", "Gets index of a counter given its name (case insensitive)."
    "GPA_GetCounterGroup", "Gets the group of the specified counter."
    "GPA_GetCounterDescription", "Gets the description of the specified counter."
    "GPA_GetCounterDataType", "Gets the data type of the specified counter."
    "GPA_GetCounterUsageType", "Gets the usage type of the specified counter."
    "GPA_GetCounterUuid", "Gets the UUID of the specified counter."
    "GPA_GetCounterSampleType", "Gets the supported sample type of the specified counter."
    "GPA_GetDataTypeAsStr", "Gets a string with the name of the specified counter data type."
    "GPA_GetUsageTypeAsStr", "Gets a string with the name of the specified counter usage type."

Creating and Using a Session
@@@@@@@@@@@@@@@@@@@@@@@@@@@@

After creating a context, a session can be created. A session is the
container for enabling counters, sampling GPU workloads and storing results.

The following methods can be used to manage sessions:

.. csv-table::
    :header: "Session Handling Method", "Brief Description"
    :widths: 45, 55

    "GPA_CreateSession", "Creates a session."
    "GPA_DeleteSession", "Deletes a session object."
    "GPA_BeginSession", "Begins sampling with the currently enabled set of counters."
    "GPA_EndSession", "Ends sampling with the currently enabled set of counters."

Enabling Counters on a Session
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

After creating a session but before sampling on that session, counters should
be enabled. This must be done after GPA_CreateSession is called, but before
GPA_BeginSession is called.

The following methods can be used to enable/disable counters on a session:

.. csv-table::
    :header: "Counter Enable/Disable Method", "Brief Description"
    :widths: 45, 55

    "GPA_EnableCounter", "Enables a specified counter."
    "GPA_DisableCounter", "Disables a specified counter."
    "GPA_EnableCounterByName", "Enables a specified counter using the counter name (case insensitive)."
    "GPA_DisableCounterByName", "Disables a specified counter using the counter name (case insensitive)."
    "GPA_EnableAllCounters", "Enables all counters."
    "GPA_DisableAllCounters", "Disables all counters."

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

    "GPA_GetPassCount", "Gets the number of passes required for the currently enabled set of counters."
    "GPA_GetNumEnabledCounters", "Gets the number of enabled counters."
    "GPA_GetEnabledIndex", "Gets the counter index for an enabled counter."
    "GPA_IsCounterEnabled", "Checks whether or not a counter is enabled."

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

    "GPA_BeginCommandList", "Begins command list for sampling."
    "GPA_EndCommandList", "Ends command list for sampling."
    "GPA_BeginSample", "Begins a sample in a command list."
    "GPA_EndSample", "Ends a sample in a command list."
    "GPA_ContinueSampleOnCommandList", "Continues a primary command list sample on another primary command list."
    "GPA_CopySecondarySamples", "Copies a set of samples from a secondary command list back to the primary command list that executed the secondary command list."
    "GPA_GetSampleCount", "Returns the number of samples created for the specified session."

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

    "GPA_IsPassComplete", "Checks whether or not a pass has finished."
    "GPA_IsSessionComplete", "Checks if results for all samples within a session are available."
    "GPA_GetSampleResultSize", "Gets the result size for a given sample."
    "GPA_GetSampleResult", "Gets the result data for a given sample."

Displaying Status/Error
@@@@@@@@@@@@@@@@@@@@@@@

All GPUPerfAPI functions return a GPA_Status code to indicate success or
failure. A simple string representation of the status or error codes can be
retrieved using the following method:

.. csv-table::
    :header: "Status/Error Helper Method", "Brief Description"
    :widths: 45, 55

    "GPA_GetStatusAsStr", "Gets a string representation of a GPA_Status value."

Multi-pass Counter Collection
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Collection of some individual counters and some combinations of counters will
require more than one pass. After enabling counters, you can query the number
of passes required. If the number of passes is greater than one, you will need
to execute an identical GPU workload once for each pass. For DirectX 12 and
Vulkan, this typically means recording the same command list or command buffer
more than once, calling GPA_BeginCommandList on each command list for each
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
initialization. GPUPerfAPI simplifies this by defining two macros in the
GPUPerfAPI-Vk.h header file: ``AMD_GPA_REQUIRED_INSTANCE_EXTENSION_NAME_LIST``
for the required instance extensions and
``AMD_GPA_REQUIRED_DEVICE_EXTENSION_NAME_LIST`` for the required device
extensions. The extensions defined in
``AMD_GPA_REQUIRED_INSTANCE_EXTENSION_NAME_LIST`` should be included in the
``VkInstanceCreateInfo`` structure that is passed to the ``vkCreateInstance``
function. Similarly, the extensions defined in
``AMD_GPA_REQUIRED_DEVICE_EXTENSION_NAME_LIST`` should be included in the
``VkDeviceCreateInfo`` structure that is passed to ``vkCreateDevice`` function.

.. _specific_usage_bundles:

Specific Usage Note for Bundles (DirectX 12) and Secondary Command Buffers (Vulkan)
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

While samples within a Bundle or Secondary Command Buffer (both referred to
here as "secondary command lists") are supported by GPUPerfAPI, they require
special handling. Both the primary and secondary command list must be started
using GPA_BeginCommandList. Samples can be created on both types of command
lists; however, the samples on the secondary command list must be copied back
to the primary command list. This is done using the GPA_CopySecondarySamples
function. Once samples are copied back to the primary command list, results
will be available after the primary command list has been executed. Bundles or
secondary command buffers must be re-recorded for each counter pass. This also
means that extra GPA_CommandListId instances must be created (one per pass for
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
where the sample ends must be started using GPA_BeginCommandList. After the
sample has been started on the first command list using GPA_BeginSample, it can
be continued on another command list by calling
GPA_ContinueSampleOnCommandList. After it has been continued, the sample can be
ended using GPA_EndSample and specifying the second command list.

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
