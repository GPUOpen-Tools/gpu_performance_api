.. Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.

GpaBeginCommandList
@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaBeginCommandList(
        GpaSessionId session_id,
        GpaUInt32 pass_index,
        void* command_list,
        GpaCommandListType command_list_type,
        GpaCommandListId* command_list_id)

Description
%%%%%%%%%%%

Begins a command list for sampling. You will be unable to create samples on a
command list or command buffer before GpaBeginCommandList is called. The
session must have been previously created and started before starting a command
list. For multi-pass counter collection, you must call this function for each
command list once per pass.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``","Unique identifier of a previously-created session."
    "``pass_index``", "The zero-based index of the pass."
    "``command_list``", "API-specific command list on which to begin sampling. For DirectX 12, this should be a ID3D12GraphicsCommandList. For Vulkan, this should be a vkCommandBuffer. For all other APIs, this should be kGpaCommandListNone."
    "``command_list_type``", "The type of the ``command_list`` parameter. For DirectX 12 and Vulkan, this should be either kGpaCommandListPrimary or kGpaCommandListSecondary. Secondary command lists are either bundles (DirectX 12) or secondary command buffer (Vulkan). For all other APIs, this should be kGpaCommandListNone."
    "``command_list_id``", "On successful execution of this function, this parameter will be set to a GPA-generated unique command list identifier. This value can subsequently passed to any GPA function taking a GpaCommandListId as an input parameter."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The command list was successfully started."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``session_id`` parameter is NULL.
    | The supplied ``command_list`` parameter is NULL and command_list_type is not kGpaCommandListNone.
    | The supplied ``command_list_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorInvalidParameter", "| The ``command_list_type`` parameter has an invalid value.
    | The supplied ``command_list`` parameter is not NULL and the ``command_list_type`` parameter is kGpaCommandListNone."
    "kGpaStatusErrorSessionNotStarted", "The supplied GPA Session object has not yet been started. Call GpaBeginSession before GpaBeginCommandList."
    "kGpaStatusErrorCommandListAlreadyStarted", "The supplied command list has already been started."
    "kGpaStatusErrorFailed", "The command list could not be started."
    "kGpaStatusErrorException", "Exception occurred."
