add jar /opt/cloudera/parcels/CDH/jars/hive-contrib-1.1.0-cdh5.7.0.jar;
add jar /opt/cloudera/parcels/CDH/jars/hive-serde-1.1.0-cdh5.7.0.jar;

USE my_db;


select age from user_inf
inner join (select ip from
			(select ip, count(1) as cnt from log group by ip) as pair_ip_count,
			(select count(DISTINCT region) as c_r from ip_inform) as count_reg,
			(select count(ip) as c_i from log) as count_ip
			where pair_ip_count.cnt > count_reg.c_r / count_ip.c_i) as res
on user_inf.ip=res.ip
LIMIT 50;

--SELECT * FROM example LIMIT 5;
--SELECT * FROM ip_example LIMIT 5;
