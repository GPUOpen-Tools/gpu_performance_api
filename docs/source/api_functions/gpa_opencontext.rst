.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_OpenContext
@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_OpenContext(
        void* pContext,
        GPA_OpenContextFlags flags,
        GPA_ContextId* pContextId);

Description
%%%%%%%%%%%

Opens the specified context, which provides access to GPU performance counters.
This function must be called after GPA_Initialize and before any other GPUPerfAPI
functions.

The type of the supplied ``pContext`` is different depending on which API is
being used. See the table below for the required type which should be passed to
GPA_OpenContext:

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

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``pContext``", "The context to open counters for. The specific type for this parameter depends on which API GPUPerfAPI is being used with. Refer to the table above for the specific type to be used."
    "``flags``", "Flags used to initialize the context. This should be a combination of GPA_OpenContext_Bits."
    "``pContextId``", "On successful execution of this function, this parameter will be set to a GPA-generated unique context identifier. This value can subsequently passed to any GPA function taking a GPA_ContextId as an input parameter."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The context was successfully opened."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``pContext`` parameter is NULL."
    "GPA_STATUS_ERROR_INVALID_PARAMETER", "The ``flags`` parameter has an invalid value."
    "GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED", "The current GPU hardware is not supported."
    "GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED", "The currently-installed GPU driver is not supported."
    "GPA_STATUS_ERROR_CONTEXT_ALREADY_OPEN", "The supplied context has already been opened."
    "GPA_STATUS_ERROR_FAILED", "The context could not be opened."

A Note about GPU Clock Modes
&&&&&&&&&&&&&&&&&&&&&&&&&&&&

Due to the desire to operate within reasonable power envelopes, modern GPUs
employ techniques which alter the frequencies of their clocks dynamically.
This can make tuning for performance difficult, as there is no single clock
frequency which can be assumed. By default, GPA uses a clock mode known as
"Profiling Clocks". Under this mode, the clocks will be fixed at frequencies
which may be lower than the normal operating frequencies. This mode should help
to ensure consistent results between different runs of the application.
However, the observed performance of the application (especially using the
GPUTime counter) may be lower than expected or lower than the application can
achieve during normal operation. Using the ``flags`` parameter when calling
GPA_OpenContext, you can alter the GPU clock frequencies used while profiling.
The table below explains the stable clock modes that can be specified via the
``flags`` parameter. Currently only DirectX 12 and Vulkan support modifying
the GPU clock mode used while profiling.

.. csv-table::
    :header: "Clock mode", "Description"
    :widths: 35, 65

    "| ``GPA_OPENCONTEXT_DEFAULT_BIT``
    | (or any combination of GPA_OpenContext_Bits which doesn't include any of the ``GPA_OPENCONTEXT_CLOCK_MODE_`` bits)", "Clocks are set to stable frequencies which are known to be power and thermal sustainable. The ratio between the engine and memory clock frequencies will be kept the same as much as possible."
    "``GPA_OPENCONTEXT_CLOCK_MODE_NONE_BIT``", "Clock frequencies are not altered and may vary widely during profiling based on GPU usage and other factors."
    "``GPA_OPENCONTEXT_CLOCK_MODE_PEAK_BIT``", "Clocks are set to peak frequencies. In most cases this is safe to do for short periods of time while profiling. However, the GPU clock frequencies could still be reduced from peak level under power and thermal constraints."
    "``GPA_OPENCONTEXT_CLOCK_MODE_MIN_MEMORY_BIT``", "The memory clock frequency is set to the minimum level, whiles the engine clock is set to a power and thermal sustainable level."
    "``GPA_OPENCONTEXT_CLOCK_MODE_MIN_ENGINE_BIT``", "The engine clock frequency is set to the minimum level, whiles the memory clock is set to a power and thermal sustainable level."
