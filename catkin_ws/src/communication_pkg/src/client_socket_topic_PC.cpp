
#include <communication_pkg/PWMAction.h>
#include <actionlib/server/simple_action_server.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>


// Socket address
#define HOST "192.168.0.42"
#define PORT 8888

char pwm_values[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
int distance_U = 0;
int accel_X = 0;
int accel_Y = 0;
int accel_Z = 0;
int gyro_X = 0;
int gyro_Y = 0;
int gyro_Z = 0;

typedef actionlib::SimpleActionServer<communication_pkg::PWMAction> Server;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void execute(const communication_pkg::PWMGoalConstPtr& goal, Server* as)
{
	char aux[100];
	as->setSucceeded();
	
	//sprintf(aux,"goal 1:%d, goal 12:%d\n",(*goal).pwm[0],(*goal).pwm[11]);
	sprintf(aux,"/arduino/pwm service callback executed");
	write(1,aux,strlen(aux));
}

int main(int argc, char** argv)
{
	int s,n;
	struct sockaddr_in addr;
	char buff[256];

	ros::init(argc, argv, "socket_client_topic_server");
	printf("Initializing socket_client_topic_server\n");
	ros::NodeHandle h;


	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s==-1)
		perror("Creat socket:");
	else
		printf("Socket created\n");
	
    	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	inet_aton(HOST, &addr.sin_addr);

	if (connect(s,(struct sockaddr *) &addr,sizeof(addr))<0)
		perror("Error connecting socket:");
	else
		printf("Socket connected\n");


	Server server(h, "/arduino/pwm", boost::bind(&execute, _1, &server), false);
	server.start();
	printf("Action /arduino/pwm launched\n");
	

	// Main loop
	while(1){	
	// Ultrasound
		sprintf(buff,"100");
		write(s,buff,strlen(buff));
		//printf("writen %s in socket\n",buff);	

		memset(buff,0,strlen(buff));
		n = read(s,buff,255);
		distance_U = atoi(buff);
		if (n == 0)		printf("nothing read\n");
		else if (n<0)		perror("Read Error:");
		//else			
		printf("distance_U = %d\n",distance_U);

	// Accelerometer
		sprintf(buff,"101");		write(s,buff,strlen(buff));
		memset(buff,0,strlen(buff));
		n = read(s,buff,255);		accel_X = atoi(buff);
		printf("accel_X = %d\n",accel_X);

		sprintf(buff,"102");		write(s,buff,strlen(buff));
		memset(buff,0,strlen(buff));
		n = read(s,buff,255);		accel_Y = atoi(buff);
		printf("accel_Y = %d\n",accel_Y);

		sprintf(buff,"103");		write(s,buff,strlen(buff));
		memset(buff,0,strlen(buff));
		n = read(s,buff,255);		accel_Z = atoi(buff);
		printf("accel_Z = %d\n",accel_Z);

	// Gyroscope
		sprintf(buff,"104");		write(s,buff,strlen(buff));
		memset(buff,0,strlen(buff));
		n = read(s,buff,255);		gyro_X = atoi(buff);
		printf("gyro_X = %d\n",gyro_X);

		sprintf(buff,"105");		write(s,buff,strlen(buff));
		memset(buff,0,strlen(buff));
		n = read(s,buff,255);		gyro_Y = atoi(buff);
		printf("gyro_Y = %d\n",gyro_Y);

		sprintf(buff,"106");		write(s,buff,strlen(buff));
		memset(buff,0,strlen(buff));
		n = read(s,buff,255);		gyro_Z = atoi(buff);
		printf("gyro_Z = %d\n",gyro_Z);

	// PWM
		/*for (int i=0;i<12;i++){
			std::stringstream stream;	
			stream << i;
			write(s,stream.str(),stream.gcount());	//send the value of 'i'
			memset(buff,0,strlen(buff));	read(s,buff,255);	memset(buff,0,strlen(buff));	//wait for acknowledge
			stream << pwm_values[i]
			write(s,stream.str(),stream.gcount());	//send pwm of servo 'i'
			printf("pwm_value[%d] = %d\n",i,pwm_values[i]);
		}*/

		printf("Values sent\n");

		ros::spinOnce();
		ros::Duration(2).sleep();
	}
	return 0;
}
