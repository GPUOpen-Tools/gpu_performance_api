.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetCounterIndex
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterIndex(
        GpaContextId context_id,
        const char* counter_name,
        GpaUInt32* index);

Description
%%%%%%%%%%%

Gets index of a counter given its name (case insensitive).

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``counter_name``", "The name of the counter whose index is needed."
    "``index``", "The address which will hold the index upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter index was successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``counter_name`` parameter is NULL.
    | The supplied ``index`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorCounterNotFound", "The specified counter could not be found."
    "kGpaStatusErrorException", "Exception occurred."
