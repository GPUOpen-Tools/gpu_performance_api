Environment Variables
#####################

This page lists environment variables that have special meaning to GPA.

GPA_EXPOSE_HW_COUNTERS
======================

Allow an environment variable to force HW counters to be exposed.
This is to support third-party tools (like RenderDoc / PIX) where users can't conditionally
add the kGpaOpenContextEnableHardwareCountersBit.

**Usage**

Set the variable before loading or initializing GPA.

On Windows:

.. code-block:: batch

   set GPA_EXPOSE_HW_COUNTERS=1

On Linux:

.. code-block:: bash

   export GPA_EXPOSE_HW_COUNTERS=1

**Notes**

- This variable should be considered an advanced or diagnostic option.
- Counter availability can vary by API, GPU, driver, and GPA build.
- If the variable is not set, GPA uses its default counter exposure behavior.

GPA_OVERRIDE_LOG_LEVEL
======================

Overrides the logging level used by GPA when a logging callback is registered.

This environment variable is intended for advanced or diagnostic scenarios
where the effective GPA logging level needs to be changed without modifying
application code. If set, GPA parses the value as an integer and uses it
instead of the logging level requested by the application.

**Usage**

Set the variable before registering a logging callback with GPA.

GPA_OVERRIDE_LOG_LEVEL is currently parsed as base 10 only.

kGpaLoggingDebugAll = 65280 is a common value to enable all debug logging.
This value corresponds to the bitwise OR of all logging types in the GpaLoggingType
enumeration. Setting this value will enable all logging types, which can be useful
for comprehensive debugging and diagnostics.

On Windows:

.. code-block:: batch

   set GPA_OVERRIDE_LOG_LEVEL=65280

On Linux:

.. code-block:: bash

   export GPA_OVERRIDE_LOG_LEVEL=65280

**Notes**

- The value must be a valid numeric value from the ``GpaLoggingType``
  enumeration.
- GPA reads this variable when the logging callback is set.
- If the variable is not set, GPA uses the logging level requested by the
  application.
- If the value cannot be parsed or is outside the supported range, GPA ignores
  the override and continues using the application-requested logging level.
- This variable only affects GPA logging when a logging callback is registered.
