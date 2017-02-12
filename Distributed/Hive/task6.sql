add jar /opt/cloudera/parcels/CDH/jars/hive-contrib-1.1.0-cdh5.7.0.jar;

add file script.sh;

USE my_db;

select TRANSFORM(ip, date, url, pagesize, statuscode, browser)
using 'script.sh' FROM log
LIMIT 50;
