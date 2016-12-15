
# Function Requirement

- can send messages periodicly, each message can be modified, and there should be
  delay time between messages
  
- can receive and parse message, include CAN, LIN

- can send/receive diagnostic messages with request/response sequence

# Customer Requirement Review Notes

## Cases with messages send only

### periodic

	case 1
	case 2, need change data
	case 3, need change data
	case 4
	case 5
	case 6
	case 7

## Cases with messages receive only

	case 8, timeout = 1000ms
	case 9, timeout = 1000ms
	case 10, timeout = 1000ms
	case 11
	case 12
	case 13
	case 14

## Cases with both send and receive

	case 15
    case 16
    case 17

## Phy(y)/Raw(x) alg

Step        Raw->Phy               	Phy->Raw            PhyTargetValue  	RawTargetValue

18 			y = (1/10)x + 3 		x = (y - 3)*10      12                  90
?19         y = (7058/100000)x 		x = y*100000/7058
20 			y = x                   x = y               1                   1
21 			y = x - 40              x = y + 40          -40/25/80           0/65/120
22 			y = x - 40              x = y + 40          -40/25/80           0/65/120
23 			y = x - 40              x = y + 40          -40/25/80           0/65/120
24 			y = x - 40              x = y + 40          -40/25/80           0/65/120
25 			y = x - 40              x = y + 40          -40/25/80           0/65/120
26 			y = (100/255)x          x = y*255/100       30/85/95            76/216/242
27 			y = x - 40              x = y + 40          -40/25/80           0/65/120
28 			y = x - 40              x = y + 40          -40/25/80           0/65/120
29 			y = (1/10)x             x = y*10            15/50/70            150/500/700
30 			y = 10x             	x = y/10            20/100/700          2/10/70
31          y = (100/255)x          x = y*255/100       50                  127

32          y = (100/255)x          x = y*255/100       
33          y = (100/255)x          x = y*255/100 
34          y = x                   x = y               Active/Not Active
35          y = x                   x = y               Active/Not Active
36          y = x                   x = y               Active/Not Active
37          y = x%
38          y = x%


# TODO

## Items need to be clarified

- What's the app signal value for min temperature -40 ? [DONE]
A: application signal doesn't support negative value, translate in text label.

- step 16, 17 how to show current value?
- step 19, What's the target value? 9,12,16 seems wrong.
- step 27, value format?

## Items need to be clarified [DONE]

- case 3, left/right should change to backlight/indicator
- case 8, 9, 10 don't need bar to present the current and target value
- case 11, 2 can't share same button, since one is present send values, and other is received status

- case 15: How data presents in message?

- case 15-38: Does the hex value in column C should be used with both send and receive message?
A: NO. ID has defined in PIDs.

- case 15-38: What should we prepend to messages defined in last column? ID+DATA or ID+PID+...?
A: please reference to new document with full CAN data.

- case 26, 29, 30, 31: What's the target values? What's the duty value?
A: 31 duty is a fix value which 50%.


- case 32-38: need send periodic to update values, what's the value of cycle time? (15-31 need execute only once)
A: case 32-38, time delay between steps = 100ms.
case 15-31, time delay between steps < 50ms, between not have.
response timeout value is 100ms.

- What's the resolution should be use for graphic panel?

1366x768
