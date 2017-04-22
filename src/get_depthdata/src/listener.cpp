#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h" 
#include <deque>

#define MAX_ITER 400
#define MAX_COL 480
#define MAX_ROW 360
#define BOT_COL_BOUND 235
#define TOP_COL_BOUND 245
#define BOT_ROW_BOUND 175
#define TOP_ROW_BOUND 185

static uint16_t scandata[MAX_ROW][MAX_COL];
static uint16_t iter_counter = 0;

void chatterCallback(const sensor_msgs::Image::ConstPtr& msg)
{

    uint16_t *scanpointer;
    scanpointer = (uint16_t*)&(msg->data[0]);
	
    //put data in scandata

    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            if((*scanpointer) != 0) {
                scandata[i][j] = *scanpointer;
            }
            scanpointer++;

        }

    }
    iter_counter++;

    //once data has started to saturate, carve out 10x10 in middle
    if(iter_counter > MAX_ITER){
	iter_counter = 0;
	std::deque<int> dq; 

	//create 1D data structure, eliminating zeroes

	for (int i = BOT_ROW_BOUND; i < TOP_ROW_BOUND; i++) {
        	for (int j = BOT_COL_BOUND; j < TOP_COL_BOUND; j++) {
	            std::cout <<  scandata[i][j] << " ";
		    if (scandata[i][j] != 0) {
			dq.push_back(scandata[i][j]);
		    }
		}
	std::cout << std::endl;
	}	
	
	std::cout << "Queue size = " << dq.size() << std::endl;
	
	//sort dequeue
	std::cout << "Sorting queue" << std::endl;
	std::sort ( dq.begin(), dq.end() );	
	

	//remove 5 from top, 5 from bottom
	if (dq.size() > 20) {	//big enough where shaving 10 off won't ruin data set
		std::cout << "Trimming queue" << std::endl;
		int wcount = 0;
		while (wcount < 5) {
			dq.pop_front();
			dq.pop_back();
			wcount++;
		}
	}

	//average the depths
	int sum = 0;
	int avg = 0;
	int size = dq.size();
	while (!dq.empty()) {
		sum += dq.back();
		dq.pop_back();
	}
	
	avg = sum/size;

	std::cout << "Total sum: " << sum << " " << "Size: " << size << " " << "Avg: " << avg << std::endl;		

	//clean the scandata, and dq
	memset(scandata, 0, sizeof(scandata[0][0]) * MAX_COL * MAX_ROW);

	//check if bigend, or lilend

	//todo
	//make it so program lets you call for a reading to be done
    }
}

int main(int argc, char **argv)
{

  //init scandata ....


  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/camera/depth/image_raw", 1000, chatterCallback);

  ros::spin();

  return 0;
}
