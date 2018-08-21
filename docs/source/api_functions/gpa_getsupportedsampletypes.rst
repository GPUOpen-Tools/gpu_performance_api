.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetSupportedSampleTypes
@@@@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetSupportedSampleTypes(
        GPA_ContextId contextId,
        GPA_ContextSampleTypeFlags* pSampleTypes);

Description
%%%%%%%%%%%

Gets a mask of the sample types supported by the specified context. A call to
GPA_CreateSession will fail if the requested sample types are not compatible
with the context's sample types.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``contextId``", "Unique identifier of a previously-opened context."
    "``pSampleTypes``", "The value that will be set to the the mask of the supported sample types upon successful execution. This will be a combination of GPA_Sample_Bits."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The supported sample types were successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``pSampleTypes`` parameter is NULL.
    | The supplied ``contextId`` parameter is NULL."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied context is not currently open."
    "GPA_STATUS_ERROR_CONTEXT_NOT_FOUND", "The supplied ``contextId`` parameter was not recognized as a previously-opened context identifier."
    "GPA_STATUS_ERROR_FAILED", "The supported sample types could not be retrieved."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
