
===================
Amazon Web Services
===================

Sources:

* `Chalice <https://github.com/aws/chalice>`_
* `Chalice Docs <https://aws.github.io/chalice/main.html>`_


#####################
AWS Credentials Setup
#####################

Install AWS CLI and start configuring:

.. code-block:: bash

    pipx install awscli

    aws configure
    # AWS Access Key ID [None]:      <id>
    # AWS Secret Access Key [None]:  <key>
    # Default region name [None]:    eu-central-1
    # Default output format [None]:  text


Go to credentials menu:

#. `AWS Console`_
#. ``<Name> <Name>``
#. `My Security Credentials`_
#. ``Access keys``
    #. ``Create New Access Key``
    #. ``Show Access Key``
    #. Copy key ID and access key to configuration
#. ``Multi-factor authentication``

.. _`AWS Console`: https://console.aws.amazon.com
.. _`My Security Credentials`: https://console.aws.amazon.com/iam/home#security_credential


############################
Chalice Serverless Framework
############################

.. code-block:: bash

    # Bootstrap project
    chalice new-project helloworld
    # Deploy function and try it out
    chalice deploy
    curl https://qxea58oupc.execute-api.us-west-2.amazonaws.com/api/
    # Cleanup
    chalice delete


