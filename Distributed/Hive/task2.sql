add jar /opt/cloudera/parcels/CDH/jars/hive-contrib-1.1.0-cdh5.7.0.jar;
add jar /opt/cloudera/parcels/CDH/jars/hive-serde-1.1.0-cdh5.7.0.jar;

USE my_db;

select browser, count(1) as cnt
from log
group by browser
order by cnt desc;

--SELECT * FROM example LIMIT 5;
--SELECT * FROM ip_example LIMIT 5;
