GpaOpenContext
@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaOpenContext(
        void* context,
        GpaOpenContextFlags flags,
        GpaContextId* context_id);

Description
%%%%%%%%%%%

Opens the specified context, which provides access to GPU performance counters.
This function must be called after GpaInitialize and before any other GPUPerfAPI
functions.

The type of the supplied ``context`` is different depending on which API is
being used. See the table below for the required type which should be passed to
GpaOpenContext:

.. csv-table::
    :header: "API", "GpaOpenContext ``context`` Parameter Type"
    :widths: 45, 55

    "Vulkan", "| ``GpaVkContextOpenInfo*``
    | (defined in gpu_perf_api_vk.h)"
    "DirectX 12", "| ``ID3D12Device*``"
    "DirectX 11", "| ``ID3D11Device*``"
    "OpenGL", "| Windows: ``HGLRC``
    | Linux: ``GLXContext``"

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context``", "The context to open counters for. The specific type for this parameter depends on which API GPUPerfAPI is being used with. Refer to the table above for the specific type to be used."
    "``flags``", "Flags used to initialize the context. This should be a combination of GpaOpenContext."
    "``context_id``", "On successful execution of this function, this parameter will be set to a GPA-generated unique context identifier. This value can subsequently passed to any GPA function taking a GpaContextId as an input parameter."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The context was successfully opened."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "The supplied ``pContext`` parameter is NULL."
    "kGpaStatusErrorInvalidParameter", "The ``flags`` parameter has an invalid value."
    "kGpaStatusErrorHardwareNotSupported", "The current GPU hardware is not supported."
    "kGpaStatusErrorDriverNotSupported", "The currently-installed GPU driver is not supported."
    "kGpaStatusErrorContextAlreadyOpen", "The supplied context has already been opened."
    "kGpaStatusErrorFailed", "The context could not be opened."
    "kGpaStatusErrorException", "Exception occurred."

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
GpaOpenContext, you can alter the GPU clock frequencies used while profiling.
The table below explains the stable clock modes that can be specified via the
``flags`` parameter.

.. csv-table::
    :header: "Clock mode", "Description"
    :widths: 35, 65

    "| ``kGpaOpenContextDefaultBit``
    | (or any combination of GpaOpenContextBits which doesn't include any of the ``kGpaOpenContextClockMode*`` bits)", "Clocks are set to stable frequencies which are known to be power and thermal sustainable. The ratio between the engine and memory clock frequencies will be kept the same as much as possible."
    "``kGpaOpenContextClockModeNoneBit``", "Clock frequencies are not altered and may vary widely during profiling based on GPU usage and other factors."
    "``kGpaOpenContextClockModePeakBit``", "Clocks are set to peak frequencies. In most cases this is safe to do for short periods of time while profiling. However, the GPU clock frequencies could still be reduced from peak level under power and thermal constraints."
    "``kGpaOpenContextClockModeMinMemoryBit``", "The memory clock frequency is set to the minimum level, whiles the engine clock is set to a power and thermal sustainable level."
    "``kGpaOpenContextClockModeMinEngineBit``", "The engine clock frequency is set to the minimum level, whiles the memory clock is set to a power and thermal sustainable level."

A Note about Raw Hardware Counters
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

By default, GPA exposes a set of derived counters that are computed from one or
more raw hardware counters. GPA can also be configured to expose the raw
hardware counters directly. In order to do this, the ``flags`` parameter
specified when calling GpaOpenContext should include the
``kGpaOpenContextEnableHardwareCountersBit`` bit.