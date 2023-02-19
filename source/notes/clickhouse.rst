
==========
Clickhouse
==========


MergeTree
=========
* the main clickhouse engine
* non-blocking inserts/reads
* atomic (all or nothing) insert
* primary/secondary indexes
* partitionaning (e.g. per month), for faster ALTER
* slow insert (should insert in batches)
* background tasks on records with same PKs
* non-unique PKs


.. code-block:: sql

    CREATE TABLE mt (
        EventDate Date,
        OrderID Int32,
        BannerID UInt64,
        GoalNum Int8
    ) ENGINE = MergeTree()
    PARTITION BY toYYYYMM(EventDate) ORDER BY (OrderID, BannerID);

    INSERT INTO mt SELECT toDate('2018-09-26'),
        number, number + 10000, number % 128 from numbers(1000000);
    INSERT INTO mt SELECT toDate('2018-10-15'),
        number, number + 10000, number % 128 from numbers(1000000, 1000000);

    -- SELECT count(*) FROM mt;
    -- OPTIMIZE TABLE mt FINAL DEDUPLICATE;

.. code-block:: shell

    $ ls /var/lib/clickhouse/metadata/default/
    mt.sql

    $ ls /var/lib/clickhouse/data/default/mt  # mainly it's dirs with parts
    201809_2_2_0 201809_3_3_0 201810_1_1_0 201810_4_4_0 201810_1_4_1
    detached format_version.txt

Partitioning:

* For range queries data should be sorted by PK (here: ``(OrderID, BannerID)``)
* But data is being inserted sorted by time (``EventDate``)
* Solution: store data in parts (each sorted by PK)



