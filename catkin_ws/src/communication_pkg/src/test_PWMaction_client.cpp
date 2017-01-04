
#include <communication_pkg/PWMAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<communication_pkg::PWMAction> Client;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "pwm_client");
	Client client("/arduino/pwm", true); // true -> don't need ros::spin()
	client.waitForServer();

	communication_pkg::PWMGoal goal;
	for (int i=0;i<12;i++){
		goal.pwm[i] = i;
	}
	client.sendGoal(goal);

	client.waitForResult(ros::Duration(5.0));
	if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		printf("Yay! The dishes are now clean");
	printf("Current State: %s\n", client.getState().toString().c_str());
	return 0;
}
