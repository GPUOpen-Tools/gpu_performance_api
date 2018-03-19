.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_BeginCommandList
@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_BeginCommandList(
        GPA_SessionId sessionId,
        gpa_uint32 passIndex,
        void* pCommandList,
        GPA_Command_List_Type commandListType,
        GPA_CommandListId* pCommandListId)

Description
%%%%%%%%%%%

Begins a command list for sampling. You will be unable to create samples on a
command list or command buffer before GPA_BeginCommandList is called. The
session must have been previously created and started before starting a command
list. For multi-pass counter collection, you must call this function for each
command list once per pass.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``","Unique identifier of a previously-created session."
    "``passIndex``", "The zero-based index of the pass."
    "``pCommandList``", "API-specific command list on which to begin sampling. For DirectX 12, this should be a ID3D12GraphicsCommandList. For Vulkan, this should be a vkCommandBuffer. For all other APIs, this should be GPA_NULL_COMMAND_LIST."
    "``commandListType``", "The type of the ``pCommandList`` parameter. For DirectX 12 and Vulkan, this should be either GPA_COMMAND_LIST_PRIMARY or GPA_COMMAND_LIST_SECONDARY. Secondary command lists are either bundles (DirectX 12) or secondary command buffer (Vulkan). For all other APIs, this should be GPA_COMMAND_LIST_NONE."
    "``pCommandListId``", "On successful execution of this function, this parameter will be set to a GPA-generated unique command list identifier. This value can subsequently passed to any GPA function taking a GPA_CommandListId as an input parameter."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The command list was successfully started."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``sessionId`` parameter is NULL.
    | The supplied ``pCommandList`` parameter is NULL and commandListType is not GPA_COMMAND_LIST_NONE.
    | The supplied ``pCommandListId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_INVALID_PARAMETER", "| The ``commandListType`` parameter has an invalid value.
    | The supplied ``pCommandList`` parameter is not NULL and the ``commandListType`` parameter is GPA_COMMAND_LIST_NONE."
    "GPA_STATUS_ERROR_SESSION_NOT_STARTED", "The supplied GPA Session object has not yet been started. Call GPA_BeginSession before GPA_BeginCommandList."
    "GPA_STATUS_ERROR_COMMAND_LIST_ALREADY_STARTED", "The supplied command list has already been started."
    "GPA_STATUS_ERROR_FAILED", "The command list could not be started."
