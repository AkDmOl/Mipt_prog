add jar /opt/cloudera/parcels/CDH/jars/hive-contrib-1.1.0-cdh5.7.0.jar;
add jar /opt/cloudera/parcels/CDH/jars/hive-serde-1.1.0-cdh5.7.0.jar;
add jar ./motivator/jar/motivator.jar;

USE my_db;


create temporary function motivator as 'com.example.hive.udf.motivator'; 

select ip, motivator(age)
from user_inf
LIMIT 50;
