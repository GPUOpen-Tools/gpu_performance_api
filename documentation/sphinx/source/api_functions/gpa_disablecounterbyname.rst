GpaDisableCounterByName
@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaDisableCounterByName(
        GpsSessionId session_id,
        const char* counter_name);

Description
%%%%%%%%%%%

Disables the counter with the specified counter name (case insensitive).
Subsequent sampling sessions will not provide values for any disabled counters.
Initially all counters are disabled, and must explicitly be enabled.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``","Unique identifier of a previously-created session."
    "``counter_name``", "The name of the counter to disable."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The specified counter was successfully disabled."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorCannotChangeCountersWhenSampling", "The set of enabled counters cannot be changed after GpaBeginSession is called."
    "kGpaStatusErrorContextNotOpen", "The supplied session's parent context is not currently open."
    "kGpaStatusErrorNotEnabled", "The specified counter is not currently enabled."
    "kGpaStatusErrorCounterNotFound", "The specified counter name is not valid."
    "kGpaStatusErrorFailed", "An error occurred while trying to disable the counter."
    "kGpaStatusErrorException", "Exception occurred."
