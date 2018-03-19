.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_RegisterLoggingCallback
@@@@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_RegisterLoggingCallback(
        GPA_Logging_Type loggingType,
        GPA_LoggingCallbackPtrType pCallbackFuncPtr);

Description
%%%%%%%%%%%

Registers a callback function to receive log messages. Only one callback
function can be registered, so the implementation should be able to handle the
different types of messages. A parameter to the callback function will indicate
the message type being received. Messages will not contain a newline character
at the end of the message. To unregister a callback function, specify
GPA_LOGGING_NONE for the ``loggingType`` and NULL for the ``pCallbackFuncPtr``.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``loggingType``", "Identifies the type of messages to receive callbacks for."
    "``pCallbackFuncPtr``", "Pointer to the callback function."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The logging callback function was successfully registered."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``pCallbackFuncPtr`` parameter is NULL and the specified ``loggingType`` is not GPA_LOGGING_NONE."
