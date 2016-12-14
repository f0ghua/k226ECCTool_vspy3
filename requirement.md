
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


# TODO

## Items need to be clarified

- What's the app signal value for min temperature -40 ?


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
