add jar /opt/cloudera/parcels/CDH/jars/hive-contrib-1.1.0-cdh5.7.0.jar;
add jar /opt/cloudera/parcels/CDH/jars/hive-serde-1.1.0-cdh5.7.0.jar;

USE my_db;

select statuscode, sex, count(1) as cnt
from ( select log.statuscode, user_inf.sex
	from log inner join user_inf 
	on log.ip = user_inf.ip ) as param
group by param.statuscode, param.sex
LIMIT 50;

