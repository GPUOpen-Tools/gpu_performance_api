.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaCloseContext
@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaCloseContext(
        GpaContextId context_id);

Description
%%%%%%%%%%%

Closes the specified context, which ends access to GPU performance counters.
After closing a context, GPA functions should not be called again until the
counters are reopened with GpaOpenContext.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The context was successfully closed."
    "kGpaStatusErrorNullPointer", "The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorInvalidParameter", "The API type of the supplied context does not match GPA's API type."
    "kGpaStatusErrorFailed", "The context could not be closed."
    "kGpaStatusErrorException", "Exception occurred."
