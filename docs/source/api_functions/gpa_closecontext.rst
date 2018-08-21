.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_CloseContext
@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_CloseContext(
        GPA_ContextId contextId);

Description
%%%%%%%%%%%

Closes the specified context, which ends access to GPU performance counters.
After closing a context, GPA functions should not be called again until the
counters are reopened with GPA_OpenContext.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``contextId``", "Unique identifier of a previously-opened context."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The context was successfully closed."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``contextId`` parameter is NULL."
    "GPA_STATUS_ERROR_CONTEXT_NOT_FOUND", "The supplied ``contextId`` parameter was not recognized as a previously-opened context identifier."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied context is not currently open."
    "GPA_STATUS_ERROR_INVALID_PARAMETER", "The API type of the supplied context does not match GPA's API type."
    "GPA_STATUS_ERROR_FAILED", "The context could not be closed."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
