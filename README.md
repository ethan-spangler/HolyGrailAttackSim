# HolyGrailAttackSim

## About
A C++ simulation of the battle that takes place during the French castle scene of *Monty Python and the Holy Grail*. This project was assigned as homework in an Operating Systems course and has been broken down into three iterations. The first iteration establishes simple models, configuration, and logging. The second iteration adds the battle simulation across multiple child processes. The third iteration migrates from child processes into a properly multi-threaded simulation and includes remote logging over a network. Detailed information for each iteration, as well as setup information, can be found below:

---

## Iteration 1
The first iteration of the project establishes models for the French Castle and the attacking Knights, allows loading data into these models from text files, and enables logging messages to an external text file. The first iteration has no actual simulation code, but rather loads data for the Castle/Knights, logging this data as it enters, and logs any errors encountered.

### Castle
The Castle model class tracks the following information:
* Hit points (health) - *abbreviated hp in the setup file*
* Attack rate - *expressed in nanoseconds*
* Attack chances - *as a whole number of a percentage - __must sum to 100__*:
    * Taunt - weak attack against a single Knights
    * Cow - weak attack against all Knights
    * Rabbit - strong attack against a single Knight
* Damage for attack types:
    * Weak attack
    * Strong attack

The Castle setup file must follow the following format:
* hp: [100, 300]
* rate: [1, 100]
* taunt: [75, 89]
* cow: [10, 20]
* rabbit: [1, 5]
* weak: [1, 9]
* strong: [25, 50]

### Knight
The Knight model class tracks the following information:
* Name - *as a string*
* Hit points (health) - *also abbreviated hp in the setup file*
* Bravery - *when hp falls to or below bravery threshold, the Knight runs away*
    * __NOTE__: Bravery threshold must be less than starting hit points
* Attack rate - *expressed in nanoseconds*
* Damage per attack

The Knight setup file must follow the following format:
* count: [1, 5]
    * Represents how many Knight(s) to initialize
* name: <string of length [2, 50]>
* hp: [25, 50]
* bravery: [0, up to hp]
* rate: [10, 50]
* damage: [1, 9]

### Command Line Parameters
```
-c castlefilename *Required*: read set-up information for Castle from castlefilename
-k knightfilename *Optional*: read from the file knightfilename instead of the standard input: if missing, prompt/read Knight setup information from the keyboard.
-l logfilename    *Optional*: name of the log file: if missing or error with filename, use "log"
```

---

## Iteration 2
The second iteration expands upon the first by recreating the attack on the French castle by Arthur and his Knights of the Round Table using child processes to model the individual Knights, the Castle, and the Logger. The main parent process handles command-line arguments to set up the scenario, starts all child processes, receives/sends Knight/Castle state notifications, and waits for simulation completion.

The Castle and Knights each run in their own **two** processes: one for attacking and one for bookkeeping. The Castle attacking process writes attack messages to the Knight bookkeeping processes while the Knight attacking processes write to the Castle bookkeeping process. Attacking processes are responsible for attacks **only**; they do not update the state of the related Castle/Knight instance. For testing/visibility sake, attack rates are processed on millisecond scale rather than on nanosecond scale.

---

## Iteration 3
The third iteration functions similarly to the second iteration, but includes two major changes:
* The Castle and Knight instances have been moved from child processes to threads and now use thread-safe message queues to relay attack messages.
* A standalone log server is included and the simulation now connects to this server via socket to log messages remotely.

---