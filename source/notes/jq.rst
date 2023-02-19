
==
JQ
==
* `Bash for Loop Over JSON Array Using jq <https://www.starkandwayne.com/blog/bash-for-loop-over-json-array-using-jq/>`_


.. code-block:: sh

    sample='[{"name":"foo"},{"name":"bar"}]'
    for row in $(<<<"${sample}" jq -r '.[] | @base64'); do
         <<<"${row}" base64 --decode | jq -r '.name'
    done
