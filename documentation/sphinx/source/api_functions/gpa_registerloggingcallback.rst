GpaRegisterLoggingCallback
@@@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaRegisterLoggingCallback(
        GpaLoggingType logging_type,
        GpaLoggingCallbackPtrType callback_func_ptr);

Description
%%%%%%%%%%%

Registers a callback function to receive log messages. Only one callback
function can be registered, so the implementation should be able to handle the
different types of messages. A parameter to the callback function will indicate
the message type being received. Messages will not contain a newline character
at the end of the message. To unregister a callback function, specify
kGpaLoggingNone for the ``logging_type`` and NULL for the ``callback_func_ptr``.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``logging_type``", "Identifies the type of messages to receive callbacks for."
    "``callback_func_ptr``", "Pointer to the callback function."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The logging callback function was successfully registered."
    "kGpaStatusErrorNullPointer", "The supplied ``callback_func_ptr`` parameter is NULL and the specified ``logging_type`` is not kGpaLoggingNone."
    "kGpaStatusErrorException", "Exception occurred."
