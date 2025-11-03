GpaGetStatusAsStr
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    const char* GpaGetStatusAsStr(
        GpaStatus status);

Description
%%%%%%%%%%%

Gets a string representation of the specified GPA status value. Provides a
simple method to convert a GpaStatus value into a string which can be used to
display log messages. When an error is returned from a GPA function, GPA will
also output more information about the error to a logging function if one has
been registered using GpaRegisterLoggingCallback.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``status``", "The status whose string representation is needed."

Return value
%%%%%%%%%%%%

A string which briefly describes the specified status. If the specified status
is unknown, this function will return either "Unknown Status" or "Unknown Error".
